# USBX_CDC_ACM

Azure RTOS **ThreadX + USBX** device demo for STM32U535CBT6 (U5C_LITE board, LQFP48).
The board enumerates as a **USB CDC ACM virtual COM port**; everything typed into the
host terminal is echoed back by the device.
Ported from `STM32Cube_FW_U5_V1.9.0\Projects\NUCLEO-U545RE-Q\Applications\USBX\Ux_Device_CDC_ACM`.

## Behavior

* `MX_ThreadX_Init()` starts the kernel; `app_ux_device_thread_entry()` initialises the
  USB DRD peripheral, registers the CDC ACM class and starts the USB device.
* Two application threads (`usbx_cdc_acm_read_thread_entry` /
  `usbx_cdc_acm_write_thread_entry`) move data between the host and the class driver
  through an event-flag group, so the port acts as an **echo** terminal.
* Heartbeat: the blue LED on **PA0** blinks at ~1 Hz from the USB device thread, which
  shows that the scheduler and the SysTick tick are running.
* USART1 (PA9/PA10, 115200 8N1) is initialised by the example and kept available for
  additional debug printing.

## Connections

| Signal | Pin | Configuration |
| --- | --- | --- |
| USB D- | PA11 | AF10 (`GPIO_AF10_USB`) |
| USB D+ | PA12 | AF10 (`GPIO_AF10_USB`) |
| Blue LED | PA0 | Push-pull output, blinks as heartbeat |
| USART1 TX / RX | PA9 / PA10 | AF7, 115200 8N1 |
| VBUS sensing (unused) | PC2 | ADC1_IN3, still configured but not used (see below) |

> **Board adaptation** - the original NUCLEO-U545RE-Q example starts the USB device only
> after an ADC measurement of the VBUS divider exceeds 2500 LSB. The U5C_LITE board has no
> VBUS sensing divider, so that state machine would never start the device. The port calls
> `HAL_PCD_Start()` directly (`vbus_sensing_enable = DISABLE`) and the VBUS state machine
> was removed.
> The USB pins are also not configured by the CubeMX-generated MSP, so PA11/PA12 are set
> to AF10 in `HAL_PCD_MspInit()`.

## Clock

* `HSI` 16 MHz -> PLL1 (M=4, N=80, P=2, Q=2, R=2) -> **SYSCLK 160 MHz**, `FLASH_LATENCY_4`,
  `PWR_REGULATOR_VOLTAGE_SCALE1`.
* **HSI48** provides the 48 MHz USB kernel clock (`RCC_CLK48CLKSOURCE_HSI48`) and is trimmed
  by the **CRS** using the USB SOF signal (`HSI48CalibrationValue = 32`).
* No HSE crystal is required - the whole demo runs from internal oscillators.
* The regulator stays on the internal LDO (`PWR_LDO_SUPPLY`) instead of SMPS, matching the
  U5C_LITE power stage.
* ThreadX SysTick is generated for `SYSTEM_CLOCK = 160000000` (100 Hz tick), the HAL time
  base uses TIM6.

## Memory footprint

| Region | Used |
| --- | --- |
| Code + RO | ~63 KB |
| RW + ZI | ~23 KB |
| Flash available | 128 KB |
| RAM available | 274 KB |

## Structure

```
USBX_CDC_ACM/
├── AZURE_RTOS/App/          ThreadX application glue (app_azure_rtos.c, config)
├── Core/Inc, Core/Src/      main.c, MSP, IT, system_stm32u5xx.c, tx_initialize_low_level.S
├── USBX/App/                app_usbx.c, app_usbx_device.c, ux_device_cdc_acm.c, descriptors
├── USBX/Target/             ux_stm32_config.h
├── Drivers/                 STM32U5xx HAL + CMSIS (local copy, self-contained)
├── Middlewares/ST/threadx/  ThreadX core + Cortex-M33/AC6 port
├── Middlewares/ST/usbx/     USBX core, STM32 device controller, CDC ACM class
└── MDK-ARM/                 USBX_CDC_ACM.uvprojx (Keil MDK, ARMCLANG V6.21)
```

## Build and use

Open `MDK-ARM\USBX_CDC_ACM.uvprojx` with Keil MDK, build and program the target.

1. Connect the board's USB connector to the PC (the D-/D+ pair on PA11/PA12).
2. Windows enumerates `STM32U535CBT6 Virtual ComPort` (VID 0x0483 / PID 0x5740).
3. Open the COM port (any baud rate, 8N1) and type - the characters are echoed back.
4. The blue LED keeps blinking at 1 Hz while the firmware is alive.

Build status: **0 Error(s), 0 Warning(s)** (ARMCLANG V6.21, MicroLIB).
