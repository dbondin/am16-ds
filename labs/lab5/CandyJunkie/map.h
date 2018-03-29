#pragma once

template <class K, class V>
class map {
public:
	virtual ~map () {};
	virtual void insert (K key, V value) = 0;
	virtual V search (K key) = 0;
};