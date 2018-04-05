#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <string.h>

#include "timsort.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        cout << "Недостаточно параметров :(" << endl;
        cout << "TimSort <файл_данных>" << endl;
        return 0;
    }

    vector<CatInfo *> cats;

    ifstream ifs(argv[1]);
    if(!ifs.is_open())
    {
        cout << "Ошибка при доступе к файлу '" << argv[1] << "'" << endl;
        return 0;
    }

    char buffer[4096];
    while(!ifs.eof())
    {
        memset(buffer, 0, sizeof(buffer));
        ifs.getline(buffer, 4096, '\n');

        if(strlen(buffer) == 0)
            continue;

        CatInfo *cat = new CatInfo();

        string p = "";
        p.assign(buffer);

        string::size_type pos0, pos1;
        pos0 = p.find(";");
        if(pos0 == string::npos)
        {
            delete cat;
            continue;
        }

        cat->number = atoi(p.substr(0, pos0).c_str());

        pos1 = pos0 + 1;

        pos0 = p.find(";", pos1);
        if(pos0 == string::npos)
        {
            delete cat;
            continue;
        }

        cat->name = p.substr(pos1, pos0-pos1);

        pos1 = pos0 + 1;

        pos0 = p.find(";", pos1);
        if(pos0 == string::npos)
        {
            delete cat;
            continue;
        }

        cat->age = atoi(p.substr(pos1, pos0-pos1).c_str());

        pos1 = pos0 + 1;

        pos0 = p.find(";", pos1);
        if(pos0 == string::npos)
        {
            delete cat;
            continue;
        }

        cat->breed = p.substr(pos1, pos0-pos1);

        pos1 = pos0 + 1;

        pos0 = p.find(";", pos1);
        if(pos0 == string::npos)
        {
            delete cat;
            continue;
        }

        cat->food = p.substr(pos1);

        cats.push_back(cat);
    }

    ifs.close();

    cout << "Всего загружено " << cats.size() << " котов из файла '" << argv[1] << "'" << endl;
    if(cats.empty())
    {
        cout << "Упс, а список то пуст :(" << endl;
        return 0;
    }

    vector<CatInfo *> cc;
    TimSort tt;
    int q = 0;
    while(true)
    {
        cout << "Укажите тип сортировки:" << endl;
        cout << "1 - по номеру" << endl;
        cout << "2 - по имени" << endl;
        cout << "3 - по возрасту" << endl;
        cout << "4 - по породе" << endl;
        cout << "5 - по еде" << endl;
        cout << "0 - выход" << endl;
        cout << "==> " << ends;
        cin >> q;

        if(q == 0)
        {
            cout << "УРА УРА работа закончена, выход!!" << endl;
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        cout << "ВВедите имя выходного файла ==> " << ends;
        cin >> buffer;

        // Очищаем копию исходного массива
        for(auto ii = 0; ii < cc.size(); ii++)
        {
            CatInfo *cat = cc.at(ii);
            delete cat;
        }

        cc.clear();

        for(auto ii = 0; ii < cats.size(); ii++)
        {
            CatInfo *cat = cats.at(ii);
            CatInfo *p = new CatInfo(cat);
            cc.push_back(p);
        }

        tt.sortType(q);
        tt.sort(cc);

        ofstream ofs(buffer);
        if(!ofs.is_open())
        {
            cout << "Ошибка при создании файла '" << buffer << "'" << endl;
            continue;
        }

        for(auto ii = 0; ii < cc.size(); ii++)
        {
            CatInfo *cat = cc.at(ii);
            ofs << cat->toString().c_str() << endl;
        }
        ofs.flush();
        ofs.close();
    }

    for(auto ii = 0; ii < cc.size(); ii++)
    {
        CatInfo *cat = cc.at(ii);
        delete cat;
    }

    cc.clear();

    for(auto ii = 0; ii < cats.size(); ii++)
    {
        CatInfo *cat = cats.at(ii);
        delete cat;
    }

    cats.clear();

    return 0;
}
