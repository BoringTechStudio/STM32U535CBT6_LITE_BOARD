# STM32U535CBT6 Directory Guide

English | [简体中文](./README.md)

> **Board**: U5C_LITE
> **MCU**: STM32U535CBT6 (LQFP48 package)

## Board Introduction

### MCU
- STM32U535CBT6, Cortex-M33, 160 MHz core clock
- 128 KB Flash, 274 KB RAM

### LED & Button
- User LED ×1 (blue, PA0)
- User button ×1 (USER_KEY, PC13)

### Interfaces
- USART1 (TX PA9 / RX PA10)
- USB ×1 (DM PA11 / DP PA12)
- LCD header ×1 (SPI half-duplex driven, color IPS TFT)
- SPI Flash header ×1 (CLK PB13 / CS PB12 / MOSI PB14 / MISO PB15)

## 1. Board-Level Pin Map (HDK/U5C_LITE-PinMap.md)

| Function | Pin | Notes |
|------|------|------|
| LED (blue) | **PA0** | User LED |
| USER_KEY | **PC13** | User button |
| USART1 - TX | **PA9** | AF7 |
| USART1 - RX | **PA10** | AF7 |
| USB - DM / DP | PA11 / PA12 | — |
| SPI_LCD | PB7/PB6/PB4/PB5/PB3 + PA15 | PWR/RST/DC/SDA/SCL + CS |
| SPI_FLASH | PB13/PB12/PB14/PB15 | CLK/CS/MOSI/MISO |

## 2. Top-Level Directory Structure

| Path | Description |
|------|------|
| `HDK/` | Hardware Development Kit |
| `HDK/U5C_LITE-Schematic.pdf` | Board schematic |
| `HDK/U5C_LITE-PinMap.md` | Board-level pin map |
| `HDK/Altium-Designer-Libraries/U5C_LITE.PcbLib` | Altium Designer PCB footprint library |
| `HDK/Altium-Designer-Libraries/U5C_LITE.SchLib` | Altium Designer schematic symbol library |
| `HDK/Assembly-Drawing/` | Assembly drawing (Assembly-Top / Assembly-Bottom) |
| `HDK/Mechanical/` | Mechanical dimension drawings |
| `SDK/Examples/` | Official example library (adapted to U5C_LITE, 16 projects) |
| `SDK/LED/` | Standalone project: LED reference |
| `SDK/SPI_LCD_1.47inch/` | Standalone project: 1.47" SPI LCD (ST7789) |
| `SDK/SPI_FLASH/` | Standalone project: SPI flash read/write (W25Q + SFUD driver, SPI2) |
| `SDK/USBX_CDC_ACM/` | Standalone project: USBX CDC ACM virtual COM port (ThreadX + USBX, USB DRD FS) |
| `STM32_CubeMX_Keil_快速上手.md` | CubeMX/Keil quick-start guide (Chinese) |
| `README.md` | This document (Simplified Chinese) |
| `README_EN.md` | English version of this document |

## 3. Examples Library (16 in total)

| Category | Example |
|------|----------|
| DMA | DMA_DataHandling |
| DMA | DMA_FLASHToRAM |
| FLASH | FLASH_EraseProgram |
| GPIO | GPIO_Demo |
| GPIO | GPIO_IOToggle |
| I2C | I2C_TwoBoards_ComIT |
| I2C | I2C_WakeUpFromStop |
| PWR | PWR_ModesSelection |
| PWR | PWR_SLEEP |
| PWR | PWR_STANDBY |
| RTC | RTC_ActiveTamper |
| RTC | RTC_Alarm |
| SPI | SPI_FullDuplex_ComIT_Master |
| SPI | SPI_FullDuplex_ComIT_Slave |
| USART | USART_SlaveMode |
| USART | USART_SlaveMode_DMA |

> Category count: DMA(2), FLASH(1), GPIO(2), I2C(2), PWR(3), RTC(2), SPI(2), USART(2)
