# Final Project Proposal

## Group Members:

Simon Shkolnik

Benjamin Nudelman
       
# Intentions:

We intend to create a distributed computing tool to construct an image of a subportion of the Mandelbrot set (the portion chosen by the user).
    
# Intended usage:

The user will have to choose minimum and maximum x and y coordinates for the computers to assemble the graph, as well as other optional arguments such as max iteration count and coloring method.
  
# Technical Details:

Our project will be run by a main server computer, that will SSH into every computer in the lab and have each computer run a "client" computing program that communicates with and is given instructions by the main server. Each client will be given a section of the image to compute, and send its results back to the main computer, where it will be reconstructed and outputed to an image file. Ideally, the server program won't be run for every image output as there is a large amount of overhead, and the user will be able to continuously enter new coordinates to render.

## Topics used:

-sockets (for communication)

-allocating memory (likely for strings, communication)

-shared memory (between all the children that communicate with each client socket)

-processes (fork to create children)

-working with files (image output, potentially will be in a script to download an executable file from github on the lab machines)

-semaphores (will be used to determine when all clients are done computing)

-signals (for error handling, potentially to end the program if we choose to make the program constantly update the image file)

## Project Breakdown:

-obtaining user input for the desired portion of the Mandelbrot set (Simon)

-forking the children and allocating a specific portion of shared memory for each child (Ben)

-communication between the child and the lab machine (Ben)

-a function that calculates the data from the Mandelbrot set for a specific pixel (Simon)

-a function that writes to the proper data to the image file once the communication is complete (Ben)

-a script that logs us in and downloads the executable file on each lab machine (Simon)
  
## Data structures / Algorithms:

-Shared memory - there will be one large continuous chunk of shared memory, and each client will be given a section to compute

-Mandlebrot set - mandlebrot set will be computed via an escape-time algorithm and colored according to some kind of histogram

# Intended pacing:

Week of 1/5: shared memory allocation should be completed and the script for preparing all of the computers should be completed as well

Week of 1/12: communication should be set up and temporary user input should be set up in the first half of the week, and communication should be completed by the end of the week, as well as the function that calculates the data from the Mandelbrot set

End of week 1/12, weekend, and up to final deadline: proper means of obtaining user input should be set up (whether with python GUI or simple user input), and writing to the image file should be complete

Last few days: large scale testing, especially for edge cases (in terms of the graph), this still assumes plently of tests have been conducted along the way
