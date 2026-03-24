#include <iostream>
#include <vector>
#include <algorithm> // for next_permutation
#include <limits> // for numeric_limits

using std::vector;

class Item {
    public:
    int weight;
    int value;

    // overload << operator for fun with friends
    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        os << "Item(weight: " << item.weight << ", value: " << item.value << ")";
        return os;
    }
};

template<typename T>
void printVector(const vector<T>& vec) {
    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

vector<Item> knapsackBruteforce(const vector<Item>& items, int capacity) {
    vector<Item> bestCombination;
    int maxValue = 0;  // Maximization problem -> initialize to 0
    int n = items.size();
    int stateSpaceSize = 1 << n; // 2^n possible combinations

    // loop through the state space
    for (int mask = 0; mask < stateSpaceSize; ++mask) {
        vector<Item> currentCombination;
        int currentWeight = 0;
        int currentValue = 0;

        // get individual bits from the mask to determine which items are included
        for (int j = 0; j < n; ++j) {
            if (mask & (1 << j)) {
                currentWeight += items[j].weight;
                currentValue += items[j].value;
            }
        }
        // alternatively, we could save the bits in a vector and use another loop to calculate the weight and value
        // but this is nicer as long as we can live with the bit manipulation

        if(currentWeight > capacity) continue; // nothing to do if we exceed the capacity
        if (currentValue > maxValue) {  // update current best
            maxValue = currentValue;
            for(int j = 0; j < n; ++j) {
                if (mask & (1 << j)) {
                    currentCombination.push_back(items[j]);
                }
            }
            bestCombination = currentCombination;
        }
    }
    return bestCombination;
}

void testKnapsack() {
    const vector<Item> items = { // Values taken from Levitin's book
        {7, 42},
        {3, 12},
        {4, 40},
        {5, 25}
    };
    int capacity = 10;
    auto bestLoad = knapsackBruteforce(items, capacity);
    int finalValue = 0;
    for (const auto& item : bestLoad) {
        finalValue += item.value;
    }
    std::cout << "Best load value: " << finalValue << ". Knapsack contains:\n";
    printVector(bestLoad);
}

vector<int> TSPbruteForce(const vector<vector<int>>& data){
    int minDist = std::numeric_limits<int>::max(); // minimization problem -> initialize to MAX_INT
    vector<int> cities(data.size() - 1); // we will always start at city 0, so we only need to permute the other cities
    for(int i = 1; i < data.size(); i++){ // initialize with cities in ascending order -> this is the first permutation
        cities[i - 1] = i;
    }

    vector<int> bestPath;

    // as always, loop over the state space and find the best state
    do {
        int totalDist = 0;
        int prevCity = 0; // path starts at city 0

        for(int city : cities ){
            totalDist += data[prevCity][city];
            prevCity = city;
        }

        totalDist += data[prevCity][0]; // path ends at city 0
        if( totalDist < minDist ){
            minDist = totalDist;
            bestPath = cities;
        }

    } while (std::next_permutation(cities.begin(), cities.end()));
    bestPath.push_back(0); // include the special starting city
    return bestPath;
}

void testTSP() {
    // data matrix, effectively weighted adjacency matrix of the graph, where the weight is the distance between the cities
    vector<vector<int>> dist = { // data taken from Levitin's book, labeling a, b, c, d as 0, 1, 2, 3
        { 0, 2, 5, 7 },
        { 2,  0, 8, 3 },
        { 5, 8,  0, 1 },
        { 7, 3, 1,  0 }
    };

    auto bestPath = TSPbruteForce(dist);
    std::cout << "TSP best path: ";
    printVector(bestPath);
}


int main() {
    testKnapsack();
    testTSP();
    return 0;
}