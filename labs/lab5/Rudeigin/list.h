#ifndef LIST_H
#define LIST_H

#include "m_list.h"

class list {
    private:
        m_list l;
        m_list *node;
    public:
        list();
        list(int key, std::string data, m_list *n, m_list *p);
        ~list();
        void set(int key, std::string data);
        std::string get(int key);
};

#endif
