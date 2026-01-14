*This project has been created as part of the 42 curriculum by ncruz-ne.*

## Description

The goal is to build a small message-passing system where a client program sends a string to a server program, using only UNIX signals as the communication mechanism.
We could also call this a custom inter-process communication (IPC) protocol on top of UNIX signals.



## Instructions

1. Compile the project with `make` or `make all`.
2. Open 2 or more terminal windows at the root of the project folder.
3. From one window we'll start the server program: `./server`
4. In other windows we start the client program, adding the PID that was provided by `./server` and a message, as following: `./client server_PID "message"`
5. Confirm messages are received from different terminals.
6. Use `kill server_PID` at a client's terminal to end the program gracefully.

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
- 