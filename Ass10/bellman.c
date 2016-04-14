#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef struct Edge
{
  int src, dest;
  double weight;
} Edge;

typedef struct Graph
{
  int V, E; //number of edges and vertices
  Edge* edge;
}Graph;


Graph* createGraph(int V, int E)
{
  Graph* graph = (Graph*) malloc(sizeof(Graph));
  graph->V = V;
  graph->E = E;
  graph->edge = (Edge*) malloc( graph->E * sizeof(Edge));
  return graph;
}

void relax(Graph* graph, int dist[], int pred[])
{
  int j;
  int E = graph->E;

  for (j = 0; j < E; j++)
	{
	  int u = graph->edge[j].src;
	  int v = graph->edge[j].dest;
	  double weight = graph->edge[j].weight;
	  if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
	  {
		dist[v] = dist[u] + weight;
		pred[v]=u;
	  }
	}
}

// A utility function used to print the solution
void printArr(int dist[], int n)
{
  printf("Vertex Distance from Source\n");
  int i;
  for (i = 0; i < n; ++i)
	printf("%d \t\t %d\n", i, dist[i]);
}

void showcycle(int pred[], int u, int v, int NV)
{
  int hash[NV];
  int k=v;
  printf("%d-->%d-->", u,v);
  hash[v]=hash[u]=1;
  while(1)
  {
	k=pred[k];
	if(hash[k]==1)
	  break;
	else
	{
		hash[k]=1;
		printf("%d-->", k);
	}

  }
  printf("%d\n", u);

}


void bellmanFord(Graph* graph, int src)
{
  int V = graph->V;
  int E = graph->E;
  int dist[V];
  int pred[V];

  int i;


  // Init-Single-Source
  for (i = 0; i < V; i++)
  {
	dist[i] = INT_MAX;
	pred[i]=-1;
  }
  dist[src] = 0;

  // Relax edges V-1 times
  for (i = 1; i <= V-2; i++)
  {
	 relax(graph,dist,pred);
  }

  // Check for negative-weight cycles.
  for (i = 0; i < E; i++)
  {
	int u = graph->edge[i].src;
	int v = graph->edge[i].dest;
	double weight = graph->edge[i].weight;


	if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
	  // printf("Arbitrage Opportunity from currency %d to %d\n", u ,v);
	  printf("Arbitrage Opportunity exists.\n");


	  relax(graph,dist,pred); //relax one more time

	  showcycle(pred,u,v, V);

	  return;
	}

  }

  printArr(dist, V);

  return;
}

int main(int argc, char *argv[])
{

  printf("Enter number of currencies: \n");
  int V; // Number of vertices in graph
  scanf("%d", &V);
  V=V+2;//adding start and stop point
  printf("Enter base for conversion:\n");
  int B;
  scanf("%d",&B);

  int E = V*(V-1); // Number of edges in graph
  E=E-V-V; // one directed edge per node for s' and t'
  struct Graph* graph = createGraph(V, E);

  int i,j;
  double w;
  int ec=0;
  FILE *f;

  if(argc!=2)
		 f = fopen("table.txt", "r");
  else
		 f = fopen(argv[1], "r");




  for(i=1;i<V-1;i++)
  {
	for(j=1;j<V-1;j++)
	{

	  fscanf(f,"%lf\t", &w);
	  if(i==j) continue;
	  printf("Conversion rate in base %d for currency %d --> %d is %lf\n", B, i, j, w);
	  graph->edge[ec].src=i;
	  graph->edge[ec].dest=j;
	  // scanf("%lf",&w);
	  graph->edge[ec].weight= - log(w/B);
	  ec++;
	}
  }

  fclose(f);

  for(i=1;i<V-1;i++)
  {
	  graph->edge[ec].src=0;
	  graph->edge[ec].dest=i;
	  graph->edge[ec].weight= 1;
	  ec++;
	  graph->edge[ec].src=i;
	  graph->edge[ec].dest=V;
	  graph->edge[ec].weight= 1;
  }



  bellmanFord(graph, 0);

  return 0;
}
