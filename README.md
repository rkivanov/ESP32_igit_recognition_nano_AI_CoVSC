ESP32 digit recognition by jetson orin nano AI model
1. Description
I want to demonstrate usage of the AI capabilities from ESP32 based on the model which runs on Jetson nano. Global architecture is on the figure below.
If user draw a digit by hand in the drawing area, the digit has to be drown on the drawing area. When the user clicks on send button ESP32 have to send the image to the Nano. AI will recognize the digit and return it to ESP32. ESP32 have to display the digit    on the screen. Clear button will clear the image from the drawing area.  

2. Hardware
Jetson Orin Nano development kit 8GB
ESP32-2432S028R kit
SCREEN_WIDTH 320 SCREEN_HEIGHT 240
3. Communication
ESP32 and jetson nano will communicate by MQTT broker running on nano. Both wil use WiFi network as clients to AP.

AI app <> MQTT broker <> Jetson Nano dev board WiFi module <> WiFi AP <> ESP32 <> App

4. Requirenements
4.1. Programing requirements
4.1.1. ESP32
Environment – Arduino IDE
Language C++
Modular structured design – ino file and cpp and h files for different functional blocks. For example: WiFi, MQTT, Display, touch, main logic and so on.
Touch screen to use hardware interrupt on pin 36. No polling.
4.1.1.1. User interface
User interfase consists of:
* Draw area with dimension of 112x112 pixels
* Button “Send”
* Button “Clear”
* Area labeled “The digit is:” where the digit have to be displayed

4.1.2. Jetson nano
Jetpack 6.2
Language python 3
Model and app are already done. Interface is MQTT.
4.1.3. Program interface between esp32 and nano. 
AI model expects one-dimensional bite array represents 28x28 pixels matrix row by row. The drawing area have to be converted to 28x28 pixels matrix before to send it. The stylus touch have to be represented as a brush with defined radius (r=2 pixels).













