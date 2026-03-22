#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using std::vector, std::string;

// Similar functionality  to C enum, nicer behaviour
enum class ConstraintType {
    EQUAL,
    DIFFERENT,
    IMPLICATION,
    TRUE,
    FALSE
};

struct Constraint {
    ConstraintType type;
    int clause1;
    int clause2; // only used for EQUAL, DIFFERENT and IMPLICATION
};

ConstraintType parseType(const string& s) {
    if (s == "same") return ConstraintType::EQUAL;
    if (s == "diff") return ConstraintType::DIFFERENT;
    if (s == "impl") return ConstraintType::IMPLICATION;
    if (s == "true") return ConstraintType::TRUE;
    if (s == "false") return ConstraintType::FALSE;
    std::cerr << s + " is not a valid constraint type.\n";
    exit(1);
}

// parse the file in the format:
// first line: number of variables
// the rest: one constraint per line, in the format:
// type clause1 clause2 (clause2 is only used if needed)
std::pair<vector<Constraint>, int> parseFile(const string& filename) {
    std::ifstream input_file(filename);
    string line;
    vector<Constraint> constraints;

    int numOfVariables;
    std::getline(input_file, line);
    numOfVariables = std::stoi(line);

    // NOTE: no sanity checks, it is heavily assumed that the file is in corrent format
    while( std::getline(input_file, line) ){
        std::istringstream iss(line);
        string typeStr;
        int clause1, clause2;
        iss >> typeStr >> clause1;
        if(typeStr == "same" or typeStr == "diff" or typeStr == "impl"){
            iss >> clause2;
        } else {
            clause2 = -1; // special value endcoding clause2 is not used
        }
        constraints.push_back({parseType(typeStr), clause1, clause2});
    }
    return {constraints, numOfVariables};
}
