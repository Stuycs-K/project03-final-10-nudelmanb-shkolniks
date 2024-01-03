# Final Project Proposal

## Group Members:

Simon Shkolnik
Benjamin Nudelmawn
       
# Intentions:

We intend to create a distributed computing tool to construct an image of a subportion of the Mandelbrot set (the portion chosen by the user).
    
# Intended usage:

The user will either have to choose minimum and maximum x and y coordinates for the computers to assemble the graph of, or, if time persists, a GUI tool may be created for the user to choose a specific portion of the set.
  
# Technical Details:

Our project will be run by a main, server-like computer, that forks approximately 35 children (the number of computers in our classroom), each of which will have access to shared memory and will be designated a portion of that shared memory (which represents a portion of the final image output). Through sockets, the children will communicate with their corresponding computer, which should have, through a separate script, been logged into and contain an executable file for facilitating this communication. Each lab machine will send data back to the child containing numbers that represent different colors for an image. Once all the colors for the corresponding pixels are sent to the child, and all of the children have recieved their data, the parent can write the complete shared memory to an image file that can be opened by any image application by the user.

## Topics used:

-sockets (for communication)
-allocating memory (likely for strings, communication)
-shared memory (between all the children that communicate with the computers)
-processes (fork to create children)
-working with files (potentially will be in a script to download an executable file from github on the lab machines)
-semaphores (may be used to allow only a certain number of editors to the shared memory at a time)
-signals (for error handling, potentially to end the program if we choose to make the program constantly update the image file)

## Project Breakdown:

-obtaining user input for the desired portion of the Mandelbrot set (Simon)
-forking the children and allocating a specific portion of shared memory for each child (Ben)
-communication between the child and the lab machine (Ben)
-a function that calculates the data from the Mandelbrot set for a specific pixel (Simon)
-a function that writes to the proper data to the image file once the communication is complete (Ben)
-a script that logs us in and downloads the executable file on each lab machine (Simon)
  
## Data structures / Algorithms:

-structs (for setting up the sockets, potentially for working with files)
-ints and/or chars (for pixel data)
-char* (for user input)
-union (for semaphores)

-bind, socket, listen, accept, connect (for sockets and communication)
-open, read, write, close (for writing to image file and writing to shared memory)
-shmget, shmdt, shmat, shmctl (for shared memory)
-semget, semctl, semop (for semaphores)
-printf, malloc (for debugging and using char pointers)
-fgets, sscanf (for user input)
-fork (for creating child processes)
    
# Intended pacing:

Week of 1/5: shared memory allocation should be completed and the script for preparing all of the computers should be completed as well
Week of 1/12: communication should be set up and temprary user input should be set up in the first half of the week, and communication should be completed by the end of the week, as well as the function that calculates the data from the Mandelbrot set
End of week 1/12, weekend, and up to final deadline: proper means of obtaining user input should be set up (whether with python GUI or simple user input), and writing to the image file should be complete
Last few days: large scale testing, especially for edge cases (in terms of the graph), this still assumes plently of tests have been conducted along the way