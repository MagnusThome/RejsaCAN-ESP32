# Example how to use both two CAN bus ports on an ESP32-C6
  
- CAN0 acts like an external OBD2 device requesting OBD2 rpm data from a car
- CAN1 acts like a car replying to OBD2 requests with dummy data
  
You can test either CAN bus separately, CAN0 connected to a car or CAN1 connected to some external OBD2 device. Or connect the two buses together so CAN0 get its replies from CAN1  
  
Don't forget to have the 120ohm termination resistors activated (they are activated/connected by default on a RejsaCAN v6.x unless you cut the pcb traces)

## ESP-IDF Toolchain
You need espressif's 5.2 toolchain or newer with the twai v2 update (twai_send_v2, twai_start_v2 and so on) which supports multiple CAN controllers. Today (dec 2023) the only way to do this is via ESP-IDF with for example VSCode. Not PlatformIO's built in espressif toolchain since it seems to be an older version (I might be wrong but I couldn't get it to compile with PIO's built in ESP-IDF, if you find out how please tell me :-)
