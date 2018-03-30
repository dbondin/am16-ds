using namespace std;


int poww (int a, int b);

struct X  {
  int integ;
  char ch;
};

class Lexema {
public:
  struct X x;
  int flag; // 1 - int, 2 - char
  Lexema ();
  Lexema (const Lexema &l);
  int intD();
  int iDrop();
  char chDrop();
  void get(int i);
  void get(char charity);
};

class Stack {
  int size;
  Lexema *c;
public:
  Stack();
  Stack(const Stack &s);
  ~Stack();
  int showSize();
  void get(Lexema ch);
  Lexema push();
  int isEmpty();
};

int Operation (int &result, Lexema l, Stack &s);
int Calculation(Stack &s);

Stack InfixToPostfix(char *s);
