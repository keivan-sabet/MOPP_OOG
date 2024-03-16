void fprintSolutionCost(struct mvar* mn)
{
	for(int count = 0; count < mn->numobj; count++)
	{
		if(count == mn->numobj - 1)
			mn->vector[count] +=mn->DF[0]->Map[count][mn->DB[0]->XI[0]*mn->DF[0]->N + mn->DB[0]->XI[1]];
		else
			mn->vector[count] = min(mn->vector[count] , mn->DF[0]->Map[count][mn->DB[0]->XI[0]*mn->DF[0]->N + mn->DB[0]->XI[1]]);
		if(count == mn->numobj-1)
		{
			fprintf(mn->outputind,"%f",mn->vector[count]);
			fprintf(mn->output,"%f",mn->vector[count]);
			printf("%f",mn->vector[count]);
		}
		else
		{
			fprintf(mn->outputind,"%f,",mn->vector[count]);
			fprintf(mn->output,"%f,",mn->vector[count]);
			printf("%f,",mn->vector[count]);
		}
	}
	fprintf(mn->outputind,"\n");
	if((double)checkamount/(double)checktotal >= .9)
	{
		check90++;
	}
	else if((double)checkamount/(double)checktotal >= .8)
	{
	check80++;
	}
	else if((double)checkamount/(double)checktotal >= .7)
	{
	check70++;
	}
	else if((double)checkamount/(double)checktotal >= .6)
	{
	check60++;
	}
	else if((double)checkamount/(double)checktotal >= .5)
	{
	check50++;
	}
	else if((double)checkamount/(double)checktotal >= .4)
	{
	check40++;
	}
	else if((double)checkamount/(double)checktotal >= .3)
	{
	check30++;
	}
	else if((double)checkamount/(double)checktotal >= .2)
	{
	check20++;
	}
	else if((double)checkamount/(double)checktotal >= .1)
	{
	check10++;
	}
	fprintf(mn->output,"\n%d\n%d\n%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",checkamount,checktotal,check,check10,check20,check30,check40,check50,check60,check70,check80,check90);
	printf("\n");
}

void fprintSolutionPath(struct mvar* mn)
{
	mn->tempfinish = mn->finish;
	
	//Get solution path
	if(!(start[0] == end[0] && start[1] == end[1]))//Trivial solution if goal and start state are the same
	{
		while (mn->tempfinish != NULL)
		{
			fprintf(mn->outputind,"[%d,%d],",mn->tempfinish->V[0],mn->tempfinish->V[1]);
			//fprintf(mn->output,"[%d,%d],",mn->tempfinish->V[0],mn->tempfinish->V[1]);
			mn->tempfinish = mn->tempfinish->tail;
		}
		fprintf(mn->outputind,"[%d,%d]\n",end[0],end[1]);
		//fprintf(mn->output,"[%d,%d]\n",end[0],end[1]);
	}
}


void printSolutionPath(struct mvar* mn)
{
	mn->tempfinish = mn->finish;
	
	//Get solution path
	if(!(start[0] == end[0] && start[1] == end[1]))//Trivial solution if goal and start state are the same
	{
		while (mn->tempfinish != NULL)
		{
			printf("[%d,%d],",mn->tempfinish->V[0],mn->tempfinish->V[1]);
			mn->tempfinish = mn->tempfinish->tail;
		}
		printf("[%d,%d]\n",end[0],end[1]);
	}
}


void printSolutionCost(struct mvar* mn)
{
	for(int count = 0; count < mn->numobj; count++)
	{
		if(count == mn->numobj - 1)
			mn->vector[count] +=mn->DF[0]->Map[count][mn->DB[0]->XI[0]*mn->DF[0]->N + mn->DB[0]->XI[1]];
		else
			mn->vector[count] = min(mn->vector[count] ,mn->DF[0]->Map[count][mn->DB[0]->XI[0]*mn->DF[0]->N + mn->DB[0]->XI[1]]);
		if(count == mn->numobj-1)
		{
			printf("%f",mn->vector[count]);
		}
		else
		{
			printf("%f,",mn->vector[count]);
		}
		
	}
	printf("\n");
}
