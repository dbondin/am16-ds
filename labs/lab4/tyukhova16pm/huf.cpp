#include "huf.h"
#include  <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node
{
    uint8_t symbol;
    uint32_t frequency;
    Node * left;
    Node * right;

    explicit Node(uint32_t symbol = 0, uint32_t freq = 0): symbol(symbol), frequency(freq), left(nullptr), right(nullptr)
    { }

    Node(Node * leftptr, Node * rightptr): symbol(max(leftptr->symbol, rightptr->symbol)), frequency(leftptr->frequency + rightptr->frequency), left(leftptr), right(rightptr)
    { }

    ~Node()
    {
        delete left;
        delete right;
    }
};

map<uint8_t, uint32_t> count_frequences(const vector<uint8_t> & text)
{
    map<uint8_t, uint32_t> char_frequencies;
    for (auto c : text)
    {
        char_frequencies[c]++;
    }
    return char_frequencies;
}

void   VspomTree(Node * root, vector<bool> &code, map<uint8_t, vector<bool>> & table)
{
    if (root->left != nullptr)
    {
        code.push_back(1);
        VspomTree(root->left, code, table);
    }
    if (root->right != nullptr)
    {
        code.push_back(0);
        VspomTree(root->right, code, table);
    }
    if (root->left == nullptr && root->right == nullptr)
    {
        if (code.empty())
        {
            table[root->symbol].push_back(1);
        }
        else
        {
            table[root->symbol] = code;
        }
    }
    code.pop_back();
}

struct compare
{
    bool operator()(const Node * a, const Node * b) const
    {
        if (a->frequency > b->frequency)
            return true;
        else if (a->frequency == b->frequency)
        {
            return (a->symbol > b->symbol);
        }
        return false;
    }
};


Node * Make_Huffman_Tree(const vector<uint8_t> & chars, const vector<uint32_t> & freqs)
{
    priority_queue <Node *, vector<Node*>, compare> frequencies;
    for (size_t i = 0; i < chars.size(); ++i)
    {
        frequencies.push(new Node(chars[i], freqs[i]));
    }
    while(frequencies.size() > 1)
    {
        Node * first = frequencies.top();
        frequencies.pop();
        Node * second = frequencies.top();
        frequencies.pop();
        Node * parrent = new Node(first, second);
        frequencies.push(parrent);
    }
    return frequencies.top();
}


string vector_bool_to_binary_string(const vector<bool> & code)
{
    string s;
    uint32_t size = code.size();
    for (size_t j = 0; j < size; ++j)
    {
        if (code[j])
        {
            s += '1';
        }
        else
        {
            s += '0';
        }
    }
    return s;
}


map<uint8_t, vector<bool>> Make_Table(Node * Head)
{
    map<uint8_t, vector<bool>> result;
    vector<bool> code;
    VspomTree(Head, code, result);
    return result;
}

string decode(const string &text, Node * head)
{
    string result;
    Node * root = head;
    if (root->left == nullptr && root->right == nullptr)
    {
        string s(text.length(), root->symbol);
        return s;
    }
    size_t size = text.length();
    for (size_t i = 0; i < size; ++i)
    {
        if (text[i] == '1')
        {
            root = root->left;
        }
        else if (text[i] == '0')
        {
            root = root->right;
        }
        if (root->left == nullptr && root->right == nullptr)
        {
            result += root->symbol;
            root = head;
        }
    }
    return result;
}


string uint8_to_binary_string(uint8_t x)
{
    string s;
    for (uint32_t i = 0; i < 8; ++i)
    {
        s += ((x & (1 << 7))) ? '1' : '0';
        x = x << 1;
    }
    return s;
}


string vector_to_binary_string(const vector<uint8_t> & numbers)
{
    string s;
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        s += uint8_to_binary_string(numbers[i]);
    }
    return s;
}


bool file_empty_check (ifstream & fin)
{
    fin.seekg (0, ios::end);
    uint32_t length = fin.tellg();
    fin.seekg (0, fin.beg);
    if (length == 0)
    {
        cout << 0 <<endl;
        cout << 0 <<endl;
        cout << 0 <<endl;
        return 1;
    }
    else
        return 0;
}


