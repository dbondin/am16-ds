#pragma once

using namespace std;

template <class K, class V>
class map {
public:
	virtual ~map() {};
	virtual void add(K key, V value) = 0;
	virtual V search(K key) = 0;
};
