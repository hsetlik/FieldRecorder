/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32h7xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{

  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
  * @brief I2C MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hi2c->Instance==I2C1)
  {
    /* USER CODE BEGIN I2C1_MspInit 0 */

    /* USER CODE END I2C1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
    PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C1235CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = ADC_SCL_Pin|ADC_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
    /* USER CODE BEGIN I2C1_MspInit 1 */

    /* USER CODE END I2C1_MspInit 1 */

  }

}

/**
  * @brief I2C MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C1)
  {
    /* USER CODE BEGIN I2C1_MspDeInit 0 */

    /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(ADC_SCL_GPIO_Port, ADC_SCL_Pin);

    HAL_GPIO_DeInit(ADC_SDA_GPIO_Port, ADC_SDA_Pin);

    /* USER CODE BEGIN I2C1_MspDeInit 1 */

    /* USER CODE END I2C1_MspDeInit 1 */
  }

}

/**
  * @brief OSPI MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hospi: OSPI handle pointer
  * @retval None
  */
void HAL_OSPI_MspInit(OSPI_HandleTypeDef* hospi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hospi->Instance==OCTOSPI2)
  {
    /* USER CODE BEGIN OCTOSPI2_MspInit 0 */

    /* USER CODE END OCTOSPI2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
    PeriphClkInitStruct.OspiClockSelection = RCC_OSPICLKSOURCE_D1HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_OCTOSPIM_CLK_ENABLE();
    __HAL_RCC_OSPI2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**OCTOSPI2 GPIO Configuration
    PA1     ------> OCTOSPIM_P1_DQS
    PA7     ------> OCTOSPIM_P1_IO2
    PB2     ------> OCTOSPIM_P1_CLK
    PE7     ------> OCTOSPIM_P1_IO4
    PE8     ------> OCTOSPIM_P1_IO5
    PE9     ------> OCTOSPIM_P1_IO6
    PE10     ------> OCTOSPIM_P1_IO7
    PE11     ------> OCTOSPIM_P1_NCS
    PD11     ------> OCTOSPIM_P1_IO0
    PD12     ------> OCTOSPIM_P1_IO1
    PD13     ------> OCTOSPIM_P1_IO3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPIM_P1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USER CODE BEGIN OCTOSPI2_MspInit 1 */

    /* USER CODE END OCTOSPI2_MspInit 1 */

  }

}

/**
  * @brief OSPI MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hospi: OSPI handle pointer
  * @retval None
  */
void HAL_OSPI_MspDeInit(OSPI_HandleTypeDef* hospi)
{
  if(hospi->Instance==OCTOSPI2)
  {
    /* USER CODE BEGIN OCTOSPI2_MspDeInit 0 */

    /* USER CODE END OCTOSPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_OCTOSPIM_CLK_DISABLE();
    __HAL_RCC_OSPI2_CLK_DISABLE();

    /**OCTOSPI2 GPIO Configuration
    PA1     ------> OCTOSPIM_P1_DQS
    PA7     ------> OCTOSPIM_P1_IO2
    PB2     ------> OCTOSPIM_P1_CLK
    PE7     ------> OCTOSPIM_P1_IO4
    PE8     ------> OCTOSPIM_P1_IO5
    PE9     ------> OCTOSPIM_P1_IO6
    PE10     ------> OCTOSPIM_P1_IO7
    PE11     ------> OCTOSPIM_P1_NCS
    PD11     ------> OCTOSPIM_P1_IO0
    PD12     ------> OCTOSPIM_P1_IO1
    PD13     ------> OCTOSPIM_P1_IO3
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1|GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);

    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13);

    /* USER CODE BEGIN OCTOSPI2_MspDeInit 1 */

    /* USER CODE END OCTOSPI2_MspDeInit 1 */
  }

}

/**
  * @brief SD MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hsd: SD handle pointer
  * @retval None
  */
