# Model Rocket GPS Tracker with Web Interface

## 1. Objective

To develop a compact and efficient GPS tracking system for a model rocket using an ESP32-S3 Zero mini microcontroller and a Sparkfun Zoe-M8Q GPS board. The primary goal is to obtain GPS coordinates (latitude and longitude) at a rate of approximately once per second and display them on a simple web page hosted by the ESP32-S3. This will facilitate real-time tracking and recovery after launch.

## 2. Key Requirements

- **High-Frequency Updates:** The system must be capable of providing a GPS coordinate update every second.
- **Web-Based Display:** The ESP32 shall host a web server, accessible via Wi-Fi, that displays the current latitude, longitude, and number of visible satellites.
- **I2C Communication:** The ESP32-S3 and Zoe-M8Q module will communicate over the I2C bus.
- **Accuracy:** The GPS data should be as accurate as possible to enable precise location of the rocket.
- **Power Efficiency:** The system should be designed to run efficiently on a small LiPo battery suitable for model rocket payloads.
- **Robustness:** The code should be resilient to temporary signal loss and able to re-establish a satellite lock quickly.

## 3. Hardware Components

- **Microcontroller:** ESP32-S3-ZERO
- **GPS Module:** Sparkfun Zoe-M8Q GPS Breakout
- **Power Source:** 3.7V Single-Cell LiPo Battery
- **Connecting Wires:** Jumper wires or a custom PCB.

## 4. Software & Development Environment

- **IDE:** Visual Studio Code with the PlatformIO extension.
- **Framework:** Arduino
- **Key Libraries:**
    - `SparkFun u-blox GNSS Arduino Library`
    - `ArduinoJson`
    - `ESPAsyncWebServer`

## 5. Flash Size and Build Configuration

The serial console showed: "Detected size(4096k) smaller than the size in the binary image header(8192k)." This indicates the firmware was built for 8MB flash while the board has 4MB.

Use the following PlatformIO configuration to target 4MB flash and DIO mode on ESP32-S3:

```
[env:esp32-s3]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino
board_build.flash_size = 4MB
board_build.flash_mode = dio
board_build.partitions = default.csv
board_upload.flash_size = 4MB
lib_deps =
    sparkfun/SparkFun u-blox GNSS Arduino Library@^2.2.15
    bblanchon/ArduinoJson@^6.21.3
    esphome/ESPAsyncWebServer-esphome@^3.1.0
monitor_speed = 115200
```

After updating, perform a full chip erase before uploading:

```
pio run -t erase
pio run -t upload
pio device monitor -b 115200
```

## 6. Wiring

| ESP32-S3-ZERO Pin | Zoe-M8Q Pin | Purpose     |
|-------------------|-------------|-------------|
| `GND`             | `GND`       | Common Ground |
| `3V3`             | `3V3`       | Power       |
| `SDA` (GPIO8)     | `SDA`       | I2C Data    |
| `SCL` (GPIO9)     | `SCL`       | I2C Clock   |

Note: Verify the I2C pins with your specific ESP32-S3 board's pinout diagram.

## 7. Setup and Usage

1. Clone the repository
2. Open with PlatformIO
3. Build and Upload
4. Connect to Wi-Fi `RocketTracker`
5. Navigate to `http://192.168.4.1`

The web page will display the current latitude, longitude, and number of visible satellites. The coordinates will update automatically every second.