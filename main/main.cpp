#include <iostream>
#include <fstream>
#include "tree/tree.h"


void setTree(Tree* T, std::ifstream& in) {
    int n;
    in >> n;
    int info;
    for (int i = 0; i < n; ++i) {
        in >> info;
        T->insert(info);
    }
}
void testIn(std::ifstream& in) {
    int n;
    in >> n;
    int info;
    for (int i = 0; i < n; ++i) {
        in >> info;
        std::cout << info << " ";
    }
    std::cout << '\n';
}
int main()
{
    std::ifstream in;
    in.open("data/graph.txt");
    Tree T;
    for (int i = 0; i < 4; ++i) {
        setTree(&T, in);
        T.leftToRight();
        std::cout << "max diagonal is in: " << T.findDiagonal()->info << "\n";
        T.print();
        T.deleteTree();
        T.leftToRight();
    }
}
