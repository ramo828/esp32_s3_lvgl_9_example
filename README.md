# ESP32-S3 LVGL 9 Example

A clean and ready-to-use **LVGL 9** example for the **LCDWIKI ES3C28P / ES3N28P** (ESP32-S3 + 2.8" ILI9341V + FT6336G capacitive touch).

> **Important Note**  
> This repository is shared primarily as a **working configuration and hardware setup reference**.  
> The included UI (On/Off buttons) is **only a simple example** generated with SquareLine Studio.  
> You are expected to replace it with your own interface. The real value of this repo is the correct pin mapping, TFT_eSPI configuration, touch driver, and LVGL 9 integration.

---

## Features

- Fully working **LVGL 9.1.0** integration
- **TFT_eSPI** driver configured for ILI9341V (240×320 IPS)
- Custom **FT6336G** capacitive touch driver with rotation support
- SquareLine Studio generated UI (example only)
- Partial rendering buffer (low RAM usage)
- RGB565 color format with proper byte swapping
- Easy rotation switching (0–3)
- Clean separation between display, touch, and UI layers

---

## Hardware

| Component       | Details                              |
|-----------------|--------------------------------------|
| Board           | LCDWIKI ES3C28P / ES3N28P            |
| MCU             | ESP32-S3                             |
| Display         | 2.8" ILI9341V IPS (240 × 320)        |
| Touch Controller| FT6336G (I2C capacitive)             |
| Resolution      | 240 × 320                            |

### Pinout (ESP32-S3)

**Display (SPI - HSPI)**

| Signal | GPIO |
|--------|------|
| MOSI   | 11   |
| MISO   | 13   |
| SCLK   | 12   |
| CS     | 10   |
| DC     | 46   |
| RST    | -1 (shared with ESP32 reset) |
| BL     | 45   |

**Touch (I2C)**

| Signal | GPIO |
|--------|------|
| SDA    | 16   |
| SCL    | 15   |
| RST    | 18   |
| INT    | 17   |

---

## Requirements

### Arduino IDE / PlatformIO

1. **ESP32 Board Package**
   - Board: `ESP32S3 Dev Module` (or the correct variant for your board)
   - Recommended: Enable **USB CDC On Boot**

2. **Required Libraries**
   - [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
   - [lvgl](https://github.com/lvgl/lvgl) (version 9.x)

3. **TFT_eSPI Configuration**
   - Copy the content of `espi_tft/User_Setup.h` into the `User_Setup.h` file of your TFT_eSPI library  
     **or**
   - Replace the library’s `User_Setup.h` with the one provided in this repository.

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/ramo828/esp32_s3_lvgl_9_example.git
