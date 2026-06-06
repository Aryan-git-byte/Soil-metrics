# Soil Metrics ESP32-S3 Firmware

This folder is now an ESP-IDF project for the Soil Metrics ESP32-S3 board.

## Target

- MCU module: ESP32-S3-WROOM-1-N16R8
- Framework: ESP-IDF 5.5/5.6
- Display bus: 16-bit Intel 8080 parallel via `esp_lcd`
- UI: LVGL
- Touch: TSC2046/XPT2046-compatible resistive controller over SPI
- Soil sensor: Modbus RTU over MAX3485 RS485
- Storage: microSD over the shared touch/SD SPI bus
- Modem/GNSS: SIM7080G over UART

## Build

```powershell
idf.py set-target esp32s3
idf.py build
```

## Hardware Notes

The first implementation is written before hardware is available. Verify these items on the real board:

- LCD controller compatibility with the ILI9488 16-bit DBI Type B init table.
- `RD` is inactive/high for write-only display operation.
- LCD reset is actually tied to ESP `EN/RESET` and does not need a separate GPIO.
- Backlight is always on through the schematic resistor path.
- Touch calibration constants match the assembled display orientation.
- i80 pixel clock can be increased from the conservative 10 MHz default after stable output.
- The soil sensor Modbus map is taken from `R224073R224074-ZTS-3002-TR-N01.pdf`: address `1`, baud `4800`, 8 data bits, no parity, 1 stop bit, function `0x03`, registers `0x0000..0x0006` for moisture, temperature, conductivity, pH, nitrogen, phosphorus, potassium.
- The SIM7080G timing is taken from `SMM-SIM7080G-Hardware-Design-V1.04-DS-200525-TE.pdf`: `PWRKEY` is active low at the module pin, needs at least 1 s low to power on, UART is ready after at least 2.5 s, and AT UART defaults to auto-baud.
- The ILI9488 interface setup is taken from `ILI9488.pdf`: 16-bit DBI Type B uses IM pins `010`, RGB565 uses pixel format `0x55`, one 16-bit bus transfer sends one RGB565 pixel, and the init table uses the ILI9488 command parameter lengths for `B0`, `B6`, `B7`, `C0`, `C1`, `C5`, `E0`, and `E1`.
- The SIM7080 UART pin direction follows the schematic labels. If `AT` does not answer after PWRKEY is confirmed, swap `BOARD_SIM_TX` and `BOARD_SIM_RX` in `main/board_pins.h`.
- `GPIO0`, `GPIO3`, `GPIO45`, and `GPIO46` are ESP32-S3 strapping pins. Your schematic uses `GPIO3` for RS485 RX, `GPIO45` for SIM PWRKEY, and `GPIO46` for RS485 TX. Firmware follows the schematic, but the PCB must ensure these nets do not force bad boot strap levels.

## Datasheets Needed

Send these when you have them:

- TFT module vendor init table, if the bare ILI9488 sequence does not wake the specific display module.
- Any updated soil sensor manual if your shipped sensor differs from `ZTS-3002-TR-N01`.

## Pin Map

LCD data pins:

| LCD | ESP32-S3 |
| --- | --- |
| DB0 | GPIO4 |
| DB1 | GPIO5 |
| DB2 | GPIO6 |
| DB3 | GPIO7 |
| DB4 | GPIO8 |
| DB5 | GPIO9 |
| DB6 | GPIO10 |
| DB7 | GPIO11 |
| DB8 | GPIO12 |
| DB9 | GPIO13 |
| DB10 | GPIO14 |
| DB11 | GPIO15 |
| DB12 | GPIO16 |
| DB13 | GPIO17 |
| DB14 | GPIO18 |
| DB15 | GPIO21 |

LCD control pins:

| Signal | ESP32-S3 |
| --- | --- |
| WR | GPIO38 |
| RS/DC | GPIO39 |
| CS | GPIO40 |

Touch pins:

| Signal | ESP32-S3 |
| --- | --- |
| T_CS | GPIO1 |
| T_DIN/MOSI | GPIO42 |
| T_DOUT/MISO | GPIO47 |
| T_CLK/SCLK | GPIO48 |

Other peripherals:

| Signal | ESP32-S3 |
| --- | --- |
| SD_CS | GPIO41 |
| RS485_RX/RO | GPIO3 |
| RS485_DE_RE | GPIO2 |
| RS485_TX/DI | GPIO46 |
| SIM_TX | GPIO43 |
| SIM_RX | GPIO44 |
| SIM_PWRKEY | GPIO45 |

## Firmware Layout

- `main/display_i80.c`: custom i80 LCD init and LVGL flush path.
- `main/touch_tsc2046.c`: polling touch controller driver.
- `main/rs485_modbus.c`: small Modbus RTU master for RS485.
- `main/soil_sensor.c`: ZTS-3002-TR-N01 Modbus register decoding.
- `main/sd_storage.c`: optional SD card mount and CSV append.
- `main/sim7080.c`: SIM7080 UART and power-key bring-up.
- `main/ui.c`: LVGL diagnostics UI for display, touch, SD, modem, and soil readings.
