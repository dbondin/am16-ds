#include <iostream>
#include <cstdarg>
#include <stdexcept>
#include <list>

using namespace std;

#define FIELD_ROWS 2
#define FIELD_COLS 3

enum MOVE {
	LEFT, UP, RIGHT, DOWN, MOVE_MAX
};

class field {
	unsigned char data[FIELD_ROWS][FIELD_COLS];
	field * childs [MOVE_MAX];
	field * parent;
	bool can_move(MOVE m, int & zero_c, int & zero_r, int & new_zero_c, int & new_zero_r) const;
public:
	static const field SOL1;
	static const field SOL2;
	field();
	/**
	 * There MUST be FIELD_ROWS * FIELD_COLS arguments here.
	 * Unpredicted behavior if less.
	 */
	field(int x, ...);
	void print() const;
	bool equals(const field & f) const;
	bool is_solution() const;
	bool move(MOVE m);
	field * get_child(MOVE m);
	bool already_in_tree(field * root) const;
	field * get_parent() const;
};

field * field::get_parent() const {
	return parent;
}

bool field::already_in_tree(field * root) const {
	if(root == NULL) {
		return false;
	}
	if(root->equals(*this)) {
		return true;
	}
	for(int m=0; m<MOVE_MAX; ++m) {
		field * ch = root->childs[m];
		if(ch != NULL) {
			bool x = this->already_in_tree(ch);
			if(x == true) {
				return true;
			}
		}
	}
	return false;
}

/**
 * Only UP, DOWN, LEFT and RIGHT are allowed as 'm'
 */
field * field::get_child(MOVE m) {
	return childs[m];
}

bool field::can_move(MOVE m, int & zero_c, int & zero_r, int & new_zero_c, int & new_zero_r) const {
	/* find 0 - need optimization here */
	zero_r = -1;
	zero_c = -1;
	for(int r=0; r<FIELD_ROWS; ++r) {
		for(int c=0; c<FIELD_COLS; ++c) {
			if(data[r][c] == 0) {
				zero_r = r;
				zero_c = c;
				c = FIELD_COLS;
				r = FIELD_ROWS;
			}
		}
	}
	if(zero_r == -1 || zero_c == -1) {
		return false;
	}
	switch(m) {
	case UP:
		new_zero_r = zero_r - 1;
		new_zero_c = zero_c;
		break;
	case DOWN:
		new_zero_r = zero_r + 1;
		new_zero_c = zero_c;
		break;
	case LEFT:
		new_zero_r = zero_r;
		new_zero_c = zero_c - 1;
		break;
	case RIGHT:
		new_zero_r = zero_r;
		new_zero_c = zero_c + 1;
		break;
	default:
		return false;
	}

	if(new_zero_c < 0 || new_zero_c >= FIELD_COLS || new_zero_r < 0 || new_zero_r >= FIELD_ROWS) {
		return false;
	}
	return true;
}

bool field::move(MOVE m) {
	int zero_c, zero_r, new_zero_c, new_zero_r;
	if(!can_move(m, zero_c, zero_r, new_zero_c, new_zero_r)) {
		return false;
	}
	field * result = new field();
	for(int r=0; r<FIELD_ROWS; ++r) {
		for(int c=0; c<FIELD_COLS; ++c) {
			result->data[r][c] = data[r][c];
		}
	}
	unsigned char tmp = result->data[new_zero_r][new_zero_c];
	result->data[new_zero_r][new_zero_c] = result->data[zero_r][zero_c];
	result->data[zero_r][zero_c] = tmp;

	field * root = this;
	while(root->parent != NULL) {
		root = root->parent;
	}

	if(result->already_in_tree(root)) {
		delete result;
		return false;
	}

	childs[m] = result;
	result->parent = this;

	return true;
}


const field field::SOL1 = field(1, 2, 3, 4, 5, 0);
const field field::SOL2 = field(1, 2, 3, 5, 4, 0);

field::field(int x, ...) {
	va_list ap;
	va_start(ap, x);
	data[0][0] = x;
	for(int r=0; r<FIELD_ROWS; ++r) {
		for(int c=0; c<FIELD_COLS; ++c) {
			if(r != 0 || c != 0) {
				data[r][c] = va_arg(ap, int);
			}
		}
	}
	va_end(ap);
	for(int m=0; m<MOVE_MAX; ++m) {
		childs[m] = NULL;
	}
	parent = NULL;
}

bool field::is_solution() const {
	return equals(SOL1) || equals(SOL2);
}

bool field::equals(const field & f) const {
	for(int r=0; r<FIELD_ROWS; ++r) {
		for(int c=0; c<FIELD_COLS; ++c) {
			if(data[r][c] != f.data[r][c]) {
				return false;
			}
		}
	}
	return true;
}

field::field() {
	for(int r=0; r<FIELD_ROWS; ++r) {
		for(int c=0; c<FIELD_COLS; ++c) {
			data[r][c] = 0;
		}
	}
	for(int m=0; m<MOVE_MAX; ++m) {
		childs[m] = NULL;
	}
	parent = NULL;
}

void field::print() const {
	for(int r=0; r<FIELD_ROWS; ++r) {
		for(int c=0; c<FIELD_COLS; ++c) {
			cout<<(int)data[r][c]<<" ";
		}
		cout<<endl;
	}
}

field * x(list<field *> & lst) {
	if(lst.size() == 0) {
		return NULL;
	}
	field * f = lst.front();
	lst.pop_front();
	for(int m=0; m<MOVE_MAX; ++m) {
		bool created = f->move((MOVE)m);
		if(created) {
			field * child = f->get_child((MOVE)m);
			if(child->is_solution()) {
				return child;
			}
			lst.push_back(child);
		}
	}

	return x(lst);
}

int main(int argc, char **argv) {
	field f(1, 2, 4, 5, 0, 3);
	f.print();
	cout<<f.is_solution()<<endl;
	cout<<"move "<<f.move(UP)<<endl;
	field * m = f.get_child(UP);
	if(m != NULL) {
		m->print();
	}
	field f2(1, 2, 3, 4, 5, 0);
	f2.print();
	cout<<f2.is_solution()<<endl;

	cout<<"-------------------------------"<<endl;

	list<field *> lst;
	field f3(5, 1, 3, 4, 2, 0);
	if(f3.is_solution()) {
		cout<<"Already a solution"<<endl;
	}
	lst.push_back(&f3);
	field * sol = x(lst);
	if(sol != NULL) {
		cout<<"Solution found"<<endl;
		list<field *> tmp;
		while(sol != NULL) {
			tmp.push_back(sol);
			sol = sol->get_parent();
		}
		while(tmp.size() > 0) {
			sol = tmp.back();
			tmp.pop_back();
			sol->print();
			cout<<"-----------------"<<endl;
		}
	}
	else {
		cout<<"No solution found"<<endl;
	}
}
