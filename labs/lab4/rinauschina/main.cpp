#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int SYMBOLS = 256;

class treeNode{
	public:
		treeNode();
		treeNode(treeNode *leftChild, treeNode *rightChild, treeNode *parentNode, int wght, char c);
		~treeNode();
		int isLeaf();
		int weight();
		char value();
		treeNode *left();
		treeNode *right();
		treeNode *parent();
	private:
		int m_weight;
		char m_value;
		treeNode *m_left;
		treeNode *m_right;
		treeNode *m_parent;
};


treeNode::treeNode()
{
	m_weight = 0;
	m_value = 0;
	m_left = NULL;
	m_right = NULL;
	m_parent = NULL;
}

treeNode::treeNode(treeNode *leftChild, treeNode *rightChild, treeNode *parentNode, int wght, char c)
{
	m_weight = wght;
	m_value = c;
	m_left = leftChild;
	m_right = rightChild;
	m_parent = parentNode;
}

treeNode::~treeNode()
{
	if (m_left)	 delete m_left;
	if (m_right) delete m_right;
}

int treeNode::isLeaf()
{
	if (m_left || m_right)
		return 0;
	else
		return 1;
}

int treeNode::weight()
{
	return m_weight;
}

char treeNode::value()
{
	return m_value;
}

treeNode *treeNode::left()
{
	return m_left;
}

treeNode *treeNode::right()
{
	return m_right;
}

treeNode *treeNode::parent()
{
	return m_parent;
}

treeNode *merge(treeNode *left, treeNode *right)
{
	return new treeNode(left, right, NULL, left->weight() + right->weight(), 0);
}

int indexOFmin(treeNode **trees)
{
	int res = 0;
	int min_weight = -1;

	for (int i = 0;i < SYMBOLS;++i) 
	{
		if (trees[i])
			if ((trees[i]->weight() < min_weight) || (min_weight == -1))
			{
				res = i;
				min_weight = trees[res]->weight();
			}
	}
	return res;
}

treeNode *build_Huffman_tree(int *frequency)
{
	treeNode *trees[SYMBOLS] = {};

	for (int i = 0;i < SYMBOLS;i++)
		trees[i] = new treeNode(NULL, NULL, NULL, frequency[i],(char)i);
	
	int min_index = 0;

	for (int j = 0; j < SYMBOLS - 1; j++) 
	{
		min_index = indexOFmin(trees);
		treeNode * firstMinTree = trees[min_index];

		for (int i = min_index; i < SYMBOLS - 1; ++i) 
			trees[i] = trees[i + 1];

		trees[SYMBOLS - 1] = NULL;
		min_index = indexOFmin(trees);
		treeNode *secondMinTree = trees[min_index];

		for (int i = min_index; i < SYMBOLS - 1; ++i) 
			trees[i] = trees[i + 1];

		trees[SYMBOLS - 1] = merge(firstMinTree, secondMinTree);	
	}
	return trees[SYMBOLS - 1];
}

void createCodes(treeNode *HuffmanTreeNode, string *codes, string symbolCode = "")
{
	if (HuffmanTreeNode->isLeaf())
	{
		codes[(unsigned char)HuffmanTreeNode->value()] = symbolCode;
	} else 
	{
		if (HuffmanTreeNode->left())
		{
			symbolCode += "0";
			createCodes(HuffmanTreeNode->left(), codes, symbolCode);
			symbolCode.pop_back();
		}
		if (HuffmanTreeNode->right())
		{
			symbolCode += "1";
			createCodes(HuffmanTreeNode->right(), codes, symbolCode);
			symbolCode.pop_back();
		}
	}
}

void writeSymbol(ofstream &out, string & readyFORoutput, string symbolCode)
{
	readyFORoutput += symbolCode;

	if (readyFORoutput.length() < 8) return;

	int bytesTOoutput = readyFORoutput.length() / 8;
	for (int i = 0;i < bytesTOoutput;i++) 
	{	
		readyFORoutput[0] -= '0';
		for (int j = 1;j < 8;j++)
			readyFORoutput[j] = (readyFORoutput[j - 1] << 1) | (readyFORoutput[j] - '0');
		out.put(readyFORoutput[7]);
		
		readyFORoutput.erase(0, 8);
	}
}

