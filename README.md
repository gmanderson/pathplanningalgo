# Path Planning Algorithm
University assignment for a simplified algorithm for path planning to move a simulated 2D robot around a room.

A 2D environment represented by ASCII characters, provides a maze for a robot to navigate from the start (S) to the goal point (G). = symbols represent walls blocking the robot while . symbols represent open space the robot may use to reach the goal. 

The forward search algorithm was implemented from provided psuedocode and the path solution is printed so it may be compared to an expected output. An input environment of 20x20 cells is provided to the program upon running.


To compile:

`g++ -Wall -Werror -std=c++14 -O -o pathplanalgo Node.cpp NodeList.cpp PathSolver.cpp main.cpp`

To run:

`./assign1 < ./tests/testname.env`

This will print the maze to the terminal.

Alternatively:

`./assign1 < ./tests/testname.env > actual.out`

This will output the terminal to a file where it can be inspected, or the diff command can be run to compare output versus expected output.

`diff actual.out ./tests/testname.out`
