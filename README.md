# HuskyLens AI Vision and Sensor Applications

A collection of Arduino-based applications exploring AI-assisted machine vision with **DFRobot HUSKYLENS**, I2C communication, servo control, LEDs, and environmental sensors.

These projects were developed as part of the **Smart Engineering Robotics** course offered through the **Engineers Syndicate**. The work focuses on practical robotics, hardware integration, and embedded-system programming.

## Project Overview

The repository contains three Arduino sketches and a project photo. Each sketch demonstrates a different stage of working with HUSKYLENS and integrating its visual recognition output with external hardware.

- Read HUSKYLENS recognition results over I2C.
- Print detected block or arrow information to the Serial Monitor.
- Control LEDs according to learned object IDs.
- Move a servo to scan the camera's field of view.
- Use object detection as a trigger for reading a DHT22 temperature/humidity sensor and a flame sensor.

## Repository Structure

```text
HuskyLens/
├── HUSKYLENS_I2C.ino
├── camera_husky_camera.ino
├── camerahuskyservosensors.ino
└── photo_2026-10-23_11-20-41.jpg
```

## Hardware Components

The sketches and project image indicate the use of the following components:

- Arduino-compatible microcontroller board
- DFRobot HUSKYLENS AI vision sensor
- Servo motor for camera scanning
- LEDs
- DHT22 temperature and humidity sensor
- Flame sensor
- Breadboard and jumper wires
- USB cable for programming and Serial Monitor communication

The DHT22, flame sensor, and servo are used by the integrated sensor-and-scanning sketch. Individual components may not be required for every example.

## Software and Libraries

- Arduino IDE
- HUSKYLENS Arduino library
- Wire library for I2C communication
- Servo library
- DHT sensor library
- Serial Monitor for status messages and sensor readings

## Applications and Sketches

### 1. HUSKYLENS I2C Communication

**File:** `HUSKYLENS_I2C.ino`

This sketch demonstrates the basic communication workflow between Arduino and HUSKYLENS using I2C.

Main functions:

- Starts serial communication at 115200 baud.
- Initializes the I2C interface using `Wire.begin()`.
- Attempts to connect to HUSKYLENS and reports connection/setup problems.
- Requests recognition data from the sensor.
- Checks whether the sensor has learned an object and whether results are available.
- Reads and prints recognition results to the Serial Monitor.
- Reports block coordinates, dimensions, and ID values.
- Reports arrow origin, target coordinates, and ID values when an arrow result is returned.

This example is useful for checking sensor communication and understanding the structure of HUSKYLENS recognition results.

### 2. Object ID Detection and LED Control

**File:** `camera_husky_camera.ino`

This sketch links object recognition to simple digital outputs.

Main functions:

- Initializes HUSKYLENS over I2C.
- Configures digital pins 8 and 9 as LED outputs.
- Requests recognition data continuously.
- Prints each detected result ID to the Serial Monitor.
- Turns LED 1 on when ID 1 is detected.
- Turns LED 2 on when ID 2 is detected.
- Turns both LEDs off at the start of each loop, then activates the output corresponding to any matching IDs in the current results.

This demonstrates a basic vision-to-action workflow: the camera's learned object ID determines the state of an external output.

**Important:** The HUSKYLENS must be configured to use I2C, and the relevant objects must be learned on the sensor with the IDs expected by the sketch.

### 3. Servo Scanning with Object Detection and Sensor Readings

**File:** `camerahuskyservosensors.ino`

This sketch combines HUSKYLENS recognition with a servo, a DHT22 sensor, and a flame sensor.

The intended workflow is:

1. Initialize serial communication, I2C, the servo, DHT22, and flame sensor.
2. Connect to HUSKYLENS.
3. Request recognition results.
4. Continue sweeping the servo between 0 and 180 degrees while the target ID is not detected.
5. When target ID 1 is detected, stop the scanning behavior at the current servo angle.
6. Read temperature and humidity from the DHT22.
7. Read the flame sensor's digital output.
8. Print the sensor readings and flame status to the Serial Monitor every two seconds.

The sketch uses the following key configuration:

- Servo signal pin: 6
- DHT22 data pin: 7
- Flame sensor digital pin: 4
- Target HUSKYLENS ID: 1
- Servo scan step: 2 degrees

The flame sensor logic in the sketch treats a LOW digital reading as flame detected. Confirm that this matches the specific sensor module being used, since module output behavior can vary.

**Code note:** Review and compile this sketch in the Arduino IDE before running it. The uploaded source contains malformed text in several places, so those fragments may need to be removed or corrected before the sketch will compile.

## System Workflow

```text
HUSKYLENS AI Vision
        |
        | I2C recognition results
        v
Arduino Microcontroller
        |
        +--> Object ID 1 --> LED output
        |
        +--> Object ID 2 --> LED output
        |
        +--> Target ID 1 --> Stop servo scanning
                                |
                                +--> Read DHT22
                                |
                                +--> Read flame sensor
                                |
                                +--> Print status to Serial Monitor
```

The first two sketches demonstrate the I2C and LED-control stages independently. The third sketch explores combining recognition, servo movement, and sensor readings.

## Setup and Usage

### 1. Install the Libraries

In the Arduino IDE Library Manager, install the HUSKYLENS library and the DHT sensor library. The Wire and Servo libraries are available for common Arduino-compatible boards supported by the IDE.

### 2. Configure HUSKYLENS

- Set the HUSKYLENS protocol to **I2C** in the sensor's settings.
- Connect the sensor's I2C lines to the matching SDA and SCL pins of the selected board.
- Learn the objects on the HUSKYLENS and confirm their IDs.
- Check power and ground connections before running the sketches.

### 3. Upload a Sketch

Open one of the `.ino` files in Arduino IDE, select the correct board and port, and upload it. For `camerahuskyservosensors.ino`, inspect and correct the malformed source text first.

### 4. Inspect Serial Output

Open the Serial Monitor at the baud rate configured in the sketch:

- `HUSKYLENS_I2C.ino`: **115200 baud**
- `camera_husky_camera.ino`: **9600 baud**
- `camerahuskyservosensors.ino`: **9600 baud**

The Serial Monitor displays connection status, detected IDs, recognition coordinates, and sensor readings, depending on the sketch.

## Safety and Integration Notes

- Verify the board's operating voltage and the sensor's voltage requirements before wiring.
- Connect all required grounds together when using a separate power supply.
- Do not power a servo from a microcontroller's 5 V pin if the servo current exceeds what the board can safely supply; use a suitable external supply when needed.
- Check pin assignments against the actual wiring before powering the circuit.
- Confirm the flame sensor's active output level for the specific module.
- Test recognition and each output separately before integrating all components.
- Treat flame sensing in this project as an educational demonstration, not as a certified fire-detection or safety system.

## Concepts Practiced

- AI-assisted machine vision
- HUSKYLENS object learning and ID-based recognition
- I2C communication
- Arduino digital input/output
- LED control based on recognition results
- Servo positioning and scanning
- Temperature and humidity sensing
- Flame sensor integration
- Serial debugging
- Combining sensing, recognition, and physical outputs

## Project Context

This work was completed as part of the **Smart Engineering Robotics** course at the **Engineers Syndicate**. The repository documents the practical Arduino sketches and hardware applications explored during the course.

## Author

**Menna Hany Abdelaziz**

GitHub: [mennnaaaaa](https://github.com/mennnaaaaa)
