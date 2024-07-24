#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int key) : val(key), left(NULL), right(NULL) {}
};

class BinarySearchTree {
private:
    TreeNode* root;
    int size;
    int maxSize;

    TreeNode* insert(TreeNode* node, int key) {
        if (size >= maxSize) {
            cout << "Tree has reached its maximum size." << endl;
            return node;
        }
        if (!node) {
            size++;
            return new TreeNode(key);
        }
        if (key < node->val) {
            node->left = insert(node->left, key);
        } else if (key > node->val) {
            node->right = insert(node->right, key);
        }
        return node;
    }

    TreeNode* search(TreeNode* node, int key) {
        if (!node || node->val == key) return node;
        if (key < node->val) return search(node->left, key);
        return search(node->right, key);
    }

    TreeNode* deleteNode(TreeNode* node, int key) {
        if (!node) return node;

        if (key < node->val) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->val) {
            node->right = deleteNode(node->right, key);
        } else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                size--;
                return temp;
            }
            else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                size--;
                return temp;
            }

            TreeNode* minNode = findMin(node->right);
            node->val = minNode->val;
            node->right = deleteNode(node->right, minNode->val);
        }
        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void inOrderTraversal(TreeNode* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << node->val << " ";
            inOrderTraversal(node->right);
        }
    }

    void preOrderTraversal(TreeNode* node) {
        if (node) {
            cout << node->val << " ";
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    void postOrderTraversal(TreeNode* node) {
        if (node) {
            postOrderTraversal(node->left);
            postOrderTraversal(node->right);
            cout << node->val << " ";
        }
    }

public:
    BinarySearchTree(int max_size) : root(NULL), size(0), maxSize(max_size) {}

    void insert(int key) {
        root = insert(root, key);
    }

    TreeNode* search(int key) {
        return search(root, key);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    void displayInOrder() {
        cout << "In-order: ";
        inOrderTraversal(root);
        cout << endl;
    }

    void displayPreOrder() {
        cout << "Pre-order: ";
        preOrderTraversal(root);
        cout << endl;
    }

    void displayPostOrder() {
        cout << "Post-order: ";
        postOrderTraversal(root);
        cout << endl;
    }
};

int main() {
    int numTrees;
    cout << "Enter number of trees: ";
    cin >> numTrees;

    vector<BinarySearchTree> forests;
    for (int i = 0; i < numTrees; ++i) {
        int maxSize;
        cout << "Enter max size for tree " << i + 1 << ": ";
        cin >> maxSize;
        forests.emplace_back(maxSize);
    }

    int choice, treeIndex, key;
    do {
        cout << "Menu: " << endl;
        cout << "1. Insert " << endl;
        cout << "2. Search " << endl;
        cout << "3. Delete " << endl;
        cout << "4. Display In-Order " << endl;
        cout << "5. Display Pre-Order " << endl;
        cout << "6. Display Post-Order " << endl;
        cout << "7. Exit " << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 6) {
            cout << "Select tree index (0 to " << numTrees - 1 << "): ";
            cin >> treeIndex;
            if (treeIndex < 0 || treeIndex >= numTrees) {
                cout << "Invalid tree index. Please try again." << endl;
                continue;
            }
        }

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                forests[treeIndex].insert(key);
                cout << "Inserted " << key << endl;
                break;
            case 2:
                cout << "Enter key to search: ";
                cin >> key;
                cout << (forests[treeIndex].search(key) ? "Found" : "Not found") << endl;
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                forests[treeIndex].deleteNode(key);
                cout << "Deleted node with key " << key << endl;
                break;
            case 4:
                forests[treeIndex].displayInOrder();
                break;
            case 5:
                forests[treeIndex].displayPreOrder();
                break;
            case 6:
                forests[treeIndex].displayPostOrder();
                break;
            case 7:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
