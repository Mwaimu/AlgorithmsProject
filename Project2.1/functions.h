//
// Created by Nathan Welch on 4/29/2017.
//

#ifndef PROJECT2_1_FUNCTIONS_H
#define PROJECT2_1_FUNCTIONS_H

#include <iostream>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <fstream>

#include <stack>

using namespace std;

#define V 20
#define INPUT  "Graph1.txt"			//Input File
#define OUTPUT "FordFulkersonOutput.txt"		//Output File

//------- Function Definitions -------//
int* maxFlow(int graph[V][V], int s, int t);  //Ford-Fulkerson implementation
bool findPath(int residual[V][V], int source, int dest, int parent[]); //Finds paths...


//Returns max flow from source to dest in given graph
int* maxFlow(int graph[V][V], int source, int dest, int path[]) {
  int u, v; //start and finish of edges
  int maxFlow = 0;
  int resCap = 21; //residual capacity, higher than capacity so that any edge will be considered

  int residual[V][V]; //residual[i][j] is residual capacity at edge(i,j)

  //copy the graphs
  for (u = 0; u < V; u++)
    for (v = 0; v < V; v++)
      residual[u][v] = graph[u][v];

//  int path[V]; //holds the augmenting path

  while(findPath(residual, source, dest, path)) {
    //for each element in the path, find the "edge" that has the lowest residual capacity
    for(v = dest; v != source; v = path[v]) {
      u = path[v];                          //update the node looked at
      resCap = min(resCap, residual[u][v]); //picks the lowest
    }

    //have to add flow to the path that was picked
    for(v = dest; v != source; v = path[v]) {
      u = path[v];
      residual[u][v] -= resCap;
      residual[v][u] += resCap;
    }

    maxFlow += resCap; //update the maxFlow
  }

  cout << maxFlow;
  for(int i = 0; i < V; i++) {
    cout << path[i] << "  ";
  }

  return path;
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

#endif //PROJECT2_1_FUNCTIONS_H
