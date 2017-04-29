

#include "functions.h"




int main() {
/*-------------------------------------------
 * ---------------NOTES----------------------
 * when a location on graph[][] == 0 -> no more available flow for that edge
 *
 *
 --------------------------------------------
 ------------------------------------------*/

  //------- Constant Declarations -------//



  //------- Variable Declarations -------//
  int capacityOfEdge = 15; //if this is zero, there is no edge
  int source;
  int dest;

  freopen(OUTPUT, "w", stdout);
  ifstream ifptr(INPUT, fstream::in);
  ///Have to use their input stuff for now
  int graph[V][V];
  for(int i = 0; i < V; i++)
    for( int j = 0; j < V; j++)
      graph[i][j] = 0;
  int v1, v2, c;
  if ( ifptr.is_open() ) {
    ifptr >> source; ifptr >> dest;
    while( !ifptr.eof() ) {
      ifptr >> v1; ifptr >> v2; ifptr >> c;
      graph[v1][v2] = c;
    }
  }

//  //sets all initial values of the graph to zero -> these values are the flow of "edges"
//  int graph[V][V];
//  for(int i = 0; i < V; i++)
//    for( int j = 0; j < V; j++)
//      graph[i][j] = 0;
//
//  //set graph full of capacities
//  for(int i = 0; i < V; i++) {
//    for(int j = 0; j < V; j++) {
//      graph[i][j] = capacityOfEdge;
//    }
//  }

  maxFlow(graph, source, dest);

  return 0;
}










