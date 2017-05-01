/*  Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 *
 * Description:
 *  Compare attacking algorithms (static and reactive) on a network that will (reactive) and won't (static)
 *  recalculate maxFlow after each attack.
 */

#include <iostream>
#include <limits.h>
#include <string.h>
#include <stack>
using namespace std;


//TODO: if we use this its going to have to be much larger than 6...
// Number of vertices in given graph
#define V 6

/* returns true if path fom source to dest in residual graph.
 * parent keeps track of the path
 * paths[][] keeps track of all the paths that the DFS finds
 */
bool DFS(int resGraph[V][V], int source, int dest, int parent[], int paths[V][V]) {
  static int iter = 0;
  //All vertices as not visited for each "node"
  bool visited[V];
  memset(visited, 0, sizeof(visited));

  // Create a stack, stack source "node", source parent as "null", source visited
  stack<int> stack;
  stack.push(source);
  visited[source] = true;
  parent[source] = -1;

  //while stack not empty
  while (!stack.empty()) {
    int u = stack.top();  //u = next "node" in stack
    stack.pop();

    //for each of the "nodes"
    for (int v = 0; v < V; v++) {
      //if it's not visited and there is flow left in the graph
      if (visited[v] == false && resGraph[u][v] > 0) {
        stack.push(v); //push visited "node" to stack
        parent[v] = u;
        visited[v] = true;
      }
    }
  }
  //assign parent[] to paths[][] to keep track of paths
  for(int g = 0; g < V; g++) {
    cout << parent[g] << " ";
    paths[iter][g] = parent[g];
  }
  iter++; //increment so the next path is remembered
  cout << endl;
  //if dest is reached, then return true
  return (visited[dest] == true);
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

//returns maxFlow, also (by reference) creates and keeps track of resPaths
int fordFulkerson(int graph[V][V], int source, int dest, int paths[V][V], int resGraph[V][V], int visited2[V]) {
  cout << "   Entered fordFulkerson" << endl;
  int u, v;
//  int resGraph[V][V]; //residual graph, resGraph[i][j] is resCap of edge(i, j) -> 0 means no edge
  int parent[V]; //stores path
  int maxFlow = 0;

  //set resGraph == graph -> when the path becomes zero, no more flow available
  for(u = 0; u < V; u++) {
    for(v = 0; v < V; v++) {
      resGraph[u][v] = graph[u][v];
    }
  }

  //while flow, find augmenting paths
  while(DFS(resGraph, source, dest, parent, paths)) {
    int resCap = 21; //residual capacity -> init higher that capacities to make any capacity possible resCap

    //find min resCap of edges along found path
    for (v = dest; v != source; v = parent[v]) {
      u = parent[v];
      resCap = min(resCap, resGraph[u][v]);
    }

    //update flow along path found
    for (v = dest; v != source; v = parent[v]) {
      u = parent[v];
      resGraph[u][v] -= resCap;
      resGraph[v][u] += resCap;
    }
    maxFlow += resCap;
  }
  return maxFlow;
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

void StaticAttack(int graph[V][V], int source, int dest, int paths[V][V], int resGraph[V][V], int visited2[V]) {
  int maxFlow = 0;
//  int resGraph[V][V]; //residual graph, resGraph[i][j] is resCap of edge(i, j) -> 0 means no edge
//  bool visited2[V];
  int delEdge[2];
  int max_edge = 0;

  //run FFA on graph
  maxFlow = fordFulkerson(graph, source, dest, paths, resGraph, visited2);    //this returns not only the maxflow, but also the set of edges in the augmenting paths

  cout << "   Static Attack gets through FFA" << endl;

  int path = 0;
  int  v;

  for(int u = 0; u < V; u++) {
    for(int v = 0; v < V; v++) {
      cout << resGraph[u][v] << " ";
    }
    cout << endl;
  } cout << endl;



  //finding the maxFlow through of the residual edges
  for(int u = 0; u < V; u++) {
    for(int v = 0; v < V; v++) {
      if(resGraph[v][u] > max_edge) {
        cout << "MAX_EDGE: " << max_edge << endl;
        maxFlow = resGraph[v][u];
        delEdge[0] = v;
        delEdge[1] = u;
      }
    }
  }

  cout << "A:   u: " << delEdge[0] << "  A: " << delEdge[1] << endl;


  //delete max_edge	//delete it (make graph[u][v] = 0)
  graph[delEdge[0]][delEdge[1]] = 0;
  resGraph[delEdge[0]][delEdge[1]] = 0;
  //max_edge == resGraph[largestFlow_u][largestFlow_v]


  while(paths[path][0] == -1 || paths[path][0] == -2) { //If it ever equals zero, no path exists
    cout << "checking path " << path  << "     ";
    //this is just to check the path (output)
    for(int j = 0; j < V; j++) {
      cout << paths[path][j] << " ";
    }
    cout << endl;

    v = V - 1;
    if(paths[path][0] != -2) {
      while(v != delEdge[1]) { //update 'v' until you find a 'v' that is equal to largestFlow_v
        v = paths[path][v]; //set v to the parent of v
      }
      cout << "v: " << v << ", delEdge[0]: " << delEdge[0] << endl;
      if(paths[path][v] == delEdge[0]) { //If true, this path needs the edge we're deleting. So, flag it as -2.
        cout << "    found a match   " << endl;
        paths[path][0] = -2;
      }
    }
    path++;
  }

  cout << "  paths after delete: " << endl;
  for(int i = 0; i < V; i++) {
    for(int j = 0; j < V; j++) {
      cout << paths[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

    //then have to recalculate the flow using mincut
//    maxFlow = print_mincut(graph, visited2, source, dest, resGraph);


    //paths are deleted by taking the residual capacity of the path associated with the deleted edge and subtracting it from the flow of each edge in the path.
//  }
  return;
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

int main() {
  int paths[V][V] = {}; //keeps track of residual paths
  // Let us create a graph shown in the above example
  int source = 0;
  int dest = 5;
  int resGraph[V][V] = {};
  int visited2[V] = {};


  //TODO: this will obviously have to be changed

  //keeps track of capacity at edge(i, j)
  int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                      {0, 0, 10, 12, 0, 0},
                      {0, 4, 0, 0, 14, 0},
                      {0, 0, 9, 0, 0, 20},
                      {0, 0, 0, 7, 0, 4},
                      {0, 0, 0, 0, 0, 0}   };

  /* TODO: could change to maybe...
   * cin >> node1 >> node2;
   * graph[node1][node2] = rand % 20 + 1; //random number between 1 and 20
   */

//  cout << "The maximum possible flow is " << fordFulkerson(graph, source, dest, paths, resGraph, visited2) << endl;

// ----- prints what's in paths before anything happens -----
//  cout << "paths is: " << endl;
//  for(int i = 0; i < V; i++) {
//    for(int j = 0; j < V; j++) {
//      cout << paths[i][j] << " ";
//    }
//    cout << endl;
//  }
//  cout << endl;

  for(int u = 0; u < V; u++) {
    for(int v = 0; v < V; v++) {
      cout << graph[u][v] << " ";
    }
    cout << endl;
  } cout << endl;

  cout << "  Testing static Attack" << endl;
  StaticAttack(graph, source, dest, paths, resGraph, visited2);

  cout << "leaves attack" << endl;



  return 0;
}
