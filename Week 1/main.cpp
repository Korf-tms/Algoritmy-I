#include <iostream>
#include <vector>

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


template<typename T>
void printVec(const vector<T>& vec){
    for(int item : vec){
        cout << item << " ";
    }
    cout << "\n";
}

vector<int> sieve(const int N){
    vector<int> numbers(N - 1, 1);
    vector<bool> isPrime(N - 1, true);
    vector<int> primes;

    // initialization
    for(size_t i = 0; i < numbers.size(); i++){
        numbers[i] = i + 2;
    }

    //sieving
    for(size_t i = 0; i < numbers.size(); i++){
        int number = numbers[i];
        if( isPrime[i] ){
            primes.push_back(number);
            for(size_t j = i; j < isPrime.size(); j += number){
                isPrime[j] = false;
            }
        }
    }
    return primes;
}


int main(){
    helloWorld();

    vector<int> myVec = {-1, 0, 1, 2, 4};
    vector<int> twos(5, 2);  // vyrobi vektor dane delky s danou hodnou ve vsech pozicich

    printIntVec(myVec);
    printIntVec(twos);
    printVec(myVec);

    const auto primes = sieve(23);
    printVec(primes);


    return 0;
}
