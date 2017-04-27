/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#ifndef ALGORITHMS_EDGE_H
#define ALGORITHMS_EDGE_H

#include <iostream>
#include <cstdlib>

#include "Edge.h"
#include "Node.h"
#include "Network.h"

using namespace std;


class Edge {
public:
  Edge(int s, int d);

  void printEdge();

  int getSource() { return source; }
  int getDest() { return dest; }
  int getFlow() { return flow; }
  int getCapacity() { return capacity; }

private:
  int source;
  int dest;
  int flow;
  int capacity;
};


#endif //ALGORITHMS_EDGE_H
