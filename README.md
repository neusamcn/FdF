*This project has been created as part of the 42 curriculum by ncruz-ne.*

## Description

For this project, minilibX is used, which is a simple X-Window (X11R6) programming API in C, designed for students, suitable for X-beginners.

The X Window system (X11, or simply X) is a windowing system for bitmap displays, common on Unix-like operating systems.

X provides the basic framework for a GUI environment: drawing and moving windows on the displau device and interacting with a mouse and keyboard.



## Instructions

1. Compile the project with `make` or `make all`.
2. 

### Recommendations for testing:
- For a complete leak check and cleaner outputs:
	- Server:

		  valgrind --log-file=valg_server_log.log --leak-check=full --show-leak-kinds=all -s ./server

	- Client (for each message sent):
		
		  valgrind --log-file=valg_client_log.log --leak-check=full --show-leak-kinds=all -s ./client server_PID "message"

- To check the time it takes to display 100 characters (should be under 1 second):

	  time ./client server_PID "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 abcdefghijklmnopqrstuvwxyz 9876543210"

## Resources

AI was used as a support for research in order to find and better understand the most relevant resources and concepts related to this project.

#### Wireframe model

- https://en.wikipedia.org/wiki/Wire-frame_model
- https://mapsystemsindia.com/resources/what-is-3d-wireframe-modeling.html
- https://www.howengineeringworks.com/questions/what-is-wireframe-modeling-and-where-is-it-used/

### X-Window System

- https://en.wikipedia.org/wiki/X_Window_System

### minilibx-linux

- https://github.com/42Paris/minilibx-linux
- https://harm-smits.github.io/42docs/libs/minilibx.html

### Data alignment

- https://www.youtube.com/watch?v=iz958I8Xb2g

### Isometric Projection

-

### Bresenham's Line Generation Algorithm

- https://www.geeksforgeeks.org/dsa/bresenhams-line-generation-algorithm/

### perror()

- 

### strerror()

- 