/* Algorithms Project 2
 * Shelby Luttrell, Ben Simpson, Nathan Welch
 */


#include "Network.h"

Network::Network() {
  nodeVec;
  edgeVec;
}

void Network::printNetwork() {
	//for every edge in the network print it's edges
  cout << "Edges" << endl;
  for(Edge edge : edgeVec) {
    edge.printEdge();
    cout << endl;
  }
  cout << "Nodes" << endl;
	//for every node in the network print the nodes
  for(Node node : nodeVec) {
    cout << node.getID() << " " << node.getVisited() << endl;

  }
}



void Network::addEdge(Edge e) {
	edgeVec.push_back(e);
}

void Network::addNode(Node n) {
	nodeVec.push_back(n);
}

vector<Edge> Network::getEdgeVect() {
	return edgeVec;
}

vector<Node> Network::getNodeVect() {
	return nodeVec;
}

vector<Node> Network::DFS(Network N) {
	//for each of the nodes in the network, set the parents to null and the visit to false
  vector<Node> path;
	for(Node node: N.getNodeVect()) {
		node.setVisited(false);
	}
	//for each of the nodes in the network, (only happens once with a directed graph)   \
		if the has not been visited, visit the node
	for(Node node: N.getNodeVect()) {
		if(!node.getVisited()) {
      path.push_back(node);
			DFSVisit(N, node, path); //here node has to be S
		}
	}
  return path;
}

vector<Node> Network::DFSVisit(Network N, Node u, vector<Node> path) {
  u.setVisited(true); //set node visit value to true
  //for the nodes adjacent tp the input node
  for(Node v: u.getAdjList()) {
    //if adjacent node hasn't been visited
    if(v.getID() == -4) { //if it's dest_node
      path.push_back(v);
      return path;
    }
    if(v.getVisited() == 0) {
      path.push_back(v);
      DFSVisit(N, v, path); //visit node v
    }

    //might need to take the back off of here to not have everything in it...

  }
  return path;
}



///////////Shelby's Stuff///////////////////////////////////////
/*
pair Network::modFFA(Network N) {
	for(Edge e: N.edgeVec) {
		e.setFlow(0);
	}

    //returns a pair
    tuple<int, list of edges> Modified_Ford_Fulkerson(Network G) {
        for each edge in E {
                set flow to zero
        }
        calculate residual network G_f -> stored as a set
        while(there is a path from D to S) {
            select augmenting path p in G_f
            cf_p = minimum capacity along that path
            for(each edge in p) {
                if(edge is in E)
                edge.flow = edge.flow + cf_p
                else
                oppEdge.flow = oppEdge.flow - cf_p;
            }
            calculate G_f
        }
        return (outputFlow - inputFlow, set of Edges);
    }


}



StaticAttack(Network N) {
    tuple<int, set> flow;
    flow = modFFA(N);    //this returns not only the maxflow, but also the set of edges in the augmenting paths
    while maxflow not zero {
        max_edge = edge with most flow
        delete max_edge
        delete associated paths
        //paths are deleted by taking the residual capacity of the path associated with the deleted edge and subtracting it from the flow of each edge in the path.
    }
    return;
}

StaticRandomAttack(Network N) {
    flow = modFFA(N);
    while flow not zero {
        random_edge = randomly selected edge
        delete random_edge
    }
    return;
}


void Network::reactiveRandomAttack(Network N) {
	pair<int, set> flow = modFFA(N);
	while(flow.first != 0){
		edge;//= random link in set
		delete edge;//delete edge from the set
		flow = modFFA(pass in set here?);  //make something in FFA that keeps track of the link that has the max flow running through it
	}
	return;
}

void Network::reactiveAttack(Network N) {
	pair<int,set> flow = modFFA(N);
	while(flow.first != 0){

		//for loop to find the the link with the max flow in the set
		//flow.second //Edge edgeMaxFlow; // set equal to the link with most flow
		if (multiple edges with same flow pick one with highest capacity)
			//delete edge;

			return;

	}


}

*/