void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hsd->Instance==SDMMC2)
  {
    /* USER CODE BEGIN SDMMC2_MspInit 0 */

    /* USER CODE END SDMMC2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDMMC;
    PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_SDMMC2_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**SDMMC2 GPIO Configuration
    PD6     ------> SDMMC2_CK
    PD7     ------> SDMMC2_CMD
    PG9     ------> SDMMC2_D0
    PG10     ------> SDMMC2_D1
    PG11     ------> SDMMC2_D2
    PG12     ------> SDMMC2_D3
    */
    GPIO_InitStruct.Pin = SD_CK_Pin|SD_CMD_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_SDMMC2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SD_D0_Pin|SD_D1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF11_SDMMC2;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = SD_D2_Pin|SD_D3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_SDMMC2;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* USER CODE BEGIN SDMMC2_MspInit 1 */

    /* USER CODE END SDMMC2_MspInit 1 */

  }

}

/**
  * @brief SD MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hsd: SD handle pointer
  * @retval None
  */
void HAL_SD_MspDeInit(SD_HandleTypeDef* hsd)
{
  if(hsd->Instance==SDMMC2)
  {
    /* USER CODE BEGIN SDMMC2_MspDeInit 0 */

    /* USER CODE END SDMMC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDMMC2_CLK_DISABLE();

    /**SDMMC2 GPIO Configuration
    PD6     ------> SDMMC2_CK
    PD7     ------> SDMMC2_CMD
    PG9     ------> SDMMC2_D0
    PG10     ------> SDMMC2_D1
    PG11     ------> SDMMC2_D2
    PG12     ------> SDMMC2_D3
    */
    HAL_GPIO_DeInit(GPIOD, SD_CK_Pin|SD_CMD_Pin);

    HAL_GPIO_DeInit(GPIOG, SD_D0_Pin|SD_D1_Pin|SD_D2_Pin|SD_D3_Pin);

    /* USER CODE BEGIN SDMMC2_MspDeInit 1 */

    /* USER CODE END SDMMC2_MspDeInit 1 */
  }

}

/**
  * @brief UART MSP Initialization
  * This function configures the hardware resources used in this example
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(huart->Instance==UART5)
  {
    /* USER CODE BEGIN UART5_MspInit 0 */

    /* USER CODE END UART5_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART5;
    PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_UART5_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**UART5 GPIO Configuration
    PC12     ------> UART5_TX
    PD2     ------> UART5_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USER CODE BEGIN UART5_MspInit 1 */

    /* USER CODE END UART5_MspInit 1 */

  }

}

/**
  * @brief UART MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==UART5)
  {
    /* USER CODE BEGIN UART5_MspDeInit 0 */

    /* USER CODE END UART5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART5_CLK_DISABLE();

    /**UART5 GPIO Configuration
    PC12     ------> UART5_TX
    PD2     ------> UART5_RX
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

    /* USER CODE BEGIN UART5_MspDeInit 1 */

    /* USER CODE END UART5_MspDeInit 1 */
  }

}

/**
  * @brief PCD MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hpcd: PCD handle pointer
  * @retval None
  */
void HAL_PCD_MspInit(PCD_HandleTypeDef* hpcd)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hpcd->Instance==USB_OTG_HS)
  {
    /* USER CODE BEGIN USB_OTG_HS_PCD_MspInit 0 */

    /* USER CODE END USB_OTG_HS_PCD_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

  /** Enable USB Voltage detector
  */
    HAL_PWREx_EnableUSBVoltageDetector();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USB_OTG_HS GPIO Configuration
    PC0     ------> USB_OTG_HS_ULPI_STP
    PC2_C     ------> USB_OTG_HS_ULPI_DIR
    PC3_C     ------> USB_OTG_HS_ULPI_NXT
    PA3     ------> USB_OTG_HS_ULPI_D0
    PA5     ------> USB_OTG_HS_ULPI_CK
    PB0     ------> USB_OTG_HS_ULPI_D1
    PB1     ------> USB_OTG_HS_ULPI_D2
    PB10     ------> USB_OTG_HS_ULPI_D3
    PB11     ------> USB_OTG_HS_ULPI_D4
    PB12     ------> USB_OTG_HS_ULPI_D5
    PB13     ------> USB_OTG_HS_ULPI_D6
    PB5     ------> USB_OTG_HS_ULPI_D7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG1_HS;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG1_HS;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG1_HS;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
    __HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE();
    /* USER CODE BEGIN USB_OTG_HS_PCD_MspInit 1 */

    /* USER CODE END USB_OTG_HS_PCD_MspInit 1 */

  }

}

