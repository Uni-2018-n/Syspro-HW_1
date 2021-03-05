#include <iostream>
#include <time.h>
#include "../Structures/skipList.hpp"

int main(){
  srand(time(NULL));
  skipHeader* s= new skipHeader();

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
  std::cout << "0:" << std::endl;
  int numk = 0;
  if(s->insertItem(&numk)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();
  std::cout << ":/" << std::endl;

  std::cout << "12:" << std::endl;
  int numl = 12;
  if(s->insertItem(&numl)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();
  std::cout << ":/" << std::endl;

  std::cout << "41:" << std::endl;
  int numm = 41;
  if(s->insertItem(&numm)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();
  std::cout << ":/" << std::endl;

  std::cout << "0:" << std::endl;
  int numn = 0;
  if(s->insertItem(&numn)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();
  std::cout << ":/" << std::endl;

  std::cout << "14:" << std::endl;
  int numo = 14;
  if(s->insertItem(&numo)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();
  std::cout << ":/" << std::endl;

  std::cout << "41:" << std::endl;
  int nump = 41;
  if(s->insertItem(&nump)){
    std::cout << "inserted!" << std::endl;
  }else{
    std::cout << "already exists!" << std::endl;
  }
  s->testPrint();
  std::cout << ":/" << std::endl;

  std::cout << "0: ";
  if(s->searchItem(0)){
    std::cout << "FOUND" << std::endl;
  }else{
    std::cout << "NOT FOUND" << std::endl;
  }
  std::cout << "15: ";
  if(s->searchItem(15)){
    std::cout << "FOUND" << std::endl;
  }else{
    std::cout << "NOT FOUND" << std::endl;
  }

  delete s;
	return 0;
}
