
Rb_tree::Rb_tree(std::string _value, std::string _key, Colors _colors, Rb_tree *l, Rb_tree *r, Rb_tree *p){

    value = _value;
    key = _key;
    colors = _colors;
    left = l;
    right = r;
    parent = p;
    if(NULL == parent){
       colors = BLACK;
    }
}

Rb_tree::~Rb_tree(){

    if(left){
        delete left;
        left = NULL;
    }
    if(right){
        delete right;
        right = NULL;
    }
}

std::string Rb_tree::search(std::string _key, const int exactly){
    if(key.compare(_key) < 0){
        if(right){
            return right->search(_key);
        }
        else{
            return "";
        }
    }
    else{
        int detected = key.find(_key);
        std::string from_left;
        std::string from_right;
        if(0 == detected){
            if(1 == exactly){
                if(key.compare(_key) == 0){
                    return value;
                }
                else{
                    return "";
                }
            }
       	    if(left){
                    from_left = left->search(_key);
            }
            if(from_left.size() > 0){
                    from_left += "\n";
            }
            from_left += value;
            if(right){
	                from_right = right->search(_key);
            }
            if(from_right.size() > 0){
                    from_right += "\n";
            }
            from_left += from_right;
                    return from_left;
        }
        else{
            if(left){
                return left->search(_key);
            }
            else{
                return "";
            }
        }
    }
}

int Rb_tree::is_sheet(){
    return (left || right) ? 0:1;
}

void Rb_tree::balans(){
    if(parent->colors == BLACK){
        return;
    }
    Rb_tree *grandpa = parent->parent;
    if(grandpa->left && grandpa->right && (grandpa->left->colors == RED) && (grandpa->right->colors == RED)){
        grandpa->left->colors = BLACK;
        grandpa->right->colors = BLACK;
        if(NULL == grandpa->parent){
            return;
        }
        grandpa->colors = RED;
        grandpa->balans();
    }
    else{
        if(parent->key.compare(grandpa->key) < 0){
            if(key.compare(parent->key) > 0){
                parent->right = left;
                if(left){
                    left->parent = parent;
                }
                parent->parent = this;
                left = parent;
                parent = grandpa;
                grandpa->left = this;
                left->balans();
            }
            else{
                grandpa->left = parent->right;
                if(parent->right){
                    parent->right->parent = grandpa;
                }
                if(grandpa->parent){
                    if(grandpa->key.compare(grandpa->parent->key) > 0){
                        grandpa->parent->right = parent;
                    }
                    else{
                        grandpa->parent->left = parent;
                    }
                }
                parent->parent = grandpa->parent;
                parent->right = grandpa;
                grandpa->parent = parent;
                parent->colors = BLACK;
            }
        }
        else{
            if(key.compare(parent->key) > 0){
                grandpa->right = parent->left;
                if(parent->left){
                    parent->left->parent = grandpa;
                }
                if(grandpa->parent){
                    if(grandpa->key.compare(grandpa->parent->key) > 0){
                        grandpa->parent->right = parent;
                    }
                    else{
                        grandpa->parent->left = parent;
                    }
                }
                parent->parent = grandpa->parent;
                parent->left = grandpa;
                grandpa->parent = parent;
                parent->colors = BLACK;
            }
            else{
                parent->left = right;
                if(right){
                    right->parent = parent;
                }
                parent->parent = this;
                right = parent;
                parent = grandpa;
                grandpa->right = this;
                right->balans();
            }
        }
    }
}

void Rb_tree::add(std::string _value, std::string _key){
    if(key.compare(_key) < 0){
        if(right){
            right->add(_value,_key);
        }
        else{
            Rb_tree *new_tree = new Rb_tree(_value,_key,RED,NULL,NULL,this);
            right = new_tree;
            new_tree->balans();
        }
    }
    else{
        if(left){
            left->add(_value,_key);
        }
        else{
            Rb_tree *new_tree = new Rb_tree(_value,_key,RED,NULL,NULL,this);
            left = new_tree;
            new_tree->balans();
        }
    }
}
