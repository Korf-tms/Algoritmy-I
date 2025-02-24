#include<iostream>
#include<vector>

using std::cout, std::vector;

void helloWorld(){
    cout << "Hello World\n";
}

void printIntVec(const vector<int>& vec){
    for(int item : vec){
        cout << item << " ";
    }
    cout << "\n";
}

vector<int> helloVector(const int size){
    vector<int> res;

    int value = 1;
    vector<int> ones(size, value);

    for(int i = 0; i < size; i++){
        res.push_back(2*i + 1);
    }

    for(int i = 0; i < size; i++){
        res[i] += ones[i];
    }

    return res;
}

int sumEven(const vector<int> vec){
    int suma = 0;
    for(const int item : vec){
        if ( item % 2 == 0){
            suma += item;
        }
    }
    return suma;
}

int main(){
    helloWorld();

    vector<int> myVec = {-1, 0, 1, 2, 4};
    vector<int> otherVec = helloVector(10);
    vector<int> twos(5, 2);  // vyrobi vektor dane delky s danou hodnou ve vsech pozicich

    printIntVec(myVec);
    printIntVec(otherVec);
    printIntVec(twos);
    cout << sumEven(myVec) << "\n";

    return 0;
}