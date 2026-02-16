#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <random>

using std::vector;

// skutecny stav obaleny spoustou -1
using State = vector<int>;

// obali size x size mrizku okrajem z -1
State convertToState(const vector<int>& trueState, const size_t size){
    vector<int> state(( size+2)*(size+2), -1);
    size_t index = 0;
    for( size_t i = 0; i < state.size(); i++ ){
        if( (i / (size+2) == 0) or (i / (size+2) == size+1)){
            continue;
        }
        if( (i % (size+2) == 0) or (i % (size+2) == size+1)){
            continue;
        }
        state[i] = trueState[index];
        index += 1;
    }
    return state;
}

void printVec(const vector<int>& v){
    for(int item : v){
        std::cout << item << " ";
    }
    std::cout << "\n";
}

// print relevantni casti, bez -1
void printState(const State s){
    for( int item : s){
        if( item != -1){
            std::cout << item;
        }
    }
    std::cout << "\n";
}

bool isWinning(const State& state){
    State w = convertToState({0, 1, 2, 3, 4, 5, 6, 7, 8}, 3);
    return state == w;
}

vector<State> generateNextStates(const State& state){
    vector<State> res;
    const int n = 5; // zvetsit pro vetsi tabulky

    vector<int> potentialNeighbours = {-n, -1, +1, +n};

    auto iteratorPoitingToZero = find(state.begin(), state.end(), 0);
    int indexOfZero = std::distance(state.begin(), iteratorPoitingToZero);

    for(int move : potentialNeighbours){
        int potentialMove = indexOfZero + move;
        if( state[potentialMove] != -1){
            State newState = state;
            std::swap(newState[indexOfZero], newState[indexOfZero + move]);
            res.push_back(newState);
        }
    }

    return res;
}

vector<State> bsfSolve(const State& start){
    std::queue<State> bfsQ;
    std::set<State> visited;
    std::map<State, State> parentState; // mapa node -> parent
    vector<State> winningPath;

    visited.insert(start);
    bfsQ.push(start);

    // bfs jako vzdy
    while( not bfsQ.empty() ){
        State currentNode = bfsQ.front();
        bfsQ.pop();

        const vector<State> neighbours = generateNextStates(currentNode);
        for(const State & item : neighbours ){
            if( visited.find(item) == visited.end()){
                visited.insert(item);
                bfsQ.push(item);
                // stavime mapu
                parentState[item] = currentNode;
                if( isWinning(item) ){
                    winningPath.push_back(item);
                    State aux = item;
                    // pouzivame mapu k sestaveni postupu
                    while(aux != start){
                        aux = parentState[aux];
                        winningPath.push_back(aux);
                    }
                    // akorat je nutno ji obratit, staci trochu rozmyslet
                    std::reverse(winningPath.begin(), winningPath.end());
                    return winningPath;
                }
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

    // nahodne opermutuje vektor
    std::shuffle(data.begin(), data.end(), generator);

    State start = convertToState(data, 3);

    auto path = bsfSolve(start);
    if ( path.empty() ){
        std::cout << "Solution not possible from state\n";
        printState(start);
    } else{
        std::cout << "Solution foud in " << path.size()-1 << " moves\n";
        for(auto item : path){
            printState(item);
        }
    }

    return 0;
}