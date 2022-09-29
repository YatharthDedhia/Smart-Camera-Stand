# Smart Camera Stand

This project aims to make a self-sufficient phone stand with it's own camera and microcontroller that can track a person and rotate the stand in 2-axes to follow the person primararily in frame. 

#### **Mentors** : Sarrah, Marck, Aniruddha
#### **Mentees** : Medha Sati, Yatharth Dedhia

---

# Table of Contents:
* About the project
    * Tech Stack
    * File Structure
* Getting Started

---

# About The Project:
The smart camera stand is capable of following a person to keep him/her in the frame and hence giving freedom of movement to the user.

The picture quality is not compromised as the phone camera is used as the primary video recording device, while the camera built into the stand merely provides data to the microprocessor for tracking the person in frame.

### **Challenges:**

The microcontroller should be able to process a lightweight TinyML object classification/ object detection model that can track a person and rotate the stand in 2-axes in Real-time.

---

## Tech Stack:
* [TensorFLow](tensorflow.org)
* ESP-32 microcontroller programming
* Google Colab
* Python
* Numpy
* C/C++
---

# File Structure:

---

# Getting Started:
We use Google Colab for preparation of dataset and training our model as it provides additional GPU support to boost the computational power needed.

Additionally, Google Colab has TensorFLow environment setup by default, so we can use its environment without having to make many changes to the environment.

## Prerequisites:
Software:
* [ESP-IDF v4.4](https://github.com/espressif/esp-idf)

Hardware:
* ESP32-CAM module
* MG90 servo motor
* Mounts for the servo and camera 
* Hardware set-up and pinout-connections as shown here:
![Pinout connections]()

## Installation:
1. Clone the repo:
```
git clone https://github.com/YatharthDedhia/Eklavya-Smart-Stand
```
2. Install [ESP-IDF v4.4](https://github.com/espressif/esp-idf) and set it up on the system using the [Instructions](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/) provided by Espressif.

## Execution:
Open new terminal session in [ESP-WHO](https://github.com/YatharthDedhia/Eklavya-Smart-Stand/tree/Yatharth-programs/ESP-WHO) folder of the repo.

Run the following commands:

1. Setup ESP-IDF environment in current terminal session:
```
get_idf
```
2. Setup config files for the [ESP32-CAM](https://github.com/espressif/esp32-camera) module:
```
idf.py set-target esp32
```
3. Change current working directory:
```
cd ESP-WHO/examples/human_face_detection_terminal
```
4. Flash the code to ESP32-CAM and view the output in the terminal: 
```
idf.py -p (PORT) flash monitor
```

# Theory
For Dataset preparation instructions and details refer to [Dataset_preparation.md](https://github.com/YatharthDedhia/Eklavya-Smart-Stand/blob/Yatharth-programs/CIFAR-100_Dataset/Dataset_preparation.md)

For Model Details Refer to [Model_selection.md]()