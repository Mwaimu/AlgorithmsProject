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

/* //////////////////////
 * instead of using pointers to keep track of a node's parent for DFS, if when we are making a network, we keep track
 * of a node's children we will automatically have the parents through each recursive call of DFSVisit
 ////////////////////////*/


	Network N;
  for(int i = 0; i < 8; i++) {
    Node n1(rand()%13);
    Node n2(rand()%13);
    Edge edge(n1, n2);
    N.addEdge(edge);
    N.addNode(n1);
    N.addNode(n2);
  }

  string chars, thing1, thing2;
  cin >> chars;
  while(chars != "e") {
    cin >> thing1;
    Node n1();
  }
  N.printNetwork();
  cout << "DFS" << endl;
  modFFA(N);
  return 0;
}


void modFFA(Network N) {
  //set all edge.flow values to zero
  for(Edge e: N.getEdgeVect()) {
    e.setFlow(0);
  }
  N.DFS(N);


//		calculate residual network G_f -> stored as a set
//		while(go through each path in G_f) {
//			select augmenting path p in G_f
//			cf_p = minimum capacity along that path
//			for(each edge in p) {
//				if(edge is in E)
//				edge.flow = edge.flow + cf_p
//				else
//				oppEdge.flow = oppEdge.flow - cf_p;
//			}
//			calculate G_f
//		}
//		return (outputFlow - inputFlow, set of Edges);




}






