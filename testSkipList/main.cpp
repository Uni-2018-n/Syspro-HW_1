#include <iostream>
#include <time.h>
#include "skipList.hpp"

int main(){
  srand(time(NULL));
	listHeader* t = new listHeader();
  t->insertItem(5);
  t->insertItem(2);
  t->insertItem(7);
  t->insertItem(1);
  t->insertItem(4);
  t->insertItem(6);
  t->insertItem(20);
  t->insertItem(22);
  t->insertItem(3);
  t->insertItem(0);

  skipHeader s(t);
  s.testPrint();
	return 0;
}
