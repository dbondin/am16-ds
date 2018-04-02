#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

class List{
private:
    struct element{
        int key;
        std::string value;
        element *next;
    };
    element *root;
public:
    List();
    ~List();
    void add(int _key,std::string _value);
    std::string search(int _key);
};


#include "list.tpp"
#endif // LIST_HPP

