#include <iostream>
#include <vector>
#include <string>

using std::vector, std::string;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    // Note that there is alternative implementation as void insert(Node*& node, int key)
    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        // No duplicates in search tree
        return node;
    }

    void inorder(Node* node, vector<int>& res) const {
        if (node == nullptr){
            return;
        }
        inorder(node->left, res);
        res.push_back(node->key); // moving this line up chantes to predorder, down to postorder
        inorder(node->right, res);
    }

    void destroy(Node* node) {
        if (node == nullptr){
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    int heigth(Node* node) const {
        if(node == nullptr){
            return 0; // or return -1, depends on convention
        }
        return 1 + std::max(heigth(node->left), heigth(node->right));
    }

public:
    BST(){
        root = nullptr;
    }

    ~BST() {
        destroy(root);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    vector<int> inorderTraverse() const {
        vector<int> res;
        inorder(root, res);
        return res;
    }

    int heigth() const {
        return heigth(root);
    }
    
};

void printVec(const vector<int> vec){
    for(const auto& item : vec){
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int main(){
    BST tree;
    vector<int> data = {4, 5, 3, -1, -3, -5, 10, 11, 12, 15};
    for(const int item : data){
        tree.insert(item);
    }

    std::cout << tree.heigth() << "\n";

    auto vec = tree.inorderTraverse();
    printVec(vec);

    return 0;
}