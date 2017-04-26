# Algorithms Project 2
# Shelby Luttrell, Ben Simpson, Nathan Welch

# -- We will need a collection of Nodes and Edges.

#-- PARSER FUNCTION
#--
import random

class Edge(object):
   def __init__(self, source, dest):
       self.u = source
       self.v = dest
       self.flow = 0
   def __str__(self):
       return str(self.u) + "->" + str(self.v)
   __repr__ = __str__

class Node(object):
   def __init__(self, num):
       self.id = num
   def __str__(self):
       return str(self.id)
   __repr__ = __str__

class Path(object):
   def __init__(self):
       self.residual_flow = 0
       self.path = []  # this is a list of edges

class Network(object):
   def __init__(self):
       self.nodes = []
       self.edges = [] # set of edges in the list of paths

   def __str__(self):
       if self.nodes or self.edges:
           return "--Non-empty--"
        #    print "--EDGES--"
        #    for n in self.edges:
        #        print self.edges
        #    print "--NODES--"
        #    for n in self.nodes:
        #       print self.nodes
       else:
           return "--Empty Network--"

def add_edge(edge, network):
    network.edges.append(edge)

def add_node(node, network):
    network.nodes.append(node)

# def modified_ford_fulkerson(network):
#     e = network.edges
#     p = network.path
#     print("hi")
#     for edge in e:
#         edge.flow = 0
#     calculate residual network -> stored as set of paths (augmenting paths)
   # while each path in G_f:
   #     cf_p = 21
   #     for path in G_f
   #         if path.residual_flow < cf_p:
   #             cf_p = path.residual_flow
   #             p = path
   #     for edge in p:
   #         for edge1 in e:
   #             if edge1 is edge:
   #                 edge.flow = edge.flow + cf_p
   #             else:
   #                 edge.flow = edge.flow - cf_p
   # calculate G_f



# Network = Network()
# Edge = Edge(14,15)
# Network.add_node(14)
# Network.add_node(15)
# Network.add_edge(Edge)
#
# print Network
