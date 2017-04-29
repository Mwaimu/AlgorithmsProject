

#include "functions.h"




int main() {
/*-------------------------------------------
 * ---------------NOTES----------------------
 * when a location on graph[][] == 0 -> no more available flow for that edge
 *
 * graph[][] is initially full of capacities
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
  int path1[V] = {};
  int *path = maxFlow(graph, source, dest, path1);
  cout << endl;
  for(int i = 0; i < V; i++) {
    cout << path[i] << "  ";
  }

  cout << endl;
  return 0;
}


void FordFulkerson(int graph[V][V], int source, int dest) {
  int augPaths[V][V];  //to keep track of the augmenting paths
  int maxFlow = 0;
  int residualGraph[V][V];

  //initial empty flow
  for(int i = 0; i < V; i++) {
    for(int j = 0; i < V; i++) {
      residualGraph[i][j] = 0;
    }
  }

  //TODO: calculate residual network G_f
  bool visited[V]; //used to keep track of visited nodes
  for(int i = 0; i < V; i++) {
    visited[i] = 0;
  }

  int first = 0;  //keeps track of the augmenting path you are on
                  //called first because it is the first in the order
  stack<int> stack;
  stack.push(source);
  visited[source] = true;
  while(!stack.empty()) {
    int u = stack.top(); //take the first element off the stack
    stack.pop();
    //check each of the nodes in the graph
    for(int v = 0; v < V; v++) {
      //if they have not been visited and have a residualFlow(from residualGraph)
      // it means there is a connection between the two nodes
      if(visited[v] == 0 && residualGraph[u][v] > 0) {
        /*  first:  for the augmenting path you are on
         *      u:  the "node" last popped off the stack -> making it the "node" that is currently being considered as the source of an edge
         *      v:  what's being iterated through by the for loop above -> effectively searching for the "node" that's the destination of an edge
         */
        augPaths[first][u] = v;
        stack.push(v);
        visited[v] = true;
      }
    }
    first++; //increase the number of augmenting paths you have
  }


  first = 0; //reset to start back up at top
  int u, v;
  //TODO: while there are paths from s to t
  //select augPath in G_f
  while(augPaths[first][0] != 0) {
    //say pick paths from top to botton of the array
    for(u = source; v != dest; u = augPaths[first][v]) {




    }




    first++;
  }








}







