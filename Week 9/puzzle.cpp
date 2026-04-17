#include "puzzle.h"

Puzzle::Puzzle() {};

Puzzle::Puzzle(const vector<vector<int>>& s) : state(s), size(s.size()) {
    // find the empty space
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (state[i][j] == 0) {
                emptySpace = {i, j};
                return;
            }
        }
    }
}

bool Puzzle::isFinal() const {
    int number = 0;
    // state is represented line by line, easy to check for the final state
    for (const auto& line : state) {
        for (int value : line) {
            if (value != number) {
                return false;
            }
            number += 1;
        }
    }
    return true;
}

vector<Puzzle> Puzzle::getNextStates() const {
    vector<Puzzle> nextStates;
    // possible moves: up, down, left, right
    vector<coord> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto& move : moves) {
        int newX = emptySpace.x + move.x;
        int newY = emptySpace.y + move.y;
        // check if the move is within bounds
        if( newX < 0 or newX >= size) continue;
        if( newY < 0 or newY >= size) continue;
        // create a new state by swapping the empty space with the adjacent tile
        vector<vector<int>> newState = state;
        std::swap(newState[emptySpace.x][emptySpace.y], newState[newX][newY]);
        // note: emaplace back is probably the better choice here, but requires a come C++ knowledge
        // nextStates.emplace_back(newState);
        Puzzle newPuzzle(newState);
        nextStates.push_back(newPuzzle);

    }
    return nextStates;
}

// the usual
void Puzzle::print() const {
    for (const auto& line : state) {
        for (int value : line) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
}

// all information is contained in state variable, we delegate the == operator
// to the == operator of vector, which behaves as expected
bool Puzzle::operator==(const Puzzle& other) const {
    return state == other.state;
}

// same as for ==
bool Puzzle::operator!=(const Puzzle& other) const {
    return  state != other.state;
}

// same as for ==, note the we do not care about the actual meaning of <
// we just need a strict weak ordering for the use of Puzzle as a key in map or set
// and this is provided by the < operator of vector, which lexicographically compares the elements of the vector
bool Puzzle::operator<(const Puzzle& other) const {
    return state < other.state;
}

size_t PuzzleHash::operator()(const Puzzle& p) const {
   // perfect hash for the puzzle state, based on interpretation of the state as a number in base n^2, where n is the size of the puzzle
    size_t result = 0;
    size_t base = p.size * p.size;
    for (const auto& line : p.state) {
        for (int value : line) {
            result = result * base + value;
        }
    }
    return result;
}