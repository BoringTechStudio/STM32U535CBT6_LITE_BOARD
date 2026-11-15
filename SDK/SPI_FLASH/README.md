# SPI_FLASH

Independent STM32CubeMX / Keil MDK example for STM32U535CBT6 (U5C_LITE board, LQFP48).
Reads/writes a W25Q serial flash over SPI2 using the SFUD driver.
Ported from `STM32G474CBT6\SDK\SPI_FLASH`.

## Behavior

`sfud_init()` detects the flash, then the demo erases 1024 bytes at address 0, writes a
ramp pattern, reads it back and verifies it. Progress is printed on USART1.

LED feedback: **slow blink (500 ms) = test passed**, **fast blink (100 ms) = test failed**
(single blue LED on PA0, so the same LED shows both states).

## Connections

| Signal | Pin | Configuration |
| --- | --- | --- |
| SPI2_CLK | PB13 | SPI2_SCK, AF5 |
| SPI2_CS | PB12 | Software chip select (GPIO) |
| SPI2_MOSI | PB15 | SPI2_MOSI, AF5 |
| SPI2_MISO | PB14 | SPI2_MISO, AF5 |
| Blue LED | PA0 | Push-pull output (active low) |
| USART1 TX / RX | PA9 / PA10 | AF7, 115200 8N1 |

> `PinMap.md` lists the flash-side names (MOSI = PB14 / MISO = PB15); from the MCU side the
> SPI2 MOSI is **PB15** and MISO is **PB14**, as used by this project.

## Clock

MSI 48 MHz (no PLL, no HSE crystal needed), FLASH_LATENCY_2.
SPI2 runs at 48 MHz / 4 = **12 MHz**.

## Build and use

Open `MDK-ARM\SPI_FLASH.uvprojx` with Keil MDK, build, and program the target.
