#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>

template<class K, class V>

class Map{
public:
    virtual ~Map(){};
    virtual void add(K key,V value) = 0;
    virtual V search(K key) = 0;
};

#endif // MAP_HPP

