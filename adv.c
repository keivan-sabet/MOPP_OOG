#define BILLION  1000000000.0 //used for runtime calculation

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h> 
#include <omp.h>
#include "structures.c"		//Holds the structures used in the program
#include "constructors.c"	//Holds the constructors for all functions in the program
#include "global.c"		  	//Holds all global variables
#include "dijkstra.c"		//Holds Dijkstra's Algorithm
#include "rulebook.c"		//A rulebook to determine the cost of a vector
#include "objectivecost.c"	//Holds the logic for how to determine the cost of an action for objectives
#include "finalsearch.c"	//Holds the implementation of Dijkstra's Algorithm for the Optimistic Outlook Graph
#include "csv.c"			//Handles loading csv input files
#include "program.c"
#include "freemem.c"		//Handles freeing dynamically allocated memory
#include "printfunc.c"		//Provides file and terminal output functions
#include "debug.c"
#include "initializers.c"	//Provides functions to initialize the program
#include "MOOP.c"


//Initialize and Run Algorithim
int main()
{
	struct mvar main_variables;
	struct mvar* mn = &main_variables;
	
	initializeMain(mn);//handles initialization of main function
	
	//while file exists
	while(mn->atr != NULL)
	{
		initializeSearch(mn); //Initialize forward and backward dijkstra environments with problem instance from file
		
		//executeProgram(mn);//run instance with desired algorithm and clock the runtime
		//executeProgramMVP(mn);
		executeProgramDstra(mn);
		
		outputHandler(mn);//Provides output information from instance to terminal and file
		
		//closeInstance(mn);//Remove instance from program (close files, free dynamic mem)
		//closeInstanceMVP(mn);
		closeInstanceDstra(mn);
		
		//debugCheck(); //check if dynamically allocated memory is deallocated properly
		loadNext(mn); //Load and initialize the next file
	}
	wrapup(mn);//close and clear files and memory before program exits
	return 0;
}

void executeProgram(struct mvar* mn)
{
	clock_gettime(CLOCK_REALTIME, &mn->timestart);//Begin clock time
	OOG(mn);//For each objective run forward and backward dijkstra merge results and search outlook maps
	clock_gettime(CLOCK_REALTIME, &mn->timeend);//Stop clock time
	//Algorithm Finished
	calculateRuntime(mn);//Calculate runtime
}

void executeProgramMVP(struct mvar* mn)
{
	clock_gettime(CLOCK_REALTIME, &mn->timestart);//Begin clock time
	MVP(mn);
	clock_gettime(CLOCK_REALTIME, &mn->timeend);//Stop clock time
	//Algorithm Finished
	calculateRuntime(mn);//Calculate runtime
}

void executeProgramDstra(struct mvar* mn)
{
	clock_gettime(CLOCK_REALTIME, &mn->timestart);//Begin clock time
	Dstra(mn);
	clock_gettime(CLOCK_REALTIME, &mn->timeend);//Stop clock time
	//Algorithm Finished
	calculateRuntime(mn);//Calculate runtime
}


void calculateRuntime(struct mvar* mn)
{
	mn->time_spent = ((mn->timeend.tv_sec - mn->timestart.tv_sec) + (mn->timeend.tv_nsec - mn->timestart.tv_nsec) / BILLION);
	printf("The elapsed time is %f seconds\n", mn->time_spent);//Output algorithm runtime
	fprintf(mn->output,"%f\n",mn->time_spent);
}

void outputHandler(struct mvar* mn)
{
	extractSolution(mn); //Extract Solution and its cost
	fprintSolutionPath(mn);
	fprintSolutionCost(mn);
	printSolutionPath(mn);
	//printSolutionCost(mn); //print solution cost
}

void closeInstance(struct mvar* mn)
{
	freeMemory(mn); //Free dynamically allocated memory
	fclose(mn->outputind);
	fclose(mn->output);
}

void closeInstanceMVP(struct mvar* mn)
{
	freeMemoryMVP(mn); //Free dynamically allocated memory
	fclose(mn->outputind);
}

void closeInstanceDstra(struct mvar* mn)
{
	freeMemoryDstra(mn); //Free dynamically allocated memory
	fclose(mn->outputind);
}

void loadNext(struct mvar* mn)
{
	mn->csvcounter++;
	sprintf(mn->file, "%s%d.csv",mn->folder,mn->csvcounter);//Starting file name
	mn->atr = initializeProgram(mn->file);
	mn->numobj = nobj;
	
	sprintf(mn->file3, "%s%d.csv",mn->folder2,mn->csvcounter);//Starting file name
	mn->outputind = fopen(mn->file3,"w");
	if(mn->atr != NULL)
	{
		if(mn->outputind == NULL)
		{
			printf("Error occured when attempting to open output file\n");
			exit(1);
		}
	}
	mn->output = fopen(mn->file2,"a");
	if(mn->output == NULL)
	{
		printf("Error occured when attempting to open output file\n");
		exit(1);
	}
}

void wrapup(struct mvar *mn)
{
	fclose(mn->output);
}
