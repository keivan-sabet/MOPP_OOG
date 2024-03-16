//keep a list of pointers
struct Listptr
{
	void *p;
	int id;
	int size;
	struct Listptr *tail;
	struct Listptr *last;
};

//doubly linked interger list
struct List
{
	int *V;
	struct List *head;
	struct List *tail;
};

//single linked double pointer list
struct ListD
{
	double **V;
	struct ListD *tail;
};

//list of objective maps as well as the largest and smallest value
struct objectives
{
	double **OL;
	double *EL;
	double Max;
	double Min;
};

//Dijkstra data structure
struct Dijkstra
{
	struct List *Q;
	struct objectives *ol;
	double **Map;
	double *VertexCost;
	double **fVertexCost;
	double **fVertexPathCost;
	double **ffVertexPathCost;
	int *VertexVisited;
	struct List **HasVisited;
	int **VertexEdge;
	int **SE;
	int *XI;
	int M;
	int N;
	int size;
	int s;
	int nobjs;
};

struct mvar
{
	FILE *init;//initializer file
	FILE *output;//output file
	FILE *outputind;
	struct timespec timestart;//start time
	struct timespec timeend;//end time
	double time_spent;// runtime
	int csvcounter;//starting file number
	char folder[990];
	char file[1000];//holds input file name
	char file2[1000];//holds output file summary name
	char folder2[990];
	char file3[1000];//holds output file name
	struct ListD *atr;//holds cost maps
	struct Dijkstra *DF[256];//One dijkstra struct per objective
	struct Dijkstra *DB[256];//One dijkstra struct per objective
	struct objectives *outlookmap;//the optimal costs of each objective
	struct Dijkstra *last;//holds the dijkstra struct for the run of the outlook map
	struct List *finish;//holds the result of the outlook map
	struct List *tempfinish;
	double vector[256];//holds the cost of the resulting path
	int numobj;//number of objectives
};




