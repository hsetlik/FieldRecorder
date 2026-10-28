/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC_LRCK_Pin GPIO_PIN_4
#define ADC_LRCK_GPIO_Port GPIOE
#define ADC_BCK_Pin GPIO_PIN_5
#define ADC_BCK_GPIO_Port GPIOE
#define ADC_DATA_Pin GPIO_PIN_6
#define ADC_DATA_GPIO_Port GPIOE
#define OCTOSPI_RST_Pin GPIO_PIN_12
#define OCTOSPI_RST_GPIO_Port GPIOE
#define UI_NRST_Pin GPIO_PIN_3
#define UI_NRST_GPIO_Port GPIOD
#define UI_BOOT0_Pin GPIO_PIN_4
#define UI_BOOT0_GPIO_Port GPIOD
#define SD_CK_Pin GPIO_PIN_6
#define SD_CK_GPIO_Port GPIOD
#define SD_CMD_Pin GPIO_PIN_7
#define SD_CMD_GPIO_Port GPIOD
#define SD_D0_Pin GPIO_PIN_9
#define SD_D0_GPIO_Port GPIOG
#define SD_D1_Pin GPIO_PIN_10
#define SD_D1_GPIO_Port GPIOG
#define SD_D2_Pin GPIO_PIN_11
#define SD_D2_GPIO_Port GPIOG
#define SD_D3_Pin GPIO_PIN_12
#define SD_D3_GPIO_Port GPIOG
#define ADC_SCL_Pin GPIO_PIN_6
#define ADC_SCL_GPIO_Port GPIOB
#define ADC_SDA_Pin GPIO_PIN_7
#define ADC_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
