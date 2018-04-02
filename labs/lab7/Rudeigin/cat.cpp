#include <iostream>
#include <fstream>
#include <string>
#include "cat.h"

int cat::get_id() {
    return id;
}

int cat::get_age() {
    return age;
}

std::string cat::get_name() {
    return name;
}

std::string cat::get_breed() {
    return breed;
}

std::string cat::get_food() {
    return food;
}

void cat::set_id(int _id) {
    id = _id;
}

void cat::set_age(int _age) {
    age = _age;
}

void cat::set_name(std::string _name) {
    name = _name;
}

void cat::set_breed(std::string _breed) {
    breed = _breed;
}

void cat::set_food(std::string _food) {
    food = _food;
}
