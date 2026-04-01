#include <vector>
#include <iostream>
#include <queue>
#include <stack>

using std::vector;

struct Edge {
    int from;
    int to;
};

class Graph {
    // all will be public for simplicity, we only want to showcase the algorithms, data structures and OOP are not the focus here
    public:
    // graph is represented as an adjacency list, adjacencyList[i] is the list of neighboring vertices of vertex i
    // note that this is only possible if the vertices are labeled from 0 to n-1, otherwise we would need a mapping from vertex labels to indices in the adjacency list
    vector<vector<int>> adjacencyList;
    int numVertices; // number of vertices in the graph, this is not strictly necessary as we can get it from the size of the adjacency list but convenient
    int numEdges;

    // empty default constructor
    Graph() {
        numVertices = 0;
        numEdges = 0;
    };

    // constructor that takes the adjacency list as input
    Graph(const vector<vector<int>>& data) : adjacencyList(data) {
        numVertices = adjacencyList.size();
        numEdges = 0;
        for (const auto& neighbors : adjacencyList) {
            numEdges += neighbors.size();
        }
        numEdges /= 2; // because the graph is undirected, each edge is counted twice in the adjacency list
    }

    // constructor that takes a list of edges as input is also nice to have
    Graph(const vector<Edge>& edges) {
        // TODO
        // Implementation for creating graph from list of edges
    }

    // print some minimal info and list of neighbors for each vertex
    void print() const {
        std::cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges:\n";
        for(size_t vertex = 0; vertex < adjacencyList.size(); vertex++){
            std::cout << vertex << ": ";
            for(const int item : adjacencyList[vertex]){
                std::cout << item << " ";
            }
            std::cout << "\n";
        }
    }
};

// BFS pass to list all vertices reachable from a given starting vertex
vector<int> BFStoListAllReachableVertices(const Graph& graph, int start) {
    vector<int> reachableVertices;
    vector<bool> visited(graph.numVertices, false);
    std::queue<int> bfsQueue;

    bfsQueue.push(start);
    visited[start] = true;

    while ( not bfsQueue.empty() ) {
        // get the next vertex to process from the queue
        int currentVertex = bfsQueue.front();
        bfsQueue.pop();

        // process the vertex, here only to add it to the list
        reachableVertices.push_back(currentVertex);

        // enqueue all unvisited neighbors of the current vertex
        for (int neighbor : graph.adjacencyList[currentVertex]) {
            if ( not visited[neighbor]) { // visited neighbours are already in the queue or have been processed
                visited[neighbor] = true;
                bfsQueue.push(neighbor); // push to the end of the queue -> organized pass
            }
        }
    }

    return reachableVertices;
}

// BFS to find the number of connected components in the graph
int BFSconnectedComponents(const Graph& graph, int start) {
    int numComponents = 0;
    vector<bool> visited(graph.numVertices, false);
    std::queue<int> bfsQueue;

    // multiples BFS passes, each pass is one component
    // each new pass starts once a component is exhausted
    do{
        bfsQueue.push(start);
        visited[start] = true;

        while ( not bfsQueue.empty() ) {
            int currentVertex = bfsQueue.front();
            bfsQueue.pop();

            for (int neighbor : graph.adjacencyList[currentVertex]) {
                if ( not visited[neighbor]) {
                    visited[neighbor] = true;
                    bfsQueue.push(neighbor);
                }
            }
        }

        numComponents++;

        // find the next unvisited vertex to start a new BFS pass
        start = -1; // reset start to an invalid value
        for (size_t i = 0; i < visited.size(); i++) {
            if ( not visited[i]) {
                start = i;
                break;
            }
        }
    } while(start != -1); // if start is -1, there are no more unvisited vertices, we are done
    // alternative implementation would be a for cycle over all vertices, and start a BFS pass for each unvisited vertex
    // what is more useful depends on the specific use case
    return numComponents;
}

// DFS pass to list all vertices reachable from a given starting vertex
// Compare with BFS implementation and realize that DFS <-> BFS ~ queue <-> stack, the rest if conceptually the same
vector<int> DFStoListAllReachableVertices(const Graph& graph, int start) {
    vector<int> reachableVertices;
    vector<bool> visited(graph.numVertices, false);
    std::stack<int> dfsStack;

    dfsStack.push(start);
    visited[start] = true;

    while( not dfsStack.empty() ) {
        int currentVertex = dfsStack.top();
        dfsStack.pop();

        reachableVertices.push_back(currentVertex);

        for (int neighbor : graph.adjacencyList[currentVertex]) {
            if ( not visited[neighbor]) {
                visited[neighbor] = true;
                dfsStack.push(neighbor); // push to the top of the stack -> depth first pass
            }
        }
    }
    return reachableVertices;
}

template<typename T>
void printVec(const vector<T>& vec) {
    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int main() {
    vector<vector<int>> data = { // small test graph with two componenents
        {1, 2},
        {0, 3},
        {0},
        {1},
        {5, 6},
        {4, 6},
        {4, 5, 7},
        {6},
    };
    Graph graph(data);
    graph.print();

    std::cout << "BFS reachable vertices from vertex 0: ";
    printVec(BFStoListAllReachableVertices(graph, 0));

    std::cout << "DFS reachable vertices from vertex 0: ";
    printVec(DFStoListAllReachableVertices(graph, 0));

    std::cout << "\n";

    std::cout << "BFS reachable vertices from vertex 4: ";
    printVec(BFStoListAllReachableVertices(graph, 4));

    std::cout << "DFS reachable vertices from vertex 4: ";
    printVec(DFStoListAllReachableVertices(graph, 4));

    std::cout << "\n";

    std::cout << "Number of components in the graph: " << BFSconnectedComponents(graph, 0) << "\n";
    return 0;
}