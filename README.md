1. Title & High-Level Overview
Project Title: “Wi-Fi Crowdness & Help Button System”

What It Does (1–3 Sentences)
There are two devices communicating over Wi-Fi:

A Help Button Device that counts people passing by (using a sensor) and also provides a help button for customers. Pressing the button sends a help request, and an LED lights up once help is confirmed.
A Monitor Device that pulls data from all Help Button Devices—displaying a crowdness level on a stepper-motor gauge and providing a screen interface. This “crowdness” metric helps decide how many salespeople are needed in that aisle or overall.
General Sketch (Highlighting Physical Features)
css
Copy
[Help Button Device x N]
 - Wi-Fi MCU
 - People-Counting Sensor (ToF/PIR)
 - Button (Request Help)
 - LED (Help Confirmation)
 
                Wi-Fi
                
[Monitor Device (Console)]
 - Wi-Fi MCU
 - Screen (UI + data from all help devices)
 - Stepper-Motor Gauge (shows overall crowdness)
 - Possibly a button for staff interactions

 ![Description of the Image](HWSW_Project_I/images/system sketch.png)

2. “Help Button Device” Slide (Now with People-Counting Sensor)
Detailed Sketch
scss
Copy
 ┌───────────────────────────────────────────┐
 │   Help Button Device (ESP32 or ESP8266)  │
 │ ┌───────────────────────────────────────┐ │
 │ │ People-Counting Sensor (e.g., ToF)   │ │
 │ └───────────────────────────────────────┘ │
 │ ┌───────────────────────────────────────┐ │
 │ │ Button (Help Request)               │ │
 │ └───────────────────────────────────────┘ │
 │ ┌───────────────────────────────────────┐ │
 │ │ LED (Help Confirmed)                │ │
 │ └───────────────────────────────────────┘ │
 │   Wi-Fi MCU + Custom PCB + Enclosure     │
 └───────────────────────────────────────────┘
How It Works (Few Sentences)
People Counting Sensor (e.g., a Time-of-Flight sensor like the ST VL53L1X, or a simple PIR motion sensor) detects and counts passersby in real-time.
Help Button: When pressed, a help request message is sent over Wi-Fi to the Monitor Device.
LED: Lights up once the Monitor Device acknowledges the request (“Help is on the way”).
Wi-Fi MCU (ESP32/ESP8266) aggregates both sensor (people counts) and button events, sends them periodically or on event to the Monitor Device.
3. “Monitor Device” Slide (Screen + Gauge)
Detailed Sketch
scss
Copy
 ┌──────────────────────────────────────────────┐
 │      Monitor Device (ESP32 or ESP8266)      │
 │ ┌──────────────────────────────────────────┐ │
 │ │ Screen (TFT e.g. ILI9341)              │ │
 │ └──────────────────────────────────────────┘ │
 │ ┌──────────────────────────────────────────┐ │
 │ │ Stepper Motor + Gauge (Crowdness)      │ │
 │ └──────────────────────────────────────────┘ │
 │   Wi-Fi MCU + Custom PCB + Enclosure       │
 └──────────────────────────────────────────────┘
How It Works (Few Sentences)
Wi-Fi MCU connects to the local network, pulling or receiving data from multiple Help Button Devices:
People Counts to gauge how busy an aisle or store section is.
Help Requests to see if customers pressed the button.
Screen Display: Shows a user interface listing active help requests, or more detailed data from each device (counts, aisle name, etc.).
Stepper-Motor Gauge: Reflects an overall “crowdness” level (e.g., from 0 to 100). Higher values mean more traffic => more sales associates needed.
Optionally a Button or simple input method for the staff to confirm requests or navigate menu items.
4. Communication & System Diagram Slide
Figure A: Device-to-Device Communication Workflow
java
Copy
[Help Device] --(Wi-Fi)--> [Monitor Device]

1. People Counter: Device sends (count data) at intervals or threshold changes.
2. Help Button Press => sends "HELP_REQUEST" message (LED off).
3. Monitor Device:
   - Processes data, updates "crowdness" calculation & gauge.
   - Acknowledges help => returns "HELP_ACK" => lights LED on device.
4. Screen UI shows stats (#people, #help requests, etc.).
Figure B: System Architecture (Detailed)
scss
Copy
       ┌───────────────────────────────────────────────────┐
       │          Help Button Device (ESP32)             │
       │  ┌───────────────────────────────────────────┐   │
   ToF --│--│ I2C or GPIO to MCU for people count    │   │
  Button-│--│ GPIO input for help requests           │   │
    LED -│--│ GPIO output for help-confirm LED       │   │
       │  └───────────────────────────────────────────┘   │
       │      Wi-Fi (Station Mode) + Custom PCB          │
       └───────────────────────────────────────────────────┘
                          ~ ~ ~ ~ ~ ~
                          Wi-Fi Network
                          ~ ~ ~ ~ ~ ~
       ┌───────────────────────────────────────────────────┐
       │           Monitor Device (ESP32)                 │
       │  ┌───────────────────────────────────────────┐   │
       │  │ Screen (TFT, e.g. ILI9341)               │   │
       │  └───────────────────────────────────────────┘   │
       │  ┌───────────────────────────────────────────┐   │
       │  │ Stepper Motor + Driver (Gauge)           │   │
       │  └───────────────────────────────────────────┘   │
       │      Wi-Fi (AP or Station) + Custom PCB          │
       └───────────────────────────────────────────────────┘

![Description of the Image](HWSW_Project_I/images/Screenshot 2025-01-22 104817.png)

Explanation:

Help Device measures passersby counts, detects help button presses, sends data to the Monitor via Wi-Fi. If the Monitor acknowledges a request, the device lights the LED.
Monitor Device aggregates all data, updates the screen with how many requests and people counts, and drives the stepper gauge to show overall “crowdness level.”


Hardware Choices & Part Numbers
Below are recommended parts; pick alternatives as needed:

Wi-Fi MCU (Both Devices):
ESP32-WROOM-32 or ESP8266-based dev modules.
People-Counting Sensor (Help Device):
ST VL53L1X Time-of-Flight (accurate short-to-mid range)
or a simpler PIR sensor if you just need motion-based counting.
Button + LED (Help Device):
Generic tact switch + 5 mm LED with appropriate resistor.
Display (Monitor Device):
7.0" TFT LCD with ILI9488 or RA8875 controller (800x480 or 1024x600 resolution).
Stepper Motor & Driver (Monitor Device):
28BYJ-48 stepper + ULN2003 driver
or NEMA17 + A4988 driver if you want more torque.
Power Supplies & Regulator:
e.g., AMS1117-3.3 for the 3.3V rail.