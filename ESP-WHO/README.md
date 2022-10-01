# ESP-WHO

ESP-WHO is an image processing development platform based on Espressif chips. It contains development examples that may be applied in practical applications.

## Overview

ESP-WHO provides examples such as Human Face Detection, Human Face Recognition, Cat Face Detection, Gesture Recognition, etc. You can develop a variety of practical applications based on these examples. ESP-WHO runs on ESP-IDF. [ESP-DL](https://github.com/espressif/esp-dl) provides rich deep learning related interfaces for ESP-WHO, which can be implemented with various peripherals to realize many interesting applications.


## What You Need

### Hardware

We recommend novice developers to use the development boards designed by Espressif. The examples provided by ESP-WHO are developed based on the following Espressif development board, and the corresponding relationships between the development boards and SoC are shown in the table below.
    
|    SoC    | [ESP32](https://www.espressif.com/en/products/socs/esp32) | [ESP32-S2](https://www.espressif.com/en/products/socs/esp32-s2) | [ESP32-S3](https://www.espressif.com/en/products/socs/esp32-s3) |
| :------- | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| Development Board | [ESP-EYE](https://www.espressif.com/en/products/devkits/esp-eye/overview) | [ESP32-S2-Kaluga-1](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/hw-reference/esp32s2/user-guide-esp32-s2-kaluga-1-kit.html) | [ESP-S3-EYE](https://www.espressif.com/en/products/devkits/esp-s3-eye/overview) |

> Using a development board not mentioned in the table above, configure pins assigned to peripherals manually, such as camera, LCD, and buttons.

### Software

#### Get ESP-IDF

ESP-WHO runs on ESP-IDF. For details on getting ESP-IDF, please refer to [ESP-IDF Programming Guide](https://idf.espressif.com/).

> Please use the latest ESP-IDF on the [release/v4.4](https://github.com/espressif/esp-idf/tree/release/v4.4) branch.

#### Get ESP-WHO

Run the following commands in your terminal to download ESP-WHO:

```bash
git clone --recursive https://github.com/espressif/esp-who.git
```

> Remember to use ``git submodule update --recursive --init`` to pull and update submodules of ESP-WHO.

## Run Human Face Detection
To run human_face_detection, you only need to perform [Step 1: Set the target chip] (#Step-1 Set the target chip) and [Step 4: Launch and monitor] (#Step-4 Launch and monitor).

### Step 1: Set the target chip

Open the terminal and go to any folder that stores examples (e.g. examples/human_face_detection/lcd). Run the following command to set the target chip: 

```bash
idf.py set-target esp32
```

### Step 2: Launch and monitor

Flash the program and launch IDF Monitor:

```bash
idf.py flash monitor
```
