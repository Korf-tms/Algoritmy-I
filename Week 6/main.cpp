#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>

using std::unordered_map, std::unordered_set, std::cout, std::vector;


class Graph{
    public:
    unordered_map<int, unordered_set<int>> neighbouringMap;
    // vertex -> neighbouring vertices

    Graph(const vector<vector<int>>& data){
        for( const auto& line : data){
            vertices.insert(line[0]);
            neighbouringMap[line[0]] = {};
            for(size_t i = 1; i < line.size(); i++){
                neighbouringMap[line[0]].insert(line[i]);
            }
        }
    }

    Graph() {}; // is this necessary?
    
    void print() const {
        for(const auto& [vertex, friends] : neighbouringMap){
            cout << vertex << ": ";
            for(const int item : friends){
                cout << item << " ";
            }
            cout << "\n";
        }
    }
};

void DFS(const Graph graph, const int start){
    std::stack<int> DFSstack;
    unordered_set<int> visited;

    DFSstack.push(start);
    visited.insert(start);

    while( not DFSstack.empty() ){
        int currentVertex = DFSstack.top();
        DFSstack.pop();

        cout << currentVertex << " ";

        unordered_set<int> friends = graph.neighbouringMap.at(currentVertex);
        for(int item : friends ){
            if(  visited.find(item) == visited.end() ){ // visited.count(item) != 1
                visited.insert(item);
                DFSstack.push(item);
            }
        }
    }
}

void BFS(const Graph graph, const int start){
    std::queue<int> BFSQ;
    unordered_set<int> visited;

    BFSQ.push(start);
    visited.insert(start);

    while( not BFSQ.empty() ){
        int currentVertex = BFSQ.front();
        BFSQ.pop();

        cout << currentVertex << " ";

        unordered_set<int> friends = graph.neighbouringMap.at(currentVertex);
        for(int item : friends ){
            if(  visited.find(item) == visited.end() ){ // visited.count(item) != 1
                visited.insert(item);
                BFSQ.push(item);
            }
        }
    }
}

int main(){
    vector<vector<int>> data = {
        {1, 2, 3, 4},
        {2, 1, 3, 99},
        {3, 1, 2},
        {4, 1},
        {99, 100, 2},
        {100, 101, 99},
        {101, 100},
    };
    Graph myGrap(data);

    myGrap.print();

    DFS(myGrap, 4);
    cout << "\n";
    BFS(myGrap, 4);
    cout << "\n";

    return 0;
}
