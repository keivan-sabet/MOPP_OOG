struct List *finalsearch(struct Dijkstra *D, struct objectives *ol, int *xg)
{
	int vert[2];
	int *actions;
	double *cst;
	double *vector = xmalloc(nobj*sizeof(double),10);
	checkswitch = 0;
	checknormal = 0;
	checkamount = 0;
	checktotal = 0;
	
	int count = 0;
	
	for(count = 0; count < nobj; count++)
	{
		vector[count] = 0;
	}
	
	D->fVertexCost[D->XI[0]*D->N + D->XI[1]] = vector;
	for(count = 0; count < D->nobjs; count++)
		D->fVertexPathCost[D->XI[0]*D->N + D->XI[1]][count] = D->Map[count][D->XI[0]*D->N + D->XI[1]];
	D->ol = ol;
	
	while(D->Q != NULL)
	{
		pop(D,vert);
		//printf("[%d,%d]\n",vert[0],vert[1]);
		actions = D->SE[D->N*vert[0]+vert[1]];
		if(vert[0] == xg[0] && vert[1] == xg[1])
		{
			return path(D,xg);
		}
		for(count = 0; count < actions[0]; count++)
		{
			cst = costfinal(D,ol,&actions[count*4+1],count);
			//printf("[%d,%d]:",actions[count*4+3],actions[count*4+4]);
			//for(int counter = 0; counter < nobj; counter++)
			//	printf("%f,",cst[counter]);
			//printf("\n");
			if(hasVisited(D, &actions[count*4+3]) == 0)
			{
				fvisitedf(D, &actions[count*4 + 1],cst);
				finsertAction(D,&actions[count*4+3]);
			}
			else
			{
				fhvisit(D,&actions[count*4+1],cst);
			}
		}
	}
	return NULL;
}

double * costfinal(struct Dijkstra *D, struct objectives *ol, int *a, int acount)
{
	double *p = D->fVertexCost[a[0]*D->N + a[1]];
	int n = a[2]*D->N + a[3];
	double *vector = xmalloc(nobj*sizeof(double)*2,11);
	int count = 0;
	checknormal = 0;
	for(count = 0; count < nobj; count++)
	{
		if(count == nobj - 1)
		{
			vector[count] = D->fVertexPathCost[a[0]*D->N + a[1]][count] + D->Map[count][n];
			vector[nobj + count] = D->fVertexPathCost[a[0]*D->N + a[1]][count] + D->Map[count][n];
		}
		else
		{
			if(p[count] < ol[count].OL[a[0]*D->N + a[1]][acount])
			{
				vector[count] = ol[count].OL[a[0]*D->N + a[1]][acount];
			}
			else
			{
				vector[count] = p[count];
			}
		}
	}
	return vector;
}

struct List *path(struct Dijkstra *D, int *xg)
{
	struct List *sol = xmalloc(sizeof(struct List),12);
	//printf("%d,%d\n",xg[0],xg[1]);
	sol->V = D->VertexEdge[xg[0] * D->N + xg[1]];
	printf("[%d,%d],[%d,%d]\n",sol->V[0],sol->V[1],sol->V[2],sol->V[3]);
	sol->tail = NULL;
	sol->head = NULL;
	if(xg[0] == D->XI[0] && xg[1] == D->XI[1])
		return sol;
	while(!((sol->V[0] == D->XI[0]) && (sol->V[1] == D->XI[1])))
	{
		sol->head = xmalloc(sizeof(struct List),13);
		sol->head->tail = sol;
		sol->head->V = D->VertexEdge[sol->V[0] * D->N + sol->V[1]];
		sol->head->head = NULL;
		sol = sol->head;
		//printf("[%d,%d],[%d,%d]\n",sol->V[0],sol->V[1],sol->V[2],sol->V[3]);
	}
	return sol;
}

void finsertAction(struct Dijkstra *D, int * action)
{
	struct List *Q = D->Q;
	struct List *last;
	while(Q != NULL)
	{
		if(fevaluate(D,Q->V,action) == 1)
		{
				insert(D,Q->head,Q,action);
				return;
		}
		last = Q;
		Q = Q->tail;
	}
	if(D->Q == NULL)
		insert(D,NULL,NULL,action);
	else
		insert(D,last,NULL,action);
	
}

int fevaluate(struct Dijkstra *D, int * old, int * new)
{
	double *o = D->fVertexCost[D->N * old[0] + old[1]];
	double *n = D->fVertexCost[D->N * new[0] + new[1]];
	if(rulecompare(D,o,n) == 1)
		return 1;
	return 0;
}

