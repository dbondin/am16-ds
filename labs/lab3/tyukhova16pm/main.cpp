#include "stack.h"

int main() 
{
    cout<<"Please, define expression below:"<<endl;
    string term;
    getline(cin,term); 
    string post = Replacement(term);
    cout<<"Result here: "<<endl;
    Proc(post);
    return 0;
}
