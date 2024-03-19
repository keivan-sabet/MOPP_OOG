# MOPP_OOG
To Run the code with the parallel implementation you need to be
able to use a gcc compiler with openMP and compile the file adv.c
From a terminal the following can be used to compile the code:
"gcc -fopenmp adv.c"

A brief description of each file is given below:

-init.csv
Holds input information for user to change before running the code.


-adv.c 
Main execution file



-constructors.c
Holds every constructor of the program.
Function names are organized and grouped based on the file where they appear.

-structures.c
Holds every structure used by the program.

-debug.c
Tools for debugging


-csv.c
Loads input csv file into the program. 


initializers.c
Turns input csv problem description into a graph model compatible with Dijkstra


-MOOP.c
High level Description of search techniques


-objectivecost.c
How the cost of a path is determined.


-printfunc.c
Functions to print data to either the terminal or to file.


-program.c
Miscellaneous functions


-rulebook.c
Rules for comparing different vectors and determining preference.




-dijkstra.c
An Implementation of Dijkstra's Algorithm mostly related to the creation of
outlook graphs


-finalsearch
Dijkstra search for vectors


-global.c
Contains all global variables


-freemem.c
Functions to free dynamically allocated memory locations


