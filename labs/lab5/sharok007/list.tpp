
List::List(){

    root = NULL;

}

void List::add(int _key, std::string _value){
    if(NULL == root){
        root = new element{_key, _value, NULL};
    }
    else{
        element *temp = root;
        while(temp->next){
            temp = temp->next;
        }
        temp->next = new element{_key,_value,NULL};
    }
}

std::string List::search(int _key){
    element *temp = root;
    while(temp){
        if(_key == temp->key){
            return temp->value;
        }
        else{
            temp = temp->next;
        }
    }
    std::cout << "Ничего не найдено" << std::endl;
    return "";
}

List::~List(){
    element *temp;
    while(root){
        temp = root->next;
        delete root;
        root = temp;
    }
}

