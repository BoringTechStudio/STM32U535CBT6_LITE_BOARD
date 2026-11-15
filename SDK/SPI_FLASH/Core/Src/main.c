/**
  ******************************************************************************
  * @file    main.c
  * @brief   SPI flash (W25Q) read/write demo using the SFUD driver.
  *
  *          Ported from STM32G474CBT6\SDK\SPI_FLASH.
  *          U0C_LITE board: SPI2 on PB13/PB14/PB15 (AF5), CS on PB12,
  *          USART1 on PA9/PA10, single blue LED on PA0.
  *          Clock: MSI 48 MHz (MSI 48 MHz).
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "spi.h"
#include "usart.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sfud.h>

/* Private variables ---------------------------------------------------------*/
static uint8_t rx1_buf;

/* Private functions ---------------------------------------------------------*/
void SystemClock_Config(void);

/* printf retarget (MicroLIB) */
int fputc(int ch, FILE *f)
{
  (void)f;
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    HAL_UART_Receive_IT(&huart1, &rx1_buf, 1);
  }
}

#define SFUD_DEMO_TEST_BUFFER_SIZE  1024
static uint8_t sfud_demo_test_buf[SFUD_DEMO_TEST_BUFFER_SIZE];

/**
  * @brief  Erase / write / read / verify a block of the serial flash.
  * @retval 0 on success, 1 on failure
  */
static int sfud_demo(uint32_t addr, size_t size, uint8_t *data)
{
  sfud_err result = SFUD_SUCCESS;
  const sfud_flash *flash = sfud_get_device(SFUD_W25_DEVICE_INDEX);
  size_t i;

  for (i = 0; i < size; i++)
  {
    data[i] = (uint8_t)i;
  }

  result = sfud_erase(flash, addr, size);
  if (result != SFUD_SUCCESS)
  {
    printf("Erase the %s flash data failed.\r\n", flash->name);
    return 1;
  }
  printf("Erase the %s flash data finish. Start from 0x%08X, size is %u.\r\n",
         flash->name, (unsigned int)addr, (unsigned int)size);

  result = sfud_write(flash, addr, size, data);
  if (result != SFUD_SUCCESS)
  {
    printf("Write the %s flash data failed.\r\n", flash->name);
    return 1;
  }
  printf("Write the %s flash data finish. Start from 0x%08X, size is %u.\r\n",
         flash->name, (unsigned int)addr, (unsigned int)size);

  result = sfud_read(flash, addr, size, data);
  if (result != SFUD_SUCCESS)
  {
    printf("Read the %s flash data failed.\r\n", flash->name);
    return 1;
  }
  printf("Read the %s flash data success. Start from 0x%08X, size is %u.\r\n",
         flash->name, (unsigned int)addr, (unsigned int)size);

  for (i = 0; i < size; i++)
  {
    if (i % 16 == 0)
    {
      printf("\r\n[%08X] ", (unsigned int)(addr + i));
    }
    printf("%02X ", data[i]);
  }
  printf("\r\n\r\n");

  for (i = 0; i < size; i++)
  {
    if (data[i] != (uint8_t)(i % 256))
    {
      printf("Read and check write data has an error.\r\n");
      return 1;
    }
  }

  printf("The %s flash test is success.\r\n", flash->name);
  return 0;
}

/**
  * @brief  The application entry point.
  */
int main(void)
{
  int flash_ok = 0;

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_SPI2_Init();

  printf("\r\n==============================================\r\n");
  printf(" SPI_FLASH (SFUD) - STM32U5 board\r\n");
  printf(" SPI2: PB13 SCK / PB14 MISO / PB15 MOSI, CS PB12\r\n");
  printf("==============================================\r\n");
  HAL_UART_Receive_IT(&huart1, &rx1_buf, 1);

  if (sfud_init() == SFUD_SUCCESS)
  {
    flash_ok = (sfud_demo(0, sizeof(sfud_demo_test_buf), sfud_demo_test_buf) == 0);
  }
  else
  {
    printf("sfud_init() failed - check the SPI flash wiring.\r\n");
  }

  /* Slow heartbeat (500 ms) = success, fast blink (100 ms) = failure */
  while (1)
  {
    HAL_GPIO_TogglePin(LED_OK_GPIO_Port, LED_OK_Pin);
    HAL_Delay(flash_ok ? 500 : 100);
  }
}

/**
  * @brief  System clock configuration: MSI 48 MHz (no PLL, no HSE).
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  printf("Wrong parameters value: file %s on line %lu\r\n", file, (unsigned long)line);
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */
