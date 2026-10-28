/**
  * APS12808L 128 Mbit octal DDR PSRAM on OCTOSPI1.
  * Adapted from ST's APS6408 component driver (same AP Memory OPI family).
  */
#include "psram.h"

/* Commands */
#define CMD_READ_LINEAR_BURST   0x20U
#define CMD_WRITE_LINEAR_BURST  0xA0U
#define CMD_READ_REG            0x40U
#define CMD_WRITE_REG           0xC0U
#define CMD_GLOBAL_RESET        0xFFU

/* Mode registers */
#define MR0                     0x00U
#define MR1                     0x01U
#define MR2                     0x02U
#define MR4                     0x04U

#define MR0_DS_HALF             0x01U  /* 50 ohm drive */
#define MR0_RLC_5               0x08U  /* read latency code 5, valid up to 133 MHz */
#define MR0_LT_FIXED            0x20U  /* fixed latency: OCTOSPI can't track variable latency */
#define MR4_WLC_5               0x40U  /* write latency 5, valid up to 133 MHz */

#define MR1_VENDOR_MASK         0x1FU
#define MR1_VENDOR_APM          0x0DU
#define MR2_DENSITY_MASK        0x07U
#define MR2_DENSITY_128MB       0x05U

/* Fixed latency doubles the read latency; write latency is never doubled.
 * The device counts the last address cycle as a latency cycle, hence the -1. */
#define READ_LATENCY            (5U * 2U)
#define WRITE_LATENCY           5U
#define REG_READ_LATENCY        5U
#define READ_DUMMY_CYCLES       (READ_LATENCY - 1U)
#define WRITE_DUMMY_CYCLES      (WRITE_LATENCY - 1U)
#define REG_READ_DUMMY_CYCLES   (REG_READ_LATENCY - 1U)

/* Octal command template: 8-line STR instruction, 32-bit DTR address, DTR data */
static void octal_cmd(OSPI_RegularCmdTypeDef *cmd, uint32_t instruction)
{
  cmd->OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
  cmd->FlashId            = HAL_OSPI_FLASH_ID_1;
  cmd->Instruction        = instruction;
  cmd->InstructionMode    = HAL_OSPI_INSTRUCTION_8_LINES;
  cmd->InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
  cmd->InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
  cmd->Address            = 0;
  cmd->AddressMode        = HAL_OSPI_ADDRESS_8_LINES;
  cmd->AddressSize        = HAL_OSPI_ADDRESS_32_BITS;
  cmd->AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_ENABLE;
  cmd->AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
  cmd->DataMode           = HAL_OSPI_DATA_8_LINES;
  cmd->DataDtrMode        = HAL_OSPI_DATA_DTR_ENABLE;
  cmd->NbData             = 0;
  cmd->DummyCycles        = 0;
  cmd->DQSMode            = HAL_OSPI_DQS_DISABLE;
  cmd->SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;
}

