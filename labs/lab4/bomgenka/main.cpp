#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tree.h>

using namespace std;

int min_id(tree ** _tree) {
    int min = -1;
    int result = 0;
    for (int i = 0; i < NUM_OF_SYMB; ++i) {
        if (_tree[i] && ((_tree[i]->get_weight() < min) || (min == -1))) {
            result = i;
            min = _tree[i]->get_weight();
        }
    }
    return result;
}

tree * merge_children(tree * left_child, tree * right_child) {
    tree * root = new tree(left_child, right_child, 0, left_child->get_weight() + right_child->get_weight());
    return root;
}

tree * merge_tree(tree **forest)
{
    int min  = 0;
        for (int trees = NUM_OF_SYMB; trees > 1; --trees) {
            min = min_id(forest);
            tree * left = forest[min];
            for (int i = min; i < NUM_OF_SYMB; ++i) {
                forest[i] = forest[i + 1];
            }
            forest[NUM_OF_SYMB-1] = NULL;
            min = min_id(forest);
            tree *right = forest[min];
            for (int i = min; i < NUM_OF_SYMB-1; ++i) {
                forest[i] = forest[i + 1];
            }
            forest[NUM_OF_SYMB-1] = merge_children(left, right);
        }
    return forest[NUM_OF_SYMB-1];
}

void built_compress_codes(tree * _tree, string *codes, string current_code){
    if (_tree->get_left_child()) {
        current_code += '0';
        built_compress_codes(_tree->get_left_child(), codes, current_code);
        current_code.pop_back();
    }
    if (_tree->get_right_child ()) {
        current_code += '1';
        built_compress_codes(_tree->get_right_child (), codes, current_code);
        current_code.pop_back();
    }
    else if (_tree->is_leaf()) {
        codes[_tree->get_symbol()] = current_code;
    }
}
tree *uncode(tree * Huffman_tree, string sequence)
{
    tree * counter = Huffman_tree;
        for (unsigned int i = 0; i < sequence.size (); ++i) {
            if (sequence[i] == '0') {
                counter = counter->get_left_child ();
                if (counter->is_leaf()) {
                    return counter;
                }
            }
            else {
                counter = counter->get_right_child ();
                if (counter->is_leaf()) {
                    return counter;
                }
            }
        }
    return NULL;
}
void built_uncompress_codes(tree *_tree, string input, string output, string * codes)
{
    ifstream in(input);
    ofstream out(output);
    string rem;
    int file_size = _tree->get_weight();
    char symbol;
    int size = 0;
    string new_byte;
    while (in.get(symbol)) {
        if (size >= file_size) {
            break;
        }
        for (int i = 7; i >= 0; --i) {
            if(symbol & (0x1 << i)) new_byte += "1";
            else new_byte += "0";
            //new_byte.push_back((c & (0x1 << i)) ? '1' : '0');
        }

        rem += new_byte;
        new_byte.clear ();
        tree * uncoding;
        while (uncoding = uncode(_tree, rem)) {
            char letter = (char)uncoding->get_symbol();
            out.put (letter);
            ++size;
            if (size == file_size) {
                break;
            }
            rem.erase(0, codes[(unsigned char)letter].size ());
        }
    }

}

void compress(string input, string output){
    ifstream in(input);
    ofstream out(output, ios_base::trunc | ios_base::binary);
    int *count = new int[NUM_OF_SYMB];
    char symbol;
    for(int i = 0; i < NUM_OF_SYMB; ++i) {
          count[i] = 0;
    }
    while(in.get(symbol)) {
        ++count[(unsigned int)symbol];
    }
    out << "HF16";
    for(int i = 0; i < NUM_OF_SYMB; ++i) {
        bytec buff;
        buff.number = count[i];
        out.put(buff.bytes[3]);
        out.put(buff.bytes[2]);
        out.put(buff.bytes[1]);
        out.put(buff.bytes[0]);
    }
    in.close();
    in.open(input);

    tree * forest[NUM_OF_SYMB];
    for (int i = 0; i < NUM_OF_SYMB; ++i) {
        forest[i] = new tree(NULL, NULL, count[i], (char)i);
    }

    tree * _tree = merge_tree(forest);
    string codes[NUM_OF_SYMB];
    string buff = "";
    built_compress_codes(_tree, codes, buff);
    string rem;
    while (in.get(symbol)) {
        rem += codes[(unsigned int)symbol];
        int bytes = rem.size () / 8;
        unsigned char outbyte = 0;
        for (int i = 0; i < bytes; ++i) {
            for (unsigned int j = 0; j < 8; ++j) {
                outbyte |= rem[j] - '0';
                if (j < 7) {
                    outbyte <<= 1;
                }
            }
            out.put( (char)outbyte );
            rem.erase (0, 8);
            outbyte = 0;
        }
    }
    out.close ();
    return;
}

void uncompress(string input, string output) {
    ifstream in(input);
    ofstream out(output, ofstream::binary);
    char symbol;
    string enter = "HF16";
    for (int i = 0; i < 4; ++i) {
        in >> symbol;
        if(symbol != enter[i]) return;
    }
    tree * forest[NUM_OF_SYMB];
    for (int i = 0; i < NUM_OF_SYMB; ++i) {
        unsigned int stat = 0;
        for (int j = 0; j < 4; ++j) {
            in.get(symbol);
            stat |= (unsigned char)symbol;
                        stat <<= 8;
                    }
                    stat >>= 8;
                    forest[i] = new tree(NULL, NULL, stat, i);
                }

                tree * _tree = merge_tree(forest);
                string codes[NUM_OF_SYMB];
                (_tree, codes);

                built_uncompress_codes(_tree, input, output, codes);
    out.close ();
}

int main(int argc, char **argv) {
    if(argc != 2) {
        cout << "Укажите исходный файл и выходной файл" << endl;
        return 0;
    }
    string in(argv[1]);
    string out(argv[2]);
    compress(in, out);
    cout << "Compress is done\n";
    return 0;
}

/*
 * int main(int argc, char **argv) {
    if(argc != 2) {
        cout << "Укажите исходный файл и выходной файл" << endl;
        return 0;
    }
    string in(argv[1]);
    string out(argv[2]);
    uncompress(in, out);
    cout << "Uncompress is done\n";
    return 0;
}
*/
