# Smart BeeHouse

ESP32-based IoT monitor for beehive conditions. The board runs as a Wi-Fi access point, connects to a sensor station over TCP, and serves a live dashboard on a local web page.

## What it does

- Creates a Wi-Fi access point (`Esp_Server` / `12345678`)
- Connects to a sensor station at `192.168.1.120:8088` over TCP
- Parses incoming sensor data (hive number, IP, temperature, humidity, weight, food status, health status)
- Serves an HTTP dashboard at `192.168.1.128` with auto-refresh

## Hardware

- ESP32 board
- Sensors on the station side (temperature, humidity, weight)

## Setup

1. Open `AP [updated].ino` in Arduino IDE
2. Install the ESP32 board package
3. Adjust SSID/password and server IP if needed
4. Upload to the ESP32

## Network

```
Station (sensors) --TCP:8088--> ESP32 AP (this code) --HTTP:80--> Browser
```
