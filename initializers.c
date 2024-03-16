//initialize the main method and variables
void initializeMain(struct mvar* mn)
{
	initializeDebug();
	readcsv(mn);
	
	
	//write
	mn->output = NULL;
	

	sprintf(mn->file, "%s%d.csv",mn->folder,mn->csvcounter);//Starting file name
	
	//open file to write
	mn->output = fopen(mn->file2,"w");
	if(mn->output == NULL)
	{
		printf("Error occured when attempting to open output file\n");
		exit(1);
	}
	
	//Load file into program
	mn->atr = initializeProgram(mn->file);//read file data,populate global variables and cost maps
	mn->numobj = nobj;
	
	sprintf(mn->file3, "%s%d.csv",mn->folder2,mn->csvcounter);//Starting file name
	mn->outputind = fopen(mn->file3,"w");
	if(mn->outputind == NULL)
	{
		printf("Error occured when attempting to open output file\n");
		exit(1);
	}
	
}

void initializeDebug()
{
	//Code to verify that dynamic memory is deallocated.
	dyn = calloc(sizeof(struct Listptr),1);
	dyn->last = dyn;
	dyn->tail = NULL;
	dyn->p = NULL;
	dyn->id = 0;
	dyn->size = 0;
}

void initializeSearch(struct mvar* mn)
{
	//Initialize forward and backward dijkstra environments
	for(int count = 0; count < mn->numobj; count++)//for each objective
	{
		mn->DF[count] = initialize(start, count, mn->atr);//initialize forward dijkstra
		mn->DB[count] = initialize(end, count, mn->atr);//initialize backward dijkstra
	}
	mn->last = initialize(start, -1, mn->atr);//initialize final search
	
	mn->outlookmap = xmalloc(sizeof(struct objectives)*mn->numobj,1);//Memory reserved for storing outlook maps
	fprintf(mn->output,"%d\n",mn->csvcounter);
}

void initializeDstar(struct mvar* mn)
{
	mn->last = initialize(start, -1, mn->atr);//initialize final search
	fprintf(mn->output,"%d\n",mn->csvcounter);
}

struct Dijkstra *initialize(int* st, int s, struct ListD *atr)
{
	struct Dijkstra *D = xmalloc(sizeof(struct Dijkstra),16);
	struct List *q = xmalloc(sizeof(struct List),17);
	struct ListD *tatr = atr;
	int caction = 0;
	int m = row;
	int n = col;
	int *xi = xmalloc(sizeof(int)*2,18);
	int count = 0;
	int counter = 0;
	int cou = 0;
	
	xi[0] = st[0];
	xi[1] = st[1];
	q->V = xi;
	q->head = NULL;
	q->tail = NULL;
	
	D->Q = q;
	D->M = m;
	D->N = n;
	D->nobjs = nobj;
	D->Map = xmalloc(sizeof(double *) *nobj,19);
	D->VertexVisited = xmalloc(sizeof(int) * m * n,20);
	if(s == -1)
	{
		D->fVertexCost = xmalloc(sizeof(double *) * m * n,21);
		D->fVertexPathCost = xmalloc(sizeof(double *) * m * n,22);
		D->ffVertexPathCost = xmalloc(sizeof(double *) * m * n,22);
		for(count = 0;count < m*n;count++)
		{
			D->fVertexCost[count] = NULL;
			D->fVertexPathCost[count] = xmalloc(sizeof(double) * nobj,23);
			D->ffVertexPathCost[count] = D->fVertexPathCost[count];
			for(counter = 0; counter < nobj; counter++)
			{
				D->fVertexPathCost[count][counter] = 0;
			}
		}
	}
	
	D->VertexCost = xmalloc(sizeof(double) * m * n,24);
	D->VertexEdge = xmalloc(sizeof(int *) * m * n,25);
	D->HasVisited = xmalloc(sizeof(int *) * m * n,26);
	D->SE = xmalloc(sizeof(int *) * m * n,27);
	D->XI = xi;
	D->size = 1;
	D->s = s;
	cou = 0;
	while(tatr->tail != NULL)
	{
		D->Map[cou] = xmalloc(sizeof(double) * row * col,28);
		
		for(count = 0; count < m; count++)
		{
			for(counter = 0; counter < n; counter++)
			{
				D->Map[cou][count*n + counter] = tatr->V[count][counter];
			}
		}
		tatr = tatr->tail;
		cou++;
	}
	
	for(count = 0; count < m; count++)
	{
		for(counter = 0; counter < n; counter++)
		{
			D->VertexVisited[count*n + counter] = 0;
			D->VertexCost[count*n + counter] = 0;
			D->VertexEdge[count*n + counter] = xmalloc(sizeof(int)*4,29);
			D->HasVisited[count*n + counter] = NULL;
			D->SE[count*n + counter] = xmalloc(sizeof(int)*(4*4+1),30);
		}
	}
	for(count = 0; count < m; count++)
	{
		for(counter = 0; counter < n; counter++)
		{
			caction = 0;
			if(count > 0)
			{
				D->SE[count*n+counter][caction*4+1] = count;
				D->SE[count*n+counter][caction*4+2] = counter;
				D->SE[count*n+counter][caction*4+3] = count - 1;
				D->SE[count*n+counter][caction*4+4] = counter;
				caction++;
			}
			if(count < m - 1)
			{
				D->SE[count*n+counter][caction*4+1] = count;
				D->SE[count*n+counter][caction*4+2] = counter;
				D->SE[count*n+counter][caction*4+3] = count + 1;
				D->SE[count*n+counter][caction*4+4] = counter;
				caction++;
			}
			if(counter > 0)
			{
				D->SE[count*n+counter][caction*4+1] = count;
				D->SE[count*n+counter][caction*4+2] = counter;
				D->SE[count*n+counter][caction*4+3] = count;
				D->SE[count*n+counter][caction*4+4] = counter - 1;
				caction++;
			}
			if(counter < n - 1)
			{
				D->SE[count*n+counter][caction*4+1] = count;
				D->SE[count*n+counter][caction*4+2] = counter;
				D->SE[count*n+counter][caction*4+3] = count;
				D->SE[count*n+counter][caction*4+4] = counter + 1;
				caction++;
			}
			D->SE[count*n+counter][0] = caction;
		}
	}
	
	D->VertexVisited[xi[0]*n+xi[1]] = 1;
	
	if(s == -1)
		D->VertexCost[xi[0]*n+xi[1]] = 0;
	else
		D->VertexCost[xi[0]*n+xi[1]] = D->Map[s][xi[0]*n+xi[1]];
	return D;
}
