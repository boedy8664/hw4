# hw4
# Eqipment
PC or notebook B_L4S5I_IOT01A XBee chips PING Encoder Boe Bot Car OpenMV H7 Plus board

# Development
C++

# Discription 
#XBee Controlled BB Car

PC/Python sends a RPC command though XBee (with position parameters) to reverse park a BB car.

The BB Car will park automatically according to the position parameters.

BB car could start at different initial positions. For example, in the following figure, we have set the BB car at (d1, d2, west) position. This parameter will be sent from PC to mbed for the reverse parking.

reverse parking

#Line Following BB Car

We can use this part to steer the BB car to follow a straight line.

Use OpenMV to detect a straight line (printed on a paper). Send the parameters of the detected line (end points of lines as x1, y1, x2, y2) to mbed through UART connections. Steer BB car to go forward and follow the line.

#BB Car Position Calibration

We can use this part to identify the location of the BB car with respect to a surface (with an AprilTag).

Print or show an AprilTag (from mbed lab 14).

Use OpenMV to scan the above AprilTag codes. We can use the scanned AprilTag to determine the viewing angle from OpenMV to the AprilTag surface.

And steer BB Car such that the car is facing directly and perpendicular to the AprilTag surface.

Also use PING to measure the distance between BB Car and AprilTag surface.
