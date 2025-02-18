#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::vector, std::string;


vector<int> readIntsFromFile(const string& filename){
    vector<int> numbers;
    std::ifstream file(filename, std::ios::in);

    if (not file.is_open()) {
        std::cerr << "Unable to open file " << filename << "\n";
        return {};
    }
    
    string line;

    // NOTE: this assumes that the file contains only ints of reasonable sizes!
    while (std::getline(file, line)) {
        std::stringstream lineAsStream(line);
        string word;
        while(lineAsStream >> word){
            int num = std::stoi(word);
            numbers.push_back(num);
        }
    }

    return numbers;
}

void printIntVec(const vector<int>& inVec){
    for(const auto& item : inVec){
        std::cout << item << " ";
    }
    std::cout << "\n";
}

void test(string filename){
    vector<int> numbers;

    numbers = readIntsFromFile(filename);
    printIntVec(numbers);
}

int main(int argc, char* argv[]) {
    if (argc < 2){
        std::cerr << "No filename provided" << std::endl;
        return 0;
    }
    if (argc > 2){
        std::cerr << "Only first parameter is used as filename\n";
    }
    
    string filename = argv[1];

    test(filename);
    
    return 0;
}