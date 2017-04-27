/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */

#ifndef ALGORITHMS_NETWORK_H
#define ALGORITHMS_NETWORK_H

#include <vector>
#include "Node.h"
#include "Edge.h"

using namespace std;
class Network {
public:
  Network();

  void printNetwork();

private:
  vector<Node> nodeVec;
  vector<Edge> edgeVec;
};


#endif //ALGORITHMS_NETWORK_H
