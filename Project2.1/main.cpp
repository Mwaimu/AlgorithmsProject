#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

#define V 20


//------- Function Definitions -------//
void maxFlow(int graph[V][V], int s, int t);  //Ford-Fulkerson implementation
bool findPath(int residual[V][V], int source, int dest, int parent[]); //Finds paths...



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

//Returns max flow from source to dest in given graph
void maxFlow(int graph[V][V], int source, int dest) {
  int u, v; //start and finish of edges
  int it = 0;
  int maxFlow = 0;

  int residual[V][V]; //residual[i][j] is residual capacity at edge(i,j)

  //copy the graphs
  for (u = 0; u < V; u++)
    for (v = 0; v < V; v++)
      residual[u][v] = graph[u][v];

  int path[V]; //holds the augmenting path

  while(findPath(residual, source, dest, path)) {

  }


  return;
}

//finds paths
bool findPath(int residual[V][V], int source, int dest, int parent[]) {
  bool visited[V]; //to know if nodes have been visited
  memset(visited, 0, sizeof(visited)); //make available nodes read false

  stack<int> stack;   //keeps track of nodes to visit
  stack.push(source);
  visited[source] = true;
  parent[source] = -1;  //null parent basically

  while(!stack.empty()) {   //do stuff while there are elements in the stack
    int u = stack.top(); //source of the edge
    stack.pop();

    //look and see if the source is connected to any of the elements in residual \
    and if the nodes it is connected to have any flow space left
    //used v to keep in mind this is the destination of the edge
    for(int v = 0; v < V; v++) {
      if(visited[v] == 0 && residual[u][v] > 0) {
        //if it's not been visited and there is flow left at edge(u,v)

        stack.push(v);  //then add it to the stack of nodes to check next
        parent[v] = u;  //make the parent of node v == u
        visited[v] = true;  //show that v has been visited
      }
    }
  }
  //if there is a path then the destination will have been visited
  return visited[dest];
}








