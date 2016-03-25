// A C / C++ program for Bellman-Ford's single source 
// shortest path algorithm.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// a structure to represent a weighted edge in graph
typedef struct Edge
{
  int src, dest;
  double weight;
} Edge;

// a structure to represent a connected, directed and 
// weighted graph
typedef struct Graph
{
  // V-> Number of vertices, E-> Number of edges
  int V, E;

  // graph is represented as an array of edges.
  Edge* edge;
}Graph;

// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E)
{
  Graph* graph = (Graph*) malloc( sizeof(Graph) );
  graph->V = V;
  graph->E = E;
  graph->edge = (Edge*) malloc( graph->E * sizeof( Edge ) );
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
  for (int i = 0; i < n; ++i)
    printf("%d \t\t %d\n", i, dist[i]);
}

void showcycle(int pred[], int u, int v)
{
  int k=v;
  printf("%d<--%d<--", u,v);
  while(1)
  {
    k=pred[k];
    if(k==u)
      break;
    printf("%d<--", k);
    
  }
  printf("%d\n", u);

}

// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm. The function
// also detects negative weight cycle
void bellmanFord(Graph* graph, int src)
{
  int V = graph->V;
  int E = graph->E;
  int dist[V];
  int pred[V];

  int i;


  // Step 1: Initialize distances from src to all other vertices
  // as INFINITE
  for (i = 0; i < V; i++)
  {  
    dist[i] = INT_MAX;
    pred[i]=-1;
  }
  dist[src] = 0;

  // Step 2: Relax all edges |V| - 1 times. A simple shortest 
  // path from src to any other vertex can have at-most |V| - 1 
  // edges
  for (i = 1; i <= V-2; i++)
  {
     relax(graph,dist,pred);
  }

  // Step 3: check for negative-weight cycles. The above step 
  // guarantees shortest distances if graph doesn't contain 
  // negative weight cycle. If we get a shorter path, then there
  // is a cycle.

  // char PATH[1000];
  for (i = 0; i < E; i++)
  {
    int u = graph->edge[i].src;
    int v = graph->edge[i].dest;
    double weight = graph->edge[i].weight;
    

    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
      printf("Arbitrage Opportunity from currency %d to %d\n", u ,v);
      
      relax(graph,dist,pred);
      showcycle(pred,u,v);

      return;
    }

  }

  printArr(dist, V);

  return;
}

// Driver program to test above functions
int main()
{
  int V = 5; // Number of vertices in graph
  int E = V*(V-1); // Number of edges in graph
  E=E-V-V; // one graph for zero
  struct Graph* graph = createGraph(V, E);

  int i,j;
  int w;
  int ec=0;

  for(i=1;i<V-1;i++)
  {
    for(j=1;j<V-1;j++)
    {
      if(i==j) continue;
      printf("Enter conversion rate in base 100 for %d --> %d\n", i, j);
      graph->edge[ec].src=i;
      graph->edge[ec].dest=j;
      scanf("%d",&w);
      graph->edge[ec].weight= - log(w/100);
      ec++;
    }
  }

  for(i=1;i<V-1;i++)
  {
      graph->edge[ec].src=0;
      graph->edge[ec].dest=i;
      graph->edge[ec].weight= 1;
      ec++;
      graph->edge[ec].src=i;
      graph->edge[ec].dest=4;
      graph->edge[ec].weight= 1;
  }



  bellmanFord(graph, 0);

  return 0;
}
