# Ultrasonic-Obstacle-Detection-and-Visualization

## Overview

This project utilizes two Arduino boards with an ultrasonic sensor to measure the distance to obstacles. One Arduino sends the distance data via CAN communication, while the other Arduino receives this CAN data and outputs it to the serial monitor. The data is then transmitted to a QT program that visualizes the distance in real-time. If the distance is less than 10cm, the parking line changes color to red.

## 1. Arduino Code

Sender Arduino: Measures the distance to obstacles using an ultrasonic sensor and sends the data via CAN communication.

Receiver Arduino: Receives CAN data and outputs the distance to the serial monitor.

## 2. QT Visualization Program

Reads data from the serial port and displays the distance on the screen. If the distance is less than 10cm, the parking line turns red.

important : Ensure to set the correct PortName and SerialPort BaudRate in mainwindow.cpp for proper serial communication.

