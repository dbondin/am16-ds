
#include "head.h"

using namespace std;


int GetMinrun(int n)
    {
        int r = 0;
        while (n >= 64) {
            r |= n & 1;
            n >>= 1;
        }
        return n + r;
    }


void sort_insert (mass sor, int first, int last,bool compare(cat cat1, cat cat2))
{
    for (int i = first; i < last; i++) {
        for (int j = i; j > first; j--) {
            if(compare(sor.cats[j], sor.cats[j-1]))
            {
                cat new_cat(sor.cats[j-1]);
                sor.cats[j-1]=sor.cats[j];
                sor.cats[j]=new_cat;
         }
        }
    }
}

void merger(mass mas, int bord1,int bord2,int bord3, bool compare(cat cat1, cat cat2))
{
    mass new_mass(bord3-bord1+1);
    int j=bord2, i=bord1;
    int num=0;
    while(i!=bord2 || j!=bord3)
    {

        if(i==bord2)
        {
            while(j<bord3)
            {
                new_mass.cats[num]=mas.cats[j];
                num++;
                j++;

            }
            break;
        }
        if(j==bord3)
        {
            while(i<bord2)
            {
                new_mass.cats[num]=mas.cats[i];
                num++;
                i++;
            }
            break;
        }
        if(compare(mas.cats[i],mas.cats[j]))
        {new_mass.cats[num]=mas.cats[i];
            i++;
            num++;}
        else
        {new_mass.cats[num]=mas.cats[j];
            j++;
            num++;}
    }
    j=0;
    for(int i=bord1;i<bord3;i++)
    {
        mas.cats[i]=new_mass.cats[j];
        j++;
    }
    cout<<endl;
}

void insert(int *mas, int num, int &size)
{
    size--;
    for(int i=num;i<size;i++)
        mas[i]=mas[i+1];
}

void Timsort(mass sor,bool compare(cat cat1, cat cat2))
{
   int minrun=GetMinrun(sor.size);
   if(minrun==sor.size)
   {
       sort_insert(sor, 0, minrun,compare);
       return;
   }
   int *num_of_new_subarr=new int[sor.size/2], size_of_num=1;
   num_of_new_subarr[0]=0;
   int first_elem;
   for(int i=1;i<sor.size;)
   {
       if(sor.size-i==1){
           i++;
           num_of_new_subarr[size_of_num]=i;
           size_of_num=size_of_num+1;
           break;}

       first_elem=i-1;
       while( !compare(sor.cats[i],sor.cats[i-1]) && i<sor.size)
           i++;
       if(first_elem==(i-1))
       {
           while( compare(sor.cats[i],sor.cats[i-1]) && i<sor.size)
               i++;
           int num=i-1;
           for(int t=first_elem; t<first_elem+((i-first_elem)/2);t++)
           {
                   cat tmp(sor.cats[t]);
                   sor.cats[t]=sor.cats[num];
                   sor.cats[num]=tmp;
                   num--;
           }

       }
       if(i-first_elem<=minrun)
       {

           if(sor.size-first_elem>=minrun){
           sort_insert(sor,first_elem,first_elem+minrun,compare);
           i=first_elem+minrun;
       } else if(sor.size-first_elem<minrun){
           sort_insert(sor,first_elem,sor.size,compare);
           num_of_new_subarr[size_of_num]=i;
           size_of_num=size_of_num+1;
           break;
       }
   }
       num_of_new_subarr[size_of_num]=i;
       size_of_num=size_of_num+1;
       i++;
}
    int i;
    for( i=3;i<size_of_num;) {
      if(num_of_new_subarr[i]-num_of_new_subarr[i-1]>=num_of_new_subarr[i-1]-num_of_new_subarr[i-2]
      || num_of_new_subarr[i-2]-num_of_new_subarr[i-3]<=num_of_new_subarr[i]-num_of_new_subarr[i-2])
      {
          cout<<endl<<"  "<<num_of_new_subarr[i-3]<<"  "<<num_of_new_subarr[i-2]<<"  "<<num_of_new_subarr[i-1]<<"  "<<num_of_new_subarr[i]<<endl;
          if(num_of_new_subarr[i]-num_of_new_subarr[i-1]<num_of_new_subarr[i-2]-num_of_new_subarr[i-3])
          {
              merger(sor,num_of_new_subarr[i-2],num_of_new_subarr[i-1],num_of_new_subarr[i],compare);
              insert(num_of_new_subarr,i-1,size_of_num);
          } else {
              merger(sor,num_of_new_subarr[i-3],num_of_new_subarr[i-2],num_of_new_subarr[i-1],compare);
              insert(num_of_new_subarr,i-2,size_of_num);
          }

      } else
      i++;
    }
    i--;
      if(size_of_num-i==1)
      {
          while (i-3>0) {
              if(num_of_new_subarr[i]-num_of_new_subarr[i-1]<num_of_new_subarr[i-2]-num_of_new_subarr[i-3])
              {
                  merger(sor,num_of_new_subarr[i-2],num_of_new_subarr[i-1],num_of_new_subarr[i],compare);
                  insert(num_of_new_subarr,i-1,size_of_num);
              } else {
                  merger(sor,num_of_new_subarr[i-3],num_of_new_subarr[i-2],num_of_new_subarr[i-1],compare);
                  insert(num_of_new_subarr,i-2,size_of_num);
              }
             i--;
          }
      }
      if(size_of_num>=4)
      {
     if(num_of_new_subarr[3]-num_of_new_subarr[2]>num_of_new_subarr[1])
     { merger(sor,num_of_new_subarr[0],num_of_new_subarr[1],num_of_new_subarr[2],compare);
     insert(num_of_new_subarr,1,size_of_num);
     }
     else{
         merger(sor,num_of_new_subarr[1],num_of_new_subarr[2],num_of_new_subarr[3],compare);
      insert(num_of_new_subarr,2,size_of_num);
     }
      }
      if(size_of_num>=3)
      merger(sor,num_of_new_subarr[0],num_of_new_subarr[1],num_of_new_subarr[2],compare);

}



