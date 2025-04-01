import networkx as nx
import matplotlib.pyplot as plt
import random
from pathlib import Path


def save_graph_data(G, filename_prefix, output_dir="graph_test_data"):
    """
    Saves graph data in adjacency list format and generates a visualization.

    Args:
        G (nx.Graph): The networkx graph object.
        filename_prefix (str): The prefix for the output filenames.
        output_dir (str): The directory to save the files in.
    """
    "Gemini 2.5 generated"
    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)

    txt_filename = output_path / f"{filename_prefix}.txt"
    pic_filename = output_path / f"{filename_prefix}.pdf"

    # Ensure nodes are 0-indexed integers, especially for grid graphs
    # Create a mapping if nodes are not simple integers (like grid tuples)
    if not all(isinstance(n, int) for n in G.nodes()) or \
       sorted(list(G.nodes())) != list(range(G.number_of_nodes())):
        print(f"  Remapping nodes for {filename_prefix} to 0..N-1 integers.")
        node_list = sorted(list(G.nodes()))  # Get a consistent order
        node_map = {node: i for i, node in enumerate(node_list)}
        # Create the graph structure with the new integer labels
        draw_G = nx.Graph()
        draw_G.add_nodes_from(range(len(node_map)))
        draw_G.add_edges_from([(node_map[u], node_map[v]) for u, v in G.edges()])
        # Store original positions if needed for drawing (e.g., grid)
        original_pos = None
        if all(isinstance(n, tuple) for n in G.nodes()):
            original_pos = {node_map[node]: node for node, i in node_map.items()}
    else:
        draw_G = G.copy()  # Work on a copy
        node_map = None
        original_pos = None

    num_vertices = draw_G.number_of_nodes()
    num_edges = draw_G.number_of_edges()

    print(f"Generating {filename_prefix}: V={num_vertices}, E={num_edges}")

    with open(txt_filename, 'w') as f:
        for i in range(num_vertices):
            neighbors = sorted(list(draw_G.neighbors(i)))
            neighbors_str = ", ".join(map(str, neighbors))
            f.write(f"{i}: {neighbors_str}\n")

    print(f"  Saved data to {txt_filename}")

    plt.figure(figsize=(10, 8))

    pos = None
    node_size = 60
    font_size = 10

    # Use different layout algorithms depending on graph type for better visuals
    if original_pos:
        pos = original_pos
    elif nx.is_connected(draw_G):
        try:
            pos = nx.kamada_kawai_layout(draw_G)
        except Exception as e:
            pos = nx.spring_layout(draw_G, seed=42)
    else:
        pos = nx.spring_layout(draw_G, seed=42)

    if num_vertices > 150:
        node_size = 20
        font_size = 5
    elif num_vertices > 50:
        node_size = 30
        font_size = 6

    nx.draw(draw_G, pos, with_labels=True, node_size=node_size,
            font_size=font_size, node_color='skyblue', edge_color='gray',
            font_weight='bold')
    plt.title(f"{filename_prefix} (V={num_vertices}, E={num_edges})", fontsize=15)
    plt.savefig(pic_filename, dpi=150)
    plt.close()
    print(f"  Saved image to {pic_filename}")
    print("-" * 20)


