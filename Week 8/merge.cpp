#include<iostream>
#include<vector>

using std::vector, std::cout;
constexpr int MERGE_SORT_LIMIT = 10; // limit delky pro prepnuti z mergesortu na O(n^2) sort

void insertionSort(vector<int>& vec){
    int temp; // promenna pro umistovanou hodnotu
    int j;  // promenna pro vnitrni umistovaci cyklus
    for(int i = 0; i < vec.size(); i++){
        temp = vec[i];  // hodnota, kterou chci zatridit
        j = i - 1; // chci projet pozice nalevo od i, od i-1 do nuly
        while((j >= 0) and (vec[j] >= temp)){
            vec[j+1] = vec[j];  // zatrizena hodnota vynuti posunuti, tak uz posunuju
            j -= 1;
        }
        vec[j + 1] = temp;
    }
}

void print(const vector<int>& vec){
    for(auto item : vec){
        cout << item << " ";
    }
    cout << "\n";
}

void merge(const vector<int>& left, const vector<int>& right, vector<int>& target){
    size_t left_i = 0;
    size_t right_i = 0;
    size_t target_i = 0;

    while( left_i < left.size() and right_i < right.size() ){
        // zapisujeme z mensiho z leveho/praveho pole
        if( left.at(left_i) < right.at(right_i) ){
            target[target_i] = left.at(left_i);
            target_i += 1;
            left_i += 1;
        } else {
            target[target_i] = right.at(right_i);
            target_i += 1;
            right_i += 1;
        }
    }
    // jesti nekde neco zbylo, tak to patri nakonec
    // if pro zjisteni, v kterem poli je ten zbytek
    if ( left_i == left.size() ){
        while( right_i < right.size() ){
            target[target_i] = right.at(right_i);
            target_i += 1;
            right_i += 1;
        }
    } else {
        while( left_i < left.size() ){
            target[target_i] = left.at(left_i);
            target_i += 1;
            left_i += 1;
        }
    }
}

// naivni primocara implementace se spoustou kopii
void mergeSort(vector<int>& vec){
    // konec rekurze
    if( vec.size() < MERGE_SORT_LIMIT){
        insertionSort(vec);   
        return;
    }

    int mid = vec.size()/2;

    // divide & conquer vektory pro levou a pravou cast 
    vector<int> left;
    vector<int> right;
    left.reserve(vec.size()/2 + 1);
    right.reserve(vec.size()/2 + 1);

    for(size_t i = 0; i < vec.size(); i++){
        if(i < mid){
            left.push_back(vec.at(i));
        } else {
            right.push_back(vec.at(i));
        }
    }

    mergeSort(left);
    mergeSort(right);
    merge(left, right, vec);
}

int main(){
    // idealni by bylo vynegerovat nahodne vektory a otestovat
    // rychlost trizdeni pro merge, std::sort a treba insertion sort
    vector<int> test = {5, 4, 3, 2, 1, 10,
         11, 12, 12, 13, 14, -1, -4, -6, -8, 20, 30, 40, 50, 60,
        101, 103, -5, -9, 1, 2};
    mergeSort(test);
    print(test);
    return 0;
}