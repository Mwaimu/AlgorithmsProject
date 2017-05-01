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
    paths[iter][g] = parent[g];
  }
  iter++; //increment so the next path is remembered
  //if dest is reached, then return true
  return (visited[dest] == true);
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

//returns maxFlow, also (by reference) creates and keeps track of resPaths
int fordFulkerson(int graph[V][V], int source, int dest, int paths[V][V], int resGraph[V][V], int parent[V], int resFlow[V]) {
  int u, v;
//  int resGraph[V][V]; //residual graph, resGraph[i][j] is resCap of edge(i, j) -> 0 means no edge
  int maxFlow = 0;

  //set resGraph == graph -> when the path becomes zero, no more flow available
  for(u = 0; u < V; u++) {
    for(v = 0; v < V; v++) {
      resGraph[u][v] = graph[u][v];
    }
  }

  int pathNum = 0; //number of paths that DFS finds
  //while flow, find augmenting paths
  while(DFS(resGraph, source, dest, parent, paths)) {
    int resCap = 21; //residual capacity -> init higher that capacities to make any capacity possible resCap

    //find min resCap of edges along found path
    for (v = dest; v != source; v = parent[v]) {
      u = parent[v];
      resCap = min(resCap, resGraph[u][v]);
    }
    resFlow[pathNum] = resCap;
    pathNum++;
    //update flow along path found
    int e;
    for (int d = dest; d != source; d = parent[d]) {
      e = parent[d];
      resGraph[e][d] -= resCap;
      resGraph[d][e] += resCap;
    }

    maxFlow += resCap;
  }
  return maxFlow;
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

void StaticAttack(int graph[V][V], int source, int dest, int paths[V][V], int resGraph[V][V]) {
  int maxFlow = 0; //the max flow of the graph
  int delEdge[2]; //delEdge[0] is 'u' of the edge that is to be deleted
                  //delEdge[1] is 'v' of the edge that is to be deleted
  int parent[V]; //stores paths
  int resFlow[V] = {}; //stores the residual capacities of found paths


  //run FFA on graph
  maxFlow = fordFulkerson(graph, source, dest, paths, resGraph, parent, resFlow);    //this returns not only the maxflow, but also the set of edges in the augmenting paths
  cout << "max flow is: " << maxFlow << endl;
  
  int roundIterator = 0;
  while(maxFlow != 0) {
    cout << "Iteration " << roundIterator++ << endl;
    int path = 0; //iterator, keeps track of path currently looking at in paths[][]
    int v; //destination of an edge
    int maxEdge = 0;  //maximum flow going through paths from source to dest

    //finding the edge (in residual Graph) that has the most flow going through it
    for(int u = 0; u < V; u++) {
      for(int v = 0; v < V; v++) {
        /* resGraph[v][u] (notice u, v positioning) is the amount of flow that if edge(u, v) is traversed could be
         * added to the maximum flow of the graph
         *
         * graph is comprised of edges that currently exist
         */
        //is resGraph[][] (flow) is greater than maxEdge (flow) AND edge(u, v) is actually an edge
        if(resGraph[v][u] > maxEdge && graph[u][v] != 0) {
          maxEdge = resGraph[v][u]; //update maxEdge
          cout << "  MaxEdge: " << maxEdge << "  u: " << u << "  v: " << v << endl;
          delEdge[0] = u; //update deleted edge
          delEdge[1] = v;
        }
      }
    }
    //update maxFlow
    maxFlow = maxFlow - maxEdge;

    //delete maxEdge from the graphs
    graph[delEdge[0]][delEdge[1]] = 0;
    resGraph[delEdge[1]][delEdge[0]] = 0;
    resGraph[delEdge[0]][delEdge[1]] = 0;

    /* the first element is paths[path] is only zero when there are no more paths found by DFS
     * so we know that anything other than zero will either:
     *    -1 -> path to be considered at a later iteration
     *    -2 -> path with an edge that was deleted who's flow needs to be recalculated
     *    -3 -> path who has been deleted and who's flow has been recalculated
     */

    //while the first element in an paths[path][] is not zero
    while(paths[path][0] == -1 || paths[path][0] == -2 || paths[path][0] == -3) {
      v =  dest;
      //if the first element is -1
      if(paths[path][0] == -1) {
        //update 'v' until you find delete_edge's_end (delEdge[1]) OR you hit a -1 in the path meaning
        // it's at the beginning -> edge looking for is not in path
        while(v != delEdge[1] && v != (-1)) {
          cout << "this is where it starts" << paths[path][v] << endl;
          v = paths[path][v]; //set v to the parent of v
        }
        //for the edge found above -> edge_above,  if start of edge_above is equal to the start of
        //  edge_to_be_deleted    flag it as -2 so we know it needs to have flow recalculated
        if(paths[path][v] == delEdge[0]) {
          paths[path][0] = -2;
        }
      }
      path++;
    }

    path = 0; //start back at the beginning of paths[][]
    //for each of the paths that start with a -2, we have to reduce the elements in the residual graph by the lowest in the
    while(paths[path][0] == -1 || paths[path][0] == -2 || paths[path][0] == -3) { //If it ever equals zero, no more paths exist
      //if path has been marked as "needs to be recalculated"
      if(paths[path][0] == -2) {
        //update flow along path found
        int u;
        //run through the path from finish to start
        //(set v to end; go until v is at the beginning; set v to it's parent)
        for (v = dest; v != source; v = u) {
          u = paths[path][v]; //u = the parent of v
          if(resGraph[u][v] != 0 || resGraph[v][u] != 0) { //doesn't take away a residual capacity from a node that was just deleted
            resGraph[u][v] = resGraph[u][v] + resFlow[path];
            resGraph[v][u] = resGraph[v][u] - resFlow[path];
          }
        }
        //means the residual capacity has been taken out of deleted path and can be skipped
        paths[path][0] = -3;
      }
      path++;
    }
    cout << "  End of iteration flow: " << maxFlow << endl;
  }

  cout << "max flow at end is: " << maxFlow << endl;
  return;
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

int main() {
  int paths[V][V] = {}; //keeps track of residual paths
  // Let us create a graph shown in the above example
  int source = 0; //source node
  int dest = 5;   //destination node
  int resGraph[V][V] = {};  //graph of residual flow


  //TODO: this will obviously have to be changed

  //keeps track of capacity at edge(i, j)
  int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                      {0, 0, 0, 12, 0, 0},
                      {0, 4, 0, 0, 14, 0},
                      {0, 0, 9, 0, 0, 20},
                      {0, 0, 0, 7, 0, 4},
                      {0, 0, 0, 0, 0, 0}   };

  /* TODO: could change to maybe...
   * cin >> node1 >> node2;
   * graph[node1][node2] = rand % 20 + 1; //random number between 1 and 20
   */


  StaticAttack(graph, source, dest, paths, resGraph);

  cout << "Out of StaticAttack()" << endl;
  //just prints the graph
  for(int u = 0; u < V; u++) {
    for(int v = 0; v < V; v++) {
      cout << resGraph[u][v] << " ";
    }
    cout << endl;
  } cout << endl;


  return 0;
}
