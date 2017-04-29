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

///things to know/remember  and/or NOTES
/* -------------------------  NOTES  ---------------------------------------------
 * -------------------------------------------------------------------------------
 * I forgot what I was going to put in here but if you have questions text me
 *
 * I believe that what we really needed (problem) for each of the algorithms was that
 *    we didn't a way to access the augmenting paths outside of FFA link we needed
 *    this fixes that
 *
 * There's some stuff marked "TODO"
 *    that should probably pop up in yellow? -> Shelby
 *                               and pink? -> Ben  that you can look at
 *
 * Also, this was just an idea that I had. May or ma not work so change as necessary
 *
 * This file is the only one that is needed. help.cpp is the code this was based off of
 *    but this file alone is the program as of now
 ---------------------------------------------------------------------------------
 ---------------------------------------------------------------------------------*/



//TODO: if we use this its going to have to be much larger than 6...
// Number of vertices in given graph
#define V 6

/* returns true if path fom source to dest in residual graph.
 * parent keeps track of the path
 * arr[][] keeps track of all the paths that the DFS finds
 */
bool DFS(int resGraph[V][V], int source, int dest, int parent[], int arr[V][V]) {
  static int iter = 0;
  //All vertices as not visited for each "node"
  bool visited[V];
  memset(visited, 0, sizeof(visited));

  // Create a stack, stack source "node", source parent as "null", source visited
  stack<int> q;
  q.push(source);
  visited[source] = true;
  parent[source] = -1;

  //while stack not empty
  while (!q.empty()) {
    int u = q.top();  //u = next "node" in stack
    q.pop();

    //for each of the "nodes"
    for (int v = 0; v < V; v++) {
      //if it's not visited and there is flow left in the graph
      if (visited[v] == 0 && resGraph[u][v] > 0) {
        q.push(v); //push visited "node" to stack
        parent[v] = u;
        visited[v] = true;
      }
    }
  }
  //assign parent[] to arr[][] to keep track of paths
  for(int g = 0; g < V; g++) {
    cout << parent[g] << " ";
    arr[iter][g] = parent[g];
  }
  iter++; //increment so the next path is remembered
  cout << endl;
  //if dest is reached, then return true
  return (visited[dest] == 0);
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

//returns maxFlow, also (by reference) creates and keeps track of resPaths
int fordFulkerson(int graph[V][V], int source, int dest, int arr[V][V]) {
  int u, v;
  int resGraph[V][V]; //residual graph, resGraph[i][j] is resCap of edge(i, j) -> 0 means no edge
  int parent[V]; //stores path
  int maxFlow = 0;
  int resCap = 21; //residual capacity -> init higher that capacities to make any capacity possible resCap

  //set resGraph == graph -> when the path becomes zero, no more flow available
  for (u = 0; u < V; u++) {
    for (v = 0; v < V; v++) {
      resGraph[u][v] = graph[u][v];
    }
  }

  //while flow, find augmenting paths
  while (DFS(resGraph, source, dest, parent, arr)) {
    //find min resCap of edges along found path
    for (v=dest; v!=source; v=parent[v]) {
      u = parent[v];
      resCap = min(resCap, resGraph[u][v]);
    }

    //update flow along path found
    for (v=dest; v != source; v=parent[v]) {
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

int main() {
  int arr[V][V] = {}; //keeps track of residual paths
  // Let us create a graph shown in the above example


  //TODO: this will obviously have to be changed

  //keeps track of capacity at edge(i, j)
  int graph[V][V] = { {0, 16, 13,  0,  0,  0},
                      {0,  0, 10, 12,  0,  0},
                      {0,  4,  0,  0, 14,  0},
                      {0,  0,  9,  0,  0, 20},
                      {0,  0,  0,  7,  0,  4},
                      {0,  0,  0,  0,  0,  0}   };

  /* TODO: could change to maybe...
   * cin >> node1 >> node2;
   * graph[node1][node2] = rand % 20 + 1; //random number between 1 and 20
   */

  cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5, arr) << endl;

  //this just prints the the paths
  for(int i = 0; i < V; i++) {
    cout << i << endl;
    for(int j = 0; j < V; j++) {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  return 0;
}
