/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#include "Node.h"

Node::Node(int i) {
  id = i;
	parent = nullptr;
}

Node::Node() {
	parent = nullptr;
}

void Node::setParent(Node p) {
	*parent = p;
}

void Node::setVisited(bool v) {
	visited = v;
}