/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#ifndef ALGORITHMS_NETWORK_H
#define ALGORITHMS_NETWORK_H

#include <vector>
#include <iostream>
#include <cstdlib>

#include "Node.h"
#include "Edge.h"

using namespace std;

class Network {
public:
  Network();

  void printNetwork();
	void modFFA(Network N);
	void addEdge(Edge e);
	void addNode(Node n);
	void DFS();
	void DFSVisit(Network N, Node node);

	void reactiveAttack(Network G);

	int getEdgeSize() { return nodeVec.size(); }

	vector<Edge> getEdgeVect();
	vector<Node> getNodeVect();

	/*
	Shelby's stuff
	void printNetwork();
  pair modFFA(Network N);

  void reactiveAttack(Network N);
	void reactiveRandomAttack(Network N);
	*/


private:
  vector<Node> nodeVec;
  vector<Edge> edgeVec;

};


#endif //ALGORITHMS_NETWORK_H
