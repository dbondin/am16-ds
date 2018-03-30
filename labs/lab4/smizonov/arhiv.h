#include <iostream>
#include <fstream>
#include <clocale>
#include <string>
#include <cstdio>


class tree
{
    unsigned int weigh;
    tree *left, *right;
    unsigned char ch;
public:
tree(unsigned int weigh1, unsigned char ch1=' ',tree* lef=NULL,tree* righ=NULL)
    {
        weigh=weigh1;
        ch=ch1;
        left=lef;
        right=righ;
    }
tree()
    {
        weigh=0;
        left=NULL;
        right=NULL;
    }

unsigned char  get_ch(){
        return ch;
    }
unsigned int get_weigh()
  {
      return weigh;
  }
tree* get_left(){
      return left;
  }
tree* get_right(){
      return right;
  }

void put_left(tree *lef)
  {
      left=lef;
  }
void put_right(tree *rig)
  {
      right=rig;
  }
};

