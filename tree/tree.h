#pragma once

struct Node {
    int info;
    Node* left;
    Node* right;
};
struct NodeInfo {
    int info;
    Node* node;
};

class Tree {
public:
    Tree(): root_{nullptr}, maxDeep_{0} {}
    ~Tree() {
        deleteTree();
    }
    void insert(int info);
    void print();
    void leftToRight();
    Node* findDiagonal();
    void deleteTree();

private:
    void recursiveWrite(Node* node);
    void recursiveInsert(int info, Node* node, int currentDeep);
    void recursiveDelete(Node* node);
    int maxLeafs(Node* node, NodeInfo* diagonalRoot);
    
    Node* root_;
    int maxDeep_;
    int minValue_;
    int maxValue_;
};
