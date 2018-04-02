#include "red_black_tree.h"

red_black_tree::red_black_tree(colour _color, string _data, string _key, red_black_tree * _left_child, red_black_tree * _right_child, red_black_tree * _parent, bool _lchild)
{
    color = _color;
    if (_parent == NULL)
        color = BLACK;
    if ((_parent == NULL) || (color == RED)) {
        if (_left_child == NULL) {
            left_child = new red_black_tree(BLACK, "", "", NULL, NULL, this, true);
        }
        else {
            left_child = _left_child;
        }

        if (_right_child == NULL)
            right_child = new red_black_tree(BLACK, "", "", NULL, NULL, this, true);
        else
            right_child = _right_child;
    }
    else {
        left_child = _left_child;
        right_child = _right_child;
    }
    parent = _parent;
    key = _key;
    data = _data;
    lchild = _lchild;
}

red_black_tree::~red_black_tree() {
    if (left_child)
        delete left_child;
    if (right_child)
        delete right_child;
}

void red_black_tree::add(string _key, string _data)
{
    int lik = _key.compare(key);
    if (lik < 0) {
        if (left_child->is_nill()) {
            left_child->color = RED;
            left_child->key = _key;
            left_child->data = _data;
            left_child->left_child  = new red_black_tree(BLACK, "", "", NULL, NULL, left_child, true);
            left_child->right_child = new red_black_tree(BLACK, "", "", NULL, NULL, left_child, false);
            left_child->mga();
        }
        else {
            left_child->add(_key, _data);
        }
    }
    else
        if (right_child->is_nill()) {
            right_child->color = RED;
            right_child->key = _key;
            right_child->data = _data;
            right_child->left_child  = new red_black_tree(BLACK, "", "", NULL, NULL, right_child, true);
            right_child->right_child = new red_black_tree(BLACK, "", "", NULL, NULL, right_child, false);
            right_child->mga();
        }
        else {
            right_child->add(_key, _data);
        }
}

string red_black_tree::get(string _key)
{
    int lik = _key.compare(key);
    if (lik < 0) {
        if (left_child->is_nill()) return "";
        else return left_child->get(_key);
    }
    else if (lik > 0) {
        if (right_child->is_nill()) return "";
        else return right_child->get(_key);
    }
    else return data;
}

void red_black_tree::mga()//make great again
{
    if (!parent || (parent->color == BLACK)) return;
    red_black_tree *grand_father = parent->parent;
    if ((grand_father->left_child->color == RED) && (grand_father->right_child->color == RED)) {
        grand_father->left_child->color = BLACK;
        grand_father->right_child->color = BLACK;
        if (grand_father->parent) grand_father->color = RED;
        else                      return;
        grand_father->mga();
    }
    else {
        if (parent->lchild) {
            if (lchild) {
                grand_father->left_child = parent->right_child;
                grand_father->left_child->parent = grand_father;
                grand_father->left_child->lchild = true;

                if (grand_father->parent)
                {
                    if (grand_father->lchild)
                        grand_father->parent->left_child = parent;
                    else
                    {
                        grand_father->parent->right_child = parent;
                        parent->lchild = false;
                    }
                }

                parent->parent = grand_father->parent;
                parent->right_child = grand_father;
                grand_father->lchild = false;
                grand_father->parent = parent;
                parent->color = BLACK;

            }
            else {
                parent->right_child = left_child;
                parent->right_child->lchild = false;
                parent->right_child->parent = parent;
                parent->parent = this;
                left_child = parent;
                parent = grand_father;
                grand_father->left_child = this;
                lchild = true;
                left_child->mga();
            }
        }
        else {
            if (!lchild) {
                grand_father->right_child = parent->left_child;
                grand_father->right_child->parent = grand_father;
                grand_father->right_child->lchild = false;
                if (grand_father->parent) {
                    if (!grand_father->lchild)
                        grand_father->parent->right_child = parent;
                    else {
                        grand_father->parent->left_child = parent;
                        parent->lchild = true;
                    }
                }

                parent->parent = grand_father->parent;
                parent->left_child = grand_father;
                grand_father->lchild = true;
                grand_father->parent = parent;
                parent->color = BLACK;

            }
            else {
                parent->left_child = right_child;
                parent->left_child->lchild = true;
                parent->left_child->parent = parent;
                parent->parent = this;
                right_child = parent;
                parent = grand_father;
                grand_father->right_child = this;
                lchild = false;
                right_child->mga();
            }
        }
    }
}

bool red_black_tree::is_nill()
{
    if ((right_child != NULL) || (left_child != NULL)) return false;
    else return true;
}

void red_black_tree::search(string k)
{
    int lik = k.compare(key);
    if (lik > 0) {
        if (right_child->is_nill()) return;
        else return right_child->search(k);
    }
    else {
        int buff = key.find(k);
        if (buff == 0) {
            if (!left_child->is_nill()) {
                left_child->search(k);
            }
            cout << data.data() << endl;
            if (!right_child->is_nill()) {
                right_child->search(k);
            }
            return;
        }
        else {
            if (left_child->is_nill()) return;
            else                 return left_child->search(k);
        }
    }
}

tree_map::tree_map()
{
    root = NULL;
}

tree_map::~tree_map()
{
    delete root;
}

void tree_map::add(string key, string data)
{
    if (!root)
        root = new red_black_tree(BLACK, "", "", NULL, NULL, NULL, true);
    else
        root->add(key, data);
}

string tree_map::get(string key) {
    if (!root)
        return "";
    else
        return root->get(key);
}

void tree_map::search(string key)
{
    if (!root)
        return;
    root->search(key);
}