void fhvisit(struct Dijkstra *D, int * a, double *cost)
{
	struct List * node = D->HasVisited[D->N * a[2] + a[3]];
	struct List * thead;
	struct List * ttail;
	if(rulecompare(D,D->fVertexCost[a[2]*D->N + a[3]], cost) == 1)
	{
		xfree(D->fVertexCost[a[2]*D->N + a[3]],21);
		D->fVertexCost[a[2]*D->N + a[3]] = cost;
		D->fVertexPathCost[a[2]*D->N + a[3]] = &cost[nobj];
		
		D->VertexEdge[a[2]*D->N + a[3]][0] = a[0];
		D->VertexEdge[a[2]*D->N + a[3]][1] = a[1];
		D->VertexEdge[a[2]*D->N + a[3]][2] = a[2];
		D->VertexEdge[a[2]*D->N + a[3]][3] = a[3];
		if(node == NULL)
		{
			finsertAction(D,&a[2]);
		}
		else
		{
			thead = node->head;
			ttail = node->tail;
			xfree(node,21);
			if(thead == NULL)
			{
				if(ttail == NULL)
				{
					D->Q = NULL;
				}
				else
				{
					ttail->head = NULL;
					D->Q = ttail;
				}
			}
			else
			{
				if(ttail == NULL)
				{
					thead->tail = NULL;
				}
				else
				{
					thead->tail = ttail;
					ttail->head = thead;
				}
			}
			D->HasVisited[D->N * a[2] + a[3]] = NULL;
			finsertAction(D,&a[2]);
		}
	}
	else
	{
		xfree(cost,22);
	}
	
}

void fvisitedf(struct Dijkstra *D, int * action, double *cost)
{
	D->VertexVisited[action[2]*D->N + action[3]] = 1;
	D->fVertexCost[action[2]*D->N + action[3]] = cost;
	D->fVertexPathCost[action[2]*D->N + action[3]] = &cost[nobj];
	
	D->VertexEdge[action[2]*D->N + action[3]][0] = action[0];
	D->VertexEdge[action[2]*D->N + action[3]][1] = action[1];
	D->VertexEdge[action[2]*D->N + action[3]][2] = action[2];
	D->VertexEdge[action[2]*D->N + action[3]][3] = action[3];
}

//High level Dijkstra algorithm
struct List *dsearchMVP(struct Dijkstra *D, int *xg)
{
	int vert[2];
	int *actions;
	int count = 0;
	double cst;
	

	while(D->Q != NULL)
	{
		pop(D,vert);//remove and examine lowest cost vertex
		actions = D->SE[D->M*vert[0]+vert[1]];//determine possible transitions from vertex
		if(vert[0] == xg[0] && vert[1] == xg[1])
		{
			return path(D,xg);
		}
		//printf("Actions:%d\n", actions[0]);
		for(count = 0; count < actions[0]; count++)//for each action
		{
			if(actions[count*4+1] == -1)
			{
				//printf("continue\n");
				continue;
			}
			cst = cost(D,&actions[count*4+1]);//determine cost if action is taken
			//printf("%f\n", cst);
			if(hasVisited(D, &actions[count*4+3]) == 0)//if state has never been reached before
			{
				//printf("notvisited\n");
				visitedf(D, &actions[count*4 + 1],cst);//add state to the visited list
				insertAction(D,&actions[count*4+3]);//insert state into the queue
			}
			else//state has been visited before
			{
				//printf("hasvisited\n");
				hvisit(D,&actions[count*4+1],cst);//determine if action has the lowest cost to reach the state and insert into queue if so
			}
		}
	}
	return NULL;
}

double * costDstra(struct Dijkstra *D, int *a)
{
	int n = a[2]*D->N + a[3];
	double *vector = xmalloc(nobj*sizeof(double)*2,13);
	for(int count = 0; count < nobj; count++)
	{
		if(count == nobj - 1)
		{
			vector[count] = D->fVertexPathCost[a[0]*D->N + a[1]][count] + D->Map[count][n];
			vector[nobj + count] = D->fVertexPathCost[a[0]*D->N + a[1]][count] + D->Map[count][n];
		}
		else
		{
			vector[count] = min(D->fVertexPathCost[a[0]*D->N + a[1]][count] , D->Map[count][n]);
			vector[nobj + count] = min(D->fVertexPathCost[a[0]*D->N + a[1]][count] , D->Map[count][n]);
		}
	}
	return vector;
}

struct List *Dstrasearch(struct Dijkstra *D, int *xg)
{
	int vert[2];
	int *actions;
	double *cst;
	double *vector = xmalloc(nobj*sizeof(double),10);	
	
	for(int count = 0; count < nobj; count++)
	{
		vector[count] = 0;
	}
	
	D->fVertexCost[D->XI[0]*D->N + D->XI[1]] = vector;
	for(int count = 0; count < D->nobjs; count++)
		D->fVertexPathCost[D->XI[0]*D->N + D->XI[1]][count] = D->Map[count][D->XI[0]*D->N + D->XI[1]];
	
	while(D->Q != NULL)
	{
		pop(D,vert);
		actions = D->SE[D->N*vert[0]+vert[1]];
		if(vert[0] == xg[0] && vert[1] == xg[1])
		{
			return path(D,xg);
		}
		for(int count = 0; count < actions[0]; count++)
		{
			cst = costDstra(D,&actions[count*4+1]);
			//printf("[%d,%d]:",actions[count*4+3],actions[count*4+4]);
			//for(int counter = 0; counter < nobj; counter++)
			//	printf("%f,",cst[counter]);
			//printf("\n");
			if(hasVisited(D, &actions[count*4+3]) == 0)
			{
				fvisitedf(D, &actions[count*4 + 1],cst);
				finsertAction(D,&actions[count*4+3]);
			}
			else
			{
				fhvisit(D,&actions[count*4+1],cst);
			}
		}
	}
	return NULL;
}