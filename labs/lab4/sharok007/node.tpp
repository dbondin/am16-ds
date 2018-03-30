#include"node.hpp"

Node::Node(){
    left=right=NULL;
}

Node::Node(Node *L, Node *R){
    left = L;
    right = R;
    quantity = L->quantity + R->quantity;
}

int Node::getQuan(){
    return quantity;
}

char Node::getSymbol(){
    return symbol;
}

Node * Node::getLeft(){
    return left;
}

Node * Node::getRight(){
    return right;
}

void Node::setQuan(int q){
    quantity = q;
}

void Node::setSymbol(char sym){
    symbol = sym;
}
