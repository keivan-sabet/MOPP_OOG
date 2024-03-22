//constructors

//adv.c
void outputHandler(struct mvar* mn);
void executeProgram(struct mvar* mn);
void calculateRuntime(struct mvar* mn);
void loadNext(struct mvar* mn);
void wrapup(struct mvar *mn);
void closeInstance(struct mvar* mn);
void closeInstanceMVP(struct mvar* mn);
void closeInstanceDstra(struct mvar* mn);
void executeProgramMVP(struct mvar* mn);
void executeProgramDstra(struct mvar* mn);


//csv.c
struct ListD * initializeProgram(char * ip);
void readcsv(struct mvar *mn);

//dijkstra.c
double *fsearch(struct Dijkstra *D);
void hvisit(struct Dijkstra *D, int * a, double cost);
void insertAction(struct Dijkstra *D, int * action);
int evaluate(struct Dijkstra *D, int * old, int * new);
void visitedf(struct Dijkstra *D, int * action, double cost);
int hasVisited(struct Dijkstra *D, int * action);
void pop(struct Dijkstra *D,int *v);
void insert(struct Dijkstra *D, struct List *h, struct List *t, int *v);
double *fsearchMVP(struct Dijkstra *D);
void busy(int x, int y);

//rulebook.c
int rulecompare(struct Dijkstra *D, double *p, double *n);

//finalsearch.c
struct List *finalsearch(struct Dijkstra *D, struct objectives *ol, int *xg);
double * costfinal(struct Dijkstra *D, struct objectives *ol, int *a, int acount);
struct List *path(struct Dijkstra *D, int *xg);
void finsertAction(struct Dijkstra *D, int * action);
int fevaluate(struct Dijkstra *D, int * old, int * new);
void fhvisit(struct Dijkstra *D, int * a, double *cost);
void fvisitedf(struct Dijkstra *D, int * action, double *cost);
struct List *dsearchMVP(struct Dijkstra *D, int *xg);

//objectivecost.c
double cost(struct Dijkstra *D, int * a);
double costmp(struct Dijkstra *D, int * a);
double min(double a, double b);

//program.c
void combine(struct Dijkstra *DF, struct Dijkstra *DB, struct objectives *o, int obj);
void combineMVP(struct Dijkstra *DF, struct Dijkstra *DB, struct Dijkstra *DF2, struct Dijkstra *DB2, int obj);

//freeMem.c
void freeObjectives(struct objectives * o);
void freeDijkstra(struct Dijkstra *D);
void freeMemory(struct mvar* mn);
void freeatr(struct ListD *atr);
void freeSolution(struct List * sol);
void freeVertexCost(struct Dijkstra *D);
void freeMemoryMVP(struct mvar* mn);
void freeMemoryDstra(struct mvar* mn);

//debug.c
void *xmalloc(int size, int id);
void xfree(void *ptr,int id);
void debugCheck();

//printfunc.c
void printSolutionCost(struct mvar* mn);
void fprintSolutionCost(struct mvar* mn);
void fprintSolutionPath(struct mvar* mn);
void printSolutionPath(struct mvar* mn);

//initializers.c
void initializeMain(struct mvar* mn);
void initializeSearch(struct mvar* mn);
struct Dijkstra *initialize(int* st, int s, struct ListD *atr);
void initializeDebug();
void initializeDstar(struct mvar* mn);

//MOOP.c
void OOG(struct mvar* mn);
void MVP(struct mvar* mn);
void Dstra(struct mvar* mn);
void extractSolution(struct mvar* mn);
