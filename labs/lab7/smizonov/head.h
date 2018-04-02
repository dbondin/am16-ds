#include <iostream>
#include <fstream>

class cat;
class mass;

void sort_insert (mass sor, int first, int last,bool compare(cat cat1, cat cat2));
void merger(mass mas, int bord1,int bord2,int bord3, bool compare(cat cat1, cat cat2));
void Timsort(mass sor, bool compare(cat cat1, cat cat2));
int GetMinrun(int n);
mass take_cats(std::ifstream &file);
void write_to_file(std::ofstream &out, mass mas);

class cat{
public:
    int id;
    int age;
    std::string name;
    std::string eate;
    std::string poroda;
    cat() {}
    cat(const cat &v)
    {
        id=v.id;
        age=v.age;
        name=v.name;
        poroda=v.poroda;
        eate=v.eate;
    }
};

class mass
{
public:
    cat *cats;
    int size, max_size;
    mass() {
        size=max_size=1;
        cats=NULL;
    }

   mass(int size1)
   {
       size=max_size=size1;
       cats=new cat[size];
   }

 void expand()
  {
     max_size=size*2+1;
     cat *new_cat=new cat[max_size];
     for(int i=0;i<size-1;i++)
         new_cat[i]=cats[i];
     delete[] cats;
     cats=new_cat;
  }

};
