# What CAN library/libraries to use?

There are many CAN libraries that work with the ESP32, here are the ones I've found so far. If you are thinking about an ESP32 based CAN project my tip is to check out the examples included with each library, they will give you some idea on different approaches.

- https://github.com/sandeepmistry/arduino-CAN

- https://github.com/adafruit/arduino-CAN

- https://github.com/collin80/esp32_can
  
- https://github.com/sdp8483/ESP32-Arduino-CAN  
  
If you only want to access OBD2 data and not dive into the lower layer CAN bus this is also available:

- https://github.com/sandeepmistry/arduino-OBD2

I'm sure there are more libraries out there. If you find something that has some special advantage feel free to email me so I can add it here

# ESP32-S3  
  
Since the ESP32-S3 is slightly different when it comes to its CAN API compared to the older ESP32 the easiest way to code for it is to use Visual Code Studio and the Espressif toolchain by following these install instructions:  
  
https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md  

You can also look into these interesting ports for ESP32-S3 that might be useful, thanks to Pawel for his ports!  

https://github.com/pawelka/ESP32RET  

https://github.com/pawelka/esp32_can

These might be worth a look also:  
  
https://github.com/Sheimy/TWAI_S3_LISEN  
  
https://github.com/halfroad/TWAIMessager  
    
  
# Install USB drivers (if necessary)

The USB chip on the 2.x boards is a CP2104 from Silicon Labs

You can find drivers for your PC here under downloads https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers


# Setting up the Arduino IDE for ESP32 on Windows

Download and install the Arduino IDE development editor https://www.arduino.cc/en/software
  
Start the IDE and go to File > Preferences  
  
<img src=https://user-images.githubusercontent.com/32169384/142822314-5def32dc-cf87-49fe-a0b1-bcffd4d74009.png width=160>

Click the symbol on the right side  
  
<img src=https://user-images.githubusercontent.com/32169384/142826179-c582716a-7bee-40b8-8fdf-2c6aa9334ae9.jpg width=680>

Add the line  
https://dl.espressif.com/dl/package_esp32_index.json  
  
<img src=https://user-images.githubusercontent.com/32169384/142822650-a810b9c3-65a4-42dd-81db-87748cbb81e3.png width=580>

Go to Tools > Board: xxx > Boards Manager...  
  
<img src=https://user-images.githubusercontent.com/32169384/142826483-25754433-f343-424a-a28b-4ecbb563d819.jpg width=510>

Enter "ESP32" in the search box and hit enter to search, then click and install the latest version  
  
<img src=https://user-images.githubusercontent.com/32169384/142823696-ba6d33e9-3aa6-4bcc-9e80-4b772502a32e.png width=640>

Go to Tools > Board: xxx > ESP32 Arduino > and choose ESP32 Dev Module  
  
<img src=https://user-images.githubusercontent.com/32169384/142824005-fce698ad-102d-4008-83c1-03cc917f38f5.png width=700>

Go to Tools > Manage Libraries...
  
<img src=https://user-images.githubusercontent.com/32169384/142826615-cc72dcb5-f0c1-4c09-bb74-e6f502f6f1c5.png width=380>
  
When you have decided what CAN library/libraries you want to use, search for and install these from here. But since it is often a bit tricky to search for CAN libraries since the word "can" is present in many many other libraries it is often easier to go directly to github and download the library you are after, unzip and place the contents in the Arduino library directory (which normally is found in the same directory as where you place your projects).

Most of the code examples on here needs these two libraries https://github.com/collin80/esp32_can and https://github.com/collin80/can_common (as stated within the example code ;-)  
  
<img src=https://user-images.githubusercontent.com/32169384/142828027-13d392e6-ed5b-4f86-88ff-91c73b121386.png width=380>



# Setting up the Arduino IDE for ESP32 on other platforms

- [Download and install](https://www.arduino.cc/en/software) Arduino IDE or cli for your platform.
- [Download and install](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/#installation-step-by-step) ESP32 prerequisites
- Follow the steps 1-5 on setting up the ESP32 environment.
- If you wish to compile and flash the ESP32 [blink](https://github.com/espressif/esp-idf/tree/451ce8a7ed486c6c6045189db57106ca7107abdb/examples/get-started/blink) example, do so by going to ~/esp/esp-idf, and do
- $ source export.sh 
- $ cd ~/esp/esp-idf/examples/blink
- $ idf.py build to compile
- $ idf.py -p (PORT) flash
- If you have a v2.1 board, change #define BLINK_GPIO CONFIG_BLINK_GPIO to: #define BLINK_GPIO 13
- recompile and reflash to get the blue LED blinking
- Choose what CAN library/libraries you want to use and download, for example clone [esp32_can](https://github.com/collin80/esp32_can) and [can_common](https://github.com/collin80/can_common) to your ~/Arduino/libraries directory.
- copy obd2.h to ~/Arduino/libraries/obd2/ 
- Install [ESP32 environment for Arduino](https://dronebotworkshop.com/esp32-intro/)
- Choose "ESP32 Dev Module" as your board, build and flash!

