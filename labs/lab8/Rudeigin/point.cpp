#include "point.h"

point::point(){

}

point::~point() {
    delete left;
    delete right;
    delete top;
    delete bottom;
}

point::point(point * _parent, state _man, std::vector<state> _box, Step _s)
{
    parent =_parent;
    top = NULL;
    bottom = NULL;
    left = NULL;
    right = NULL;
    man=_man;
    box =_box;
    s=_s;
}

state::state(){
    x=0;
    y=0;
}

state::state(unsigned char _x, unsigned char _y){
    x=_x;
    y=_y;
}

void state::set_x(int _x) {
    x = _x;
}

unsigned char state::get_x() {
    return x;
}

void state::set_y(int _y) {
    y = _y;
}

unsigned char state::get_y() {
    return y;
}
