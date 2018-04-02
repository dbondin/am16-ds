#include "m_list.h"
#include <iostream>
#include <string>

m_list::m_list() {
    
}

m_list::m_list(int _key, std::string _data, m_list *n, m_list *p) {
    key = _key;
    data = _data;
    next = n;
    prev = p;
}
