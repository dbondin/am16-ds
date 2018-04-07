#include <iostream>
#include "point.h"
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

bool compare(vector<state> a, vector<state> b){
    for(unsigned int i = 0; i < a.size(); ++i) {
        if((a[i].get_x() != b[i].get_x()) || (a[i].get_y() != b[i].get_y())) {
            return false;
        }
    }
    return true;
}

void init_tree(point *tree, int height, int widht, ifstream & in, unsigned char **table) {
    unsigned char ctemp;
    for (int i=0; i < height; ++i) {
        for(int j=0; j < widht; ++j) {
            ctemp=in.get();
            if(ctemp == '@') {
                tree->man.set_x(j);
                tree->man.set_y(i);;
                ctemp=' ';
            }
            else if(ctemp == '%') {
                state stemp(i,j);
                tree->box.push_back(stemp);
                ctemp=' ';
            }
            table[j][i]=ctemp;
        }
        in.get();
    }
}

void print(point * p, int height, int widht, unsigned char ** table) {
    cout<<endl;
    for (int j = 0; j < height; ++j) {
        for(int i = 0; i < widht; ++i) {
            if((p->man.get_x() == i) && (p->man.get_y() == j)) {
                cout.put(1);
            }
            else {
            bool flag=true;
            for(unsigned int k = 0; k < p->box.size(); ++k) {
                if((p->box[k].get_x() == i) && (p->box[k].get_y() == j)){
                    flag=false;
                    cout<<'%';
                    break;
                }
            }
            if(flag) cout << table[i][j];
            }
        }
        cout << endl;
    }
}

void move(point* p, Step st, unsigned char **table) {
    char x = 0,y = 0;
    switch(st) {
    case TOP:
        x = -1;
        break;
    case BOTTOM:
        x = 1;
        break;
    case LEFT:
        y = -1;
        break;
    case RIGHT:
        y = 1;
        break;
    default:
        break;
    }
    bool box_move = false;
    unsigned char box_id=0;
    if(table[p->man.get_y()+y][p->man.get_x()+x] != '#') {
        for(unsigned int i = 0;i < p->box.size(); ++i) {
            if((p->man.get_x()+x == p->box[i].get_x()) && (p->man.get_y()+y == p->box[i].get_y())) {
            box_id = i;
            if(table[p->box[i].get_x()+x][p->box[i].get_y()+y] != '#') {
                for(unsigned int j = 0; j < p->box.size(); ++j) {
                    if((p->box[i].get_x()+x == p->box[j].get_x()) && (p->box[i].get_y()+y == p->box[j].get_y())) {
                        return;
                    }
                }
                box_move = true;
            }
            else {
                return;
            }
            break;
            }
        }
    }
    else {
        return;
    }

    point* child = NULL;
    child = new point(p, p->man, p->box, st);

    child->man.set_x(child->man.get_x()+x);
    child->man.set_y(child->man.get_y()+y);

    if(box_move) {
    child->box[box_id].set_x(child->box[box_id].get_x()+x);
    child->box[box_id].set_y(child->box[box_id].get_y()+y);
    }
    switch(st) {
    case TOP:
        p->top = child;
        break;
    case BOTTOM:
        p->bottom = child;
        break;
    case LEFT:
        p->left = child;
        break;
    case RIGHT:
        p->right = child;
        break;
    default:
        break;
    }
}

point* answer(vector <point *> p, unsigned char **table){
    cout << "0";

    for(unsigned int i=0; i < p.size(); ++i) {
        bool finished = false;
        if(!p[i]) {
            continue;
        }
        for(unsigned int j=0; j < p[i]->box.size(); ++j) {
            if(table[p[i]->box[j].get_x()][p[i]->box[j].get_y()] != '+') {
                finished=false;
                break;
            }
            finished=true;
        }
        if(finished)
            return p[i];
    }
    vector<point *> children;
    for(unsigned int i=0; i < p.size(); ++i) {
        if(p[i]) {
            if(p[i]->parent && compare(p[i]->box,p[i]->parent->box)) {
                switch(p[i]->s) {
                case TOP: {
                    move(p[i],TOP, table);
                    move(p[i],LEFT, table);
                    move(p[i],RIGHT, table);
                    children.push_back(p[i]->top);
                    children.push_back(p[i]->left);
                    children.push_back(p[i]->right);
                    break;
                }
                case BOTTOM: {
                    move(p[i],BOTTOM, table);
                    move(p[i],LEFT, table);
                    move(p[i],RIGHT, table);
                    children.push_back(p[i]->bottom);
                    children.push_back(p[i]->left);
                    children.push_back(p[i]->right);
                    break;
                }
                case LEFT: {
                    move(p[i],TOP, table);
                    move(p[i],BOTTOM, table);
                    move(p[i],LEFT, table);
                    children.push_back(p[i]->top);
                    children.push_back(p[i]->bottom);
                    children.push_back(p[i]->left);
                    break;
                }
                case RIGHT: {
                    move(p[i],TOP, table);
                    move(p[i],BOTTOM, table);
                    move(p[i],RIGHT, table);
                    children.push_back(p[i]->top);
                    children.push_back(p[i]->bottom);
                    children.push_back(p[i]->right);
                    break;
                }
                }
            }
            else {
                move(p[i],TOP, table);
                move(p[i],BOTTOM, table);
                move(p[i],LEFT, table);
                move(p[i],RIGHT, table);
                children.push_back(p[i]->top);
                children.push_back(p[i]->bottom);
                children.push_back(p[i]->left);
                children.push_back(p[i]->right);
            }
        }
    }
    return answer(children, table);
}

int main() {
    ifstream in("/home/roller-alla/lab8/game.txt");
    int height = 0, widht = 0;
    in >> height >> widht;
    cout << height << widht;
    cout << "go **";
    unsigned char **table = new unsigned char *[height];
    for(int i = 0; i < height; ++i) {
        table[i] = new unsigned char[widht];
    }
    cout << "go new tree";
    point *  tree = new point();
    init_tree(tree, height, widht, in, table);
    vector <point *> p;
    p.push_back(tree);
    point * result = answer(p, table);
    stack<point *> all_steps;
    while(result) {
        all_steps.push(result);
        result = result->parent;
    }
    while(all_steps.size()) {
        print(all_steps.top(), height, widht, table);
        all_steps.pop();
    }


    delete tree;
    delete table;
    in.close();
    return 0;
}

