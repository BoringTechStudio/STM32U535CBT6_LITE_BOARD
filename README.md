# STM32U535CBT6 目录说明

简体中文 | [English](./README_EN.md)

> **开发板**：U5C_LITE
> **主控**：STM32U535CBT6（LQFP48 封装）

## 一、板卡介绍

### 主控
- STM32U535CBT6，Cortex-M33，160MHz 主频
- 128K Bytes Flash，274K Bytes RAM

### LED & 按键
- 用户 LED ×1（蓝色，PA0）
- 用户按键 ×1（USER_KEY，PC13）

### 接口
- 串口 USART1（TX PA9 / RX PA10）
- USB 接口 ×1（DM PA11 / DP PA12）
- LCD 接口 ×1（SPI 半双工驱动，彩色 IPS TFT）
- SPI Flash 接口 ×1（CLK PB13 / CS PB12 / MOSI PB14 / MISO PB15）

## 二、板级引脚映射（HDK/U5C_LITE-PinMap.md）

| 功能 | 引脚 | 说明 |
|------|------|------|
| LED（蓝） | **PA0** | 用户 LED |
| USER_KEY | **PC13** | 用户按键 |
| USART1 - TX | **PA9** | AF7 |
| USART1 - RX | **PA10** | AF7 |
| USB - DM / DP | PA11 / PA12 | — |
| SPI_LCD | PB7/PB6/PB4/PB5/PB3 + PA15 | PWR/RST/DC/SDA/SCL + CS |
| SPI_FLASH | PB13/PB12/PB14/PB15 | CLK/CS/MOSI/MISO |

## 三、顶层目录结构

| 路径 | 说明 |
|------|------|
| `HDK/` | 硬件开发套件（Hardware Development Kit） |
| `HDK/U5C_LITE-Schematic.pdf` | 核心板原理图 |
| `HDK/U5C_LITE-PinMap.md` | 板级引脚映射 |
| `HDK/Altium-Designer-Libraries/U5C_LITE.PcbLib` | Altium Designer PCB 封装库 |
| `HDK/Altium-Designer-Libraries/U5C_LITE.SchLib` | Altium Designer 原理图符号库 |
| `HDK/Assembly-Drawing/` | 装配位号图（Assembly-Top / Assembly-Bottom） |
| `HDK/Mechanical/` | 机械尺寸图 |
| `SDK/Examples/` | 官方例程库（已适配 U5C_LITE，16 个工程） |
| `SDK/LED/` | 独立工程：LED 参考工程 |
| `SDK/SPI_LCD_1.47inch/` | 独立工程：1.47 寸 SPI LCD（ST7789） |
| `SDK/SPI_FLASH/` | 独立工程：SPI Flash 读写（W25Q + SFUD 驱动，SPI2） |
| `SDK/USBX_CDC_ACM/` | 独立工程：USBX CDC ACM 虚拟串口（ThreadX + USBX，USB DRD FS） |
| `STM32_CubeMX_Keil_快速上手.md` | CubeMX/Keil 快速上手文档 |
| `README.md` | 本说明文档（简体中文） |
| `README_EN.md` | 英文说明文档 |

## 四、Examples 例程库（共 16 个）

| 分类 | 例程名称 |
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

> 分类统计：DMA(2)、FLASH(1)、GPIO(2)、I2C(2)、PWR(3)、RTC(2)、SPI(2)、USART(2)
