/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#include "Edge.h"

Edge::Edge() {
	flow = 0;
	capacity = (rand() % 20) + 1;
}

Edge::Edge(int s, int d) {
  source = s;
  dest = d;
  flow = 0;
  capacity = (rand() % 20) + 1;
}

void Edge::printEdge() {
  cout << source << "->" << dest;
  return;
}

void Edge::setSource(int s) {
  source = s;
}

void Edge::setDest(int d) {
  dest = d;
}

void Edge::setFlow(int f) {
  flow = f;
}

void Edge::setCapacity(int c) {
  capacity = c;
}