/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#ifndef ALGORITHMS_NETWORK_H
#define ALGORITHMS_NETWORK_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <stack>


#include "Node.h"
#include "Edge.h"

using namespace std;

class Network {
public:
  Network();

  void printNetwork();
	void addEdge(Edge e);
	void addNode(Node n);

  vector<Node> DFS(Network N);
	vector<Node> DFSVisit(Network N, Node node, vector<Node> stack);

	void reactiveAttack(Network G);

	vector<Edge> getEdgeVect(); //these should be sets
	vector<Node> getNodeVect(); //these should be sets

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
