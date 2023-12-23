# Example how to use both two CAN bus ports on an ESP32-C6
  
- Everything that comes in on CAN0 is forwarded to CAN1. And vice versa
- Add "Man In The Middle" MITM code to filter, convert, translate or swap data around
  
## ESP-IDF Toolchain
You need espressif's 5.2 toolchain or newer with the twai_v2 update which supports multiple CAN controllers. Today (dec 2023) the only way to do this is via ESP-IDF with for example VSCode. Not PlatformIO's built in espressif toolchain since it seems to be an older version (I might be wrong but I couldn't get it to compile with PIO's built in ESP-IDF, if you find out how please tell me :-)
