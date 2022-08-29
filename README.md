# WS2812 driver

Upload with serial to the bluepill:
1. Set boot0 to 1
1. Leave boot1 to 0
1. `stm32flash -w main.bin -v /dev/ttyACM0`

Upload with ST-LINK:
1. `st-flash write main.bin 0x08000000`

Screen usage:
1. `screen /dev/ttyACM0 19200` (default baud for miosix serial is 19200)
2. To quit screen `ctrl`+`A` and `D`