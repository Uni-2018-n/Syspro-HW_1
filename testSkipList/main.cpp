#include <iostream>
#include <time.h>
#include "skipList.hpp"

int main(){
  srand(time(NULL));
	listHeader* t = new listHeader();
  int* num = new int(5);
  t->insertItem(num);
  num = new int(2);
  t->insertItem(num);
  num = new int(7);
  t->insertItem(num);
  num = new int(1);
  t->insertItem(num);
  num = new int(4);
  t->insertItem(num);
  num = new int(6);
  t->insertItem(num);
  num = new int(20);
  t->insertItem(num);
  num = new int(22);
  t->insertItem(num);
  num = new int(3);
  t->insertItem(num);
  num = new int(0);
  t->insertItem(num);

  skipHeader* s= new skipHeader(t);
  s->testPrint();
  delete s;
	return 0;
}
