#include <iostream>
#include <time.h>
#include "skipList.hpp"

int main(){
  srand(time(NULL));
  listHeader* t = new listHeader();
  int numa= 5;
  t->insertItemTemp(&numa);
  int numb= 6;
  t->insertItemTemp(&numb);
  int numc= 8;
  t->insertItemTemp(&numc);
  int numd= 2;
  t->insertItemTemp(&numd);
  int nume= 1;
  t->insertItemTemp(&nume);
  int numf= 22;
  t->insertItemTemp(&numf);
  int numg= 0;
  t->insertItemTemp(&numg);
  int numh= 3;
  t->insertItemTemp(&numh);
  int numi= 40;
  t->insertItemTemp(&numi);
  int numj= 4;
  t->insertItemTemp(&numj);

  skipHeader* s= new skipHeader(t);
  s->testPrint();

  for(int i=0;i<10;i++){
    int t= rand() % 41 +0;
    std::cout << t << std::endl;
    s->searchItem(t);
  }

  std::cout << "INSERTS: " << std::endl;
  int numk = 10;
  if(s->insertItem(&numk)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();

  s->searchItem(10);

  delete s;
	return 0;
}