/**
  * @brief PCD MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hpcd: PCD handle pointer
  * @retval None
  */
void HAL_PCD_MspDeInit(PCD_HandleTypeDef* hpcd)
{
  if(hpcd->Instance==USB_OTG_HS)
  {
    /* USER CODE BEGIN USB_OTG_HS_PCD_MspDeInit 0 */

    /* USER CODE END USB_OTG_HS_PCD_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USB_OTG_HS_CLK_DISABLE();
    __HAL_RCC_USB_OTG_HS_ULPI_CLK_DISABLE();

    /**USB_OTG_HS GPIO Configuration
    PC0     ------> USB_OTG_HS_ULPI_STP
    PC2_C     ------> USB_OTG_HS_ULPI_DIR
    PC3_C     ------> USB_OTG_HS_ULPI_NXT
    PA3     ------> USB_OTG_HS_ULPI_D0
    PA5     ------> USB_OTG_HS_ULPI_CK
    PB0     ------> USB_OTG_HS_ULPI_D1
    PB1     ------> USB_OTG_HS_ULPI_D2
    PB10     ------> USB_OTG_HS_ULPI_D3
    PB11     ------> USB_OTG_HS_ULPI_D4
    PB12     ------> USB_OTG_HS_ULPI_D5
    PB13     ------> USB_OTG_HS_ULPI_D6
    PB5     ------> USB_OTG_HS_ULPI_D7
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3|GPIO_PIN_5);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_5);

    /* USER CODE BEGIN USB_OTG_HS_PCD_MspDeInit 1 */

    /* USER CODE END USB_OTG_HS_PCD_MspDeInit 1 */
  }

}

extern DMA_HandleTypeDef hdma_sai1_a;

static uint32_t SAI1_client =0;

void HAL_SAI_MspInit(SAI_HandleTypeDef* hsai)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
/* SAI1 */
    if(hsai->Instance==SAI1_Block_A)
    {
    /* Peripheral clock enable */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SAI1;
    PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    if (SAI1_client == 0)
    {
       __HAL_RCC_SAI1_CLK_ENABLE();
    }
    SAI1_client ++;

    /**SAI1_A_Block_A GPIO Configuration
    PE4     ------> SAI1_FS_A
    PE5     ------> SAI1_SCK_A
    PE6     ------> SAI1_SD_A
    */
    GPIO_InitStruct.Pin = ADC_LRCK_Pin|ADC_BCK_Pin|ADC_DATA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

      /* Peripheral DMA init*/

    hdma_sai1_a.Instance = DMA1_Stream0;
    hdma_sai1_a.Init.Request = DMA_REQUEST_SAI1_A;
    hdma_sai1_a.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_sai1_a.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sai1_a.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sai1_a.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sai1_a.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sai1_a.Init.Mode = DMA_CIRCULAR;
    hdma_sai1_a.Init.Priority = DMA_PRIORITY_LOW;
    hdma_sai1_a.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_sai1_a) != HAL_OK)
    {
      Error_Handler();
    }

    /* Several peripheral DMA handle pointers point to the same DMA handle.
     Be aware that there is only one channel to perform all the requested DMAs. */
    __HAL_LINKDMA(hsai,hdmarx,hdma_sai1_a);

    __HAL_LINKDMA(hsai,hdmatx,hdma_sai1_a);

    }
}

void HAL_SAI_MspDeInit(SAI_HandleTypeDef* hsai)
{
/* SAI1 */
    if(hsai->Instance==SAI1_Block_A)
    {
    SAI1_client --;
    if (SAI1_client == 0)
      {
      /* Peripheral clock disable */
       __HAL_RCC_SAI1_CLK_DISABLE();
      }

    /**SAI1_A_Block_A GPIO Configuration
    PE4     ------> SAI1_FS_A
    PE5     ------> SAI1_SCK_A
    PE6     ------> SAI1_SD_A
    */
    HAL_GPIO_DeInit(GPIOE, ADC_LRCK_Pin|ADC_BCK_Pin|ADC_DATA_Pin);

    /* SAI1 DMA Deinit */
    HAL_DMA_DeInit(hsai->hdmarx);
    HAL_DMA_DeInit(hsai->hdmatx);
    }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
