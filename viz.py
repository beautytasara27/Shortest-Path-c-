import warnings
import csv
import  networkx as nx
import sys
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.axes import Axes as ax
from matplotlib.cbook.deprecation import MatplotlibDeprecationWarning
warnings.filterwarnings("ignore", category=MatplotlibDeprecationWarning)

def myFunc(filepath):
    #reading the csv files to create the graph
    nodelist = pd.read_csv("C:\\Users\\beauty\\PycharmProjects\\test\\nodes.csv")
    edgelist = pd.read_csv("C:\\Users\\beauty\\PycharmProjects\\test\\edgelist.csv")

    g = nx.DiGraph()
    # Add edges and edge attributes which is weight
    for i, elrow in edgelist.iterrows():
        g.add_edge(elrow[0], elrow[1], **elrow[2:].to_dict())

    #adding nodes and node attributes which are the coordinates for plotting
    for i, nlrow in nodelist.iterrows():
        nx.set_node_attributes(g, {nlrow['id']:  nlrow[1:].to_dict()})

    #seting positions of the nodes on the graph according to coordinates
    node_positions = {node[0]: (node[1]['X'], node[1]['Y']) for node in g.nodes(data=True)}
    plt.figure(figsize=(8, 6))

    plt.title('Graph Representation of c++ shortest path', size=15)
    bbox = {'ec':[1,1,1,0], 'fc':[1,1,1,0]}  # hack to label edges over line (rather than breaking up line)
    edge_labels = nx.get_edge_attributes(g, 'weight')
    nx.draw_networkx_edge_labels(g, pos=node_positions, edge_labels=edge_labels,bbox=bbox, font_size=8, font_color='blue')
    nx.draw(g, pos=node_positions,node_size=150,arrowsize=20, arrowcolor='gray', node_color='green', with_labels='c')


    with open(filepath, mode='r') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        A =[]#array of arrays containing paths followed
        weight = []
        colors = ['red', 'yellow', 'violet', 'orange', 'red', 'yellow', 'violet', 'yellow', 'red', 'blue', 'orange', 'red']
        for row in csv_reader:
            #appending the paths from the index 3 till end of row
            A.append(row[3:])
            if len(row[2])<=2 :#to omit DBL_MAX instead use 1000 to represent infinity
                weight.append(int(row[2]))
            else :
                weight.append(1000)#1000 is the value for infinity

        x = -1
        #for arrays in A
        for i in A:
            B = []
            M = [] #contains the x coordinates
            N = [] #contains the y coordinates

            for v in i:#for each vertx in arrays in A
                if len(v) >=1:#to omit spaces
                    B.append(int(v)) #append the vertices as integers in B
            for b in B:
                #append attributes for each node in B to be plotted
                M.append(g.node[b]['X'])
                N.append(g.node[b]['Y'])
            x = x+1
            txt = plt.text(1,3,'weight =')
            text = plt.text(1.5,3,weight[x])
            ln, =  plt.plot(M,N ,color=colors[x])#plot
            try:
                plt.pause(3) #pause the display to see the path
            except Exception as e:
                print("you closed the display window !")
                sys.exit()
            ax.remove(text)
            ax.remove(ln)


myFunc("path.csv")
plt.show()


