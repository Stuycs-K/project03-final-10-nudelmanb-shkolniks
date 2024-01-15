[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# Multi-Computer Mandelbrot Visualizer

### The Mandelbros

Simon Shkolnik

Benjamin Nudelman
       
### Project Description:

This project attempts to create a faster method for computing and visualizing the MandelBrot set by splitting up the computation amongst all the computers in our CS lab. Our main computer (likely marge), forks enough pairs of children such that one child uses ssh to log into its corresponding lab machine number and the other child sets up a server for the lab machine to connect to. Once that is done, the lab machine can send over pixel colors to the main computer to construct an image file of the Mandelbrot set.
  
### Instructions:

How does the user install/compile/run the program.

make compile is used to compile the program


How does the user interact with this program?
