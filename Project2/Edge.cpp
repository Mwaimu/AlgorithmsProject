/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#include "Edge.h"

//Edge::Edge() {
//	flow = 0;
//	capacity = (rand() % 20) + 1;
//}

Edge::Edge(Node s, Node d) :source(s), dest(d) {
  source = s;
  dest = d;
  flow = 0;
  capacity = (rand() % 20) + 1;
}

void Edge::printEdge() {
  cout << source.getID() << "->" << dest.getID();
  return;
}

void Edge::setSource(Node s) {
  source = s;
}

void Edge::setDest(Node d) {
  dest = d;
}

void Edge::setFlow(int f) {
  flow = f;
}

