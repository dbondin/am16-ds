#ifndef M_LIST_H
#define M_LIST_H

#include <iostream>
#include <string>

struct m_list {
    int key;
    std::string data;
    struct m_list *next;
    struct m_list *prev;

    m_list(int key, std::string data, m_list *_n, m_list *_p);
    m_list();
};

#endif
