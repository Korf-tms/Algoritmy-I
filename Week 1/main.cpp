#include <iostream>
#include <vector>
#include <cmath> // for sqrt

using std::cout, std::vector;
using std::sqrt;

void helloWorld(){
    cout << "Hello World\n";
}

// Prints vector of ints
void printIntVec(const vector<int>& vec){
    for(int item : vec){
        cout << item << " ";
    }
    cout << "\n";
}

// Template that generates function that prints vector of anything
// that has suitable operator<<
template<typename T>
void printVec(const vector<T>& vec){
    for(const auto& item : vec){
        cout << item << " ";
    }
    cout << "\n";
}

// Erathosthenes sieve for primes
vector<int> sieve(const int N){
    vector<int> numbers(N - 1, 1);
    vector<bool> isPrime(N - 1, true);
    vector<int> primes;

    // initialization
    for(size_t i = 0; i < numbers.size(); i++){
        numbers[i] = i + 2;
    }

    // sieving
    for(size_t i = 0; i < numbers.size(); i++){
        int number = numbers[i];
        if( isPrime[i] ){
            primes.push_back(number);
            // "cross out" all multiples
            for(size_t j = i; j < isPrime.size(); j += number){
                isPrime[j] = false;
            }
        }
    }
    return primes;
}

int sumEven(const vector<int>& vec){
    int res = 0;

    for(const int item : vec){
        if( item % 2 == 0){
            res += item;
        }
    }

    return res;
}

bool isPrime(const int n){
    if( n == 2 or n == 3 ) return true;
    if( n % 2 == 0) return false;

    double upperBound = sqrt(n) + 1;
    for(int i = 3; i < upperBound; i += 2){
        if( n & i == 0) return false;
    }
    return true;
}

int main(){
    helloWorld();

    vector<int> myVec = {-1, 0, 1, 2, 4};
    vector<int> twos(5, 2);  // vyrobi vektor dane delky s danou hodnou ve vsech pozicich

    printIntVec(myVec);
    printIntVec(twos);
    printVec(myVec);

    const auto primes = sieve(200);
    printVec(primes);
    for(const int number : primes){
        if( not isPrime(number) ){
            std::cout << "Something is wrong with the number " << number << ".\n";
        }
    }

    vector<double> dVec = {-1.0, 0.0, 10.0, 22.11};
    printVec(dVec);

    return 0;
}
