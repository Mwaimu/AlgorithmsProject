/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#ifndef ALGORITHMS_EDGE_H
#define ALGORITHMS_EDGE_H

#include <vector>
#include <iostream>
#include <cstdlib>

#include "Node.h"


using namespace std;


class Edge {
public:
//  Edge();
	Edge(Node s, Node d);

  void printEdge();
	void setSource(Node s);
	void setDest(Node d);
	void setFlow(int f);

  Node getSource() { return source; }
  Node getDest() { return dest; }
  int getFlow() { return flow; }
  int getCapacity() { return capacity; }

private:
  Node source;
  Node dest;
  int flow;
  int capacity;
};


#endif //ALGORITHMS_EDGE_H
