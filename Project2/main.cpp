/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 *
 * Description:
 * Attacker deletes edge from network. Compare how reactive and static networks are effected
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Edge.h"
#include "Node.h"
#include "Network.h"
#include "main.h"

using namespace std;

int main() {
	srand(time(NULL));

	Network N;
	vector<Edge> eVect;
	Edge edge;

	for(int i= 0; i < 15; i++) {
		edge.setSource(rand() % 14);
		edge.setDest(rand() % 14);
		eVect.push_back(edge);
	}

	for(Edge edge: eVect) {
		edge.printEdge();
		cout << endl;
	}

	for(int i= 0; i < 15; i++) {
		edge.setSource(rand() % 14);
		edge.setDest(rand() % 14);
		Node node(i);
		N.addEdge(edge);
		N.addNode(node);
	}
	cout << "Network" << endl;
	N.printNetwork();

  return 0;
}









