void OOG(struct mvar* mn)
{
	//#pragma omp parallel for
	for(int count = 0; count < mn->numobj; count++)//for every objective
	{
		fsearch(mn->DF[count]);//Execute forward dijkstra with relevant objective data
		fsearch(mn->DB[count]);//Execute backward dijkstra with relevant objective data
		combine(mn->DF[count],mn->DB[count],&mn->outlookmap[count],count);//merge forward and backward dijkstra into an outlook map
	}
	
	//Runs Dijkstra on the set of outlook maps
	mn->finish = finalsearch(mn->last, mn->outlookmap,mn->DB[0]->XI);
}

void MVP(struct mvar* mn)
{
	for(int count = 0; count < mn->numobj-1; count++)//for every objective
	{
		fsearchMVP(mn->DF[count]);//Execute forward dijkstra with relevant objective data
		fsearchMVP(mn->DB[count]);//Execute backward dijkstra with relevant objective data
		combineMVP(mn->DF[count],mn->DB[count],mn->DF[count+1],mn->DB[count+1],count);//merge forward and backward dijkstra into an outlook map
	}
	mn->finish = dsearchMVP(mn->DF[mn->numobj-1],mn->DB[0]->XI);
}

void Dstra(struct mvar* mn)
{
	mn->finish = Dstrasearch(mn->last,end);
}



void extractSolution(struct mvar* mn)
{
	//initialize a cost vector
	for(int count = 0; count < mn->numobj; count++)
	{
		mn->vector[count] = 0;
	}
	mn->tempfinish = mn->finish;
	
	//mn->vector[0] = mn->DF[0]->Map[0][mn->tempfinish->V[0]*mn->DF[0]->N + mn->tempfinish->V[1]];
	//mn->vector[1] = mn->DF[0]->Map[1][mn->tempfinish->V[0]*mn->DF[0]->N + mn->tempfinish->V[1]];
	//Get solution path
	if(!(start[0] == end[0] && start[1] == end[1]))//Trivial solution if goal and start state are the same
	{
		while (mn->tempfinish != NULL)
		{
			//caluclate solution cost
			for(int count = 0; count < mn->numobj; count++)
			{
				//if(count < 2)
				//		mn->vector[count] =min(mn->vector[count],mn->DF[0]->Map[count][mn->tempfinish->V[0]*mn->DF[0]->N + mn->tempfinish->V[1]]);
				//else
				if(count == mn->numobj - 1)
					mn->vector[count] += mn->DF[0]->Map[count][mn->tempfinish->V[0]*mn->DF[0]->N + mn->tempfinish->V[1]];
				else
					mn->vector[count] = min(mn->vector[count] , mn->DF[0]->Map[count][mn->tempfinish->V[0]*mn->DF[0]->N + mn->tempfinish->V[1]]);
			}
			//printf("[%d,%d],",tempfinish->V[0],tempfinish->V[1]);
			mn->tempfinish = mn->tempfinish->tail;
		}
		//printf("\n");
	}
}