bool compress (const char * file_nameIN, const char * file_nameOUT)
{

    ifstream fin(file_nameIN,   ios_base::binary);
    if (!fin)
    {
        cerr<< "File canr be read" << file_nameIN << "\"" <<endl;
        return 1;
    }

    ofstream fout(file_nameOUT,   ios_base::binary);
    if (!fout)
    {
        cerr << "File cant be read \"" << file_nameOUT << "\"" <<endl;
        return 1;
    }

    if (file_empty_check(fin))
    {
        return 0;
    }

    fin.seekg (0, ios::end);
    uint32_t length = fin.tellg();
    fin.seekg (0,ios::beg);

    vector<uint8_t> text(length);
    char c;

    for (size_t i = 0; i < length; ++i)
    {
        if (fin.get(c))
        {
            text[i] = c;
        }
    }


    const   map<uint8_t, uint32_t> char_frequencies = count_frequences(text);
    uint32_t L = char_frequencies.size();
    vector<uint8_t> chars;
    vector<uint32_t> freqs;
    for (auto c : char_frequencies)
    {
        chars.push_back(c.first);
        freqs.push_back(c.second);
    }
    fout.write(reinterpret_cast<const char *> (&L), sizeof(uint32_t));
    fout.write(reinterpret_cast<const char *> (&chars[0]), L * sizeof(uint8_t));
    fout.write(reinterpret_cast<const char *> (&freqs[0]), L * sizeof(uint32_t));

    Node * Head = Make_Huffman_Tree(chars, freqs);
    map <uint8_t,   vector<bool>> huffman_encoding = Make_Table(Head);
    delete Head;

    vector<bool> encoded(text.size() * 8);
    uint32_t k = 0;
    for (size_t i = 0; i < text.size() ; ++i)
    {
        vector<bool> code = huffman_encoding[text[i]];
        for (size_t j = 0; j < code.size(); ++j)
        {
            encoded[k++] = code[j];
        }
    }
    uint32_t Len_Enc_Text = k;
    if (k % 8)
    {
        k += 8 - (k % 8);
    }
    encoded.resize(k);

    uint32_t n = k / 8;
    vector<uint8_t> numbers(n);
    for (uint32_t i = 0; i < n; ++i)
    {
        uint8_t x = 0;
        for (uint32_t j = 0; j < 8; ++j)
        {
            if (encoded[8 * i + j])
            {
                x += 1 << (7 - j);
            }
        }
        numbers[i] = x;
    }

    //16 am
    ofstream out;
    out.open(file_nameOUT);//, ios_base::binary);
    out<<"HF16"<<endl;

    fout.write(reinterpret_cast<const char *> (&Len_Enc_Text), sizeof(uint32_t));
    fout.write(reinterpret_cast<const char *> (&numbers[0]), numbers.size() * sizeof(uint8_t));

    //show anorher BYTES the dust, razmer ishodnogo, svernutogo, tablici
    cout << text.size() <<endl;
    cout << numbers.size() <<endl;
    cout << char_frequencies.size() * (sizeof(uint8_t) + sizeof(uint32_t)) + 2 * sizeof(uint32_t) <<endl;
    return 0;
}


bool decompress (const char * file_nameIN, const char * file_nameOUT)
{

    ifstream fin(file_nameIN,   ios_base::binary);
    if (!fin)
    {
        cerr<< "Cannot read file \"" << file_nameIN << "\"" <<endl;
        return 1;
    }

    ofstream fout(file_nameOUT,   ios_base::binary);
    if (!fout)
    {
        cerr<< "Cannot open file \"" << file_nameOUT << "\"" <<endl;
        return 1;
    }

    if (file_empty_check(fin))
    {
        return 0;
    }

    map<uint8_t, uint32_t> char_frequences2;
    uint32_t size2 = 0;
    fin.read(reinterpret_cast<char *> (&size2), sizeof(uint32_t));
    vector<uint8_t> chars2 (size2);
    vector<uint32_t> freqs2 (size2);

    fin.read (reinterpret_cast<char *> (&chars2[0]), size2 * sizeof(uint8_t));
    fin.read (reinterpret_cast<char *> (&freqs2[0]), size2 * sizeof(uint32_t));
    for (uint32_t i = 0; i < size2; ++i)
    {
        char_frequences2[chars2[i]] = freqs2[i];
    }

    uint32_t numb_size = 0;
    fin.read(reinterpret_cast<char *> (&numb_size), sizeof(uint32_t));
    uint32_t n = numb_size / 8;
    if (numb_size % 8)
        ++n;
    vector<uint8_t> numbers2(n);
    fin.read(reinterpret_cast<char *> (&numbers2[0]), n * sizeof(uint8_t));
    string encoded_text2 = vector_to_binary_string(numbers2);
    uint32_t to_cut = n * 8 - numb_size;
    encoded_text2.erase (encoded_text2.end() - to_cut, encoded_text2.end());


    Node * Head = Make_Huffman_Tree(chars2, freqs2);
    string ans = decode(encoded_text2, Head);

    delete Head;


    fout.write(reinterpret_cast<const char *> (&ans[0]), ans.length() * sizeof(uint8_t));

    cout << n << endl;
    cout << ans.length() <<endl;
    cout << size2 * (sizeof(uint8_t) + sizeof(uint32_t)) + 2 * sizeof(uint32_t) <<endl;
    return 0;
}
