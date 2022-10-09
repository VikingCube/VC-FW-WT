/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
void adsr_note_on(uint32_t ch, uint8_t note, uint8_t vel);
void adsr_note_off(uint32_t ch, uint8_t note);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOE
#define LED3_Pin GPIO_PIN_3
#define LED3_GPIO_Port GPIOE
#define LED4_Pin GPIO_PIN_4
#define LED4_GPIO_Port GPIOE
#define LED5_Pin GPIO_PIN_5
#define LED5_GPIO_Port GPIOE
#define LED6_Pin GPIO_PIN_6
#define LED6_GPIO_Port GPIOE
#define DAC_CS_Pin GPIO_PIN_14
#define DAC_CS_GPIO_Port GPIOC
#define DAC_AB_Pin GPIO_PIN_15
#define DAC_AB_GPIO_Port GPIOC
#define AIN8_Pin GPIO_PIN_0
#define AIN8_GPIO_Port GPIOC
#define AIN9_Pin GPIO_PIN_1
#define AIN9_GPIO_Port GPIOC
#define AIN10_Pin GPIO_PIN_2
#define AIN10_GPIO_Port GPIOC
#define AIN11_Pin GPIO_PIN_3
#define AIN11_GPIO_Port GPIOC
#define AIN0_Pin GPIO_PIN_0
#define AIN0_GPIO_Port GPIOA
#define AIN1_Pin GPIO_PIN_1
#define AIN1_GPIO_Port GPIOA
#define AIN2_Pin GPIO_PIN_2
#define AIN2_GPIO_Port GPIOA
#define AIN3_Pin GPIO_PIN_3
#define AIN3_GPIO_Port GPIOA
#define AIN4_Pin GPIO_PIN_6
#define AIN4_GPIO_Port GPIOA
#define AIN5_Pin GPIO_PIN_7
#define AIN5_GPIO_Port GPIOA
#define AIN6_Pin GPIO_PIN_4
#define AIN6_GPIO_Port GPIOC
#define AIN7_Pin GPIO_PIN_5
#define AIN7_GPIO_Port GPIOC
#define LED7_Pin GPIO_PIN_7
#define LED7_GPIO_Port GPIOE
#define LED8_Pin GPIO_PIN_8
#define LED8_GPIO_Port GPIOE
#define LED9_Pin GPIO_PIN_9
#define LED9_GPIO_Port GPIOE
#define LED10_Pin GPIO_PIN_10
#define LED10_GPIO_Port GPIOE
#define LED11_Pin GPIO_PIN_11
#define LED11_GPIO_Port GPIOE
#define LED12_Pin GPIO_PIN_12
#define LED12_GPIO_Port GPIOE
#define LED13_Pin GPIO_PIN_13
#define LED13_GPIO_Port GPIOE
#define LED14_Pin GPIO_PIN_14
#define LED14_GPIO_Port GPIOE
#define LED15_Pin GPIO_PIN_15
#define LED15_GPIO_Port GPIOE
#define LED16_Pin GPIO_PIN_14
#define LED16_GPIO_Port GPIOB
#define LED17_Pin GPIO_PIN_15
#define LED17_GPIO_Port GPIOB
#define BTN4_Pin GPIO_PIN_6
#define BTN4_GPIO_Port GPIOC
#define BTN5_Pin GPIO_PIN_7
#define BTN5_GPIO_Port GPIOC
#define BTN0_Pin GPIO_PIN_8
#define BTN0_GPIO_Port GPIOC
#define BTN1_Pin GPIO_PIN_9
#define BTN1_GPIO_Port GPIOC
#define VBUS_FS_Pin GPIO_PIN_9
#define VBUS_FS_GPIO_Port GPIOA
#define OTG_FS_ID_Pin GPIO_PIN_10
#define OTG_FS_ID_GPIO_Port GPIOA
#define OTG_FS_DM_Pin GPIO_PIN_11
#define OTG_FS_DM_GPIO_Port GPIOA
#define OTG_FS_DP_Pin GPIO_PIN_12
#define OTG_FS_DP_GPIO_Port GPIOA
#define BTN2_Pin GPIO_PIN_10
#define BTN2_GPIO_Port GPIOC
#define BTN3_Pin GPIO_PIN_11
#define BTN3_GPIO_Port GPIOC
#define DAC_D0_Pin GPIO_PIN_0
#define DAC_D0_GPIO_Port GPIOD
#define DAC_D1_Pin GPIO_PIN_1
#define DAC_D1_GPIO_Port GPIOD
#define DAC_D2_Pin GPIO_PIN_2
#define DAC_D2_GPIO_Port GPIOD
#define DAC_D3_Pin GPIO_PIN_3
#define DAC_D3_GPIO_Port GPIOD
#define DAC_D4_Pin GPIO_PIN_4
#define DAC_D4_GPIO_Port GPIOD
#define DAC_D5_Pin GPIO_PIN_5
#define DAC_D5_GPIO_Port GPIOD
#define DAC_D6_Pin GPIO_PIN_6
#define DAC_D6_GPIO_Port GPIOD
#define DAC_D7_Pin GPIO_PIN_7
#define DAC_D7_GPIO_Port GPIOD
#define LED0_Pin GPIO_PIN_0
#define LED0_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */
#define DAC_DATA_GPIO GPIOD
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
