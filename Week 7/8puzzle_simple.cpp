#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<set>
#include<algorithm>
#include<random>

using std::vector;
using State = vector<int>;

void printVec(const vector<int>& state){
    for(int item : state){
        std::cout << item;
    }
    std::cout << "\n";
}

bool isWinning(const State& s){
    State winningState = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    return s == winningState;
}

vector<State> getPossiblePositons(const State& start){
    vector<State> res;
    int n = 3;

    int positionOfZero;
    for(size_t i = 0; i < start.size(); i++){
        if(start.at(i) == 0){
            positionOfZero = i;
            break;
        }
    }

    // try to sawp with +n, -n
    if(positionOfZero + n < start.size()){
        State newState = start;
        std::swap(newState[positionOfZero], newState[positionOfZero + n]);
        res.push_back(newState);
    }
    if(0 <= positionOfZero - n){
        State newState = start;
        std::swap(newState[positionOfZero], newState[positionOfZero - n]);
        res.push_back(newState);
    }
    // +1
    if( positionOfZero % n != n-1){
        State newState = start;
        std::swap(newState[positionOfZero], newState[positionOfZero + 1]);
        res.push_back(newState);
    }
    // - 1
    if( positionOfZero % n != 0){
        State newState = start;
        std::swap(newState[positionOfZero], newState[positionOfZero - 1]);
        res.push_back(newState);
    }
    return res;
}


vector<State> bfsSolve(const State& start){
    std::queue<State> bfsQ;
    std::set<State> visited;
    vector<State> pathToVictory;
    std::map<State, State> parentMap;

    if(isWinning(start)){
        return {start};
    }

    bfsQ.push(start);
    visited.insert(start);

    while( not bfsQ.empty() ){
        State currentNode = bfsQ.front();
        bfsQ.pop();

        const vector<State> nextMoves = getPossiblePositons(currentNode);
        for(const State& item : nextMoves){
            if( visited.find(item) == visited.end() ){
               parentMap[item] = currentNode;
               if( isWinning(item) ){
                // glue the path to victory from parentMap
                pathToVictory.push_back(item);
                State currentParent = parentMap[item];
                // loop until start node and add start separetely
                while( currentParent != start){
                    pathToVictory.push_back(currentParent);
                    currentParent = parentMap[currentParent];
                }
                pathToVictory.push_back(start);
		std::reverse(pathToVictory.begin(), pathToVictory.end());
                return pathToVictory;
               }
               bfsQ.push(item);
               visited.insert(item);
            }
        }
    }
    return {};
}

int main(){
    std::mt19937 generator;
    // komentar v cestine by nebyl tak pekne zarovnany
    std::random_device rd; // initialize random device
    int seed = rd(); // call random device to get seed
    seed = 44; // or fix the seed value for comparison
    generator.seed(seed); // use seed to initialize MT

    vector<int> data = {1, 2, 0, 3, 4, 5, 6 ,7, 8};

    std::shuffle(data.begin(), data.end(), generator);

    auto path = bfsSolve(data);
    if ( path.empty() ){
        std::cout << "Solution not possible from state\n";
        printVec(data);
    } else{
        std::cout << "Solution foud in " << path.size()-1 << " moves\n";
        for(auto item : path){
            printVec(item);
        }
    }
    return 0;
}
