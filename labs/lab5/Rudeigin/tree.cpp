#include "tree.h"
#include <string>

tree::tree(leaf_colour _color, std::string _data, std::string _key, tree * _left, tree * _right, tree * _parent, bool _is_left)
{
    color = _color;
    if (_parent == NULL)
        color = BLACK;
    if ((_parent == NULL) || (color == RED)) {
        if (_left == NULL) {
            left = new tree(BLACK, "", "", NULL, NULL, this, true);
        }
        else {
            left = _left;
        }

        if (_right == NULL)
            right = new tree(BLACK, "", "", NULL, NULL, this, true);
        else
            right = _right;
    }
    else {
        left = _left;
        right = _right;
    }
    parent = _parent;
    key = _key;
    value = _data;
    is_left = _is_left;
}

tree::~tree() {
    if (left)
        delete left;
    if (right)
        delete right;
}

void tree::set(std::string _key, std::string _data)
{
    int buff = _key.compare(key);
    if (buff < 0) {
        if (left->is_empty()) {
            left->color = RED;
            left->key = _key;
            left->value = _data;
            left->left  = new tree(BLACK, "", "", NULL, NULL, left, true);
            left->right = new tree(BLACK, "", "", NULL, NULL, left, false);
            left->update();
        }
        else {
            left->set(_key, _data);
        }
    }
    else {
        if (right->is_empty()) {
            right->color = RED;
            right->key = _key;
            right->value = _data;
            right->left = new tree(BLACK, "", "", NULL, NULL, right, true);
            right->right = new tree(BLACK, "", "", NULL, NULL, right, false);
            right->update();
        }
        else {
            right->set(_key, _data);
        }
    }
}

std::string tree::get(std::string _key)
{
    int buff = _key.compare(key);
    if (buff < 0) {
        if (left->is_empty()) return "";
        else return left->get(_key);
    }
    else if (buff > 0) {
        if (right->is_empty()) return "";
        else return right->get(_key);
    }
    else return value;
}

void tree::update() {
    if (!parent || (parent->color == BLACK)) return;
    tree *granny = parent->parent;
    if ((granny->left->color == RED) && (granny->right->color == RED)) {
        granny->left->color = BLACK;
        granny->right->color = BLACK;
        if (granny->parent) granny->color = RED;
        else return;
        granny->update();
    }
    else {
        if (parent->is_left) {
            if (is_left) {
                granny->left = parent->right;
                granny->left->parent = granny;
                granny->left->is_left = true;

                if (granny->parent)
                {
                    if (granny->is_left)
                        granny->parent->left = parent;
                    else
                    {
                        granny->parent->right = parent;
                        parent->is_left = false;
                    }
                }

                parent->parent = granny->parent;
                parent->right = granny;
                granny->is_left = false;
                granny->parent = parent;
                parent->color = BLACK;

            }
            else {
                parent->right = left;
                parent->right->is_left = false;
                parent->right->parent = parent;
                parent->parent = this;
                left = parent;
                parent = granny;
                granny->left = this;
                is_left = true;
                left->update();
            }
        }
        else {
            if (!is_left) {
                granny->right = parent->left;
                granny->right->parent = granny;
                granny->right->is_left = false;
                if (granny->parent) {
                    if (!granny->is_left)
                        granny->parent->right = parent;
                    else {
                        granny->parent->left = parent;
                        parent->is_left = true;
                    }
                }

                parent->parent = granny->parent;
                parent->left = granny;
                granny->is_left = true;
                granny->parent = parent;
                parent->color = BLACK;

            }
            else {
                parent->left = right;
                parent->left->is_left = true;
                parent->left->parent = parent;
                parent->parent = this;
                right = parent;
                parent = granny;
                granny->right = this;
                is_left = false;
                right->update();
            }
        }
    }
}

bool tree::is_empty() {
    if ((right) || (left)) return false;
    else return true;
}

void tree::search_and_print(std::string k)
{
    int buff = k.compare(key);
    if (buff > 0) {
        if (right->is_empty()) return;
        else return right->search_and_print(k);
    }
    else {
        int buff = key.find(k);
        if (buff == 0) {
            if (!left->is_empty()) {
                left->search_and_print(k);
            }
            std::cout << value.data() << std::endl;
            if (!right->is_empty()) {
                right->search_and_print(k);
            }
            return;
        }
        else {
            if (left->is_empty()) return;
            else                  return left->search_and_print(k);
        }
    }
}
