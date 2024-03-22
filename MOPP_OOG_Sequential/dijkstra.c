//initialize

//High level Dijkstra algorithm
double *fsearch(struct Dijkstra *D)
{
	int vert[2];
	int *actions;
	int count = 0;
	double cst;
	

	while(D->Q != NULL)
	{
		pop(D,vert);//remove and examine lowest cost vertex
		actions = D->SE[D->M*vert[0]+vert[1]];//determine possible transitions from vertex
		
		for(count = 0; count < actions[0]; count++)//for each action
		{
			cst = cost(D,&actions[count*4+1]);//determine cost if action is taken
			if(hasVisited(D, &actions[count*4+3]) == 0)//if state has never been reached before
			{
				visitedf(D, &actions[count*4 + 1],cst);//add state to the visited list
				insertAction(D,&actions[count*4+3]);//insert state into the queue
			}
			else//state has been visited before
			{
				hvisit(D,&actions[count*4+1],cst);//determine if action has the lowest cost to reach the state and insert into queue if so
			}
		}
	}
	return D->VertexCost;//returns the lowest costs discovered to reach each state in the graph.
}

//determine if action has the lowest cost to reach the state and if so insert into queue
void hvisit(struct Dijkstra *D, int * a, double cost)
{
	struct List * node = D->HasVisited[D->N * a[2] + a[3]];//action that previously lead to the state
	struct List * thead;
	struct List * ttail;
	if(D->VertexCost[a[2]*D->N + a[3]] > cost)//if cost to reach state is less with the new action
	{
		D->VertexCost[a[2]*D->N + a[3]] = cost;//set cost of state to the cost for the new action
		
		//record the action/edge that leads to this state
		D->VertexEdge[a[2]*D->N + a[3]][0] = a[0];
		D->VertexEdge[a[2]*D->N + a[3]][1] = a[1];
		D->VertexEdge[a[2]*D->N + a[3]][2] = a[2];
		D->VertexEdge[a[2]*D->N + a[3]][3] = a[3];
		
		//the state was not in the queue
		if(node == NULL)
		{
			insertAction(D,&a[2]);//just insert the new action into the queue
		}
		else//state was in the queue
		{
			//remove state from the queue
			thead = node->head;//record the actions head
			ttail = node->tail;//record the actions tail
			xfree(node,19);//eliminate state from the queue
			if(thead == NULL)//if state was at the begining of the queue
			{
				if(ttail == NULL)//if queue only had the state
				{
					D->Q = NULL;//Declare the queue to now be empty so insert will handle this case
				}
				else//queue is not empty
				{
					ttail->head = NULL;//the next element is now the front of the queue set its head to NULL
					D->Q = ttail;
				}
			}
			else//if state was not at the begining of the queue
			{
				if(ttail == NULL)//if state was at the end of the queue
				{
					thead->tail = NULL;//the element in front of the state is now at the end of the queue set its tail to NULL
				}
				else//the state was somewhere in the middle of the queue
				{
					thead->tail = ttail;
					ttail->head = thead;
				}
			}
			D->HasVisited[D->N * a[2] + a[3]] = NULL;//erase queue pointer reference
			insertAction(D,&a[2]);//reinsert the state into the queue
		}
	}
}

//insert a state into the queue
void insertAction(struct Dijkstra *D, int * action)
{
	struct List *Q = D->Q;
	struct List *last;
	while(Q != NULL)//search queue untill the correct position is found
	{
		if(evaluate(D,Q->V,action) == 1)//determine of action cost became greater than the current element in the queue
		{
				insert(D,Q->head,Q,action);//insert the state at this position in the queue
				return;
		}
		last = Q;//keep track of the previous queue state
		Q = Q->tail;//traverse to the next queue element
	}
	if(D->Q == NULL)//if queue is empty intialize and insert the first element into the queue
		insert(D,NULL,NULL,action);
	else//if action cost is greater than every element in the queue the insert state at the end of the queue
		insert(D,last,NULL,action);
}

//returns 1 if old value is large than new value
int evaluate(struct Dijkstra *D, int * old, int * new)
{
	double o = D->VertexCost[D->N * old[0] + old[1]];
	double n = D->VertexCost[D->N * new[0] + new[1]];
	if(o > n)
		return 1;
	return 0;
}

//declare a state to be visited through an action with an associated cost
void visitedf(struct Dijkstra *D, int * action, double cost)
{
	D->VertexVisited[action[2]*D->N + action[3]] = 1;
	D->VertexCost[action[2]*D->N + action[3]] = cost;
	
	D->VertexEdge[action[2]*D->N + action[3]][0] = action[0];
	D->VertexEdge[action[2]*D->N + action[3]][1] = action[1];
	D->VertexEdge[action[2]*D->N + action[3]][2] = action[2];
	D->VertexEdge[action[2]*D->N + action[3]][3] = action[3];
}

//check if vertex was visited before
int hasVisited(struct Dijkstra *D, int * action)
{
	return D->VertexVisited[action[0]*D->N + action[1]];
}

//remove first value from the queue and store vertex in v
void pop(struct Dijkstra *D,int *v)
{
	struct List *thead;
	struct List *ttail;
	v[0] = D->Q->V[0];
	v[1] = D->Q->V[1];
	thead = D->Q;
	ttail = D->Q->tail;
	D->Q = ttail;
	xfree(thead,20);
	if(ttail != NULL)
		ttail->head = NULL;
	D->HasVisited[D->N * v[0] + v[1]] = NULL;
}

//Insert a vertex into the queue
void insert(struct Dijkstra *D, struct List *h, struct List *t, int *v)
{
	struct List *temp = xmalloc(sizeof(struct List),9);
	temp->V = v;
	D->HasVisited[D->N * v[0] + v[1]] = temp;
	if(h == NULL)//insert at front of list
	{
		temp->head = NULL;
		D->Q = temp;
		if(t == NULL)//list is empty
		{
			temp->tail = NULL;
		}
		else//insert at front of list
		{
			temp->tail = t;
			t->head = temp;
		}
	}
	else //insert between two items
	{
		h->tail = temp;
		temp->head = h;
		if (t == NULL) //insert at end of list
		{
			temp->tail = NULL;
		}
		else
		{
			temp->tail = t;
			t->head = temp;
		}
	}
}


//High level Dijkstra algorithm
double *fsearchMVP(struct Dijkstra *D)
{
	int vert[2];
	int *actions;
	int count = 0;
	double cst;
	

	while(D->Q != NULL)
	{
		pop(D,vert);//remove and examine lowest cost vertex
		actions = D->SE[D->M*vert[0]+vert[1]];//determine possible transitions from vertex
		
		for(count = 0; count < actions[0]; count++)//for each action
		{
			if(actions[count*4+1] == -1)
			{
				continue;
			}
			cst = cost(D,&actions[count*4+1]);//determine cost if action is taken
			if(hasVisited(D, &actions[count*4+3]) == 0)//if state has never been reached before
			{
				visitedf(D, &actions[count*4 + 1],cst);//add state to the visited list
				insertAction(D,&actions[count*4+3]);//insert state into the queue
			}
			else//state has been visited before
			{
				hvisit(D,&actions[count*4+1],cst);//determine if action has the lowest cost to reach the state and insert into queue if so
			}
		}
	}
	return D->VertexCost;//returns the lowest costs discovered to reach each state in the graph.
}


void busy(int x,int y)
{
	int count = 0;
	int counter = 0;
	for(count = 0; count < x; count++)
		for(counter = 0; counter < y; counter++);
}