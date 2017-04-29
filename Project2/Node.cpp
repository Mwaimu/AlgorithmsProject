/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(int i) {
  id = i;
  visited = false;
}

void Node::setVisited(bool v) {
	visited = v;
}

void Node::addAdj(Node node) {
  adjList.push_back(node);
}


