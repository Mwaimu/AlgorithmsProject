#Algorithms Project 2
#Shelby Luttrell, Ben Simpson, Nathan Welch


class Edge(object):
    def __init__(self, first, last):
        self.u = first
        self.v = last


class Node(object):
    def __init__(self, num):
        self.id = num


class Path(object):
    def __init__(self):
        self.residual_flow
        self.path     #this is a list of edges


class Network(object):
    def __init__(self):
        list of paths
        list of edges #set of edges in the list of paths



def static_attack():
    print("happens")
    flow = 1, 15
    print(flow[0])
    print(flow[1])
    print(flow)


def modified_ford_fulkerson():
    print("hi")
    for edge in E:
        edge.flow = 0
    # calculate residual network


static_attack()
