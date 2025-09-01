# Project Brief: Model Rocket GPS Tracker with Web Interface

## Objective
To develop a compact and efficient GPS tracking system for a model rocket using an ESP32-C3 Zero mini microcontroller and a Sparkfun Zoe-M8Q GPS board. The primary goal is to obtain GPS coordinates (latitude and longitude) at a rate of approximately once per second and display them on a simple web page hosted by the ESP32-C3. This will facilitate real-time tracking and recovery after launch.

## Key Requirements
High-Frequency Updates: The system must be capable of providing a GPS coordinate update every second.

Web-Based Display: The ESP32-C3 shall host a web server, accessible via Wi-Fi, that displays the current latitude, longitude, and number of visible satellites.

I2C Communication: The ESP32-C3 and Zoe-M8Q module will communicate over the I2C bus.

Accuracy: The GPS data should be as accurate as possible to enable precise location of the rocket.

Power Efficiency: The system should be designed to run efficiently on a small LiPo battery suitable for model rocket payloads.

Robustness: The code should be resilient to temporary signal loss and able to re-establish a satellite lock quickly.

## Hardware Components
Microcontroller: ESP32-C3 Zero mini

GPS Module: Sparkfun Zoe-M8Q GPS Breakout

Power Source: 3.7V Single-Cell LiPo Battery

Connecting Wires: Jumper wires or a custom PCB.

## Software & Development Environment
IDE: Visual Studio Code with the PlatformIO extension.

Framework: Arduino

Key Libraries:

SparkFun u-blox GNSS Arduino Library: For I2C communication and parsing data from the Zoe-M8Q.

Wire: For I2C communication.

WiFi: For ESP32 Wi-Fi capabilities (acting as an Access Point).

ESPAsyncWebServer: For creating a lightweight, asynchronous web server.

## Implementation Details
### Wiring Diagram
The connection between the ESP32-C3 Zero mini and the Sparkfun Zoe-M8Q will use I2C:

ESP32-C3 Pin

Zoe-M8Q Pin

Purpose

GND

GND

Common Ground

3V3

3V3

Power to GPS module

SDA (GPIO8)

SDA

I2C Data

SCL (GPIO9)

SCL

I2C Clock

Note: The default I2C pins on many ESP32-C3 boards are GPIO8 (SDA) and GPIO9 (SCL). Please verify with the specific board's pinout diagram.

5.2. Code Structure & Logic
Includes & Definitions:

Include Arduino.h, Wire.h, SparkFun_u-blox_GNSS_Arduino_Library.h, WiFi.h, and ESPAsyncWebServer.h.

Define Wi-Fi credentials for the Access Point (e.g., SSID: "RocketTracker").

Instantiate SFE_UBLOX_GNSS and AsyncWebServer objects.

setup() function:

Initialize the primary serial connection for debugging (Serial.begin(115200)).

Initialize the I2C bus (Wire.begin()).

Initialize the GPS module. Check for a successful connection.

Configure the ESP32 to act as a Wi-Fi Access Point.

Define web server routes:

A route for the root URL (/) that serves the main HTML page.

A route for /data that serves the latest GPS coordinates in JSON format (e.g., {"lat":35.123, "lng":138.456, "sats":8}).

Start the web server.

loop() function:

This function will be minimal. The web server runs asynchronously. The loop will primarily be responsible for polling the GPS module for new data and updating global variables that store the latest latitude and longitude.

Web Page (HTML/JS):

The HTML will be stored in a C++ string literal within the main.cpp file.

The page will have a simple layout displaying "Latitude:", "Longitude:", and "Satellites:".

JavaScript on the page will use fetch() to request data from the /data endpoint every second.

Upon receiving the JSON data, the script will update the values on the web page.

A link to Google Maps using the current coordinates should be included for easy visualization.

6. Testing & Validation
Initial Test: Power the hardware and upload the code. Open the Serial Monitor to check for debug messages, including the IP address of the web server.

Wi-Fi Connection: Use a phone or computer to connect to the "RocketTracker" Wi-Fi network.

Web Interface: Open a web browser and navigate to the IP address shown in the Serial Monitor (likely 192.168.4.1).

Expected Output: The web page should load and, after a moment for satellite lock, display updating GPS coordinates. Initially, the values may be 0 or invalid.

Outdoor Test: Take the device outdoors with a clear view of the sky to ensure it can acquire a satellite lock. The coordinates on the web page should update to reflect a real-world location.

7. Deliverables
A well-commented and clean main.cpp file containing the complete source code, including the embedded HTML and JavaScript for the web interface.

A platformio.ini configuration file specifying the board, framework, and required library dependencies (including the web server).

A brief README.md file summarizing the project and providing instructions on wiring, uploading, and connecting to the web interface.
