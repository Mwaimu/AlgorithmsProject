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
  for(Edge edge : edgeVec) {
    edge.printEdge();
    cout << endl;
  }
	//for every node in the network print the nodes
  for(Node node : nodeVec) {
    cout << node.getID() << endl;
  }
}

void Network::modFFA(Network N) {
	//set all edge.flow values to zero
  for(Edge e: N.edgeVec) {
    e.setFlow(0);
  }
	N.DFS();


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

void Network::DFS() {
	Network N; // need to set this to the calling thing
	//for each of the nodes in the network, set the parents to null and the visit to false
	for(Node node: N.getNodeVect()) {
		node.setParent(nullptr);
		node.setVisited(false);
	}
	//for each of the nodes in the network, (only happens once with a directed graph)   \
		if the has not been visited, visit the node
	for(Node node: N.getNodeVect()) {
		if(!node.getVisited()) {
			DFSVisit(N, node); //here node has to be S
		}
	}
}

void Network::DFSVisit(Network N, Node node) {
	node.setVisited(true); //set node visit value to true
	//for each of the nodes in the network
	for(Node node: N.getNodeVect()) {
		//for each of the edges in the network
		for(Edge edge: N.getEdgeVect()) {
			//if the edge.source and the node are the same && the edge's.destination node has not been visited, visit
			if(edge.getSource() == node.getID() && edge.getDest() NOT VISITED) {
				//set v.node.parent to u.node and visit
				edge_v.setParent(node);
				DFSVisit(N, edge_v_node);
			}
		}
	}
}


///////////Shelby's Stuff///////////////////////////////////////
pair Network::modFFA(Network N) {
	for(Edge e: N.edgeVec) {
		e.setFlow(0);
	}
/*
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
 */

}


/*
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
*/

void Network::reactiveRandomAttack(Network N) {
	pair<int, set> flow = modFFA(N);
	while(flow.first != 0){
		edge;//= random link in set
		delete edge;//delete edge from the set
		flow = modFFA(/*pass in set here?*/);  //make something in FFA that keeps track of the link that has the max flow running through it
	}
	return;
}

void Network::reactiveAttack(Network N) {
	pair<int,set> flow = modFFA(N);
	while(flow.first != 0){

		//for loop to find the the link with the max flow in the set
		//flow.second //Edge edgeMaxFlow; // set equal to the link with most flow
		if (/*multiple edges with same flow pick one with highest capacity*/)
			//delete edge;

			return;

	}


}





