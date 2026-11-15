# LED

Independent STM32CubeMX / Keil MDK example for STM32U535CBT6 (U5C_LITE board, LQFP48).

## Behavior

Toggles the blue LED every 500 ms.

## Connections

| Signal | Pin | Configuration |
| --- | --- | --- |
| Blue LED | PA0 | Push-pull output, active low |

## Build and use

Open the .uvprojx in MDK-ARM with Keil MDK, build, and program the target. The STM32U535CBT6.ioc file contains the matching CubeMX configuration.
