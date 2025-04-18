import networkx as nx
import matplotlib.pyplot as plt



if __name__ == '__main__':
    filename = 'ladder5.txt'
    G = nx.DiGraph()
    with open(filename) as file:
        lines = [list(map(int, line.strip().split())) for line in file.readlines()]
        for line in lines:
            print(line)
            if line:
                G.add_edge(line[0], line[1])

    pos = nx.nx_pydot.graphviz_layout(G)
    nx.draw_networkx(G, pos, with_labels=True, arrows=True, node_color='lightblue')
    plt.show()

    # Needs pydot, pygraphviz, graphviz
    A = nx.nx_agraph.to_agraph(G)
    A.layout()
    A.draw(filename[:-4]+'.png')  # assumes that filename ends with .txt
