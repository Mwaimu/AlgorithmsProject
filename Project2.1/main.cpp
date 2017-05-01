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
#include <cstdlib>

using namespace std;


//TODO: if we use this its going to have to be much larger than 6...
// Number of vertices in given graph
#define V 13

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
  cout << "Entered FFA" << endl;
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
  int initialMaxFlow;
  int delEdge[2]; //delEdge[0] is 'u' of the edge that is to be deleted
                  //delEdge[1] is 'v' of the edge that is to be deleted
  int parent[V]; //stores paths
  int resFlow[V] = {}; //stores the residual capacities of found paths
  int roundIterator = 0;


  //run FFA on graph
  maxFlow = fordFulkerson(graph, source, dest, paths, resGraph, parent, resFlow);    //this returns not only the maxflow, but also the set of edges in the augmenting paths
  initialMaxFlow = maxFlow;
  cout << roundIterator << " " << maxFlow << endl;

  while(maxFlow != 0) {
//    cout << "Iteration " << roundIterator++ << endl;
    int path = 0; //iterator, keeps track of path currently looking at in paths[][]
    int v; //destination of an edge
    int maxEdge = 0;  //maximum flow going through paths from source to dest


    for(int first = 0; first < V; first++) {
      for (int second = 0; second < V; second++) {
        cout << paths[first][second] << "  ";
      }
      cout << endl;
    }      cout << endl;


    //finding the edge (in residual Graph) that has the most flow going through it
    for(int u = 0; u < V - 2; u++) {
      for(int v = 0; v < V - 2; v++) {
        /* resGraph[v][u] (notice u, v positioning) is the amount of flow that if edge(u, v) is traversed could be
         * added to the maximum flow of the graph
         *
         * graph is comprised of edges that currently exist
         */
        //is resGraph[][] (flow) is greater than maxEdge (flow) AND edge(u, v) is actually an edge
        //TODO: changed this to accommodate the idea of having negative deleted nodes ----- this is what it WAS
//        if(resGraph[v][u] > maxEdge && graph[u][v] != 0) {
        //TODO: changed this to accommodate the idea of having negative deleted nodes ----- this is what it IS
        if(resGraph[v][u] > maxEdge && graph[u][v] > 0) {
          maxEdge = resGraph[v][u]; //update maxEdge
          delEdge[0] = u; //update deleted edge
          delEdge[1] = v;
          cout << "MAXEDGE: " << maxEdge << "   u: " << delEdge[0] << "   v: " << delEdge[1] << endl;
        }
      }
    }
    //update maxFlow
    maxFlow = maxFlow - maxEdge;

    //delete maxEdge from the graphs
    //TODO: changed this to accommodate the idea of having negative deleted nodes ----- this is what it WAS
//    graph[delEdge[0]][delEdge[1]] = graph[delEdge[0]][delEdge[1]];
    //TODO: changed this to accommodate the idea of having negative deleted nodes ----- this is what it IS
    graph[delEdge[0]][delEdge[1]] = -graph[delEdge[0]][delEdge[1]];
    resGraph[delEdge[1]][delEdge[0]] = 0;
    resGraph[delEdge[0]][delEdge[1]] = 0;

    /* the first element is paths[path] is only zero when there are no more paths found by DFS
     * so we know that anything other than zero will either:
     *    -1 -> path to be considered at a later iteration
     *    -2 -> path with an edge that was deleted who's flow needs to be recalculated
     *    -3 -> path who has been deleted and who's flow has been recalculated
     */

    //while the first element in an paths[path][] is not zero
    while(paths[path][source] == -1 || paths[path][source] == -2 || paths[path][source] == -3) {
      v =  dest;
      //if the first element is -1
      if(paths[path][source] == -1) {
        //update 'v' until you find delete_edge's_end (delEdge[1]) OR you hit a -1 in the path meaning
        // it's at the beginning -> edge looking for is not in path
        while(v != delEdge[1] && v != (-1)) {
          v = paths[path][v]; //set v to the parent of v
        }
        //for the edge found above -> edge_above,  if start of edge_above is equal to the start of
        //  edge_to_be_deleted    flag it as -2 so we know it needs to have flow recalculated
        if(paths[path][v] == delEdge[0]) {
          paths[path][source] = -2;
        }
      }
      path++;
    }

    path = 0; //start back at the beginning of paths[][]
    //for each of the paths that start with a -2, we have to reduce the elements in the residual graph by the lowest in the
    while(paths[path][source] == -1 || paths[path][source] == -2 || paths[path][source] == -3) { //If it ever equals zero, no more paths exist
      //if path has been marked as "needs to be recalculated"
      if(paths[path][source] == -2) {
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
        paths[path][source] = -3;
      }
      path++;
    }
    cout << ++roundIterator << " " << maxFlow << " " << (maxFlow*2)/initialMaxFlow << endl;
  }

  return;
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

