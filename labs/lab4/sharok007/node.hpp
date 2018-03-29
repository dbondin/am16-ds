#ifndef NODE_HPP
#define NODE_HPP
class Node{
private:
    int quantity;
    char symbol;
    Node *left;
    Node *right;
public:
    Node();
    Node(Node *L,Node *R);
    void setSymbol(char sym);
    void setQuan(int q);
    char getSymbol();
    int getQuan();
    Node *getLeft();
    Node *getRight();
};
#include "node.tpp"
#endif // NODE_HPP

