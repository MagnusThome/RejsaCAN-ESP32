# Projects ideas and tips

I'll add fun stuff here... 


## A cheap touch screen

Just a first test of CAN info on the screen with ugly fonts ;-)  The wiring between the boards will be replaced by a super small interconnect board so the RejsaCAN is sandwich mounted behind the display board.

![Touch-screen(1)](https://user-images.githubusercontent.com/32169384/138956178-591b5a11-4536-44ec-ba11-c2d607cd882b.jpg)

![Touch-screen(0)](https://user-images.githubusercontent.com/32169384/138956181-5c421461-7e94-4a66-8d21-c0f54506565e.png)


## CAN log all to Serial over USB and Bluetooth

I'll use Techstream to ask for different non standard OBD2 data over the OBD2 port (steering angle, oil pressure, brake pressure...) and simultaneously log all the traffic with this RejsaCAN in the picture below, logging both the requests from Techstream and the replies from the car. Simple Arduino code for this is in the examples directory. I can either save all data over USB to my PC or save to a log file on my mobile phone over Bluetooth using for example this app https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en&gl=US

![IMG_20211028_085844](https://user-images.githubusercontent.com/32169384/139203931-2b5d8c71-bb6d-413a-8c6a-0a8f1bfe9376.jpg)


## Using RejsaCAN as a sniffer interface with CAN software tools

I installed ESP32RET on the board and hooked it up to the CAN software tool SavvyCAN on my PC

https://github.com/collin80/ESP32RET

www.savvycan.com


Good videos to get started:

https://youtu.be/kdA5Gdf3FAk

https://youtu.be/GOuglqFtmOE

![image](https://user-images.githubusercontent.com/32169384/137488188-7943bd23-efe2-4454-a5ed-df7043051c72.png)

![image](https://user-images.githubusercontent.com/32169384/137488021-70c7fb58-a59d-4f41-86c1-395dd06bf2e3.png)

