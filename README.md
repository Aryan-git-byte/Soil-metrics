<div align="center">

<h1>SoilMetrics</h1>

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
![Platform](https://img.shields.io/badge/Platform-ESP32--S3-black)
![Kicad](https://img.shields.io/badge/KiCad-10-blue)

<img src="assets/zine.png" alt="zine" width="400">

<h4><i>A Portable AI & IoT-Based Soil Health Monitoring Device</i></h4>

</div>

---

# Overview:

SoilMetrics is an **affordable soil health monitoring system** to measure key soil parameters in real time including **NPK, EC, pH, Moisture, and Temperature.** Which can empower small and marginal farmers to make **informed decisions** for improved crop management and sustainable agriculture.

## Features:

- Measure soil moisture, temeperature, pH, electrical conductivity, and NPK.
- Remote connectivity via LTE using SIM7080G module.
- Touch Based Interface to view sensor readings, AI recommedations, weather reports.
- Offline Data Logging in a onboard SD card.
- GPS connectivity for accurate weather reports via openweather API.
- on device rechargeable batteries (2S 18650) for portability.

## Hardware Specifications:

- **MCU** - [ESP32-S3-WROOM1U-N16R8](https://documentation.espressif.com/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf)
- **Cellular & GPS** - [SIM7080G](https://www.simcom.com/product/SIM7080G.html)
- **Soil Sensor** - [ZTS-3002-TR-\*-N01](https://robu-prod-media.s3.ap-south-1.amazonaws.com/uploads/2025/04/R224073R224074-ZTS-3002-TR-N01.pdf)
- **Display** - [SmartElex 3.5" TFT Resistive Touch Display 320x480](https://robu.in/product/smartelex-3-5-tft-resistive-touch-display-320x480/)

## Repo Structure:

```
SoilMetrics/
│
├── assets/   images
├── cad/       CAD source files & exports
├── firmware/       ESP-IDF firmware
├── kicad/          kicad source file
├── production/     BOM & gerber
│
├── README.md
├── LICENSE
└── JOURNAL.md
```

---

# Hardware:

## Schematic:

![Page-01-Schematic](assets/page_001.png)
> This page has all the power realted things of the device including Type-c for programming, barrel jack for charging, BMS circuitory, Buck Converter and LDOs

![Page-02-Schematic](assets/page_002.png)
> This page has MCU, Buttons, LTE module, Receiver, SD card, sim slot etc

## PCB:

It is a 4 layer PCB board which you can checkout [here](kicad/)