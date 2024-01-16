# Final Project Proposal

## Group Members:

Simon Shkolnik

Benjamin Nudelman
       
# Intentions:

We intend to create a distributed computing tool to construct an video of zooming into a subportion of the Mandelbrot set as chosen by the user.
    
# Intended usage:

The user will have to choose coordinates to zoom into and zoom level for the computers to assemble a series of images, as well as other optional arguments such as max iteration count and coloring method. The user can then easily convert the series of images into a video with various tools such as FFmpeg.
  
# Technical Details:

Our project will be run by a main server computer which will create a TCP server and then SSH into every computer in the lab and have each computer run a "client" computing program that communicates with and is given instructions by the main server. Each client will be given a section of the set to compute, and output its image to a directory, taking advantage of Stuy's shared file system. For the program to work with non-connected computers, all that would need to be changed is that the client sends the image data to the server over the TCP connection.

## Topics used:

-sockets (for communication)

-allocating memory (likely for strings, communication)

-shared memory (client process is multithreaded, children all work on same shared memory)

-processes (fork to create children in client process to speed up computation, running SSH command)

-working with files (image output)

## Project Breakdown:

-obtaining user input for the desired portion of the Mandelbrot set (Simon)

-forking the children and allocating a specific portion of shared memory for each child (Ben)

-communication between the child and the lab machine (Ben)

-a function that calculates the data from the Mandelbrot set for a specific pixel (Simon)

-a function that writes to the proper data to the image file once the communication is complete (Simon)

-a script that logs us in and runs the executable file on each lab machine (Ben)
  
## Data structures / Algorithms:

-Shared memory - there will be one large continuous chunk of shared memory, and each of the client's threads will be given a section to compute

-Mandlebrot set - mandlebrot set will be computed via an escape-time algorithm and colored according to some kind of histogram

# Intended pacing:

Week of 1/5: shared memory allocation should be completed and the script for preparing all of the computers should be completed as well

Week of 1/12: communication should be set up and temporary user input should be set up in the first half of the week, and communication should be completed by the end of the week, as well as the function that calculates the data from the Mandelbrot set

End of week 1/12, weekend, and up to final deadline: proper means of obtaining user input should be set up (whether with python GUI or simple user input), and writing to the image file should be complete

Last few days: large scale testing, especially for edge cases (in terms of the graph), this still assumes plently of tests have been conducted along the way
