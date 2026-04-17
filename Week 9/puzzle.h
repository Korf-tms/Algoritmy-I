#include <vector>
#include <iostream>

using std::vector;

// coordinates in the puzzle
struct coord {
    int x;
    int y;
};

// straightforward implementation of a puzzle class
// internal state represented as vector of vectors of ints, 0 is empty space
class Puzzle {
    // all is public for simplicity
    public:
    vector<vector<int>> state;
    size_t size; // for convenience
    coord emptySpace;  // for convenience
   
    
    Puzzle();

    explicit Puzzle (const vector<vector<int>>& s);
    
    // check for the final state 0, 1, 2, ..., n^2-1
    bool isFinal() const;

    // generate all possible next states from the current state
    vector<Puzzle> getNextStates() const;

    void print() const;

    // needed for the use of Puzzle as a key in unordered_map or unordered_set
    bool operator==(const Puzzle& other) const;

    // for convenience
    bool operator!=(const Puzzle& other) const;

    // needed for the use of Puzzle as a key in map or set
    bool operator<(const Puzzle& other) const;
};

// needed for the use of Puzzle as a key in unordered_map or unordered_set
struct PuzzleHash {
    size_t operator()(const Puzzle& p) const;
};