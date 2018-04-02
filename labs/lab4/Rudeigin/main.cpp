#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tree.h>

using namespace std;

int main(int argc, char **argv) {
    if(argc != 2) {
        cout << "Error. Expected: ./proganame infilename outfilename" << endl;
        return 0;
    }
    string input(argv[1]);
    string output(argv[2]);

    ifstream in(input);
    ofstream out(output, ios_base::binary);
    int count[256];
    char symbol;

    for(int i = 0; i < 256; ++i) {
          count[i] = 0;
    }
    while(in.good()) {
        in.get(symbol);
        ++count[(unsigned int)symbol];
    }
    out << "HF16";
    for(int i = 0; i < 256; ++i) {
        bytec buff;
        buff.number = count[i];
        out.put(buff.bytes[3]);
        out.put(buff.bytes[2]);
        out.put(buff.bytes[1]);
        out.put(buff.bytes[0]);
    }
    in.close();
    in.open(input);

    huffman_tree * trees[256];
    for (int i = 0; i < 256; ++i) {
        trees[i] = new huffman_tree(NULL, NULL, count[i], (char)i);
    }

    huffman_tree * big_tree = make_huffman_tree(trees);
    string codes[256];
    string buff = "";
    way(big_tree, codes, buff);
    string str;

    while (in.get(symbol)) {
        str += codes[(unsigned int)symbol];
        if(str.size()>7) {
            int bytes = str.size () / 8;
            unsigned char outbyte = 0;
            for (int i = 0; i < bytes; ++i) {
                for (unsigned int j = 0; j < 8; ++j) {
                    outbyte |= str[j] - '0';
                    if (j < 7) {
                        outbyte <<= 1;
                    }
                }
                out.put( (char)outbyte );
                str.erase (0, 8);
                outbyte = 0;

            }
        }
    }

    for(int i = str.size(); i < 8; ++i) {
        str.push_back('0');
    }
    unsigned char outbyte = 0;
    for (unsigned int j = 0; j < 8; ++j) {
        outbyte |= str[j] - '0';
        if (j < 7) {
            outbyte <<= 1;
        }
    }
    out.close();
    cout << "Compress is done\n";
    return 0;
}
/*
 int main(int argc, char **argv) {
    if(argc != 2) {
        cout << "Укажите исходный файл и выходной файл" << endl;
        return 0;
    }

    string input(argv[1]);
    string output(argv[2]);
    ifstream in(input);
    ofstream out(output, ofstream::binary);
    char symbol;
    string enter = "HF16";
    for (int i = 0; i < 4; ++i) {
        in >> symbol;
        if(symbol != enter[i]) return 0;
    }
    huffman_tree * forest[256];
    for (int i = 0; i < 256; ++i) {
        unsigned int stat = 0;
        for (int j = 0; j < 4; ++j) {
            in.get(symbol);
            stat |= (unsigned char)symbol;
                        stat <<= 8;
        }
        stat >>= 8;
        orest[i] = new huffman_tree(NULL, NULL, stat, i);
    }

    huffman_tree * big_tree = make_huffman_tree(forest);
    string codes[256];
    string buff;
    way(big_tree, codes, buff);

    uncompress(big_tree, input, output, codes);

    out.close ();
    cout << "Uncompress is done\n";
    return 0;
}
*/

