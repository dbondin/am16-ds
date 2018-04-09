
Hash_map::Hash_map(){

    table = new Hash_table(100);
    size_map = 0;
}

Hash_map::~Hash_map(){

    delete table;
}

void Hash_map::add(int key, std::string value){
    table->add(key,value);
    ++size_map;
}

std::string Hash_map::search(int key){

    if(0 == size_map){
        std::cout << "Справочник пуст" << std::endl;
        return "";
    }
    return table->search(key);
}

