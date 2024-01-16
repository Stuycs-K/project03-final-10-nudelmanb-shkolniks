[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# Multi-Computer Mandelbrot Renderer

### The Mandelbros

Simon Shkolnik
       
### Project Description:

The user will be able to quickly create a "zoom" of the mandlebrot set by distributing the workload to all computers in the CS lab.

### Instructions:

Both the main and client excecutables will be compiled with `make compile` and can be ran with `make main` and `make compute` respectively, though the compute program is not meant to be run by the user.

The user runs the program by running `make main` and passing the desired location and zoom depth as command line arguments, as well as other options such as iteration count, the amount to zoom in by each frame, etc.

### Libraries Used:

* GNU MP - Library for multiprecision float arithmetic and arbitrary sized integers. Seperate installation required, compile final executable with `-lgmp` flag in GCC.

* libattopng - Easiest library for writing PNGs that I could find. Only one .c and .h file, to compile just compile the library source into a .o file and link.