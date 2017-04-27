/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#include "Network.h"

Network::Network() {
  nodeVec = NULL;
  edgeVec = NULL;
}

void Network::printNetwork() {
  for(Edge edge : edgeVec) {
    edge.printEdge();
    cout << endl;
  }
  for(Node node : nodeVec) {
    cout << node.getID() << endl;
  }
}
