# Example how to use both two CAN bus ports on an ESP32-C6
  
- CAN0 acts like an external OBD2 devcice requesting OBD2 rpm data from a car
- CAN1 acts like a car replying to OBD2 requests with dummy data
  
You can test either CAN bus separately, CAN0 connected to a car or CAN1 connected to some external OBD2 device
or connect the two buses together so CAN0 get its repleies from CAN1  
  
Don't forget to have the 120ohm termination resistors activated (they are activated/connected by default unless you cut the pcb traces)
