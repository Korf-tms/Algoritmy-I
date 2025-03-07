#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>

using std::cout, std::vector, std::string;
using std::map, std::unordered_map;
using std::stack, std::queue;

int gcdWhile(int m, int n){
    if( m < n ){
        std::swap(m, n);
    }
    while (n != 0){
        int temp = m % n;
        m = n;
        n = temp;
    }
    return m;
}

int gcd(int m, int n){
    if( m < n ){
        std::swap(m, n);
    }
    if( n == 0){
        return m;
    }
    return gcd(n, m % n);
}

vector<int> erathosthenes(int maxVal){
    vector<int> primes;
    vector<int> numbers;
    
    numbers.reserve(maxVal);

    for(int i = 2; i < maxVal + 1; i++){
        numbers.push_back(i);
    }

    // implementace jako na prednasce, skrtnute cislo je nastaveno na 0
    for(size_t i = 0; i < numbers.size(); i++){
        if( numbers.at(i) != 0){
            int newPrime = numbers.at(i);
            primes.push_back(newPrime);
            for(size_t j = i; j < numbers.size(); j += newPrime){
                numbers[j] = 0;
            }
        }
    }
    return primes;
}

void printVec(const vector<int>& vec){
    for(const auto item : vec){
        cout << item << " ";
    }
    cout << "\n";
}

void printMap(const unordered_map<char, char>& myMap){
    for(const auto& [key, value] : myMap){
        cout << key <<":" << value << "\n";
    }
}

void printMap(const unordered_map<char, int>& myMap){
    for(const auto& [key, value] : myMap){
        cout << key <<":" << value << "\n";
    }
}

void gcdDemo(){
    int a = 7456134;
    int b = 32345;
    
    cout << gcd(a, b) << "\n";
    cout << gcdWhile(a, b) << "\n";
}

void primesDemo(){
    int N = 10000;
    vector<int> primes = erathosthenes(N);
    printVec(primes);
}

void mapDemo(){
    unordered_map<char, char> dict;
    dict['('] = ')';
    dict['['] = ']';
    dict['{'] = '}';
    dict['<'] = '>';
    printMap(dict);

    // https://www.thelatinlibrary.com/cicero/cat1.shtml
    string text = "I. Quo usque tandem abutere, Catilina, patientia nostra? quam diu etiam furor iste tuus nos eludet? quem ad finem sese effrenata iactabit audacia? Nihilne te nocturnum praesidium Palati, nihil urbis vigiliae, nihil timor populi, nihil concursus bonorum omnium, nihil hic munitissimus habendi senatus locus, nihil horum ora voltusque moverunt? Patere tua consilia non sentis, constrictam iam horum omnium scientia teneri coniurationem tuam non vides? Quid proxima, quid superiore nocte egeris, ubi fueris, quos convocaveris, quid consilii ceperis, quem nostrum ignorare arbitraris?"
    "O tempora, o mores! Senatus haec intellegit. Consul videt; hic tamen vivit. Vivit? immo vero etiam in senatum venit, fit publici consilii particeps, notat et designat oculis ad caedem unum quemque nostrum. Nos autem fortes viri satis facere rei publicae videmur, si istius furorem ac tela vitemus. Ad mortem te, Catilina, duci iussu consulis iam pridem oportebat, in te conferri pestem, quam tu in nos [omnes iam diu] machinaris. ";
    
    // napocita vyskyt jednotlivych znaku
    unordered_map<char, int> counts;
    for(char token : text){
        counts[token] += 1;
    }
    cout << counts.size() << " individual chars" << "\n";
    printMap(counts);
}

int main(){
    gcdDemo();
    primesDemo();
    mapDemo();

    return 0;
}