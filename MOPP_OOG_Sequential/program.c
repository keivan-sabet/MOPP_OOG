void combine(struct Dijkstra *DF, struct Dijkstra *DB, struct objectives *o, int obj)
{
	double **result = xmalloc(sizeof(double)*DF->M*DF->N,14);
	double max;
	double min1;
	int count = 0;
	int counter = 0;
	int * actions;
	max = DF->VertexCost[0]+DB->VertexCost[0];
	min1 = DF->VertexCost[0]+DB->VertexCost[0];
	
	for(count = 0; count < DF->M; count++)
	{
		for(counter = 0; counter < DF->N; counter++)
		{
			actions = DF->SE[DF->M*count+counter];
			result[count*DF->N + counter] = xmalloc(sizeof(double)*actions[0],15);
			for(int cou = 0; cou < actions[0]; cou++)
			{
				//result[count*DF->N + counter][cou] = DF->VertexCost[actions[cou*4+1]*DF->N + actions[cou*4+2]]+DB->VertexCost[actions[cou*4+3]*DF->N + actions[cou*4+4]] + DF->Map[obj][actions[cou*4+3]*DF->N + actions[cou*4+4]];
				result[count*DF->N + counter][cou] = min(DF->VertexCost[actions[cou*4+1]*DF->N + actions[cou*4+2]],DB->VertexCost[actions[cou*4+3]*DF->N + actions[cou*4+4]]);
				
				if(result[count*DF->N + counter][cou] > max)
				{
					max = result[count*DF->N + counter][cou];
				}
				if(result[count*DF->N + counter][cou] < min1)
				{
					min1 = result[count*DF->N + counter][cou];
				}
			}
		}
	}
	/*
	for(count = DF->M-1; count >= 0; count--)
	{
		for(counter = 0; counter < DF->N; counter++)
		{
			printf("%f,", result[count*DF->N + counter]);
		}
		printf("\n");
	}
	printf("\n");
	*/
	o->OL = result;
	o->Max = max;
	o->Min = min1;
}

void combineMVP(struct Dijkstra *DF, struct Dijkstra *DB, struct Dijkstra *DF2, struct Dijkstra *DB2, int obj)
{
	double **result = xmalloc(sizeof(double)*DF->M*DF->N,14);
	double max;
	double min1;
	int count = 0;
	int counter = 0;
	int * actions;
	int *actions2;
	max = 0;
	min1 = 9999999999;
	
	for(count = 0; count < DF->M; count++)
	{
		for(counter = 0; counter < DF->N; counter++)
		{
			actions = DF->SE[DF->M*count+counter];
			result[count*DF->N + counter] = xmalloc(sizeof(double)*actions[0],15);
			for(int cou = 0; cou < actions[0]; cou++)
			{
				if(actions[cou*4+1] == -1)
				{
					continue;
				}
				
				result[count*DF->N + counter][cou] = min(DF->VertexCost[actions[cou*4+1]*DF->N + actions[cou*4+2]],DB->VertexCost[actions[cou*4+3]*DF->N + actions[cou*4+4]]);
				if(result[count*DF->N + counter][cou] > max)
				{
					max = result[count*DF->N + counter][cou];
				}
				if(result[count*DF->N + counter][cou] < min1)
				{
					min1 = result[count*DF->N + counter][cou];
				}
			}
		}
	}
	for(count = 0; count < DF->M; count++)
	{
		for(counter = 0; counter < DF->N; counter++)
		{
			actions = DF->SE[DF->N*count+counter];
			for(int cou = 0; cou < actions[0]; cou++)
			{
				if(actions[cou*4+1] == -1)
				{
					DF2->SE[count*DF->N + counter][cou*4+1] = -1;
					
					actions2 = DB->SE[actions[cou*4+3]*DF->N + actions[cou*4+4]];
					for(int coun = 0; coun < actions2[0]; coun++)
					{
						if((actions2[coun*4+3] == count) && (actions2[coun*4+4] == counter))
						{
							DB2->SE[actions[cou*4+3]*DF->N + actions[cou*4+4]][coun*4+1] = -1;
							break;
						}
					}
					
				}
				else if(result[count*DF->N + counter][cou] != min1)
				{
					DF2->SE[count*DF->N + counter][cou*4+1] = -1;
					actions2 = DB->SE[actions[cou*4+3]*DF->N + actions[cou*4+4]];
					for(int coun = 0; coun < actions2[0]; coun++)
					{
						if((actions2[coun*4+3] == count) && (actions2[coun*4+4] == counter))
						{
							DB2->SE[actions[cou*4+3]*DF->N + actions[cou*4+4]][coun*4+1] = -1;
							break;
						}
					}
				}
			}
		}
	}
	for(count = 0; count < DF->M; count++)
	{
		for(counter = 0; counter < DF->N; counter++)
		{
			xfree(result[count*DF->N + counter],11);
		}
	}
	xfree(result,10);
}