if __name__ == "__main__":
    "Gemini 2.5 generated"
    output_directory = "graph_test_data_adj"
    random.seed(42)

    # 1. Small Grid Graph (Structured, easy to debug)
    rows, cols = 15, 20
    G_grid = nx.grid_2d_graph(rows, cols)
    save_graph_data(G_grid, f"graph_grid_{rows}x{cols}", output_directory)
    # Note: Grid nodes are (row, col) tuples. save_graph_data remaps them to 0..N-1.

    # 2. Small Random Graph (Erdos-Renyi GNP) - Relatively Sparse
    n_small_sparse = 30
    p_small_sparse = 0.15  # Probability of edge creation
    G_small_sparse = nx.gnp_random_graph(n_small_sparse, p_small_sparse, seed=42)
    save_graph_data(G_small_sparse, f"graph_random_n{n_small_sparse}_p{p_small_sparse:.2f}", output_directory)

    # 3. Medium Random Graph (Erdos-Renyi GNM) - Fixed number of edges
    n_medium = 70
    m_medium = 150  # Number of edges
    G_medium_gnm = nx.gnm_random_graph(n_medium, m_medium, seed=43)
    save_graph_data(G_medium_gnm, f"graph_random_n{n_medium}_m{m_medium}", output_directory)

    # 4. Watts-Strogatz Small World Graph
    n_ws = 50
    k_ws = 4    # Each node is joined with its k nearest neighbors in a ring topology
    p_ws = 0.2  # The probability of rewiring each edge
    G_ws = nx.watts_strogatz_graph(n_ws, k_ws, p_ws, seed=44)
    save_graph_data(G_ws, f"graph_watts_strogatz_n{n_ws}_k{k_ws}_p{p_ws:.1f}", output_directory)

    # 5. Barabasi-Albert Scale-Free Graph
    n_ba = 100
    m_ba = 3     # Number of edges to attach from a new node to existing nodes
    G_ba = nx.barabasi_albert_graph(n_ba, m_ba, seed=45)
    save_graph_data(G_ba, f"graph_barabasi_albert_n{n_ba}_m{m_ba}", output_directory)

    # 6. Larger Random Graph - Possibly Disconnected
    n_large = 200
    p_large = 0.02  # Lower probability, might lead to disconnection
    G_large = nx.gnp_random_graph(n_large, p_large, seed=46)
    save_graph_data(G_large, f"graph_random_n{n_large}_p{p_large:.2f}", output_directory)

    # 7. A graph with distinct components (Example)
    G_comp1 = nx.cycle_graph(15)
    G_comp2 = nx.star_graph(10)
    # Shift nodes of the second component to avoid overlap before composing
    G_comp2 = nx.relabel_nodes(G_comp2, {n: n + 15 for n in G_comp2.nodes()})
    G_disconnected = nx.compose(G_comp1, G_comp2)
    save_graph_data(G_disconnected, "graph_disconnected_example", output_directory)

    # 8. Random Lobster Graph
    # A lobster is a tree where removing all leaves leaves a caterpillar.
    # A caterpillar is a tree where removing all leaves leaves a path.
    n_lob_backbone = 25  # Approx. nodes in the main backbone path
    p_lob_1 = 0.6       # Prob of edge from backbone to 1st level neighbors
    p_lob_2 = 0.7       # Prob of edge from 1st level neighbors to leaves (2nd level)
    G_lobster = nx.random_lobster(n_lob_backbone, p_lob_1, p_lob_2, seed=47)
    # Lobster generator labels nodes naturally, but let's ensure 0..N-1 just in case
    save_graph_data(G_lobster, f"graph_lobster_n{n_lob_backbone}_p{p_lob_1:.1f}_{p_lob_2:.1f}", output_directory)

    # 9. Barbell Graph
    # Two complete graphs connected by a path. Visually distinct.
    m1_barbell = 10  # Nodes in each complete graph part
    m2_barbell = 4  # Nodes in the connecting path (excluding endpoints)
    G_barbell = nx.barbell_graph(m1_barbell, m2_barbell)
    save_graph_data(G_barbell, f"graph_barbell_m{m1_barbell}_m{m2_barbell}", output_directory)

    # 10. Lollipop Graph
    # A complete graph connected to a path.
    m_lollipop = 12  # Nodes in the complete graph part
    n_lollipop = 6  # Nodes in the path part
    G_lollipop = nx.lollipop_graph(m_lollipop, n_lollipop)
    save_graph_data(G_lollipop, f"graph_lollipop_m{m_lollipop}_n{n_lollipop}", output_directory)

    # 11. Random Geometric Graph
    # Nodes are random points in a unit square; edges connect nodes closer than a radius.
    # Often creates clusters and interesting spatial structures.
    n_geom = 120
    radius_geom = 0.15
    G_geom = nx.random_geometric_graph(n_geom, radius_geom, seed=48)
    # Need to explicitly handle positions for drawing geometric graphs well
    # We can pass the positions networkx calculated to our save function,
    # but save_graph_data currently recalculates layout.
    # For simplicity here, we'll let save_graph_data use its default layouts.
    # A potential enhancement would be to pass 'pos=nx.get_node_attributes(G_geom, "pos")'
    # to save_graph_data and have it use those if provided.
    save_graph_data(G_geom, f"graph_geometric_n{n_geom}_r{radius_geom:.2f}", output_directory)

    # 11b. Random Geometric Graph
    # Nodes are random points in a unit square; edges connect nodes closer than a radius.
    # Often creates clusters and interesting spatial structures.
    n_geom = 60
    radius_geom = 0.2
    G_geom = nx.random_geometric_graph(n_geom, radius_geom, seed=48)
    # Need to explicitly handle positions for drawing geometric graphs well
    # We can pass the positions networkx calculated to our save function,
    # but save_graph_data currently recalculates layout.
    # For simplicity here, we'll let save_graph_data use its default layouts.
    # A potential enhancement would be to pass 'pos=nx.get_node_attributes(G_geom, "pos")'
    # to save_graph_data and have it use those if provided.
    save_graph_data(G_geom, f"graph_geometric_n{n_geom}_r{radius_geom:.2f}", output_directory)

    # 12. Wheel Graph
    # A cycle graph with a central hub node connected to all cycle nodes.
    n_wheel = 30  # Total nodes (1 center + 29 on the wheel)
    G_wheel = nx.wheel_graph(n_wheel)
    save_graph_data(G_wheel, f"graph_wheel_n{n_wheel}", output_directory)

    # 13. Graph with Communities (Stochastic Block Model)
    # Generates graphs with specific community structures.
    sizes_sbm = [25, 35, 30]  # Sizes of the 3 communities
    # Probability matrix: p[i][j] is prob of edge between community i and j
    probs_sbm = [[0.25, 0.02, 0.01],  # High intra-community prob (diag), low inter-community
                 [0.02, 0.30, 0.03],
                 [0.01, 0.03, 0.20]]
    G_sbm = nx.stochastic_block_model(sizes_sbm, probs_sbm, seed=49)
    # SBM labels nodes 0..N-1, where N = sum(sizes)
    save_graph_data(G_sbm, f"graph_communities_sbm_{len(sizes_sbm)}c", output_directory)
