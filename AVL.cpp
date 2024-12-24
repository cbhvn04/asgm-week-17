#include <iostream>
#include <algorithm>
using namespace std;

// Dinh nghia cau truc mot nut trong cay AVL
struct AVLNode {
    int value;                // Gia tri luu trong nut
    int height;               // Chieu cao cua nut
    AVLNode* leftChild;       // Con tro den nut con ben trai
    AVLNode* rightChild;      // Con tro den nut con ben phai

    AVLNode(int val) : value(val), height(1), leftChild(nullptr), rightChild(nullptr) {}
};

// Ham tinh chieu cao cua mot nut
int calcHeight(AVLNode* node) {
    return node ? node->height : 0;
}

// Ham tinh he so can bang cua mot nut
int calcBalanceFactor(AVLNode* node) {
    return node ? calcHeight(node->leftChild) - calcHeight(node->rightChild) : 0;
}

// Thuc hien xoay phai
AVLNode* performRightRotation(AVLNode* unbalancedNode) {
    cout << "Thuc hien xoay phai tai nut " << unbalancedNode->value << endl;
    AVLNode* newRoot = unbalancedNode->leftChild;
    AVLNode* tempSubTree = newRoot->rightChild;

    newRoot->rightChild = unbalancedNode;
    unbalancedNode->leftChild = tempSubTree;

    unbalancedNode->height = 1 + max(calcHeight(unbalancedNode->leftChild), calcHeight(unbalancedNode->rightChild));
    newRoot->height = 1 + max(calcHeight(newRoot->leftChild), calcHeight(newRoot->rightChild));

    return newRoot;
}

// Thuc hien xoay trai
AVLNode* performLeftRotation(AVLNode* unbalancedNode) {
    cout << "Thuc hien xoay trai tai nut " << unbalancedNode->value << endl;
    AVLNode* newRoot = unbalancedNode->rightChild;
    AVLNode* tempSubTree = newRoot->leftChild;

    newRoot->leftChild = unbalancedNode;
    unbalancedNode->rightChild = tempSubTree;

    unbalancedNode->height = 1 + max(calcHeight(unbalancedNode->leftChild), calcHeight(unbalancedNode->rightChild));
    newRoot->height = 1 + max(calcHeight(newRoot->leftChild), calcHeight(newRoot->rightChild));

    return newRoot;
}

// Ham chen mot nut vao cay AVL
AVLNode* addNodeToAVLTree(AVLNode* root, int value) {
    if (!root) {
        return new AVLNode(value);
    }

    if (value < root->value) {
        root->leftChild = addNodeToAVLTree(root->leftChild, value);
    } else if (value > root->value) {
        root->rightChild = addNodeToAVLTree(root->rightChild, value);
    } else {
        return root;
    }

    root->height = 1 + max(calcHeight(root->leftChild), calcHeight(root->rightChild));
    int balance = calcBalanceFactor(root);

    if (balance > 1 && value < root->leftChild->value) {
        return performRightRotation(root);
    }

    if (balance < -1 && value > root->rightChild->value) {
        return performLeftRotation(root);
    }

    if (balance > 1 && value > root->leftChild->value) {
        root->leftChild = performLeftRotation(root->leftChild);
        return performRightRotation(root);
    }

    if (balance < -1 && value < root->rightChild->value) {
        root->rightChild = performRightRotation(root->rightChild);
        return performLeftRotation(root);
    }

    return root;
}

// Ham in cau truc cay
void printTreeStructure(AVLNode* node, int spacing = 0) {
    if (!node) {
        return;
    }

    spacing += 10;
    printTreeStructure(node->rightChild, spacing);

    cout << endl;
    for (int i = 10; i < spacing; i++) {
        cout << " ";
    }
    cout << node->value << endl;

    printTreeStructure(node->leftChild, spacing);
}

// Chuong trinh chinh
int main() {
    AVLNode* root = nullptr;
    int elements[] = {10, 20, 30, 40, 50, 25};
    int size = sizeof(elements) / sizeof(elements[0]);

    cout << "Them cac phan tu vao cay AVL:" << endl;
    for (int i = 0; i < size; i++) {
        root = addNodeToAVLTree(root, elements[i]);
        cout << "\nSau khi them " << elements[i] << ":" << endl;
        printTreeStructure(root);
    }

    return 0;
}
