# Emulate a car

This code replies as if it is a car with OBD2 

Any OBD2 standard PID requested gets a reply with a fake value. Default is single byte value replies only. Any replies that should be two or more bytes long can be added, the only ones currently added in the code are ENGINE_RPM and SUPPORTED PIDS.

A future logical addition to this code is adding analog potentiometers to MCU input pins and do analog to digital conversion to emulate data like speed, throttle position and so on. In theory this code can be expanded to make a vehicle without OBD2 to have a working OBD2 connector for a few basic data items.

Note the female instead of male connector:
![reversed OBD2](https://user-images.githubusercontent.com/32169384/141805769-a759d0a7-4a12-4bdf-99bf-38db079c079c.jpg)
