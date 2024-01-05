# Dev Log:

## Ben

### 2024-01-04 - Connecting to Lab Machines
I have set up a temporary makefile and header file for the main file that will likely be run on marge. In this main.c file, I have created an error-handling function, a main-function with a test-call to connect_lab, and connect_lab, which is meant to ssh into a lab machine and perform preparatory tasks before the Mandelbrot data is sent. I have properly converted the function input of lab and machine numbers into IP addresses, converted the user name with the IP into an ssh input, and called execvp to ssh into the computer. In addition, I have performed tests along the way, some of which remains incomplete with regards to execvp allowing the user to type their password in for ssh. With testing, I have spent all of the class time and about 60 minutes at home.

## Simon

### 2024-01-02 - Brief description
Expanded description including how much time was spent on task.

### 2024-01-03 - Brief description
Expanded description including how much time was spent on task.
