
Map_tree::Map_tree(){
    root = NULL;
}

Map_tree::~Map_tree(){
    delete root;
    root = NULL;
}

std::string Map_tree::partial_search(std::string key){
    if(root){
        return root->search(key);
    }
    else{
        std::cout << "Дерево опало,листочков нет" << std::endl;
        return "";
    }
}

std::string Map_tree::search(std::string key){
    if(root){
        return root->search(key,1);
    }
    else{
        std::cout << "Дерево опало,листочков нет" << std::endl;
        return "";
    }
}

void Map_tree::add(std::string key, std::string value){
    if(!root){
        root = new Rb_tree(value,key,BLACK,NULL,NULL,NULL);
    }
    else{
        root->add(value,key);
    }
}
