double cost(struct Dijkstra *D, int * a)
{
	return costmp(D,a);
}

double costmp(struct Dijkstra *D, int * a)
{
	//busy(D->M,D->N);
	//if(D->s < 2)
	//{
	//	return min((D->VertexCost[D->N * a[0] + a[1]]),(D->Map[D->s][D->N * a[2] + a[3]]));
	//}
	
	//return (D->VertexCost[D->N * a[0] + a[1]]) + (D->Map[D->s][D->N * a[2] + a[3]]);
	if(D->s == (D->nobjs - 1))
		return (D->VertexCost[D->N * a[0] + a[1]]) + (D->Map[D->s][D->N * a[2] + a[3]]);
	return min((D->VertexCost[D->N * a[0] + a[1]]),(D->Map[D->s][D->N * a[2] + a[3]]));
}

double min(double a, double b)
{
	if(a < b)
		return b;
	return a;
}