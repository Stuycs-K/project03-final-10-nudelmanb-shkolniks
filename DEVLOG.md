# Dev Log:

## Ben

### 2024-01-04 - Connecting to Lab Machines
I have set up a temporary makefile and header file for the main file that will likely be run on marge. In this main.c file, I have created an error-handling function, a main-function with a test-call to connect_lab, and connect_lab, which is meant to ssh into a lab machine and perform preparatory tasks before the Mandelbrot data is sent. I have properly converted the function input of lab and machine numbers into IP addresses, converted the user name with the IP into an ssh input, and called execvp to ssh into the computer. In addition, I have performed tests along the way, some of which remains incomplete with regards to execvp allowing the user to type their password in for ssh. With testing, I have spent all of the class time and about 60 minutes at home.

### 2024-01-05 to 2024-01-07 - Forking and Running Code on Lab Machines
Ssh through execvp has now been completely set up. In class, due to difficulties with the ssh agent and ssh non-interactive mode, there were no commits done, rather testing and research to make it work by the end of the class. The stricthostkeychecking has been turned off to allow for immediate addition of the fingerprint to the known_hosts for each lab machine, and a temporary lab executable has been compiled to be ran via the arguments in the ssh. Forking has also been set up to actually connect to the corresponding lab machine for each child, and the running of the executable file has been tested as well. Due to potential issues with computers 15 and 31, the arbitrary number of lab machines has been limited to 14, until 15, 31, and other lab machines are "online" again. For this second part, including testing, 60 minutes has been spent at home.

### 2024-01-08 - Setting up Socket Between Child and Host
I made each child fork a second time so that the "second child" will run the ssh until it is done and the "regular child" will act as the main computer or server and communicate with the lab machine "client." I created all of the required functions for both the client and the server and added base code for communication after the connection is established. There is an issue with connection to the socket, and testing is in progress. The entire class time was spent and approximately 90 minutes both before and after class.

### 2024-01-09 - Adding Semaphores and Testing for 'Address already in use' error
Running the main executable produced no output originally despite the test print statements. Therefore, I added semaphore compatibility for each child to wait before the previous child finishes connecting to the network, and then they can all simulatenously send data across their corresponding network sockets. There still remains an 'address in use' error despite the socketopt function being called, and the output of the executable states that the err function is called in a certain instance where it is actually not. This issue is still being investigated. The total time spent was class time and an additional 90 minutes, and the error is yet to be resolved.

### 2024-01-09 - Reformatting and More Debugging
Along with Simon, the code was reformatted for improved readability and unnecessary components were eliminated. The lab executable was likely not being called, and this issue was fixed, and now there is more extensive debugging being done to attempt to revise a "cannot assign requested address" error. This work has taken all of class time and at least 90 minutes after class. Once this part is complete there is just the coding of the data to be sent across and the major parts of the project are complete.

## Simon

### 2024-01-02 - Brief description
Expanded description including how much time was spent on task.

### 2024-01-03 - Brief description
Expanded description including how much time was spent on task.
