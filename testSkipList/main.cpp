#include <iostream>
#include <time.h>
#include "skipList.hpp"

int main(){
  srand(time(NULL));
  listHeader* t = new listHeader();
  int numa= 5;
  t->insertItem(&numa);
  int numb= 6;
  t->insertItem(&numb);
  int numc= 8;
  t->insertItem(&numc);
  int numd= 2;
  t->insertItem(&numd);
  int nume= 1;
  t->insertItem(&nume);
  int numf= 22;
  t->insertItem(&numf);
  int numg= 0;
  t->insertItem(&numg);
  int numh= 3;
  t->insertItem(&numh);
  int numi= 40;
  t->insertItem(&numi);
  int numj= 4;
  t->insertItem(&numj);

  skipHeader* s= new skipHeader(t);
  s->testPrint();

  for(int i=0;i<10;i++){
    int t= rand() % 41 +0;
    std::cout << t << std::endl;
    s->searchItem(t);
  }
  // s->searchItem(8);

  delete s;
	return 0;
}
