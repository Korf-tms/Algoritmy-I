#include <iostream>
#include <vector>

using std::vector;


// partitions the part of the vector between left and right (inclusive), puts the pivot in its final position and returns the index of the pivot
// maintains the invariant that all the elements before the separator are less than pivot, and all the elements after the separator are greater or equal to pivot
size_t lomutoPartition(vector<int>& vec, size_t left, size_t right) {
    int pivot = vec[left]; // taken from Levitins book, but it can be any element in the vector
    size_t separator = left;  // the first element that is greater or equal to the pivot, so the elements before it are less than the pivot
    // note that the separator is initialized to left, so the first element that is greater or equal to the pivot is the pivot itself, which is ok

    for (size_t i = left + 1; i <= right; i++) {
        if (vec[i] < pivot) { // found element that belongs to the left of the pivot
            separator += 1; // move separator to the right, to make space for the new element
            std::swap(vec[separator], vec[i]);
        }
        // there is no else since the >= pivot elements are already in the right place
    }
    std::swap(vec[separator], vec[right]); // put pivot in its final position
    return separator;
}

void whateverSortThatIsReasonableFastForSmallVectors(vector<int>& vec, size_t left, size_t right) {
    for (size_t i = left + 1; i <= right; i++) {
        int item = vec[i];
        size_t j = i;
        while ( j > left && vec[j - 1] > item) {
            vec[j] = vec[j - 1];
            j -= 1;
        }
        vec[j] = item;
    }
}



const size_t SMALL_VECTOR_THRESHOLD = 10;

// super naive quicksort implementation, not optimized for performance, just to show the idea of the algorithm
// better implementation would use better pivot selection and Hoare partition scheme, but idea is the same
void lomutoQuickSort(vector<int>& vec, size_t left, size_t right) {
    // recursion base case -> use some other fast sort for small vectors
    if (right - left < SMALL_VECTOR_THRESHOLD) {
        whateverSortThatIsReasonableFastForSmallVectors(vec, left, right);
        return;
    }
    size_t pivotIndex = lomutoPartition(vec, left, right); // pivot is in place now and we can sort left and right parts independently
    lomutoQuickSort(vec, left, pivotIndex - 1);
    lomutoQuickSort(vec, pivotIndex + 1, right);
}


int main() {
    vector<int> vec = {42, 5, 3, 8, 4, 2, 12, 42, 42, 42};
    lomutoQuickSort(vec, 0, vec.size() - 1);
    for (int x : vec) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}