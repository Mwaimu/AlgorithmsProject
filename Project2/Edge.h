/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#ifndef ALGORITHMS_EDGE_H
#define ALGORITHMS_EDGE_H

#include <vector>
#include <iostream>
#include <cstdlib>


using namespace std;


class Edge {
public:
  Edge();
	Edge(int s, int d);

  void printEdge();
	void setSource(int s);
	void setDest(int d);
	void setFlow(int f);
	void setCapacity(int c);
	void addEdge(int s, int d);

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
