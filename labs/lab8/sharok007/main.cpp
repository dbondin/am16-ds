#include <iostream>
#include <fstream>
#include <vector>
#include <stack>


#define HEIGHT 6
#define WIDTH 8

using namespace std;

unsigned char field[HEIGHT][WIDTH];

enum MOVE
{
    NONE=0,
    UP=1,
    DOWN=2,
    LEFT=4,
    RIGHT=8
};


struct coord
{
    coord();
    coord(unsigned char _x, unsigned char _y);
    unsigned char x;
    unsigned char y;
};

coord::coord()
{
    x=0;
    y=0;
}

coord::coord(unsigned char _x, unsigned char _y)
{
    x=_x;
    y=_y;
}

struct Node
{
    Node();
    ~Node();
    Node(Node* _parent, coord _soko_ban, vector<coord> _boxes, MOVE _step);
    Node *parent;
    Node* up;
    Node* down;
    Node* left;
    Node* right;
    coord soko_ban;
    MOVE step;
    vector<coord> boxes;
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

Node::Node(Node* _parent, coord _soko_ban, vector<coord> _boxes, MOVE _step)
{
    parent=_parent;
    up=NULL;
    down=NULL;
    left=NULL;
    right=NULL;
    soko_ban=_soko_ban;
    boxes=_boxes;
    step=_step;
}

bool compare(vector<coord> a, vector<coord> b)
{
    for(unsigned int i=0; i<a.size(); ++i)
    {
        if((a[i].x!=b[i].x) || (a[i].y!=b[i].y))
        {
            return false;
        }
    }
    return true;
}

void load_field(ifstream & in, Node *root)
{
    for (int j=0; j < HEIGHT; ++j)
    {
        for(int i=0; i < WIDTH; ++i)
        {
            unsigned char buf=in.get();
            if(buf=='@')
            {
                root->soko_ban.x=i;
                root->soko_ban.y=j;
                buf=' ';
            }
            else if(buf=='%')
            {
                coord temp(i,j);
                root->boxes.push_back(temp);
                buf=' ';
            }
            field[i][j]=buf;
        }
        in.get();
    }

}

void print(Node* node)
{
    cout<<endl;
    for (int j=0; j <HEIGHT; ++j)
    {
        for(int i=0; i < WIDTH; ++i)
        {
            if(node->soko_ban.x==i&&node->soko_ban.y==j)
            {
                cout.put(1);
            }
            else
            {
                bool flag=true;
                for(unsigned int k=0; k<node->boxes.size(); k++)
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
                    cout<<field[i][j];
                }
            }
        }
        cout<<endl;
    }
}

void move(Node* node, MOVE MOVE)
{

    char x=0,y=0;
    switch(MOVE)
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
    if(field[node->soko_ban.x+x][node->soko_ban.y+y]!='#')
    {
        for(unsigned int i=0;i<node->boxes.size();++i)
        {
            if(node->soko_ban.x+x==node->boxes[i].x && node->soko_ban.y+y==node->boxes[i].y)
            {
                box_ind=i;
                if(field[node->boxes[i].x+x][node->boxes[i].y+y]!='#')
                {
                    for(unsigned int j=0; j < node->boxes.size(); ++j)
                    {
                        if(node->boxes[i].x+x==node->boxes[j].x && node->boxes[i].y+y==node->boxes[j].y)
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

    Node* child = new Node(node, node->soko_ban, node->boxes, MOVE);

    child->soko_ban.x+=x;
    child->soko_ban.y+=y;

    if(box_move)
    {
        child->boxes[box_ind].x+=x;
        child->boxes[box_ind].y+=y;
    }
    switch(MOVE)
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
Node* play(vector<Node*> nodes)
{
    for(unsigned int i=0; i<nodes.size(); ++i)
    {
        bool finished=false;
        if(!nodes[i])
        {
            continue;
        }
        for(unsigned int j=0; j<nodes[i]->boxes.size(); ++j)
        {
            if(field[nodes[i]->boxes[j].x][nodes[i]->boxes[j].y]!='+')
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
    vector<Node*> child;
    for(unsigned int i=0; i<nodes.size(); ++i)
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
                    child.push_back(nodes[i]->up);
                    child.push_back(nodes[i]->left);
                    child.push_back(nodes[i]->right);
                    break;
                case DOWN:
                    move(nodes[i],DOWN);
                    move(nodes[i],LEFT);
                    move(nodes[i],RIGHT);
                    child.push_back(nodes[i]->down);
                    child.push_back(nodes[i]->left);
                    child.push_back(nodes[i]->right);
                    break;
                case LEFT:
                    move(nodes[i],UP);
                    move(nodes[i],DOWN);
                    move(nodes[i],LEFT);
                    child.push_back(nodes[i]->up);
                    child.push_back(nodes[i]->down);
                    child.push_back(nodes[i]->left);
                    break;
                case RIGHT:
                    move(nodes[i],UP);
                    move(nodes[i],DOWN);
                    move(nodes[i],RIGHT);
                    child.push_back(nodes[i]->up);
                    child.push_back(nodes[i]->down);
                    child.push_back(nodes[i]->right);
                    break;
                }
            }
            else
            {
                move(nodes[i],UP);
                move(nodes[i],DOWN);
                move(nodes[i],LEFT);
                move(nodes[i],RIGHT);
                child.push_back(nodes[i]->up);
                child.push_back(nodes[i]->down);
                child.push_back(nodes[i]->left);
                child.push_back(nodes[i]->right);
            }
        }
    }
    return play(child);
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
    ifstream in("field.txt", ios::in);
    Node* root = new Node();
    load_field(in, root);
    vector <Node*> Groot;
    Groot.push_back(root);
    Node* finished = play(Groot);
    stack<Node*> the_path= set_stack(finished);
    while(the_path.size())
    {
        print(the_path.top());
        the_path.pop();
    }
    in.close();
    return 0;
}