treeNode *uncodeSymbol(treeNode *HuffmanTreeNode, string code)
{
	if (HuffmanTreeNode->isLeaf()) 
	{
		return HuffmanTreeNode;
	} else if (code.length() == 0) 
	{
		return NULL;
	} else if (code[0] == '0')
	{
		if (HuffmanTreeNode->left()) 
		{
			code.erase(0, 1);
			return uncodeSymbol(HuffmanTreeNode->left (), code);
		} else
		{
			return NULL;
		}
	} else
	{
		if (HuffmanTreeNode->right()) 
		{
			code.erase(0, 1);
			return uncodeSymbol(HuffmanTreeNode->right(), code);
		} else
		{
			return NULL;
		}
	}
}

string readByte(ifstream &in)
{
	char c;
	in.get(c);
	
	string res;

	for (int i = 0;i < 8;i++)
	{
		if (c & 128)
			res += '1';
		else
			res += '0';
		c <<= 1;
	}
	return res;
}

void uncodeText(ifstream &in, ofstream &out, treeNode *HuffmanTree, std::string *codes)
{
	int sizeRemaining = HuffmanTree->weight();
	string toBeOut;
	string temp;
	while((temp = readByte(in)).length() > 0) {
		if (sizeRemaining == 0) break;

		toBeOut += temp;
		while (treeNode *symbol = uncodeSymbol(HuffmanTree, toBeOut))
		{		
			out << symbol->value();
			--sizeRemaining;
			toBeOut.erase(0, codes[(unsigned char)symbol->value()].length());
			if (sizeRemaining == 0) 
				break;
		}
	}
}

void packMode(string inputFilename, string outputFilename)
{
	ifstream in ( inputFilename.data(), ifstream::binary);
	ofstream out(outputFilename.data(), ofstream::binary);
	int frequency[SYMBOLS] = {};
	char c;

	while(in.get(c)) 
		++frequency[(unsigned char)c];

	treeNode *HuffmanTree = build_Huffman_tree(frequency);
	string codes[SYMBOLS] = {};
	createCodes(HuffmanTree, codes);

	in.close();

	out << "HF16";
	for (int i = 0;i < 256;++i) {
		unsigned int freq = (unsigned int)frequency[i];
		for (int j = 0;j < 4; j++)
			out.put ((char)(unsigned char)(freq & (0xFF << 8*(3-j))) >> 8*(3-j));
	}

	in.open(inputFilename.data(), std::ifstream::binary);

	string toBeOut;
	while(in.get(c)) 
		writeSymbol(out, toBeOut, codes[(unsigned char)c]); //читаем и пихаем

	in.close();

	while(toBeOut.length() % 8 != 0) 
		toBeOut += "0";
	writeSymbol(out, toBeOut, "");

	out.close();
}

void unpackMode(string inputFilename, string outputFilename)
{
	ifstream in ( inputFilename.data(), ifstream::binary);
	ofstream out(outputFilename.data(), ofstream::binary);

	char c;
	for (int i = 0;i < 4;i++)
	{
		in.get(c);
		if (c != "HF16"[i]) return;
	}

	int frequency[SYMBOLS] = {};
	for (int i = 0;i < SYMBOLS;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			in.get(c);
			frequency[i] = (frequency[i] << 8) | (unsigned char)c;
		}
	}
	treeNode *HuffmanTree = build_Huffman_tree(frequency);
	string codes[SYMBOLS] = {};
	createCodes(HuffmanTree, codes);

	uncodeText(in, out, HuffmanTree, codes);

	in.close();
	out.close();
}

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		cout << "You need to enter mode(-pack or -unpack) and input file and output file names" << endl;
		return 1;
	}
	string mode = argv[1];
	string inputFilename = argv[2];
	string outputFilename = argv[3];

	if (0) 
	{
	} else if (mode == "-pack")
	{
		packMode(inputFilename, outputFilename);
	} else if (mode == "-unpack")
	{
		unpackMode(inputFilename, outputFilename);
	} else
	{
		cout << "Wrong mode. You need to enter mode(-pack or -unpack) and input file and output file names" << endl;
		return 1;
	}
	return 0;
}