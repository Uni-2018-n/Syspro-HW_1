#include <iostream>
#include <time.h>
#include "skipList.hpp"

int main(){
  srand(time(NULL));
  listHeader* t = new listHeader();
  int numa= 15;
  t->insertItemTemp(&numa);
  int numb= 20;
  t->insertItemTemp(&numb);
  int numc= 18;
  t->insertItemTemp(&numc);
  int numd= 8;
  t->insertItemTemp(&numd);
  int nume= 5;
  t->insertItemTemp(&nume);
  int numf= 22;
  t->insertItemTemp(&numf);
  int numg= 10;
  t->insertItemTemp(&numg);
  int numh= 2;
  t->insertItemTemp(&numh);
  int numi= 40;
  t->insertItemTemp(&numi);
  int numj= 14;
  t->insertItemTemp(&numj);

  skipHeader* s= new skipHeader(t);
  s->testPrint();

  std::cout << "3: ";
  if(s->searchItem(3)){
    std::cout << "FOUND" << std::endl;
  }else{
    std::cout << "NOT FOUND" << std::endl;
  }
  std::cout << "10: ";
  if(s->searchItem(10)){
    std::cout << "FOUND" << std::endl;
  }else{
    std::cout << "NOT FOUND" << std::endl;
  }
  std::cout << "14: ";
  if(s->searchItem(14)){
    std::cout << "FOUND" << std::endl;
  }else{
    std::cout << "NOT FOUND" << std::endl;
  }
  std::cout << "17: ";
  if(s->searchItem(17)){
    std::cout << "FOUND" << std::endl;
  }else{
    std::cout << "NOT FOUND" << std::endl;
  }
  std::cout << "40: ";
  if(s->searchItem(40)){
    std::cout << "FOUND" << std::endl;
  }else{
    std::cout << "NOT FOUND" << std::endl;
  }
  std::cout << "41: ";
  if(s->searchItem(41)){
    std::cout << "FOUND" << std::endl;
  }else{
    std::cout << "NOT FOUND" << std::endl;
  }

  std::cout << "INSERTS: " << std::endl;
  std::cout << "0" << std::endl;
  int numk = 0;
  if(s->insertItem(&numk)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();

  std::cout << "12" << std::endl;
  int numl = 12;
  if(s->insertItem(&numl)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();

  std::cout << "41" << std::endl;
  int numm = 41;
  if(s->insertItem(&numm)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();

  std::cout << "0" << std::endl;
  int numn = 0;
  if(s->insertItem(&numn)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();

  std::cout << "14" << std::endl;
  int numo = 14;
  if(s->insertItem(&numo)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();

  std::cout << "41" << std::endl;
  int nump = 41;
  if(s->insertItem(&nump)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();

  std::cout << "0: ";
  if(s->searchItem(0)){
    std::cout << "FOUND" << std::endl;
  }else{
    std::cout << "NOT FOUND" << std::endl;
  }
  std::cout << "41: ";
  if(s->searchItem(0)){
    std::cout << "FOUND" << std::endl;
  }else{
    std::cout << "NOT FOUND" << std::endl;
  }

  delete s;
	return 0;
}
