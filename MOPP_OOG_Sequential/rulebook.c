int rulecompare(struct Dijkstra *D, double *p, double *n)
{
	int count = 0;
	for(count = 0; count < nobj; count++)
	{
		if(p[count] < n[count])
			return 0;
		else if(p[count] > n[count])
			return 1;
	}
	for(count = nobj; count < nobj*2; count++)
	{
		if(p[count] < n[count])
			return 0;
		else if(p[count] > n[count])
			return 1;
	}
	return 0;
}
