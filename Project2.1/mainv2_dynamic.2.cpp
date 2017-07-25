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
#define E 899 //Number of edges to be considered
#define V 755 //Number of vertices to be considered (753 given + S + D)

#define testV 13
/* returns true if path fom source to dest in residual graph.
 * parent keeps track of the path
 * paths[][] keeps track of all the paths that the DFS finds
 */
bool DFS(int** resGraph, int source, int dest, int parent[testV], int** paths) {
//  cout << "     in DFS" << endl;
  static int iter = 0;
  //All vertices as not visited for each "node"
  bool visited[testV];
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
    for (int v = 0; v < testV; v++) {
      //if it's not visited and there is flow left in the graph
      if (visited[v] == false && resGraph[u][v] > 0) {
        stack.push(v); //push visited "node" to stack
        parent[v] = u;
        visited[v] = true;
      }
    }
  }
  //assign parent[] to paths[][] to keep track of paths
  for(int g = 0; g < testV; g++) {
//    cout << parent[g] << " ";
    paths[iter][g] = parent[g];
  }

  iter++; //increment so the next path is remembered
  //if dest is reached, then return true
  return (visited[dest] == true);
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

//returns maxFlow, also (by reference) creates and keeps track of resPaths
int fordFulkerson(int** graph, int source, int dest, int** paths, int** resGraph, int parent[testV], int resFlow[testV]) {

//  cout << "     in FFA" << endl;
  int u, v;
//  int resGraph[V][V]; //residual graph, resGraph[i][j] is resCap of edge(i, j) -> 0 means no edge
  int maxFlow = 0;

  //set resGraph == graph -> when the path becomes zero, no more flow available
  for(u = 0; u < testV; u++) {
    for(v = 0; v < testV; v++) {
      resGraph[u][v] = graph[u][v];
    }
  }

  int pathNum = 0; //number of paths that DFS finds
  //while flow, find augmenting paths

  while(DFS(resGraph, source, dest, parent, paths)) {
    int resCap = 21; //residual capacity -> init higher that capacities to make any capacity possible resCap

    //find min resCap of edges along found path
//    cout << endl;
    for (v = dest; v != source; v = parent[v]) {
      u = parent[v];
//      cout << u << " -> " << v <<  "  : " << resGraph[u][v];
      resCap = min(resCap, resGraph[u][v]);
//      cout << "  So, rescap = " << resCap << endl;
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
//    cout << "\n   resFlow: \n     ";
//    for(int x = 0; x < testV; x++) {
//      cout << resFlow[x] << " ";
//    }

    maxFlow += resCap;
//    cout << "\n    resCap: " << resCap << "  flow: " << maxFlow<< endl;
  }
  return maxFlow;
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------



int StaticAttack(int** graph, int source, int dest, int** paths, int** resGraph, int* resFlow) {
  int delEdge[2]; //delEdge[0] is 'u' of the edge that is to be deleted
  //delEdge[1] is 'v' of the edge that is to be deleted
  int roundIterator = 0;
  int flow;

//    cout << "Iteration " << roundIterator++ << endl;
  int path = 0; //iterator, keeps track of path currently looking at in paths[][]
  int v; //destination of an edge
  int maxEdge = 0;  //maximum flow going through paths from source to dest

  //finding the edge (in residual Graph) that has the most flow going through it
  for(int u = 0; u < testV - 2; u++) {
    for(int v = 0; v < testV - 2; v++) {
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
//        cout << "      MAXEDGE: " << maxEdge << "  u: " << delEdge[0] << "  v: " << v << endl;
      }
    }
  }
  //update flow
  flow = maxEdge;

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


  return flow;
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

int ReactiveAttack(int** graph, int source, int dest, int** paths, int** resGraph, int resFlow[testV]) {
  int maxFlow = 0; //the max flow of the graph
  int delEdge[2]; //delEdge[0] is 'u' of the edge that is to be deleted
  //delEdge[1] is 'v' of the edge that is to be deleted
  int path = 0; //iterator, keeps track of path currently looking at in paths[][]
  int v; //destination of an edge
  int maxEdge = 0;  //maximum flow going through paths from source to dest

  delEdge[0] = 0; delEdge[1] = 0;

//  cout << "paths: \n ";
//  for(int first = 0; first < testV; first++) {
//    for (int second = 0; second < testV; second++) {
//      cout << paths[first][second] << "  ";
//    }
//    cout << "   resCap: " << resFlow[first];
//    cout << endl;
//  }      cout << endl;

  //finding the edge (in residual Graph) that has the most flow going through it
  for(int u = 0; u < testV-2; u++) {
    for(int v = 0; v < testV-2; v++) {
      /* resGraph[v][u] (notice u, v positioning) is the amount of flow that if edge(u, v) is traversed could be
       * added to the maximum flow of the graph
       *
       * graph is comprised of edges that currently exist
       */
      //if resGraph[][] (which is a flow) is greater than maxEdge (flow) AND edge(u, v) is actually an edge
      if(resGraph[v][u] > maxEdge && graph[u][v] > 0) {
        maxEdge = resGraph[v][u]; //update maxEdge
        delEdge[0] = u; //update deleted edge
        delEdge[1] = v;
//        cout << "  MAXEDGE: " << maxEdge << "   u: " << delEdge[0] << "   v: " << delEdge[1] << endl;
      }
      else if(resGraph[v][u] == maxEdge && graph[u][v] > 0) {
        //if capacity of maxEdge (edge to be deleted) is smaller than the capacity of the edge
        //looking at, then new maxEdge
        if(graph[delEdge[0]][delEdge[1]] < graph[u][v]) {
          maxEdge = resGraph[v][u]; //update maxEdge
          delEdge[0] = u; //update deleted edge
          delEdge[1] = v;
//          cout << "  MAXEDGE: " << maxEdge << "   u: " << delEdge[0] << "   v: " << delEdge[1] << endl;
        }
      }
    }
  }
  //update maxFlow
  maxFlow = maxEdge;
//  cout << "  Deleted Edge:   (" << delEdge[0] << ", " << delEdge[1] << ")" << endl;

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

  //have to rest paths. Only need to reset first element because rest will get written over
  for(int first = 0; first < testV; first++) {
    paths[first][0] = 0;
  }
  //clear path
  paths[testV][testV] = {};

  return maxFlow;
}

///---------------------------------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------------------------------

int main() {
  // Allocate 2D paths array
  //keeps track of residual paths
  int** paths = new int*[testV];
  for(int i = 0; i < testV; ++i){
    paths[i] = new int[E];
  }
  // Let us create a graph shown in the above example

  // resGraph: graph of residual flow
  // Allocate 2D resGraph array
  int** resGraph = new int*[testV];
  for(int i = 0; i < testV; ++i){
    resGraph[i] = new int[testV];
  }

  int source = testV-2; //source node
  int dest = testV-1;   //destination node

  //TODO: this will obviously have to be changed
  //keeps track of capacity at edge(i, j)

  // graph array
  // Allocate 2D graph array
  int** graph = new int*[testV];
  for(int i = 0; i < testV; ++i){
    graph[i] = new int[testV];
  }

//  //Reads input to graph array from piped in file
//  int node1, node2;
//  cin >> node1 >> node2;
//  while(node1 != -1){
//    graph[node1][node2] = (rand()%20 + 1);
//    cin >> node1 >> node2;
//  }

  graph[11][0] = 20;
  graph[11][1] = 20;
  graph[11][3] = 20;
  graph[0][2] = 5;
  graph[1][2] = 8;
  graph[3][4] = 15;
  graph[2][4] = 12;
  graph[2][5] = 4;
  graph[4][6] = 9;
  graph[5][8] = 7;
  graph[6][7] = 13;
  graph[7][8] = 8;
  graph[7][9] = 14;
  graph[8][9] = 6;
  graph[9][10] = 9;
  graph[9][12] = 20;
  graph[10][12] = 20;


  int parent[testV] = {}; //stores paths
  int resFlow[testV] = {}; //stores the residual capacities of found paths
  int maxFlow;
  int flow;
  int round = 0;

  /// ---------- Start with static for graph 1 -------

  //GRAPH 1
  cout << "Graph 1 Data" << endl;
  cout << "  Enter StaticAttack" << endl;



  //run FFA on graph
  maxFlow = fordFulkerson(graph, source, dest, paths, resGraph, parent, resFlow);    //this returns not only the maxflow, but also the set of edges in the augmenting paths

//  //putput the resGraph
//  for(int h = 0; h < testV; h++) {
//    for(int y = 0; y < testV; y++) {
//      cout << resGraph[h][y] << " ";
//    }
//    cout << endl;
//  }cout << endl;
  cout << "Round:  " << round++ << "  Maxflow: " << maxFlow << endl;

  //at each iteration check the flow to make sure it's not zero
  while(maxFlow != 0) {
    flow = StaticAttack(graph, source, dest, paths, resGraph, resFlow);
    maxFlow = maxFlow - flow;
//    cout << "paths: " << endl;
//    for(int h = 0; h < testV; h++) {
//      for(int y = 0; y < testV; y++) {
//        cout << paths[h][y] << " ";
//      }
//      cout <<"    " << resFlow[h] << endl;
//    }cout << endl;
    cout << "Round:  " << round++ << "   flow: " << maxFlow << endl;
  }
  cout << "!!!!!!!!!!!!!!!!!!!!    Done with static   !!!!!!!!!!! \n\n";

/// ---------- Done with static for graph 1 -------

  //Reset graph[][]
  for(int h = 0; h < testV; h++) {
    for(int y = 0; y < testV; y++) {
      if(graph[h][y] < 0)
        graph[h][y] = -graph[h][y];
    }
  }

  //Reset resGraph[][]
  for(int h = 0; h < testV; h++) {
    for(int y = 0; y < testV; y++) {
        resGraph[h][y] = 0;
    }
  }

  //reset paths[][]
  for(int h = 0; h < testV; h++) {
    for(int y = 0; y < testV; y++)
      paths[h][y] = 0;
  }

  //reset resFlow[]
  for(int h = 0; h < testV; h++)
    resFlow[h] = 0;

  //reset parent[]
  for(int h = 0; h < testV; h++)
    parent[h] = 0;



/// ---------- start to reactive for graph 1 -------
  //run FFA on graph (setup)
//  cout << "Enter ReactiveAttack FFA" << endl;

  maxFlow = fordFulkerson(graph, source, dest, paths, resGraph, parent, resFlow);

  cout << "   Enter ReactiveAttack \n";

//  cout << "resGraph:" << endl;
//  //putput the resGraph
//  for(int h = 0; h < testV; h++) {
//    for(int y = 0; y < testV; y++) {
//      cout << resGraph[h][y] << " ";
//    }
//    cout << endl;
//  }cout << endl;
  cout << "Round:  " << round++ << "  Maxflow: " << maxFlow << endl;

  //at each iteration check the flow to make sure it's not zero
  while(maxFlow != 0) {
    flow = ReactiveAttack(graph, source, dest, paths, resGraph, resFlow);
    maxFlow = flow;
//    cout << "paths: " << endl;
//    for(int h = 0; h < testV; h++) {
//      for(int y = 0; y < testV; y++) {
//        cout << paths[h][y] << " ";
//      }
//      cout <<"    " << resFlow[h] << endl;
//    }cout << endl;
    cout << "Round:  " << round++ << "   flow: " << maxFlow << endl;
  }


/////* for the variable k node stuff
//// *    wipe the graph's source and destination columns/rows
//// *    assign k random capacities (1->20)
//// *    then run the graph repeating for 30 -> 60 iterations
////*/
////
////  int numIters = 30;
////  for(int round = 0; round < numIters; round++) {
//  //make all the deleted nodes positive again
//  //  (they were made negative instead of deleting entirely as not to loose information)
//  cout << "print graph " << endl;
//  for(int u = 0; u < V; u++) {
//    for(int v = 0; v < V; v++) {
//      if(graph[u][v] < 0)
//        graph[u][v] = -graph[u][v];
//      cout << graph[u][v] << " ";
//    }
//    cout << endl;
//  }cout << endl;
////
////    for(int i = 0; i < V; i++) {
////      //wipe the source row
////      graph[source][i] = 0;
////      //wipe dest column
////      graph[i][dest] = 0;
////    }
////
////    //make k random connections to the source
////    for(int k = (round +30); k < numIters; k++) {
////      graph[source][(rand()% V) - 2] = (rand() % 20) + 1;
////    }
////    //make k random connections to the source
////    for(int k = (round +30); k < numIters; k++) {
////      graph[(rand()% V) - 2][dest] = (rand() % 20) + 1;
////    }
////
////    //TODO: this is a problem because we have deleted a bunch of nodes and have no way of putting them back to rerun
////    //TODO:    could make the numbers in the graph that have been deleted == -1 and then run through it to make stuff positive again??
////
////    StaticAttack(graph, source, dest, paths, resGraph);
////    cout << endl;
////
////  }
//


  // Deallocate 2D graph array
  for(int i = 0; i < testV; ++i) {
    delete [] graph[i];
  }
  delete [] graph;

  // Deallocate 2D paths array
  for(int i = 0; i < testV; ++i) {
    delete [] paths[i];
  }
  delete [] paths;

  // Deallocate 2D resGraph array
  for(int i = 0; i < testV; ++i) {
    delete [] resGraph[i];
  }
  delete [] resGraph;

  return 0;
}
