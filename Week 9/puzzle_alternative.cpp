#include <vector>
#include <iostream>

using std::vector;

// alternative implementation of the puzzle class, using a single vector to represent the state instead of a vector of vectors
class Puzzle {
    public:
    vector<int> state; // state as single vector, written line by line
    size_t size; // for convenience
    int emptySpace; // for convenience;

    Puzzle();
    explicit Puzzle(const vector<int>& initialState, const int s);
    bool isFinal() const;
    vector<Puzzle> getNextStates() const;
    void print() const;
};

Puzzle::Puzzle() {};

Puzzle::Puzzle(const vector<int>& initialState, const int s) : state(initialState), size(s) {
    // find the empty space
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] == 0) {
            emptySpace = i;
            return;
        }
    }
}

bool Puzzle::isFinal() const {
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] != i) {
            return false;
        }
    }
    return true;
}

vector<Puzzle> Puzzle::getNextStates() const {
    vector<Puzzle> nextStates;
    // possible moves: up, down, left, right
    // cast to make ints from size_t, should be fine as size is small, but better to be safe
    vector<int> moves = {-static_cast<int>(size), static_cast<int>(size), -1, 1};
    for (const auto& move : moves) {
        int newEmptySpace = emptySpace + move;
        // check if the move is within bounds
        if( move == -1 and emptySpace % size == 0) continue; // left move not possible
        if( move == 1 and emptySpace % size == size - 1) continue; // right move not possible
        // up and down move conditions can be nicely put together, as they are more "universal"
        if( newEmptySpace < 0 or newEmptySpace >= state.size()) continue;
        // create a new state by swapping the empty space with the adjacent tile
        vector<int> newState = state;
        std::swap(newState[emptySpace], newState[newEmptySpace]);
        Puzzle newPuzzle(newState, size);
        nextStates.push_back(newPuzzle);
        // or use nextStates.emplace_back(newState, size);
    }
    return nextStates;
}

// hash is the same as for the other representation
struct PuzzleHash {
    size_t operator()(const Puzzle& p) const {
        size_t result = 0;
        size_t base = p.size * p.size;
        for (const auto& value : p.state) {
            result = result * base + value;
        }
        return result;
    }
};