# Ultrasonic-Obstacle-Detection-and-Visualization

## Overview

This project utilizes an Arduino with an ultrasonic sensor to measure the distance to obstacles. The data is transmitted to a QT program that visualizes the distance in real-time. If the distance is less than 10cm, the parking line changes color to red.

## 1. Arduino Code

Measures the distance to obstacles using an ultrasonic sensor and outputs the data to the serial monitor.

## 2. QT Visualization Program

Reads data from the serial port and displays the distance on the screen. If the distance is less than 10cm, the parking line turns red.