mass take_cats(ifstream &file)
{
    mass mas;
    while (!file.eof())
    {
     int id,age;
     string name,poroda,eate, rub;
    file>>id;
    getline (file, rub, ' ');
    getline (file, name, ' ');
    file>>age;
    getline (file, rub, ' ');
    getline (file, poroda, ' ');
    getline (file, eate, '\n');
    if(eate.length()!=0)
      {
        if (mas.size==mas.max_size)
            mas.expand();
        mas.cats[mas.size-1].age=age;
        mas.cats[mas.size-1].id=id;
        mas.cats[mas.size-1].name=name;
        mas.cats[mas.size-1].poroda=poroda;
        mas.cats[mas.size-1].eate=eate;
      mas.size++;
      }
   }
    mas.size--;
    return mas;
}

void write_to_file(ofstream &out, mass mas)
{
    for(int i=0;i<mas.size;i++)
    {
        out<<mas.cats[i].id<<" "
          <<mas.cats[i].name<<" "
         <<mas.cats[i].age<<" "
        <<mas.cats[i].poroda<<" "
        <<mas.cats[i].eate<<"\n";
    }
}

bool compare_age(cat cat1, cat cat2)
{
    if(cat1.age<cat2.age)
    {
        return true;
    } else { return false;}
}

bool compare_id(cat cat1, cat cat2)
{
    if(cat1.id<cat2.id)
    {
        return true;
    } else { return false;}
}

bool compare_name(cat cat1, cat cat2)
{
    if(cat1.name<cat2.name)
    {
        return true;
    } else { return false;}
}

bool compare_poroda(cat cat1, cat cat2)
{
    if(cat1.poroda<cat2.poroda)
    {
        return true;
    } else { return false;}
}

bool compare_eate(cat cat1, cat cat2)
{
    if(cat1.eate<cat2.eate)
    {
        return true;
    } else { return false;}
}

int main()
{
    int key;
    ifstream file;
    ofstream out;
    file.open("cats.txt", ios::in);
    mass mas=take_cats(file);

    cout<<"Введите действиe: \n1)Сортировать по id \n2)Сортировать по имени"<<endl;
    cout<<"3)Сортировать по возрасту\n4)Сортировать по породе\n5)Сортировать по любимой еде"<<endl;
    cin>>key;
    switch (key) {
    case 1:
    {
        Timsort(mas,compare_id);
        out.open("id.txt",ios::out);
        write_to_file(out,mas);
        out.close();
        cout<<endl<<"Данные записаны в файл id.txt"<<endl;
        break;
    }
    case 2:
    {
      Timsort(mas,compare_name);
      out.open("name.txt",ios::out);
      write_to_file(out,mas);
      out.close();
      cout<<endl<<"Данные записаны в файл name.txt"<<endl;
       break;
    }
    case 3:
    {
      Timsort(mas,compare_age);
      out.open("age.txt",ios::out);
      write_to_file(out,mas);
      out.close();
      cout<<endl<<"Данные записаны в файл age.txt"<<endl;
       break;
    }
    case 4:
    {
      Timsort(mas,compare_poroda);
      out.open("poroda.txt",ios::out);
      write_to_file(out,mas);
      out.close();
      cout<<endl<<"Данные записаны в файл poroda.txt"<<endl;
       break;
    }
    case 5:
    {
      Timsort(mas,compare_eate);
      out.open("food.txt",ios::out);
      write_to_file(out,mas);
      out.close();
      cout<<endl<<"Данные записаны в файл food.txt"<<endl;
       break;
    }
    default:
        break;
    }
    file.close();
}
