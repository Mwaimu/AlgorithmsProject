/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */


#include "Edge.h"

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