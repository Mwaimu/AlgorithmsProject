/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 *
 * Description:
 * Attacker deletes edge from network. Compare how reactive and static networks are effected
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <typeinfo>

#include "Edge.h"
#include "Node.h"
#include "Network.h"
#include "main.h"

using namespace std;

void printAdjVec(Node node);


int main() {
  srand(time(NULL));

/* //////////////////////
 * instead of using pointers to keep track of a node's parent for DFS, if when we are making a network, we keep track
 * of a node's children we will automatically have the parents through each recursive call of DFSVisit
 ////////////////////////*/

/*if the are all in order then we can just increment the second one only
 * because we always know what the first one is going to be
 *  -> and if it is not equal to the previous then update
*/

  Node n1(1);
  Node n2(2);
  Node n3(3);
  Node n4(4);
  Node n6(6);
  Node n7(7);

  Edge e1(n1, n2);
  Edge e2(n1, n3);
  Edge e3(n1, n4);
  Edge e4(n2, n6);
  Edge e5(n3, n7);

  Network N;
  N.addNode(n1);
  N.addNode(n2);
  N.addNode(n3);
  N.addNode(n4);
  N.addNode(n6);
  N.addNode(n7);

  N.addEdge(e1);
  N.addEdge(e2);
  N.addEdge(e3);
  N.addEdge(e4);
  N.addEdge(e5);

  cout << N.getNodeVect().size() << endl;
  cout << N.getEdgeVect().size() << endl;
  n1.addAdj(n2);
  n1.addAdj(n3);
  printAdjVec(n1);










//  for(int i = 0; i < N.getNodeVect().size(); i++) {  //for each of the nodes
//    //current node in iteration is nodeLookedAt
//    //current Edge in iteration is edgeLookedAt
//    for(int j = 0; i < N.getEdgeVect().size(); j++) { //look at each of the edges
//      //if the node being looked at (first) == the edgeLookedAt_source's_ID
//      if(  N.getNodeVect()[i].getID() == N.getEdgeVect()[j].getSource().getID()  ) {
//        //if they are the same then add the destination of the edge to the adjVector of the nodeLookedAt
//        //(means the ID's are equal, meaning same node
//        N.getNodeVect()[i].addAdj(N.getEdgeVect()[j].getDest());
//      }
//
//    }
//  }
  return 0;
}


void printAdjVec(Node node) {
  for(int i = 0; i < node.getAdjList().size(); i++) {
    cout << node.getAdjList()[i].getID();
  }
}

/*
 *
 * Edge e(N.getNodeVect()[thing1], N.getNodeVect()[thing2]);
    cout << "edge init";
    N.getNodeVect()[thing1].addAdj(N.getNodeVect()[thing2]);
    cout << "  end of addAdj";
    N.addEdge(e);
    cout << "  done " << endl;
 *
 *
  for(Node node: N.getNodeVect()) {
    for(Edge edge: N.getEdgeVect()) {
      cout << edge.getSource().getID();
      if(node.getID() == edge.getSource().getID()) {
        cout << "   HIT";
        node.addAdj(edge.getDest());
      }
      cout << endl;
    }
  }


  cout << "LIST      THING: " << N.getNodeVect()[0].getAdjList()[0].getID() << endl;

  cout << "adj list" << endl;

  for(Node node: N.getNodeVect()) {
    cout << node.getID() << ": ";
    for(Node adjNode: node.getAdjList()) {
      cout << adjNode.getID() << "  ";
    }
    cout << endl;
  }

 */


//  for(int i = 0; i < 8; i++) {
//    Node n1(rand()%13);
//    Node n2(rand()%13);
//    Edge edge(n1, n2);
//    N.addEdge(edge);
//    N.addNode(n1);
//    N.addNode(n2);
//  }

//  N.printNetwork();
//  cout << "DFS" << endl;
//  modFFA(N);

//    return 0;
//}
//

//void modFFA(Network N) {
//  vector<Node> path = {};
//
//  //set all edge.flow values to zero
//  for(Edge e: N.getEdgeVect()) {
//    e.setFlow(0);
//  }
//  N.printNetwork();
//  path = N.DFS(N);
//
//  cout << "print path" << endl;
//  for(Node node: path) {
//    cout << node.getID() << "  ";
//  }
//  cout << endl;
//}




////DFS to find all vertices reachable from s
//void mincut_finder(int residual[V][V], int s, bool visited2[])
//{
//  visited2[s] = true;
//  for (int i = 0; i < V; i++)
//    if (residual[s][i] && !visited2[i])
//      mincut_finder(residual, i, visited2);
//}
//
//




