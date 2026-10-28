/**
  * APS12808L 128 Mbit octal DDR PSRAM on OCTOSPI1.
  * Adapted from ST's APS6408 component driver (same AP Memory OPI family).
  */
#ifndef PSRAM_H
#define PSRAM_H

#include "main.h"

#define PSRAM_BASE_ADDR     0x90000000U
#define PSRAM_SIZE          0x01000000U  /* 16 MB */

#define PSRAM_OK            0
#define PSRAM_ERR_RESET     -1
#define PSRAM_ERR_CONFIG    -2
#define PSRAM_ERR_ID        -3
#define PSRAM_ERR_MMAP      -4

/* Resets and configures the PSRAM, then enables memory-mapped mode at PSRAM_BASE_ADDR */
int PSRAM_Init(OSPI_HandleTypeDef *hospi);

/* Fills and verifies the full array; returns the number of mismatched 32-bit words */
uint32_t PSRAM_Test(void);

#endif /* PSRAM_H */
