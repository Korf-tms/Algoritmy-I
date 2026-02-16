#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>

using std::vector, std::cout, std::next_permutation, std::numeric_limits;

vector<int> TSPbruteForce(const vector<vector<int>>& data){
    int minDist = numeric_limits<int>::max();
    vector<int> cities(data.size() - 1);
    for(int i = 1; i < data.size(); i++){
        cities[i - 1] = i;
    }

    vector<int> bestPath;

    do {
        int totalDist = 0;
        int prevCity = 0;

        for(int city : cities ){
            totalDist += data[prevCity][city];
            prevCity = city;
        }

        totalDist += data[prevCity][0];
        if( totalDist < minDist ){
            minDist = totalDist;
            bestPath = cities;
        }

    } while (next_permutation(cities.begin(), cities.end()));
    bestPath.push_back(0);
    return bestPath;
}


int main(){
    vector<vector<int>> dist = {
        { 0, 10, 15, 20 },
        { 10,  0, 35, 25 },
        { 15, 35,  0, 30 },
        { 20, 25, 30,  0 }
    };

    TSPbruteForce(dist);

    return 0;
}
