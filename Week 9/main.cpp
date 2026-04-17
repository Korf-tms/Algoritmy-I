#include <iostream>
#include <vector>
#include <algorithm>  // for std::reverse
#include <queue>
#include <set>  // for implementation of "visited" set
#include <unordered_set>  // for implementation of "visited" set
#include <map>  // for implementation of "parents" map
#include <unordered_map>  // for implementation of "parents" map
#include "puzzle.h"  

using std::vector;

// BFS bruteforce the puzzle. Note that visited is technically not needed, as the info is also present in the parents map.
bool solve(const Puzzle& start, vector<Puzzle>& solutionPath){
    std::queue<Puzzle> bfsQ;
    // visited as unordered_set, alternative is to use set, which needs only operator<
    std::unordered_set<Puzzle, PuzzleHash> visited;
    // setd::set<Puzzle> visited; 
    std::unordered_map<Puzzle, Puzzle, PuzzleHash> parents;
    // std::map<Puzzle, Puzzle> parents;

    bfsQ.push(start);
    visited.insert(start);
    while( not bfsQ.empty()){
        const Puzzle currentNode = bfsQ.front();
        bfsQ.pop();
        if(currentNode.isFinal()){
            // reconstruct the path from start to current using the parents map
            Puzzle current = currentNode;
            while(current != start){
                solutionPath.push_back(current);
                current = parents[current];
            }
            solutionPath.push_back(start);
            std::reverse(solutionPath.begin(), solutionPath.end());
            return true;
        }
        for(const Puzzle& next : currentNode.getNextStates()){
            if(visited.find(next) == visited.end()){
                visited.insert(next);
                parents[next] = currentNode;
                bfsQ.push(next);
            }
        }
    }
    return false;
}


int main() {
    vector<vector<int>> data = {
        {1, 2, 3},
        {5, 6, 0},
        {7, 8, 4}
    };
    Puzzle puzzle(data);
    // empty vector to store the path, if found
    vector<Puzzle> solutionPath;
    if(solve(puzzle, solutionPath)){
        std::cout << "Solution found! Path length: " << solutionPath.size() << "\n";
        for(const Puzzle& step : solutionPath){
            step.print();
            std::cout << "\n";
        }
    } else {
        std::cout << "No solution found.\n";
    }
}