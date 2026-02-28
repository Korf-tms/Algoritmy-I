#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
// implementace slovniku a mnoziny vyvazenym binarnim stromem
#include <map>
#include <set>
// implementace slovniku a mnoziny hashovaci tabulkou
#include <unordered_map>
#include <unordered_set>

using std::queue, std::stack, std::string, std::map, std::set, std::cout, std::vector;

int main() {
    queue<char> demoQ;
    vector<char> itemsQ = {'q', 'w', 'e', 'r'};

    for(const auto item : itemsQ){
        demoQ.push(item); // pridava na konec
    }

    while( not demoQ.empty() ){ // kontroluje, jestli je fronta prazdna
        cout << demoQ.front() << " "; // koukne se na predek fronty
        demoQ.pop(); // odstrani z predku fronty
    }
    cout << "\n";

    // pro zasobnik funguje vsechno analogicky
    stack<int> demoStack;
    vector<int> intemsStack = {1, 11, 111, 1111};
    
    for(const auto item : intemsStack){
        demoStack.push(item);
    }

    while( not demoStack.empty() ){
        cout << demoStack.top() << " ";
        demoStack.pop();
    }
    cout << "\n";

    set<string> demoSet = {"The Larch", "Chestnut", "Oak", "Douglas Fir"};
    demoSet.insert("Binary Tree");
    demoSet.erase("Oak");

    for(const auto& item : demoSet){ // chceme &, protoze nechceme extra kopie
        cout << item << " ";
    }
    cout << "\n";

    // .count je relativne primocary zpusob zjisteni jestli v mnozine prvek je
    cout << demoSet.count("Oak") << " " << demoSet.count("The Larch") << "\n";
    
    map<string, string> demoDict = {
        {"cat", "kocka"},
        {"dog", "pes"},
    };
    demoDict["swallow"] = "vlastovka";
    
    // je treba mit na pameti, ze operator[] zapisuje i cte, ciste pro cteni tu je .at
    cout << demoDict.at("swallow") << "\n";

    // takhle vytvorime zaznam ve slovniku
    cout << demoDict["swalow"] << "\n";
    // jak se muzeme presvedcit proiterovanim
    for(const auto& [key, value] : demoDict){
        cout << key << "->" << value << "\n";
    }

    return 0;
}