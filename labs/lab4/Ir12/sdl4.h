#include <iostream>

using namespace std;

class Tree {
public:
	Tree (int newfrequency = 0, char newsymbol = 0, Tree * newleftleaf = NULL, Tree * newrightleaf = NULL);
	~Tree ();
	Tree * mergeleftbranch (Tree * rightbranch);
	int leaf ();
	int getfrequency ();
	char getsymbol ();
	Tree * getleftleaf ();
	Tree * getrighleaf ();
	int frequency;
	char symbol;
	Tree * leftleaf;
	Tree * righleaf;
};


Tree::Tree (int newfrequency, char newsymbol, Tree * newleftleaf, Tree * newrightleaf)
{
	frequency = newfrequency;
	symbol = newsymbol;
	leftleaf = newleftleaf;
	righleaf = newrightleaf;
}

Tree::~Tree ()
{
	if (leftleaf) 
	{
		delete leftleaf;
	}
	if (righleaf) 
	{
		delete righleaf;
	}
}

Tree * Tree::mergeleftbranch (Tree * rightbranch) {
	Tree *newroot = new Tree (frequency + rightbranch->frequency, 0, this, rightbranch);
	return newroot;
}

int Tree::leaf ()
{
	return (righleaf || leftleaf) ? 0 : 1;
}

int Tree::getfrequency ()
{
	return frequency;
}

char Tree::getsymbol ()
{
	return symbol;
}

Tree * Tree::getleftleaf ()
{
 return leftleaf;
}

Tree * Tree::getrighleaf ()
{
	return righleaf;
} 
