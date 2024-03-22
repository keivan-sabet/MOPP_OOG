void debugCheck()
{
	/*
	dyncount = dyn;
	int count = 0;
	while(dyncount->tail != NULL)
	{
		count++;
		printf("id:%d\nsize:%d\naddress:%p\n\n",dyncount->id,dyncount->size,dyncount->p);
		dyncount = dyncount->tail;
	}
	printf("count: %d\n",count);
	*/
	
	//Code to verify that dynamic memory is deallocated.
	for(int count = 0; count < 1000; count++)
	{
		dyncount = dyn;
		int counter = 0;
		while(dyncount->tail != NULL)
		{
			if(dyncount->id == count)
			{
				counter++;
			}
			dyncount = dyncount->tail;
		}
		if(counter > 0)
			printf("id:%d\namount:%d\n",count,counter);
	}
	
}


void *xmalloc(int size, int id)
{
	void *p = calloc(size,1);
	/*
	struct Listptr *temp = calloc(sizeof(struct Listptr),1);
	//struct Listptr *count;
	temp->last = dyn->last;
	temp->tail = NULL;
	temp->p = NULL;
	temp->id = 0;
	temp->size = 0;
	
	
	dyn->last->p = p;
	dyn->last->id = id;
	dyn->last->size = size;
	dyn->last->tail = temp;
	dyn->last = temp;
	*/
	return p;
}

void xfree(void *ptr,int id)
{
	/*
	struct Listptr *count;
	struct Listptr *temp;
	count = dyn;
	int check = 0;
	while(count->tail != NULL)
	{
		if(count->p == ptr)
		{
			if(count == dyn)
			{
				temp = count;
				dyn->tail->last = dyn->last;
				dyn = dyn->tail;
				free(temp);
				check = 1;
				break;
			}
			else
			{
				temp = count;
				count->last->tail = count->tail;
				count->tail->last = count->last;
				free(temp);
				check = 1;
				break;
			}
		}
		count = count->tail;
	}
	if(check == 0)
	{
		printf("Error in xfree ptr not dynamically allocated with id:%d\n",id);
	}
	*/
	free(ptr);

}