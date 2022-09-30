# Smart Camera Stand

This project aims to make a self-sufficient phone stand with it's own camera and microcontroller that can track a person and rotate the stand in 2-axes to follow the person primararily in frame. 

---

# Table of Contents:
* [About the project](#about-the-project)
    * [Tech Stack](#tech-stack)
    * [File Structure](#file-structure)
* [Getting Started](#getting-started)
    * [Prerequisites](#prerequisites)
    * [Installation](#installation)
    * [Execution](#execution)
* [Theory](#theory)
* [Approach](#approach)
* [Future Work](#future-work)
* [Contributors](#contributors)
* [Acknowledgements and Resources](#acknowledgements-and-resources)
* [License](#license)
---

# About The Project:
The smart camera stand is capable of following a person to keep him/her in the frame and hence giving freedom of movement to the user.

The picture quality is not compromised as the phone camera is used as the primary video recording device, while the camera built into the stand merely provides data to the microprocessor for tracking the person in frame.

### **Challenges:**

The microcontroller should be able to process a lightweight TinyML object classification/ object detection model that can track a person and rotate the stand in 2-axes in Real-time.

---

## Tech Stack:
* [TensorFLow](tensorflow.org)
* [Google Colab]()
* [Numpy]()
* [ESP32 microcontroller programming](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)
* [ESP32-CAM](https://github.com/espressif/esp32-camera) module Interfacing

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
* USB-to-TTL converter
* Mounts for the servo and camera 
* Hardware set-up and pinout-connections (refer to [ESP32_CAM_Pin_Connections.md](https://github.com/YatharthDedhia/Eklavya-Smart-Stand/blob/Yatharth-programs/ESP32_CAM_Pin_Connections.md))

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

---

# Theory
Image Classification refers to recognising the different classes present in a frame.

In this project, we use Image Classification to recognise whether a person is present in the frame or not, hence we will be using a Binary Classification model for the same.

For Dataset preparation instructions and further details refer to [Dataset_preparation.md](https://github.com/YatharthDedhia/Eklavya-Smart-Stand/blob/Yatharth-programs/CIFAR-100_Dataset/Dataset_preparation.md)

We use Object Detection models for localization of objects (humans in this case) and use other object tracking techniques to track the object through each frame in real-time.

---

# Approach
We first explored the domain of Deep-Learning and gained knowledge about:
* Logistic-Regression
* Neural Networks
* Convolutional Neural Networks

We also learned about many other Neural Network architectures like LeNet-5, AlexNet, VGG-16, ResNets, Inception Networks, MobileNet etc.

Based on this information, we selected EfficientNetLite0 for Image Classification.

For further model details Refer to [Model_selection.md]()

### Challenges:
* EfficientNetLite0 is a relatively small sized model specially designed for TinyML applications.
* But even after Quantizing the model, we were only able to bring its size down to 41MB due to lack of availability for Pruning on TFLite API.

Thus, we then decided to go forth with MobileNetV2 as the 2nd option, as it is even smaller than EfficientNetLite 0, but has slighly lower accuracy too.

MobileNetV2 being a Keras Model, supports both Pruning and Quantization with the TensorFlow API.

* After training MobileNetV2 on our dataset through Transfer-Learning and applying several optimizations like Pruning and Quantizations, we were able to bring its size down to 16MB.

This model is still too big to run on the 4MB RAM of the ESP32.

Finally, we used the [Object Detection model](https://github.com/espressif/esp-who) provided by Espressif which is especially optimised for ESP32 microcontroller.

This model outputs bounding box coordinates when a person is detected, along with the location of eyes,nose,mouth of the person.

Hence we now use this data to track the person in real time and rotate the camera using Servos in order to keep the person in frame at all times.

---

# Future Work
Implement 2-Axis Rotation and Tracking, and exploring various other Deep-Learning models and Object Tracking techniques to improve the accuracy and latency of the device.

---

# Contributors
* [Yatharth Dedhia](https://github.com/YatharthDedhia)
* [Medha Sati](https://github.com/MedhaSati2002)

---

# Acknowledgements and Resources
* [SRA-VJTI](https://github.com/SRA-VJTI) for providing great opportunity and guidance throughout this project
* [ESP-WHO](https://github.com/espressif/esp-who) Object Detection model for ESP32-CAM
* [TensorFlow](https://www.tensorflow.org/) Documentation and Examples
* [TensorFlow Lite](https://www.tensorflow.org/lite) Documentation and Examples
* [Deep Learning Courses](https://www.coursera.org/specializations/deep-learning)  on Coursera by Andrew NG
* [Espressif ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)

Special thanks to our Mentors : [Sarrah Bastawala](https://github.com/sarrah-basta), [Marck Koothoor]() and [Aniruddha Thakare]()
For providing constant guidance and support in this project.

---

# License