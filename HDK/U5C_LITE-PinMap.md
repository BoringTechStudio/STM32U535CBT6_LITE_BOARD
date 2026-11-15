# STM32U535CBT6 板级引脚映射 / Board Pin Map（PinMap）

> 本文件定义 U5C_LITE 板级引脚与功能映射，供查阅与开发参考。
> This file defines the U5C_LITE board pin / function mapping for reference and development.

## LED 灯 / LED

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| BLUE 蓝 | **PA0** | 蓝色 LED / Blue LED |

## 按键 / Key

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| USER_KEY | **PC13** | 用户按键 / User key |

## 串口 USART1 / UART USART1

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| TX | **PA9** | USART1_TX |
| RX | **PA10** | USART1_RX |

## SPI LCD 屏 / SPI LCD

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| LCD_PWR | **PB7** | 电源 / Power |
| LCD_RST | **PB6** | 复位 / Reset |
| LCD_DC | **PB4** | 数据/命令 / Data / Command |
| LCD_SDA | **PB5** | 数据 / Data (MOSI) |
| LCD_SCL | **PB3** | 时钟 / Clock |
| LCD_CS | **PA15** | 片选 / Chip select |

## USB

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| DM | **PA11** | USB DM |
| DP | **PA12** | USB DP |

## SPI Flash 闪存 / SPI Flash

| 功能 Function | 引脚 Pin | 说明 Description |
|------|------|------|
| CLK | **PB13** | 时钟 / Clock |
| CS | **PB12** | 片选 / Chip select |
| MOSI | **PB14** | 主机输出 / Master out |
| MISO | **PB15** | 主机输入 / Master in |
