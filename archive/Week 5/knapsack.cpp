#include <iostream>
#include <vector>

using std::vector, std::cout;

class Item{
    public:
    int weight;
    int value;
};

void knapsackBruteForce(const vector<Item>& stuff, int capacity){
    int noOfItems = stuff.size();
    int noOfSubsets = 1 << noOfItems;
    vector<int> maskVec;

    for(int mask = 0; mask < noOfSubsets; mask++){
        // construct mask vec by repeated division
        maskVec.clear();
        int temp = mask;
        for(int i = 0; i < noOfItems; i++){
            maskVec.push_back(temp % 2);
            temp /= 2;
        }
        // compute and print the actual value
        int totalValue = 0;
        int totalWeight = 0;
	// this has alternative in mask & (1 << i )
        for(size_t i = 0; i < stuff.size(); i++){
            totalWeight += stuff[i].weight * maskVec[i];
            totalValue += stuff[i].value * maskVec[i];
        }

        for(size_t i = 0; i < maskVec.size(); i++){
            if(maskVec[i] == 1){
                cout << i + 1 << " ";
            }
        }
        if( totalWeight > capacity){
            cout << "too heavy\n";
        } else {
            cout << "has value: " << totalValue << "\n";
        }
    }

}


int main(){
    vector<Item> items = {
        {7, 42},  // Item 1
        {3, 12},  // Item 2
        {4, 40},  // Item 3
        {5, 25}   // Item 4
    };
    int knapsackCapacity = 10;
    knapsackBruteForce(items, knapsackCapacity);

    return 0;

}
