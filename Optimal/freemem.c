void freeObjectives(struct objectives * o)
{
	int count = 0;
	for(count = 0; count < nobj; count++)
	{
		for(int r = 0; r < row * col; r++)
		{
			xfree(o[count].OL[r],1);
		}
		xfree(o[count].OL,2);
	}
	xfree(o,3);
}

void freeDijkstra(struct Dijkstra *D)
{
	int count = 0;
	if(D->s == -1)
	{
		freeVertexCost(D);
	}
	xfree(D->XI,4);
	xfree(D->VertexCost,5);
	xfree(D->VertexVisited,6);
	for(count = 0; count < nobj; count++)
	{
		xfree(D->Map[count],7);
	}
	xfree(D->Map,8);
	for(count = 0; count < (row * col); count++)
	{
		xfree(D->VertexEdge[count],9);
		xfree(D->SE[count],10);
	}
	xfree(D->VertexEdge,11);
	xfree(D->SE,12);
	xfree(D->HasVisited,13);
	xfree(D,14);
}

//Free dynamically allocated memory
void freeMemory(struct mvar* mn)
{
	freeatr(mn->atr);
	freeSolution(mn->finish);
	freeObjectives(mn->outlookmap);
	freeDijkstra(mn->last);
	for(int count = 0; count < mn->numobj; count++)
	{
		freeDijkstra(mn->DF[count]);
		freeDijkstra(mn->DB[count]);
	}
}

void freeMemoryMVP(struct mvar* mn)
{
	freeatr(mn->atr);
	freeSolution(mn->finish);
	xfree(mn->outlookmap,1);
	mn->last->s = 1;
	xfree(mn->last->Q,2);
	xfree(mn->DB[mn->numobj-1]->Q,2);
	xfree(mn->last->fVertexCost,2);
	for(int count = 0; count < mn->last->M*mn->last->N; count++)
	{
		xfree(mn->last->fVertexPathCost[count],3);
	}
	xfree(mn->last->fVertexPathCost,3);
	xfree(mn->last->ffVertexPathCost,4);
	freeDijkstra(mn->last);
	for(int count = 0; count < mn->numobj; count++)
	{
		freeDijkstra(mn->DF[count]);
		freeDijkstra(mn->DB[count]);
	}
}

void freeMemoryDstra(struct mvar* mn)
{
	int vert[2];
	freeatr(mn->atr);
	freeSolution(mn->finish);
	xfree(mn->outlookmap,1);
	for(int count = 0; count < (row * col); count++)
	{
		if(mn->last->VertexVisited[count] == 1)
		{
			xfree(mn->last->fVertexCost[count],13);
		}
	}
	
	xfree(mn->last->XI,4);
	xfree(mn->last->VertexCost,5);
	xfree(mn->last->VertexVisited,6);
	while(mn->last->Q != NULL)
	{
		pop(mn->last,vert);
	}
	for(int count = 0; count < nobj; count++)
	{
		xfree(mn->last->Map[count],7);
	}
	xfree(mn->last->Map,8);
	for(int count = 0; count < (row * col); count++)
	{
		xfree(mn->last->VertexEdge[count],9);
		xfree(mn->last->SE[count],10);
	}
	xfree(mn->last->VertexEdge,11);
	xfree(mn->last->SE,12);
	xfree(mn->last->HasVisited,13);
	xfree(mn->last->fVertexCost,5);
	xfree(mn->last->fVertexPathCost,5);
	for(int count = 0;count < row*col;count++)
	{
		xfree(mn->last->ffVertexPathCost[count],12);
	}
	xfree(mn->last->ffVertexPathCost,5);
	xfree(mn->last,14);
	
	xfree(mn->DB[mn->numobj-1]->Q,2);
	for(int count = 0; count < mn->numobj; count++)
	{
		xfree(mn->DF[count]->Q,3);
		if(count != mn->numobj - 1)
			xfree(mn->DB[count]->Q,3);
		freeDijkstra(mn->DF[count]);
		freeDijkstra(mn->DB[count]);
	}
	
}

//free all of the cost maps from the csv file
void freeatr(struct ListD *atr)
{
	struct ListD *temp;
	int count = 0;
	temp = atr;
	while(temp->tail != NULL)
	{
		for(count = 0; count < row; count++)
		{
			xfree(temp->V[count],15);
		}
		xfree(temp->V,16);
		atr = temp;
		temp = temp->tail;
		xfree(atr,17);
	}
	xfree(temp,18);
}

void freeVertexCost(struct Dijkstra *D)
{
	int vert[2];
	int count = 0;
	while(D->Q != NULL)
	{
		pop(D,vert);
		xfree(D->fVertexCost[vert[0]*D->N + vert[1]],23);
		D->fVertexCost[vert[0]*D->N + vert[1]] = NULL;
	}
	for(count = 0; count < D->M*D->N; count++)
	{
		if(D->fVertexCost[count] != NULL)
		{
			xfree(D->fVertexCost[count],24);
		}
		xfree(D->ffVertexPathCost[count],25);
	}
	xfree(D->fVertexCost,26);
	xfree(D->fVertexPathCost,27);
	xfree(D->ffVertexPathCost,28);

}

void freeSolution(struct List * sol)
{
	struct List *temp;
	temp = sol;
	while(temp->tail != NULL)
	{
		sol = temp;
		temp = temp->tail;
		xfree(sol,29);
	}
	xfree(temp,30);
}