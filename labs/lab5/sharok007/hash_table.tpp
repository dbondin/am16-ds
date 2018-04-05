
Hash_table::Hash_table(int size){
    size_table = size;
    data = new List[size];
}

Hash_table::~Hash_table(){

    delete[] data;
}

int Hash_table::hash(int key){

    return key % size_table;
}

void Hash_table::add(int key, std::string value){
    int id = hash(key);
    data[id].add(key,value);
}

std::string Hash_table::search(int key){
    int id = hash(key);
    return data[id].search(key);
}

