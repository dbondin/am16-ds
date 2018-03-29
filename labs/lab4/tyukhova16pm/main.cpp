#include "huf.h"
#include <iostream>

using namespace std;

const string comp = "-c";
const string decomp = "-u";
const string f = "-f";
const string o = "-o";
const string f1 = "--file";
const string o1 = "--output";

int main(int argc, char ** arg)
{

    char * file_nameIN = nullptr;
    char * file_nameOUT = nullptr;


    if (argc == 1)
    {
        cerr << "Pls type some arg&flags"<<endl;
        return 0;
    }

    if (arg[1] != comp && arg[1] != decomp)
    {
        std::cerr << "I dont know wha u want from me sry ;c ) \"" << arg[1] << "\"" << endl;
        return 1;
    }
    else if (arg[1] == comp)
    {
        if (arg[2] != f && arg[2] != f1)
        {
            std::cerr << "Type flag \"-f\" instead of \"" << arg[2] << "\" before filename to  compress" << endl;
            return 1;
        }
        file_nameIN = arg[3];
        if (arg[4] != o && arg[4] != o1)
        {
            std::cerr << "Type flag \"-o\"  instead of \"" << arg[4] << "\" before final filename" << endl;
            return 1;
        }
        file_nameOUT = arg[5];
    }
    else if (arg[1] == decomp)
    {
        if (arg[2] != f && arg[2] != f1)
        {
            std::cerr << "Type flag \"-f\"  instead of \"" << arg[2] << "\" before filename to  decompress" << endl;
            return 1;
        }
        file_nameIN = arg[3];
        if (arg[4] != o && arg[4] != o1)
        {
            std::cerr << "Type flag \"-o\"  instead of \"" << arg[4] << "\" before final filename" << endl;
            return 1;
        }
        file_nameOUT = arg[5];
    }

    if (arg[1] == comp)
    {
        if (compress(file_nameIN, file_nameOUT))
        {
            return 1;
        }
    }

    if (arg[1] == decomp)

    {
        if (decompress(file_nameIN, file_nameOUT))
        {
            return 1;
        }
    }

    return 0;
}
