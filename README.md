# WS2812 driver

Upload with serial to the bluepill:
1. Set boot0 to 1
1. Leave boot1 to 0
1. `stm32flash -w main.bin -v /dev/ttyACM0`