#include "tree/tree.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>

//--------------------------------------------insert---------------------------------------
void Tree::insert(int info) {
    if (info > maxValue_)
        maxValue_ = info;
    if (info < minValue_)
        minValue_ = info;

    if (root_ == nullptr) {
        root_ = new Node{ info };
    }
    else {
        recursiveInsert(info, root_, 1);
    }
}
void Tree::recursiveInsert(int info, Node* node, int currentDeep) {
    if (info < node->info) {
        if (node->left == nullptr) {
            node->left = new Node{ info };
            if (currentDeep > maxDeep_)
                maxDeep_ = currentDeep;
        }
        else {
            recursiveInsert(info, node->left, currentDeep + 1);
        }
    }
    else if (info > node->info) {
        if (node->right == nullptr) {
            node->right = new Node{ info };
            if (currentDeep > maxDeep_)
                maxDeep_ = currentDeep;
        }
        else {
            recursiveInsert(info, node->right, currentDeep + 1);
        }
    }
}
//--------------------------------------------leftToRight---------------------------------------
void Tree::leftToRight() {
    if (root_ == nullptr)
        return;
    recursiveWrite(root_);
}
void Tree::recursiveWrite(Node* node) {
    if (node->left != nullptr) {
        recursiveWrite(node->left);
    }
    if (node->right != nullptr) {
        recursiveWrite(node->right);
    }
    std::cout << node->info << " ";
}
//--------------------------------------------diagonal---------------------------------------
Node* Tree::findDiagonal() {
    NodeInfo diagonal{ -1 };
    maxLeafs(root_, &diagonal);
    return diagonal.node;
}
int Tree::maxLeafs(Node* node, NodeInfo* diagonalRoot) {
    if (node == nullptr)
        return 0;
    int left = maxLeafs(node->left, diagonalRoot);
    int right = maxLeafs(node->right, diagonalRoot);
    if (diagonalRoot->info < (left + right)) {
        diagonalRoot->info = left + right;
        diagonalRoot->node = node;
    }
    return std::max(left, right) + 1;
}
//--------------------------------------------print---------------------------------------
void printChar(char ch, int n) {
    for (int i = 0; i < n; ++i) 
        std::cout << ch;
}
void printBoundedInt(int in, int bound) {
    std::string strIn = std::to_string(in);
    printChar(' ', bound - strIn.size());
    std::cout << strIn;
}
void Tree::print() {
    if (root_ == nullptr)
        return;

    int infoWidth = std::max(std::to_string(minValue_).length(), std::to_string(maxValue_).length());
    int spaceWidth = 1;
    for (int i = 0; i < maxDeep_; ++i) { 
        spaceWidth *= 2;
    }
    --spaceWidth; //spaceWidth = 2^maxDeep - 1
    spaceWidth *= infoWidth;
    
    printChar(' ', spaceWidth);
    printBoundedInt(root_->info, infoWidth);
    printChar(' ', spaceWidth);
    std::cout << '\n';
    
    std::queue<Node*> nodes;
    nodes.push(root_);
    while (spaceWidth) {
        int elements = nodes.size();
        printChar(' ', (spaceWidth - infoWidth) / 2);
        while (elements) {
            Node* currentNode = nodes.front();
            nodes.pop();
            if (currentNode) { // print left and right
                Node* left = currentNode->left;
                nodes.push(left);
                if (left) {
                    printBoundedInt(left->info, infoWidth);
                }
                else {
                    printChar(' ', infoWidth);
                }
                printChar(' ', spaceWidth);

                Node* right = currentNode->right;
                nodes.push(right);
                if (right) {
                    printBoundedInt(right->info, infoWidth);
                }
                else {
                    printChar(' ', infoWidth);
                }
                printChar(' ', spaceWidth);
            }
            else {
                nodes.push(nullptr);
                nodes.push(nullptr);
                printChar(' ', (infoWidth + spaceWidth) * 2);
            }
            --elements;
        }
        std::cout << '\n';
        spaceWidth = (spaceWidth - infoWidth) / 2;
    }
}
//--------------------------------------------delete---------------------------------------
void Tree::deleteTree() {
    if (root_ == nullptr)
        return;
    recursiveDelete(root_);
    root_ = nullptr;
    minValue_ = 0;
    maxValue_ = 0;
    maxDeep_ = 0;
}
void Tree::recursiveDelete(Node* node) {
    if (node->left)             
        recursiveDelete(node->left);
    if (node->right)
        recursiveDelete(node->right);
    delete node;
}
