#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <time.h>

#define HEIGHT 6
#define WIDTH 8

using namespace std;

unsigned char map[HEIGHT][WIDTH];

enum DIRECTION
{
    NONE=0,
    UP=1,
    DOWN=2,
    LEFT=4,
    RIGHT=8
};


struct object
{
    object();
    object(unsigned char _x, unsigned char _y);
    unsigned char x;
    unsigned char y;
};

object::object()
{
    x=0;
    y=0;
}

object::object(unsigned char _x, unsigned char _y)
{
    x=_x;
    y=_y;
}

struct Node
{
    Node();
    ~Node();
    Node(Node* _parent, object _hero, vector<object> _boxes, DIRECTION _step);
    Node *parent;
    Node* up;
    Node* down;
    Node* left;
    Node* right;
    object hero;
    DIRECTION step;
    vector<object> boxes;
};

Node::Node()
{
    parent=NULL;
    up=NULL;
    down=NULL;
    left=NULL;
    right=NULL;
    step=NONE;
}

Node::~Node(){
    delete up;
    delete down;
    delete left;
    delete right;
}

Node::Node(Node* _parent, object _hero, vector<object> _boxes, DIRECTION _step)
{
    parent=_parent;
    up=NULL;
    down=NULL;
    left=NULL;
    right=NULL;
    hero=_hero;
    boxes=_boxes;
    step=_step;
}

bool compare(vector<object> a, vector<object> b)
{
    for(int i=0; i<a.size(); i++)
    {
	if((a[i].x!=b[i].x) || (a[i].y!=b[i].y))
	{
	    return false;
	}
    }
    return true;
}

void load_map(ifstream & in, Node *root)
{
    for (int j=0; j < HEIGHT; j++)
    {
	for(int i=0; i < WIDTH; i++)
	{
	    unsigned char buf=in.get();
	    if(buf=='@')
	    {
		root->hero.x=i;
		root->hero.y=j;
		buf=' ';
	    }
	    else if(buf=='%')
	    {
		object temp(i,j);
		root->boxes.push_back(temp);
		buf=' ';
	    }
	    map[i][j]=buf;
	}
	in.get();
    }

}

void print(Node* node)
{
    cout<<endl;
    for (int j=0; j <HEIGHT; j++)
    {
	for(int i=0; i < WIDTH; i++)
	{
	    if(node->hero.x==i&&node->hero.y==j)
	    {
		cout.put(1);
	    }
	    else
	    {
		bool flag=true;
		for(int k=0; k<node->boxes.size(); k++)
		{
		    if(node->boxes[k].x==i&&node->boxes[k].y==j)
		    {
			flag=false;
			cout<<'%';
			break;
		    }
		}
		if(flag)
		{
		    cout<<map[i][j];
		}
	    }
	}
	cout<<endl;
    }
}

void move(Node* node, DIRECTION direction)
{

    char x=0,y=0;
    switch(direction)
    {
    case UP:
	x=-1;
	break;
    case DOWN:
	x=1;
	break;
    case LEFT:
	y=-1;
	break;
    case RIGHT:
	y=1;
	break;
    }
    bool box_move=false;
    unsigned char box_ind=0;
    if(map[node->hero.x+x][node->hero.y+y]!='#')
    {
	for(int i=0;i<node->boxes.size();i++)
	{
	    if(node->hero.x+x==node->boxes[i].x&&node->hero.y+y==node->boxes[i].y)
	    {
		box_ind=i;
		if(map[node->boxes[i].x+x][node->boxes[i].y+y]!='#')
		{
		    for(int j=0;j<node->boxes.size();j++)
		    {
			if(node->boxes[i].x+x==node->boxes[j].x&&node->boxes[i].y+y==node->boxes[j].y)
			{
			    return;
			}
		    }
		    box_move=true;
		}
		else
		{
		    return;
		}
		break;
	    }
	}
    }
    else
    {
	return;
    }

    Node* child=NULL;
    child = new Node(node, node->hero, node->boxes, direction);

    child->hero.x+=x;
    child->hero.y+=y;

    if(box_move)
    {
	child->boxes[box_ind].x+=x;
	child->boxes[box_ind].y+=y;
    }
    switch(direction)
    {
    case UP:
	node->up=child;
	break;
    case DOWN:
	node->down=child;
	break;
    case LEFT:
	node->left=child;
	break;
    case RIGHT:
	node->right=child;
	break;
    }
}
Node* just_do_it(vector<Node*> nodes)
{
    for(int i=0; i<nodes.size(); i++)
    {
	bool finished=false;
	if(!nodes[i])
	{
	    continue;
	}
	for(int j=0; j<nodes[i]->boxes.size(); j++)
	{
	    if(map[nodes[i]->boxes[j].x][nodes[i]->boxes[j].y]!='+')
	    {
		finished=false;
		break;
	    }
	    finished=true;
	}
	if(finished)
	{
	    return nodes[i];
	}
    }
    vector<Node*> children;
    for(int i=0; i<nodes.size(); i++)
    {
	if(nodes[i])
	{
	    if(nodes[i]->parent && compare(nodes[i]->boxes,nodes[i]->parent->boxes))
	    {
		switch(nodes[i]->step)
		{
		case UP:
		    move(nodes[i],UP);
		    move(nodes[i],LEFT);
		    move(nodes[i],RIGHT);
		    children.push_back(nodes[i]->up);
		    children.push_back(nodes[i]->left);
		    children.push_back(nodes[i]->right);
		    break;
		case DOWN:
		    move(nodes[i],DOWN);
		    move(nodes[i],LEFT);
		    move(nodes[i],RIGHT);
		    children.push_back(nodes[i]->down);
		    children.push_back(nodes[i]->left);
		    children.push_back(nodes[i]->right);
		    break;
		case LEFT:
		    move(nodes[i],UP);
		    move(nodes[i],DOWN);
		    move(nodes[i],LEFT);
		    children.push_back(nodes[i]->up);
		    children.push_back(nodes[i]->down);
		    children.push_back(nodes[i]->left);
		    break;
		case RIGHT:
		    move(nodes[i],UP);
		    move(nodes[i],DOWN);
		    move(nodes[i],RIGHT);
		    children.push_back(nodes[i]->up);
		    children.push_back(nodes[i]->down);
		    children.push_back(nodes[i]->right);
		    break;
		}
	    }
	    else
	    {
		move(nodes[i],UP);
		move(nodes[i],DOWN);
		move(nodes[i],LEFT);
		move(nodes[i],RIGHT);
		children.push_back(nodes[i]->up);
		children.push_back(nodes[i]->down);
		children.push_back(nodes[i]->left);
		children.push_back(nodes[i]->right);
	    }
	}
    }
    return just_do_it(children);
}

stack<Node*> set_stack(Node* finished)
{
    stack<Node*> path;
    while(finished)
    {
	path.push(finished);
	finished=finished->parent;
    }
    return path;
}

int main()
{
    clock_t time;

    time = clock();
    ifstream in("map.txt", ios::in);
    Node* root = new Node();
    load_map(in, root);
    vector <Node*> Groot;
    Groot.push_back(root);
    Node* finished = just_do_it(Groot);
    stack<Node*> the_path= set_stack(finished);
    while(the_path.size())
    {
	print(the_path.top());
	the_path.pop();
    }
    in.close();
    time = clock() - time;
    cout << (double)time/CLOCKS_PER_SEC<<endl;
    system("pause");
    return 0;
}
