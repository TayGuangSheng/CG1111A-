# The A-maze-ing Race Project 2023
## Introduction
In the first semester of Year 1, as part of the CG1111A module, our team undertook the mBot robot finale project known as "The A-maze-ing Race." The primary objective was to design and construct an mBot robot capable of efficiently navigating a maze within the shortest possible time.

The maze presented challenges in the form of colored tiles, indicating the next direction for the robot. These tiles came in various colors, namely red, orange, green, blue, and purple. Each color instructed the robot to perform a specific type of turn to successfully traverse the maze.

The maze featured walls that the robot had to avoid while moving towards the waypoint challenges, signified by black strips on the floor. These challenges required the robot to execute turns based on the color of the tile, adding complexity to the navigation process.

## Algorithm
![Algorithm](https://github.com/TayGuangSheng/CG1111A-mBot-Maze-Solver/blob/main/Report%20Images/Algorithm.png)

## Physical Appearance 
|![Left View](https://github.com/TayGuangSheng/CG1111A-mBot-Maze-Solver/blob/main/Report%20Images/Left%20View.png) Left View|![Right View](https://github.com/TayGuangSheng/CG1111A-mBot-Maze-Solver/blob/main/Report%20Images/Front%20View.png) Front View| 
|----------|----------|



## Hardware Set-up 
### Motor Connections
- M1: Left motor
- M2: Right motor

### mBot Sensor Connections 
- M1: Left motor
- M2: Right motor

### Arduino Component Connections
- A0: Light Dependent Resistor
- A1: Infrared Detector
- A2: 1A of 2-to-4 decoder
- A3: 1B of 2-to-4 decoder

## Calibration 
### PID 
In order to ensure the mBot travels in a straight line, we are required to use an Ultrasonic Sensor and an IR sensor to detect the distance the robot is from the wall to adjust the trajectory of the robot. However, to avoid the robot zig-zagging as it travelled, our group decided to adopt the PID function instead. Compared to using a nudge function that alters the path of the robot by a set amount, this algorithm reduces the magnitude of correction as the mBot gets closer to moving in a straight line. Thus, smoothing out the path of travel of the robot and fulfilling the requirements of the robot travelling as straight as possible.

### Colour Sensor 
All colours can be derived from a combination of the three primary colours, red, green and blue (RGB). Surfaces absorb and reflect different amounts of light from each of the three primary colours, and it is this combination of the reflected light that is perceived as different colours to our eyes. Utilising this concept with a Light-Dependent Resistor (LDR) in a potential divider circuit, and reading the output voltage, the values of reflected red, green, and blue light can be determined by sequentially activating the red, green, and blue Light Emitting Diodes (LED). The reflected colour can then be calculated.
