#ifndef CAT_H
#define CAT_H

#include <string>
#include <fstream>

enum properties {ID, AGE, NAME, BREED, FOOD};

class cat {
private:
    int id;
    int age;
    std::string name;
    std::string breed;
    std::string food;
public:
    int get_id();
    int get_age();
    std::string get_name();
    std::string get_breed();
    std::string get_food();
    void set_id(int _id);
    void set_age(int _age);
    void set_name(std::string _name);
    void set_breed(std::string _breed);
    void set_food(std::string _food);
};

#endif // CAT_H
