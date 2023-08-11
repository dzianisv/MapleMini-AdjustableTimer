This is a simple Arduino-compatible adjustable timer for [STM32F103C8T6](https://docs.platformio.org/en/latest/boards/ststm32/maple_mini_origin.html) based Mapple Mini.


- ![](./MappleMiniPinOut.png)
Board pin out.

## Usage

Push a button to increase the interval.
Keep it pushed for exact time you want to increase the interval.
Use a custom button PB5 or pin number 17 on the board to increase a second interval.

- ![](./demo.gif)
Demo

## Flashing & Debugging

I have used ST-Link to flash it, I guess DFU could be used as well.

```bash
openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg
```

If device connected correctly, you will see
```
engineer@mybook13 switchproxy % openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg
Open On-Chip Debugger 0.12.0
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
WARNING: interface/stlink-v2.cfg is deprecated, please switch to interface/stlink.cfg
Info : auto-selecting first available session transport "hla_swd". To override use 'transport select <transport>'.
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
Info : clock speed 1000 kHz
Info : STLINK V2J29S7 (API v2) VID:PID 0483:3748
Info : Target voltage: 3.256802
Info : [stm32f1x.cpu] Cortex-M3 r1p1 processor detected
Info : [stm32f1x.cpu] target has 6 breakpoints, 4 watchpoints
Info : starting gdb server for stm32f1x.cpu on 3333
Info : Listening on port 3333 for gdb connections
```


```bash
OOCD_INTERFACE=interface/stlink-v2.cfg
OOCD_BOARD=target/stm32f1x.cfg

openocd -f $OOCD_INTERFACE -f $OOCD_BOARD \
            -c "init" -c "reset init" \
            -c "stm32f1x unlock 0; reset halt" \
            -c "flash erase_sector 0 0 last" \
            -c "flash write_image erase ${DFU:?DFU is not set} 0x08000000" \
            -c "reset" \
            -c "shutdown"


```
## Requirements
- [Install Platform.io](https://platformio.org/install/ide?install=vscode)