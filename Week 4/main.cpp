#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;

vector<int> generateRandomVector(size_t size, int minValue, int maxValue, int seed=42) {
    std::mt19937 gen(seed); // Note that int as seed is not the best choice, but it is sufficient here
    std::uniform_int_distribution<> dis(minValue, maxValue);

    vector<int> vec(size);

    for (size_t i = 0; i < size; ++i) {
        vec[i] = dis(gen); // gen generates a random number, and dis transforms it to desired distribution
    }
    return vec;
}

// Bubble sort with minor optimizations and swap counting
void bubbleSort(vector<int>& vec) {
    size_t counter = 0;
    size_t rightBorder = vec.size() - 1;
    for(size_t i = 0; i < vec.size(); ++i) {
        bool swapHappened = false;
        size_t lastSwapIndex = 0;
        for(size_t j = 0; j < rightBorder; ++j) {
            if( vec[j] > vec[j + 1] ) {
                std::swap(vec[j], vec[j + 1]);
                swapHappened = true;
                lastSwapIndex = j;
                counter += 1;
            }
        }
        if ( not swapHappened){
            std::cout << "Bubble sort used " << counter << " swaps\n";
            return;
        }
        rightBorder = lastSwapIndex;
    }
}

// Selection sort with swap counting
void selectionSort(vector<int>& vec) {
    size_t counter = 0;
    for(size_t position = 0; position < vec.size(); ++position) {
        size_t minIndex = position;
        for(size_t j = position + 1; j < vec.size(); ++j) {
            if( vec[j] < vec[minIndex] ) {
                minIndex = j;
            }
        }
        if (minIndex != position) {
            std::swap(vec[position], vec[minIndex]);
            counter += 1;
        }
    }
    std::cout << "Selection sort used " << counter << " swaps\n";
}

// Wrapper for std::sort
void stdSort(vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}

// Function template for vector printing
template<typename T>
void printVector(const vector<T>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

template<typename T>
bool vectorsEqual(const vector<T>& vec1, const vector<T>& vec2) {
    if (vec1.size() != vec2.size()) return false;
    
    for (size_t i = 0; i < vec1.size(); ++i) {
        if (vec1[i] != vec2[i]) return false;
    }
    return true;
}

int main() {
    const vector<int> numbers = generateRandomVector(1e5, 0, 100000);

    auto vec1 = numbers;
    auto vec2 = numbers;
    auto vec3 = numbers;

    std::cout << "Sorting " << numbers.size() << " random ints\n";

    // measure time take by bubble sort, shaker sort and std::sort
    auto start = std::chrono::high_resolution_clock::now(); // start timer
    bubbleSort(vec1);
    auto end = std::chrono::high_resolution_clock::now(); // end timer
    std::chrono::duration<double> bubble_duration = end - start; // calculate duration, .count() returns the duration in seconds as a double
    std::cout << "Bubble sort took: " << bubble_duration.count() << " seconds" << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    selectionSort(vec2);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> selection_duration = end - start;
    std::cout << "Selection sort took: " << selection_duration.count() << " seconds" << std::endl;
    
    start = std::chrono::high_resolution_clock::now();
    stdSort(vec3);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> std_duration = end - start;
    std::cout << "std::sort took: " << std_duration.count() << " seconds" << std::endl;

    // check the sorts aginst std::sort
    if( not vectorsEqual(vec1, vec3)) {
        std::cout << "Bubble sort is not ok.\n";
    }
    if( not vectorsEqual(vec2, vec3)) {
        std::cout << "Selection sort is not ok.\n";
    }

    return 0;
}