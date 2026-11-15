# SPI LCD 1.47"

Independent STM32CubeMX / Keil MDK example for STM32U535CBT6 (U5C_LITE board, LQFP48).

## Behavior

- Initializes a 1.47" ST7789 SPI LCD (172x320, rotation 90 deg)
- Blinks the blue LED 3 times at power-on (runtime self-test)
- Shows three text lines plus a running tick counter on the LCD
- Echoes bytes received on USART1 (115200 8N1)

## Connections

| Signal | Pin | Configuration |
| --- | --- | --- |
| LCD_SCL | PB3 | SPI1_SCK, AF5 |
| LCD_SDA | PB5 | SPI1_MOSI, AF5 |
| LCD_DC | PB4 | Push-pull output |
| LCD_RST | PB6 | Push-pull output |
| LCD_PWR (backlight) | PB7 | Push-pull output |
| LCD_CS | PA15 | Push-pull output |
| Blue LED | PA0 | Push-pull output, active low |
| USART1 TX / RX | PA9 / PA10 | AF7 |

## Clock

- HSE 8 MHz + PLL -> 160 MHz when an HSE crystal is fitted
- Falls back to MSI 4 MHz + PLL -> 160 MHz if the HSE does not start

## Build and use

Open `MDK-ARM\SPI_LCD_1.47inch.uvprojx` with Keil MDK, build, and program the target.
The `SPI_LCD_1.47inch.ioc` file contains the matching CubeMX configuration.

