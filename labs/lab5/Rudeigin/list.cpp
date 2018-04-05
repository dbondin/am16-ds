#include <iostream>
#include <string>
#include "m_list.h"
#include "list.h"

list::list(){
    node = new m_list(-1,"", NULL, NULL);
}

list::list(int key, std::string data, m_list *n, m_list *p) {
    node = new m_list(key, data, n, p);
}

list::~list() {
    if(node) {
        delete node;
    }
}

void list::set(int key, std::string data) {
    if (!node) {
        node = new m_list(key, data, NULL, NULL);
        return;
    }
    m_list *buff = node;
    while (buff->next) {
        buff = buff->next;
    }
    buff->next = new m_list(key, data, NULL, buff);
}

std::string list::get(int key) {
    if (!node)
        return "";
    if (node->key == key)
        return node->data;
    m_list *buff = node;
    while (buff = buff->next)
        if (buff->key == key)
            return buff->data;
    return "";
}
