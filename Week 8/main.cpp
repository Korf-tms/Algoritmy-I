#include <string>
#include <iostream>
#include <vector>

// Node of a C-like implementation of a binary search tree
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};


// simple BST, smaller numbers go to the left, larger numbers go to the right
class BST {
    private:
        Node* root;

        // insert reccurent helper, not that does nothing if the key is already in the tree
        Node* insert(Node* node, int key) {
            if (node == nullptr) {
                return new Node(key);
            }
            if (key < node->key) {
                node->left = insert(node->left, key);
            } else if (key > node->key) {
                node->right = insert(node->right, key);
            }
            return node;
        }

        // find reccurent helper
        bool find(Node* node, int key) {
            if (node == nullptr) {
                return false;
            }
            if (key == node->key) {
                return true;
            }
            if (key < node->key) {
                return find(node->left, key);
            } else {
                return find(node->right, key);
            }
        }

        void inOrderPrint(Node* node) const {
            if (node != nullptr) {
                inOrderPrint(node->left);
                std::cout << node->key << " ";
                inOrderPrint(node->right);
            }
        }

        void preOrderPrint(Node* node) const {
            if (node != nullptr) {
                std::cout << node->key << " ";
                preOrderPrint(node->left);
                preOrderPrint(node->right);
            }
        }

        // serialize the tree in a string, using pre-order traversal, and using parentheses to denote the structure of the tree
        // structure is: key(left_subtree)(right_subtree), note that empty subtree is denoted by ()
        void serialize(Node* node, std::string& res) const {
            if( node == nullptr) return;
            res += std::to_string(node->key);
            res += "(";
            serialize(node->left, res);
            res += ")(";
            serialize(node->right, res);
            res += ")";
        }

    public:
        BST() : root(nullptr) {}

        void insert(int key) {
            root = insert(root, key);
        }

        bool find(int key) {
            return find(root, key);
        }

        void inOrderPrint() const {
            inOrderPrint(root);
            std::cout << "\n";
        }

        void preOrderPrint() const {
            preOrderPrint(root);
            std::cout << "\n";
        }

        std::string serialize() const {
            std::string res = "";
            serialize(root, res);
            return res;
        }
};

// little tree test
int main () {
    BST tree;
    const std::vector<int> keys = {5, 3, 7, 2, 4, 6, 8};
    for (int k : keys) {
        tree.insert(k);
    }
    std::cout << "In-order: ";
    tree.inOrderPrint();
    std::cout << "Pre-order: ";
    tree.preOrderPrint();
    std::cout << "Serialization:\n";
    std::cout << tree.serialize() << "\n";
    return 0;
}