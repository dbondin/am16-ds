#ifndef TREE_MAP
#define TREE_MAP

#include <iostream>
#include <string>

using namespace std;

template <class H>
class tree_node {
    public:
        tree_node();
        tree_node(tree_node *left, tree_node *right, tree_node *parent, string key, H znach, char color, bool left_child);
        ~tree_node();
        void add(string key, H znach);
        H get(string key);
        virtual void printCoincidental(string keyPart);
        void correct();
        bool leaf();
        virtual H no_result();
    private:
        string key;
        H znach;
        char color;
        tree_node *left;
        tree_node *right;
        tree_node *parent;
        bool left_child;
};

template <class H>
tree_node<H>::tree_node()
{
    color = 'b';
    znach = no_result();
    key = "";
    left  = new tree_node(NULL, NULL, this, "", no_result(), 'b', true);
    right = new tree_node(NULL, NULL, this, "", no_result(), 'b', false);;
    parent = NULL;
    left_child = true;
}

template <class H>
tree_node<H>::tree_node(tree_node *_left, tree_node *_right, tree_node *_parent, string _key, H _znach, char _color, bool left_reb)
{
    color = _color;
    if (_parent == NULL)
        color = 'b';


    if ((_parent == NULL) || (color == 'r'))
    {
        if (_left == NULL)
            left = new tree_node(NULL, NULL, this, "", no_result(), 'b', true);
        else
            left = _left;

        if (_right == NULL)
            right = new tree_node(NULL, NULL, this, "", no_result(), 'b', false);
        else
            right = _right;
    }
    else
    {
        left = _left;
        right = _right;
    }

    parent = _parent;
    key = _key;
    znach = _znach;
    left_child = left_reb;
}

template <class H>
tree_node<H>::~tree_node()
{
    if (left)
        delete left;
    if (right)
        delete right;
}

template <class H>
void tree_node<H>::add(string _key, H _znach)
{
    int comp = _key.compare(key);
    if (comp < 0)
        if (left->leaf())
        {
            left->color = 'r';
            left->key = _key;
            left->znach = _znach;
            left->left  = new tree_node(NULL, NULL, left, "", no_result(), 'b', true);
            left->right = new tree_node(NULL, NULL, left, "", no_result(), 'b', false);
            left->correct();
        }
        else
        {
            left->add(_key, _znach);
        }
    else
        if (right->leaf())
        {
            right->color = 'r';
            right->key = _key;
            right->znach = _znach;
            right->left  = new tree_node(NULL, NULL, right, "", no_result(), 'b', true);
            right->right = new tree_node(NULL, NULL, right, "", no_result(), 'b', false);
            right->correct();
        }
        else
        {
            right->add(_key, _znach);
        }
}

template <class H>
H tree_node<H>::get(string _key)
{
    int comp = _key.compare(key);
    if (comp < 0)
    {
        if (left->leaf())
            return no_result();
        else
            return left->get(_key);
    }
    else if (comp > 0)
    {
        if (right->leaf())
            return no_result();
        else
            return right->get(_key);
    } else
        return znach;
}

template <class H>
void tree_node<H>::correct()
{
    if (!parent || (parent->color == 'b'))
       return;

    tree_node *new_parent = parent->parent;
    if ((new_parent->left->color == 'r') && (new_parent->right->color == 'r'))
    {
        new_parent->left->color = 'b';
        new_parent->right->color = 'b';
        if (new_parent->parent)
            new_parent->color = 'r';
        else
            return;
        new_parent->correct();
    } else
    {
        if (parent->left_child)
        {
            if (left_child)
            {
                new_parent->left = parent->right;
                new_parent->left->parent = new_parent;
                new_parent->left->left_child = true;

                if (new_parent->parent)
                {
                    if (new_parent->left_child)
                        new_parent->parent->left = parent;
                    else
                    {
                        new_parent->parent->right = parent;
                        parent->left_child = false;
                    }
                }

                parent->parent = new_parent->parent;
                parent->right = new_parent;
                new_parent->left_child = false;
                new_parent->parent = parent;
                parent->color = 'b';

            } else
            {
                parent->right = left;
                parent->right->left_child = false;
                parent->right->parent = parent;

                parent->parent = this;
                left = parent;

                parent = new_parent;
                new_parent->left = this;
                left_child = true;

                left->correct();
            }
        } else
        {
            if (!left_child)
            {
                new_parent->right = parent->left;
                new_parent->right->parent = new_parent;
                new_parent->right->left_child = false;

                if (new_parent->parent)
                {
                    if (!new_parent->left_child)
                       new_parent->parent->right = parent;
                    else
                    {
                        new_parent->parent->left = parent;
                        parent->left_child = true;
                    }
                }

               parent->parent = new_parent->parent;
                parent->left = new_parent;
                new_parent->left_child = true;
                new_parent->parent = parent;
                parent->color = 'b';

            } else
            {
                parent->left = right;
                parent->left->left_child = true;
                parent->left->parent = parent;

                parent->parent = this;
                right = parent;

                parent = new_parent;
                new_parent->right = this;
                left_child = false;

                right->correct();
            }
        }
    }
}

template <class H>
bool tree_node<H>::leaf()
{
    if (left || right)
        return false;
    else
        return true;
}

template <class H>
void tree_node<H>::printCoincidental(string keyPart)
{
    int comp = keyPart.compare(key);
    if (comp > 0)
    {
        if (right->leaf())
            return;
        else
            return right->printCoincidental(keyPart);
    }
    else
    {
        int found = key.find(keyPart);
        if (found == 0)
        {
            if (!left->leaf())
                left->printCoincidental(keyPart);

            cout << znach.data() << endl;

            if (!right->leaf())
                right->printCoincidental(keyPart);

            return;
        }
        else
        {
            if (left->leaf())
                return;
            else
                return left->printCoincidental(keyPart);
        }
    }
}

template <class H>
class tree_map {
    public:
        tree_map();
        ~tree_map();
        void add(string key, H znach);
        H get(string key);
        virtual void printCoincidental(string keyPart);
        virtual H no_result();
    private:
        tree_node<H> *root;
};

template <class H>
tree_map<H>::tree_map()
{
    root = NULL;
}

template <class H>
tree_map<H>::~tree_map()
{
    delete root;
}

template <class H>
void tree_map<H>::add(string key, H znach)
{
    if (!root)
        root = new tree_node<H>(NULL, NULL, NULL, key, znach, 'b', true);
    else
        root->add(key, znach);
}

template <class H>
H tree_map<H>::get(string key)
{
    if (!root)
        return no_result();
    else
        return root->get(key);
}

template <class H>
void tree_map<H>::printCoincidental(string keyPart)
{
    if (!root)
        return;
    root->printCoincidental(keyPart);
}

template <class H>
H tree_node<H>::no_result()
{
    return "";
}

template <class H>
H tree_map<H>::no_result()
{
return "";
}
#endif 
