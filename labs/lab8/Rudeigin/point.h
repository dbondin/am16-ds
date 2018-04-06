#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <vector>

enum Step
{
    NAN = 0,
    TOP = 1 ,
    BOTTOM = 2,
    LEFT = 4,
    RIGHT = 8
};

class state {
private:
    unsigned char x;
    unsigned char y;
public:
    state();
    state(unsigned char _x, unsigned char _y);
    void set_x(int _x);
    unsigned char get_x();
    void set_y(int _y);
    unsigned char get_y();
};

struct point {
    point * parent;
    point * top;
    point * bottom;
    point * left;
    point * right;
    state man;
    Step s;
    std::vector<state> box;

    point();
    point(point * _parent, state _man, std::vector<state> _box, Step _s);
    ~point();
};

#endif // POINT_H
