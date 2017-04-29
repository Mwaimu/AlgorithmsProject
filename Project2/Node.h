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

	void setVisited(bool v);
  void addAdj(Node node);

  int getID() { return id; }
  int getVisited() { return visited; }

  vector<Node> getAdjList() { return adjList; }

private:
  int id; //make source_node's id "-3" and dest_node's id "-4"
	bool visited;
	vector<Node> adjList;
};


#endif //ALGORITHMS_NODE_H
