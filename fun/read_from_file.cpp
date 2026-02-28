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

string readTextFromFile(const string &fileName) {
    std::ifstream file(fileName); // needs #include<fstream>
    if (!file) {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        exit(1);
    }
    string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return text;
}

void printIntVec(const vector<int>& inVec){
    for(const auto& item : inVec){
        std::cout << item << " ";
    }
    std::cout << "\n";
}

void testReadInts(const string& filename){
    vector<int> numbers;

    numbers = readIntsFromFile(filename);
    printIntVec(numbers);
}

void testReadFile(const string& filename){
    string text;

    text = readTextFromFile(filename);
    std::cout << text;
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

    testReadInts(filename);

    testReadFile(filename);
    
    return 0;
}