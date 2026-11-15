/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Common defines for the SPI_FLASH (SFUD) demo.
  ******************************************************************************
  * Ported from STM32G474CBT6\SDK\SPI_FLASH to the U0C_LITE board.
  *   SPI2 : PB13 SCK / PB14 MISO / PB15 MOSI (AF5), CS = PB12 (software)
  *   LED  : single blue LED on PA0
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
#include "stm32u5xx_hal.h"

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
/* Status LEDs: U0C_LITE only has one blue LED on PA0.
   LED_OK is the heartbeat on success, LED_ERR blinks (fast) on failure. */
#define LED_OK_Pin          GPIO_PIN_0
#define LED_OK_GPIO_Port    GPIOA
#define LED_ERR_Pin         GPIO_PIN_0
#define LED_ERR_GPIO_Port   GPIOA

/* SPI2 chip select (software controlled) */
#define SPI2_CS_Pin         GPIO_PIN_12
#define SPI2_CS_GPIO_Port   GPIOB

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
