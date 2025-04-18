import networkx as nx
import matplotlib.pyplot as plt


if __name__ == '__main__':
    filenames = ['ladder5.txt', ]  # change and add your graphs
    for filename in filenames:
        G = nx.DiGraph()
        with open(filename) as file:
            lines = [list(map(int, line.strip().split())) for line in file.readlines()]
            for line in lines:
                if line:
                    G.add_edge(line[0], line[1])

        pos = nx.nx_pydot.graphviz_layout(G)
        nx.draw_networkx(G, pos, with_labels=True, arrows=True, node_color='lightblue')
        plt.show()

        # Needs pydot, pygraphviz, graphviz
        A = nx.nx_agraph.to_agraph(G)
        A.layout()
        A.draw(filename[:-4]+'.png')  # assumes that filename ends with .txt
