#include<vector>
#include<iostream>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<set>
#include<algorithm>
#include<cassert>

using std::vector;

class State{
    public:
    vector<vector<int>> state;
    std::pair<int, int> posOfZero;

    State(const vector<vector<int>>& data){
        state = data;
        for(size_t i = 0; i < 3; i++){
            for(size_t j = 0; j < 3; j++){
                if(data.at(i).at(j) == 0){
                    posOfZero = {i, j};
                }
            }
        }
    }

    State () {};

    vector<State> generateNextPossibilities() const {
        vector<State> res;
        vector<int> moves = {-1, +1};

        // first check first coordinate
        for(const int move : moves){
            if((0 <= posOfZero.first + move) and ( posOfZero.first + move < 3)){
                vector<vector<int>> newState = state;
                std::swap(newState[posOfZero.first][posOfZero.second],
                    newState[posOfZero.first + move][posOfZero.second]);
                // res.emplace_back(newState);
                State b(newState);
                res.push_back(b);
            }
        }
        // now check second coordinate
        for(const int move : moves){
            if((0 <= posOfZero.second + move) and ( posOfZero.second + move < 3)){
                vector<vector<int>> newState = state;
                std::swap(newState[posOfZero.first][posOfZero.second],
                    newState[posOfZero.first][posOfZero.second + move]);
                // res.emplace_back(newState);
                State b(newState);
                res.push_back(b);
            }
        }
        return res;
    }

    bool isFinal() const {
        vector<vector<int>> finalPosition = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
        };
        return state == finalPosition;
    }

    void print() const {
        for(const auto& line : state){
            for(const auto& item : line){
                std::cout << item;
            }
        }
        std::cout << "\n";
    }

    bool operator<(const State& other) const {
        return state < other.state;
    }

    bool operator==(const State& other) const {
        return state == other.state;
    }

    bool operator!=(const State& other) const {
        return not (state == other.state);
    }
};


vector<State> bfsSolve(const State& start){
    std::queue<State> bfsQ;
    std::set<State> visited;
    vector<State> pathToVictory;
    std::map<State, State> mapToParents;

    if( start.isFinal() ){
        return {start};
    }

    visited.insert(start);
    bfsQ.push(start);
    mapToParents[start] = start; // for nicer construction of pathToVictory

    while( not bfsQ.empty()){
        State currentNode = bfsQ.front();
        bfsQ.pop();

        vector<State> neighbours = currentNode.generateNextPossibilities();

        for(const auto& item : neighbours ){
            if( visited.find(item) == visited.end() ){ // item neni ve visited
                if( item.isFinal() ){
                    mapToParents[item] = currentNode;
                    // vitezstvi, sestavim vystup
                    pathToVictory.push_back(item);
                    State currentParent = mapToParents.at(item);
                    while(currentParent != start){
                        pathToVictory.push_back(currentParent);
                        currentParent = mapToParents.at(currentParent);
                    }
                    pathToVictory.push_back(start);
                    std::reverse(pathToVictory.begin(), pathToVictory.end());
                    return pathToVictory;
                }
                visited.insert(item);
                bfsQ.push(item);       
                mapToParents[item] = currentNode;
            }
        }
    }
    return {};
}

int main() {
    vector<vector<int>> data = {
        {1, 4, 2},
        {3, 7, 5},
        {6, 0, 8},
    };

    State start(data);

    const auto path = bfsSolve(start);

    for(const auto& item : path){
        item.print();
    }
    return 0;
}
