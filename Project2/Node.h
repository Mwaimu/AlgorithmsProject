/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#ifndef ALGORITHMS_NODE_H
#define ALGORITHMS_NODE_H

#include <vector>
using namespace std;

class Node {
public:
  Node(int i);
  Node() { ; }

	void setID();
	void setParent(Node* p);
	void setVisited(bool v);

  int getID() { return id; }
  int getVisited() { return visited; }

private:
  int id;
	bool visited;
	Node* parent;
	vector<Node> adjList;

};


#endif //ALGORITHMS_NODE_H
