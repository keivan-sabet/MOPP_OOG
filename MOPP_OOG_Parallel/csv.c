//load csv file into the program
struct ListD * initializeProgram(char * ip)
{
	//Loop variables
	int count = 0;
	int counter = 0;
	
	//Input file variables
	FILE *input = NULL;		//input file
	char hold[10000];		//Read line of csv file
	char *token = NULL;		//tokenize line
	char s[] = ",\n\t\r";	//token symbols
	
	//A list of objective cost maps
	struct ListD *atr;
	
	//Used to find
	struct ListD *temp;
	
	//Number of objectives
	int accum = 0;
	
	printf("File:%s\n",ip);
	
	atr = xmalloc(sizeof(struct ListD),2);
	
	
		input = fopen(ip,"r");    //Open file
		if (input==NULL)            //Check for any problems opening file
		{  
			printf("Error: file does not exist\n");
			return NULL;
		}
		//input operations
		while(fgets(hold,1000,input))
		{
			token = strtok(hold,s);
			
			if (!strcmp(token,"start"))
			{
				fgets(hold,1000,input);
				token = strtok(hold,s);
				start[0] = atoi(token);
				token = strtok(NULL,s);
				start[1] = atoi(token);
				printf("Start:[%d,%d]\n",start[0],start[1]);
			}
			else if (!strcmp(token,"Goal"))
			{
				fgets(hold,1000,input);
				token = strtok(hold,s);
				end[0] = atoi(token);
				token = strtok(NULL,s);
				end[1] = atoi(token);
				printf("Goal:[%d,%d]\n",end[0],end[1]);
			}
			else if (!strcmp(token,"RowCol"))
			{
				fgets(hold,1000,input);
				token = strtok(hold,s);
				row = atoi(token);
				token = strtok(NULL,s);
				col = atoi(token);
				printf("Rows:%d\nCols:%d\n",row,col);
			}
			else if (!strcmp(token,"Objectives"))
			{
				fgets(hold,1000,input);
				token = strtok(hold,s);
				nobj = atoi(token);
				printf("Objectives:%d\n",nobj);
			}
			else if (!strcmp(token,"obstacle"))
			{
				temp = atr;
				for(count = 0; count < accum; count++)
				{
					temp = temp->tail;
				}
				temp->tail = xmalloc(sizeof(struct ListD),3);
				temp->tail->tail = NULL;
				temp->V = xmalloc(sizeof(double*) * row,4);
				for(count = 0; count < row; count++)
					temp->V[count] = (double*)xmalloc(sizeof(double) * col,5);
				
				fgets(hold,1000,input);
				token = strtok(hold,s);
				count = row-1;
				counter = 0;
				while(strcmp(token,"obstacle"))
				{
					while(token != NULL)
					{
						temp->V[count][counter] = atof(token);
						token = strtok(NULL,s);
						counter++;
					}
					counter = 0;
					fgets(hold,1000,input);
					count--;
					token = strtok(hold,s);
				}
				accum++;
			}
			else if (!strcmp(token,"comfort"))
			{
				temp = atr;
				for(count = 0; count < accum; count++)
				{
					temp = temp->tail;
				}
				temp->tail = xmalloc(sizeof(struct ListD),6);
				temp->tail->tail = NULL;
				temp->V = xmalloc(sizeof(double*) * row,7);
				for(count = 0; count < row; count++)
					temp->V[count] = (double*)xmalloc(sizeof(double) * col,8);
				
				fgets(hold,1000,input);
				token = strtok(hold,s);
				count = row-1;
				counter = 0;
				while(strcmp(token,"comfort"))
				{
					while(token != NULL)
					{
						temp->V[count][counter] = atof(token);
						token = strtok(NULL,s);
						counter++;
					}
					counter = 0;
					fgets(hold,1000,input);
					count--;
					token = strtok(hold,s);
				}
				accum++;
			}
			else if (!strcmp(token,"Rulebook"))
				break;
			
		}
		temp = atr;
		fclose(input);
	if(row == 0 || col == 0 || nobj == 0)
		printf("An error has occured in initialized. row, col, nobj have not been initialized\n");
	
	return atr;
}


void readcsv(struct mvar *mn)
{
	char hold[10000];		//Read line of csv file
	char *token = NULL;		//tokenize line
	char s[] = ",\n\t\r";	//token symbols
	
	mn->init = NULL;
	mn->init = fopen("init.csv","r");
	if(mn->init == NULL)
	{
		printf("Error occured when attempting to open init.csv file\n");
		exit(1);
	}
	
	fgets(hold,1000,mn->init);
	token = strtok(hold,s);
	sprintf(mn->folder, "%s", token);
	
	fgets(hold,1000,mn->init);
	token = strtok(hold,s);
	sprintf(mn->file2, "%s", token);
	
	fgets(hold,1000,mn->init);
	token = strtok(hold,s);
	sprintf(mn->folder2, "%s", token);
	
	fgets(hold,1000,mn->init);
	token = strtok(hold,s);
	mn->csvcounter = atoi(token);
	
	fclose(mn->init);
}