static HAL_StatusTypeDef psram_reset(OSPI_HandleTypeDef *hospi)
{
  OSPI_RegularCmdTypeDef cmd = {0};

  octal_cmd(&cmd, CMD_GLOBAL_RESET);
  cmd.AddressSize    = HAL_OSPI_ADDRESS_24_BITS;
  cmd.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
  cmd.DataMode       = HAL_OSPI_DATA_NONE;
  cmd.DataDtrMode    = HAL_OSPI_DATA_DTR_DISABLE;

  if (HAL_OSPI_Command(hospi, &cmd, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* tRST */
  HAL_Delay(1);
  return HAL_OK;
}

static HAL_StatusTypeDef psram_write_reg(OSPI_HandleTypeDef *hospi, uint32_t reg, uint8_t value)
{
  OSPI_RegularCmdTypeDef cmd = {0};
  /* DTR moves 2 bytes per clock; the device latches the first */
  uint8_t buf[2] = {value, value};

  octal_cmd(&cmd, CMD_WRITE_REG);
  cmd.Address = reg;
  cmd.NbData  = 2;

  if (HAL_OSPI_Command(hospi, &cmd, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }
  return HAL_OSPI_Transmit(hospi, buf, HAL_OSPI_TIMEOUT_DEFAULT_VALUE);
}

static HAL_StatusTypeDef psram_read_reg(OSPI_HandleTypeDef *hospi, uint32_t reg, uint8_t *value)
{
  OSPI_RegularCmdTypeDef cmd = {0};
  uint8_t buf[2];

  octal_cmd(&cmd, CMD_READ_REG);
  cmd.Address     = reg;
  cmd.NbData      = 2;
  cmd.DummyCycles = REG_READ_DUMMY_CYCLES;
  cmd.DQSMode     = HAL_OSPI_DQS_ENABLE;

  if (HAL_OSPI_Command(hospi, &cmd, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }
  if (HAL_OSPI_Receive(hospi, buf, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }
  *value = buf[0];
  return HAL_OK;
}

static HAL_StatusTypeDef psram_memory_mapped(OSPI_HandleTypeDef *hospi)
{
  OSPI_RegularCmdTypeDef cmd = {0};
  OSPI_MemoryMappedTypeDef mmap = {0};

  /* DQS must be enabled on writes: in AP Memory mode it drives the data mask */
  octal_cmd(&cmd, CMD_WRITE_LINEAR_BURST);
  cmd.OperationType = HAL_OSPI_OPTYPE_WRITE_CFG;
  cmd.DummyCycles   = WRITE_DUMMY_CYCLES;
  cmd.DQSMode       = HAL_OSPI_DQS_ENABLE;
  if (HAL_OSPI_Command(hospi, &cmd, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  cmd.OperationType = HAL_OSPI_OPTYPE_READ_CFG;
  cmd.Instruction   = CMD_READ_LINEAR_BURST;
  cmd.DummyCycles   = READ_DUMMY_CYCLES;
  if (HAL_OSPI_Command(hospi, &cmd, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* tCEM is enforced by Init.Refresh, so no timeout counter is needed */
  mmap.TimeOutActivation = HAL_OSPI_TIMEOUT_COUNTER_DISABLE;
  return HAL_OSPI_MemoryMapped(hospi, &mmap);
}

int PSRAM_Init(OSPI_HandleTypeDef *hospi)
{
  uint8_t mr0;
  uint8_t mr1;
  uint8_t mr2;

  if (psram_reset(hospi) != HAL_OK)
  {
    return PSRAM_ERR_RESET;
  }

  if (psram_write_reg(hospi, MR0, MR0_LT_FIXED | MR0_RLC_5 | MR0_DS_HALF) != HAL_OK ||
      psram_write_reg(hospi, MR4, MR4_WLC_5) != HAL_OK)
  {
    return PSRAM_ERR_CONFIG;
  }

  /* Read back MR0 and the ID registers to confirm the bus works in both directions */
  if (psram_read_reg(hospi, MR0, &mr0) != HAL_OK ||
      psram_read_reg(hospi, MR1, &mr1) != HAL_OK ||
      psram_read_reg(hospi, MR2, &mr2) != HAL_OK)
  {
    return PSRAM_ERR_ID;
  }
  if ((mr0 & 0x3FU) != (MR0_LT_FIXED | MR0_RLC_5 | MR0_DS_HALF) ||
      (mr1 & MR1_VENDOR_MASK) != MR1_VENDOR_APM ||
      (mr2 & MR2_DENSITY_MASK) != MR2_DENSITY_128MB)
  {
    return PSRAM_ERR_ID;
  }

  if (psram_memory_mapped(hospi) != HAL_OK)
  {
    return PSRAM_ERR_MMAP;
  }
  return PSRAM_OK;
}

uint32_t PSRAM_Test(void)
{
  volatile uint32_t *mem = (volatile uint32_t *)PSRAM_BASE_ADDR;
  const uint32_t words = PSRAM_SIZE / 4U;
  uint32_t errors = 0;

  /* Address-dependent pattern catches stuck, swapped and aliased address lines */
  for (uint32_t i = 0; i < words; i++)
  {
    mem[i] = i ^ 0xA5A5A5A5U;
  }

  /* Push everything out to the PSRAM and drop cached copies so reads hit the bus */
  SCB_CleanInvalidateDCache();

  for (uint32_t i = 0; i < words; i++)
  {
    if (mem[i] != (i ^ 0xA5A5A5A5U))
    {
      errors++;
    }
  }
  return errors;
}
