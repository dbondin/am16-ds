#include "lib.h"
#include <iostream>
using namespace std;

int main() {

  char in[64];
  Stack q;
  int result;
  cout<<"VVedite virazhenie, razresheno ispolzovat:\n";
  cout<<"+, -, *, /, ^, (, )\n";
  cin>>in;

  q = InfixToPostfix(in);

  result = Calculation(q);

  cout<< "ANSWER:   "<<result;
  return 0;
}
