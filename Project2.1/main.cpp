#include <iostream>
#include <stack>

using namespace std;

#define V 20


//------- Function Definitions -------//
void max_flow(int graph[V][V], int s, int t);  //Ford-Fulkerson implementation



int main() {
/*-------------------------------------------
 * ---------------NOTES----------------------
 * when a location on graph[][] == 0 -> more available flow for that edge
 *
 *
 --------------------------------------------
 ------------------------------------------*/

  //------- Constant Declarations -------//



  //------- Variable Declarations -------//
  int capacityOfEdge = 15; //if this is zero, there is no edge
  int source;
  int dest;

  //sets all initial values of the graph to zero -> these values are the flow of "edges"
  int graph[V][V];
  for(int i = 0; i < V; i++)
    for( int j = 0; j < V; j++)
      graph[i][j] = 0;

  //set graph full of capacities
  for(int i = 0; i < V; i++) {
    for(int j = 0; j < V; j++) {
      graph[i][j] = capacityOfEdge;
    }
  }

  maxFlow(graph, source, dest);

  return 0;
}
