# Model Rocket GPS Tracker with Web Interface

## 1. Objective

To develop a compact and efficient GPS tracking system for a model rocket using an ESP32-S3 Zero mini microcontroller and a Sparkfun Zoe-M8Q GPS board. The primary goal is to obtain GPS coordinates at ~1Hz and display them on a simple web page hosted by the ESP32-S3.

## 2. Key Requirements

- High-Frequency Updates (~1 Hz)
- Web-Based Display over Wi-Fi AP
- I2C Communication with Zoe-M8Q
- Robustness to temporary signal loss

## 3. Hardware Components

- Microcontroller: ESP32-S3-ZERO
- GPS Module: Sparkfun Zoe-M8Q GPS Breakout
- Power Source: 3.7V Single-Cell LiPo Battery

## 4. Software & Libraries

- Platform: PlatformIO (Arduino framework)
- Libraries: SparkFun u-blox GNSS, ArduinoJson, ESPAsyncWebServer

## 5. Build Configuration Notes

If you see this error in the serial console:

"Detected size(4096k) smaller than the size in the binary image header(8192k)."

configure PlatformIO for 4MB flash and DIO mode:

```
[env:esp32-s3]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino
board_build.flash_size = 4MB
board_build.flash_mode = dio
```

Then erase and upload:

```
pio run -t erase
pio run -t upload
```

## 6. Wiring

- GND ↔ GND
- 3V3 ↔ 3V3
- SDA (GPIO8) ↔ SDA
- SCL (GPIO9) ↔ SCL

## 7. Operation

- Device starts AP `RocketTracker`
- Browse to `http://192.168.4.1`
- JSON endpoint at `/data` updates once per second