#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <limits>

using std::cout, std::vector;

class Point{
    public:
    double x;
    double y;

    Point(int xx, int yy) : x(xx), y(yy) {};

    void print(){
        cout << "X: " << x << " Y: " << y << "\n";
    }

    double squaredDistanceTo(Point& other){
        return (x - other.x)*(x - other.x) + (y - other.y)*(y - other.y);
    }
};


std::pair<size_t, size_t> findMinDistance(vector<Point>& vec){
    size_t imin, jmin;    
    double distance;
    double minDist = std::numeric_limits<double>::max();

    for(size_t i = 0; i < vec.size(); i++){
        for(size_t j = i + 1; j < vec.size(); j++){
            distance = vec[i].squaredDistanceTo(vec[j]);
            if( distance < minDist){
                minDist = distance;
                imin = i;
                jmin = j;
            }
        }
    }
    return {imin, jmin};
}


std::vector<int> generateRandomVector(int length, int minVal, int maxVal, int seed) {
    std::mt19937 generator;  // 32-bit random int generator based on Mersenne Twister
    std::uniform_int_distribution<int> dis(minVal, maxVal);  // the actual distribution

    std::vector<int> result;
    result.reserve(length);

    generator.seed(seed);  // naive seed setup, do not use for anything important
    for (int i = 0; i < length; ++i) {
        result.push_back(dis(generator));
    }

    return result;
}

void bubbleSort(vector<int>& vec){
    size_t rightBound = vec.size();

    bool swapHappened = true;
    size_t lastSwapped = rightBound;
    while (swapHappened)
    {
        swapHappened = false;
        for (size_t i = 1; i < rightBound; i++)
        {
            if (vec[i - 1] > vec[i])
            {
                std::swap(vec[i], vec[i - 1]);
                swapHappened = true;
                lastSwapped = i;
            }
        }
        rightBound = lastSwapped;
    }
}

void printVec(const vector<int>& vec){
    for(int item : vec){
        cout << item << " ";
    }
    cout << "\n";
}

int main() {
    vector<int> test1 = generateRandomVector(10000, 10, 100, 10);
    auto test2 = test1;

    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(test2);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << "bubble sort is done in " << duration.count() << "sec\n";


    start = std::chrono::high_resolution_clock::now();
    std::sort(test1.begin(), test1.end());
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    cout << "std::sort is done in " << duration.count() << "sec\n";

    return 0;
}
