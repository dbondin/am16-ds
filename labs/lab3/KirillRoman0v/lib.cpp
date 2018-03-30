#include "lib.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Lexema::Lexema() {
  flag = 1;
  x.integ = 0;
  x.ch = '0';
}

Lexema::Lexema(const Lexema &l) {
  if (flag == 1) {
    x.integ = l.x.integ;
  } else if (flag == 2) {
    x.ch = l.x.ch;
  }
  flag = l.flag;
}

int Lexema::intD() {
  if (flag == 1) {
    return 1;
  } else if (flag == 2) {
    return 0;
  } else return 2;
}

int Lexema::iDrop() {
  return x.integ;
}

char Lexema::chDrop() {
  return x.ch;
}

void Lexema::get (int i) {
  x.integ = i;
  flag = 1;
}

void Lexema::get (char charity) {
  x.ch = charity;
  flag = 2;
}

Stack::Stack() {
  size = 0;

}

Stack::Stack(const Stack &s) {
  size = s.size;
  c = new Lexema[size];
  for (int i=0; i<size; i++) {
    c[i]=s.c[i];
  }
}

int Stack::isEmpty() {
  if (size == 0) {
    return 1;
  } else {
    return 0;
  }
}

int Stack::showSize(){
  return size;
}

Lexema Stack::push() {
  Lexema ch = c[size];
  Lexema *buf;
  size--;
  buf = new Lexema[size];
  for (int i=0; i<size; i++){
    buf[i] = c[i];
  }
  c = new Lexema[size];
  for (int i=0; i<size; i++) {
    c[i] = buf[i];
  }
  delete[] buf;
  return ch;
}

void Stack::get(Lexema ch) {
  size++;
  Lexema *buf;
  buf = new Lexema[size-1];
  for (int i=0; i<(size-1); i++) {
    buf[i] = c[i];
  }
  c = new Lexema[size];
  for (int i=0; i<(size-1); i++) {
    c[i] = buf[i];
  }
  c[size-1] = ch;
  delete[] buf;
}

Stack::~Stack() {
  if(size) {
    delete[] c;
  }
}
