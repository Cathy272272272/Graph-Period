#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include <string.h>

#define NV 265214
#define NE 420045
#define TRUE 1
#define FALSE 0
#define MAXINT 10000000
typedef struct edgenode {
  int y;
  int weight;
  int visited;
  struct edgenode *next;
} Edgenode;
 
typedef struct {
  Edgenode *edges[NV+1];
  int degree[NV+1];
  int nvertices;
  int nedges;
  int directed;
} Graph;
Graph g;
int cnt;
void dfs(int depth[], int period[], int cur, int curDepth){
    Edgenode * e = g.edges[cur];
    if (e != NULL){
      do{
          if ( depth[e->y] == MAXINT ){
            depth[e->y] = curDepth + 1;
            period[cnt++] = 0;
            dfs(depth, period, e->y, curDepth + 1);
          }
          else period[cnt++] = depth[e->y] - curDepth - 1;
	  e = e->next;
      }
      while (e!= NULL);
    }
    return;
}
int gcd(int a, int b) 
{ 
    if ( a < 0 ) a = -a;
    if ( b < 0 ) b = -b; 
    if (a == b) 
        return a; 
    if (a > b) 
        return gcd(a-b, b); 
    return gcd(a, b-a); 
} 
int main(int argc, char **argv){
  Edgenode *e;
  FILE *file;
  char *filename;
  int u,v,w;
  int i, j, Gcd;
  filename = argv[1];
  file = fopen(filename,"r");
  g.directed = TRUE;
  g.nvertices = 0;
  g.nedges = 0;
  Edgenode *prev = NULL;
  char line[1000];
  char tmp[50];
while ( fgets(line, sizeof(line), file) ){
    char * pt = strtok (line," ");
    u = atoi(pt);
    g.nvertices++;
    while ( pt != NULL )  {
        if ( pt[0] == '[' ) {
	    i = 1;
        while ( pt[i] != ',' ) tmp[i - 1] = pt[i++]; 
            v = atoi(tmp);
            memset(tmp, 0x00, sizeof(char) * 50);
        Edgenode *new_node = (Edgenode *) malloc(sizeof(Edgenode)); 
        g.nedges++;         
        if (g.edges[u] == NULL){            
            g.edges[u]          = new_node;
            g.edges[u]->y       = v;
            g.edges[u]->next    = NULL;
            g.edges[u]->visited = 0;
            prev = new_node;
        }
        else{                                
            prev->next          = new_node;
            new_node->y         = v;
            new_node->next      = NULL;
            g.edges[u]->visited = 0;
            prev                = new_node;
        }
    }
        pt = strtok (NULL, " ");
    }
     memset(line, 0x00, sizeof(char) * 1000);
  }
  fclose(file);
int depth[g.nvertices + 1];
int period[g.nedges];
for ( i = 1; i <= g.nvertices; i++ ) depth[i] = MAXINT;
for ( i = 0; i < g.nedges; i++ ) period[i] = MAXINT;
cnt = 0;
 double	start = omp_get_wtime();
 dfs(depth, period, 1, 0);
 double stop = omp_get_wtime();
 printf("dfs costs %.6fs\n", stop - start);
Gcd = MAXINT;
for ( i = 0; i < g.nedges - 1; i++ ){
    //printf("%dth edges: %d \n", i, period[i]);
    if ( period[i] == 0 ) continue;
    for ( j = i + 1; j < g.nedges; j++ ){
    if ( period[j] == 0 ) continue;
        int tmp = gcd(period[i], period[j]);
        if ( tmp < Gcd ) Gcd = tmp;
        if ( Gcd == 0 ) break;
    }
}
printf("gcd is %d \n", Gcd);
}