void ReactiveAttack(int graph[V][V], int source, int dest, int paths[V][V], int resGraph[V][V]) {
  int maxFlow = 0; //the max flow of the graph
  int initialMaxFlow;
  int delEdge[2]; //delEdge[0] is 'u' of the edge that is to be deleted
                  //delEdge[1] is 'v' of the edge that is to be deleted
  int parent[V]; //stores paths
  int resFlow[V] = {}; //stores the residual capacities of found paths
  int roundIterator = 0;


  //run FFA on graph
  maxFlow = fordFulkerson(graph, source, dest, paths, resGraph, parent, resFlow);    //this returns not only the maxflow, but also the set of edges in the augmenting paths
  initialMaxFlow = maxFlow;
  cout << roundIterator << " " << maxFlow << endl;



    int ROUND_IT_IS = 0;
  while(maxFlow != 0) {
    cout << "\nROUND IT IS:  " << ROUND_IT_IS << endl;
    ROUND_IT_IS++;

//    cout << "Iteration " << roundIterator++ << endl;
    int path = 0; //iterator, keeps track of path currently looking at in paths[][]
    int v; //destination of an edge
    int maxEdge = 0;  //maximum flow going through paths from source to dest

    for(int first = 0; first < V; first++) {
      for (int second = 0; second < V; second++) {
        cout << paths[first][second] << "  ";
      }
      cout << "   resCap: " << resFlow[first];
      cout << endl;
    }      cout << endl;


    //finding the edge (in residual Graph) that has the most flow going through it
    for(int u = 0; u < V-2; u++) {
      for(int v = 0; v < V-2; v++) {
        /* resGraph[v][u] (notice u, v positioning) is the amount of flow that if edge(u, v) is traversed could be
         * added to the maximum flow of the graph
         *
         * graph is comprised of edges that currently exist
         */
        //if resGraph[][] (which is a flow) is greater than maxEdge (flow) AND edge(u, v) is actually an edge
        //TODO: changed this to accommodate the idea of having negative deleted nodes ----- this is what it WAS
//        if(resGraph[v][u] > maxEdge && graph[u][v] != 0) {
        //TODO: changed this to accommodate the idea of having negative deleted nodes ----- this is what it IS
        if(resGraph[v][u] > maxEdge && graph[u][v] > 0) {
          maxEdge = resGraph[v][u]; //update maxEdge
          delEdge[0] = u; //update deleted edge
          delEdge[1] = v;
          cout << "  MAXEDGE: " << maxEdge << "   u: " << delEdge[0] << "   v: " << delEdge[1] << endl;
        }
      }
    }
    //update maxFlow
    maxFlow = maxFlow - maxEdge;
    cout << "  Deleted Edge:   (" << delEdge[0] << ", " << delEdge[1] << ")" << endl;

    //delete maxEdge from the graphs
    //TODO: changed this to accommodate the idea of having negative deleted nodes ----- this is what it WAS
//    graph[delEdge[0]][delEdge[1]] = graph[delEdge[0]][delEdge[1]];
    //TODO: changed this to accommodate the idea of having negative deleted nodes ----- this is what it IS
    graph[delEdge[0]][delEdge[1]] = -graph[delEdge[0]][delEdge[1]];
    resGraph[delEdge[1]][delEdge[0]] = 0;
    resGraph[delEdge[0]][delEdge[1]] = 0;

    /* the first element is paths[path] is only zero when there are no more paths found by DFS
     * so we know that anything other than zero will either:
     *    -1 -> path to be considered at a later iteration
     *    -2 -> path with an edge that was deleted who's flow needs to be recalculated
     *    -3 -> path who has been deleted and who's flow has been recalculated
     */

    //while the first element in an paths[path][] is not zero
    while(paths[path][source] == -1 || paths[path][source] == -2 || paths[path][source] == -3) {
      v =  dest;
      //if the first element is -1
      if(paths[path][source] == -1) {
        //update 'v' until you find delete_edge's_end (delEdge[1]) OR you hit a -1 in the path meaning
        // it's at the beginning -> edge looking for is not in path
        while(v != delEdge[1] && v != (-1)) {
          v = paths[path][v]; //set v to the parent of v
        }
        //for the edge found above -> edge_above,  if start of edge_above is equal to the start of
        //  edge_to_be_deleted    flag it as -2 so we know it needs to have flow recalculated
        if(paths[path][v] == delEdge[0]) {
          paths[path][source] = -2;
        }
      }
      path++;
    }

    path = 0; //start back at the beginning of paths[][]
    //for each of the paths that start with a -2, we have to reduce the elements in the residual graph by the lowest in the
    while(paths[path][source] == -1 || paths[path][source] == -2 || paths[path][source] == -3) { //If it ever equals zero, no more paths exist
      //if path has been marked as "needs to be recalculated"
      if(paths[path][source] == -2) {
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
        paths[path][source] = -3;
      }
      path++;
    }
    cout << "  maxFlow: " << maxFlow << "   50%: " << (maxFlow*2)/initialMaxFlow << endl;
    roundIterator++;

    //have to rest paths. Only need to reset first element because rest will get written over
    for(int first = 0; first < V; first++) {
      paths[first][0] = 0;
    }

    //clear path
    paths[V][V] = {};
    maxFlow = fordFulkerson(graph, source, dest, paths, resGraph, parent, resFlow);    //this returns not only the maxflow, but also the set of edges in the augmenting paths

  }
  return;
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------


int main() {
  int paths[V][V] = {}; //keeps track of residual paths
  // Let us create a graph shown in the above example
  int source = V-2; //source node
  int dest = V-1;   //destination node
  int resGraph[V][V] = {};  //graph of residual flow
  int graph[V][V];
  //TODO: this will obviously have to be changed
//  //keeps track of capacity at edge(i, j)
//  int graph[V][V] = { { 0,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},   //THIS GRAPH HAS BEEN REFLECTED TO PUT THE SOURCE AND DESTINATION AT THE
//                      { 0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},  //LAST 2 POSITIONS OF THE GRAPH. THE CODE ALSO REFLECTS IT AND IT
//                      { 0,  0,  0,  0, 12,  4,  0,  0,  0,  0,  0,  0,  0},  //WORKS JUST FINE
//                      { 0,  0,  0,  0, 15,  0,  0,  0,  0,  0,  0,  0,  0},
//                      { 0,  0,  0,  0,  0,  0,  9,  0,  0,  0,  0,  0,  0},
//                      { 0,  0,  0,  0,  0,  0,  0,  0,  7,  0,  0,  0,  0},
//                      { 0,  0,  0,  0,  0,  0,  0, 13,  0,  0,  0,  0,  0},
//                      { 0,  0,  0,  0,  0,  0,  0,  0,  8, 14,  0,  0,  0},
//                      { 0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  0,  0},
//                      { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9,  0, 20},
//                      { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 20},
//                      {20, 20,  0, 20,  0,  0,  0,  0,  0,  0,  0,  0,  0},
//                      { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
//  };

//   TODO: could change to maybe...
  int node1, node2;
  cin >> node1 >> node2;
  while(node1 != -1) {
    graph[node1][node2] = (rand() % 20) + 1; //random number between 1 and 20
    cin >> node1 >> node2;
  }



//  cout << "Enter StaticAttack" << endl;
//  StaticAttack(graph, source, dest, paths, resGraph);
//  cout << endl;



///* for the variable k node stuff
// *    wipe the graph's source and destination columns/rows
// *    assign k random capacities (1->20)
// *    then run the graph repeating for 30 -> 60 iterations
//*/
//
//  int numIters = 30;
//  for(int round = 0; round < numIters; round++) {
    //make all the deleted nodes positive again
    //  (they were made negative instead of deleting entirely as not to loose information)
//    cout << "print graph " << endl;
    for(int u = 0; u < V; u++) {
      for(int v = 0; v < V; v++) {
        if(graph[u][v] < 0)
          graph[u][v] = -graph[u][v];
//        cout << graph[u][v] << " ";
      }
//      cout << endl;
    }
  cout << endl;
//
//    for(int i = 0; i < V; i++) {
//      //wipe the source row
//      graph[source][i] = 0;
//      //wipe dest column
//      graph[i][dest] = 0;
//    }
//
//    //make k random connections to the source
//    for(int k = (round +30); k < numIters; k++) {
//      graph[source][(rand()% V) - 2] = (rand() % 20) + 1;
//    }
//    //make k random connections to the source
//    for(int k = (round +30); k < numIters; k++) {
//      graph[(rand()% V) - 2][dest] = (rand() % 20) + 1;
//    }
//
//    //TODO: this is a problem because we have deleted a bunch of nodes and have no way of putting them back to rerun
//    //TODO:    could make the numbers in the graph that have been deleted == -1 and then run through it to make stuff positive again??
//
//    StaticAttack(graph, source, dest, paths, resGraph);
//    cout << endl;
//
//  }
  cout << "Enter ReactiveAttack" << endl;
  ReactiveAttack(graph, source, dest, paths, resGraph);

  return 0;
}
