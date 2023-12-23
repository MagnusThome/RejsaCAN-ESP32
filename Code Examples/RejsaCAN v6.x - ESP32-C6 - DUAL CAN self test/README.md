# Example how to use both two CAN bus ports on an ESP32-C6
  
- CAN0 acts like an external OBD2 device requesting OBD2 rpm data from a car
- CAN1 acts like a car replying to OBD2 requests with dummy data
  
You can test either CAN bus separately, CAN0 connected to a car or CAN1 connected to some external OBD2 device. Or connect the two buses together so CAN0 get its replies from CAN1.  
  
If you do a self test with a short cable as the CAN bus between two transceivers don't forget to have 120ohm termination resistors activated (on a RejsaCAN they are activated/connected by default unless you cut the pcb trace)

## ESP-IDF Toolchain
You need espressif's 5.2 toolchain or newer since that has the twai v2 update (twai_driver_install_v2, twai_start_v2, twai_transmit_v2, twai_receive_v2 and so on) which supports multiple CAN controllers. Today (dec 2023) the only way to do this is via ESP-IDF with for example VSCode. Not PlatformIO's built in espressif toolchain since it seems to be an older version (I might be wrong but I couldn't get it to compile with PIO's built in ESP-IDF, if you find out how please tell me :-)  

##  
![self test](https://github.com/MagnusThome/RejsaCAN-ESP32/assets/32169384/38335e42-193e-4efd-a700-a233cd2ab3ab)  
  
![292323542-6e29e880-1655-4fed-8590-ffe28d65e589](https://github.com/MagnusThome/RejsaCAN-ESP32/assets/32169384/99e4d895-7e23-49a0-8b14-b76a3e1e294e)
  
![screw terminal 4](https://github.com/MagnusThome/RejsaCAN-ESP32/assets/32169384/38a3c7ae-c115-42aa-ae2a-c2d264c29d05)

