#ifndef _SKIPLIST_HPP_
#define _SKIPLIST_HPP_

#include <iostream>
// #include "../classes.hpp"
using namespace std;

#define MAXIMUM 3

class citizenRecord {
public:
  void print(){

  }
};


class SkiplistNode{//nodes
  int* item;//id TODO use citizens id not diffrent variable
  citizenRecord* citizen;
  string* date_vaccinated;
  SkiplistNode* next;
  SkiplistNode* prev;
  SkiplistNode* lower_level;
public:
  SkiplistNode(int* i, citizenRecord* c, string* dv);
  SkiplistNode(SkiplistNode* i);
  SkiplistNode(SkiplistNode* i, SkiplistNode* n);
  SkiplistNode(int* i, citizenRecord* c, string* dv, SkiplistNode* n);
  ~SkiplistNode();

  int getItem(){
    return *item;
  }
  citizenRecord* getCitizen(){
    return citizen;
  }
  SkiplistNode* getNext(){
    return next;
  }
  void setNext(SkiplistNode* n){
    next = n;
  }
  SkiplistNode* getLowerLevel(){
    return lower_level;
  }
  void setPrev(SkiplistNode* p){
    prev = p;
  }
  SkiplistNode* getPrev(){
    return prev;
  }

  void print();
  void testPrint();
};

class SkiplistHeader{//list
  SkiplistNode* start;
public:
  SkiplistHeader();
  ~SkiplistHeader();
  SkiplistNode* insertAtStart(SkiplistNode* i);
  SkiplistNode* insertItem(int* i, citizenRecord* c, string* dv, int top_lvl);
  SkiplistNode* searchItem(int i);
  SkiplistNode* deleteItem(int i);
  SkiplistNode* getFirst(){
    return start;
  }
  void removeFirst(){
    SkiplistNode* temp = start->getNext();
    if(start != NULL && start->getLowerLevel() != NULL){
      delete start;
    }
    start= temp;
    if(start != NULL){
      start->setPrev(NULL);
    }
  }
  void print();
  void testPrint();
};
/////////////////////////////////////
class skipNode{//nodes of lists
  SkiplistHeader* item;
  skipNode* prev;
  skipNode* next;
public:
  skipNode();
  ~skipNode();
  SkiplistNode* insertAtStart(SkiplistNode* i);

  skipNode* getNext(){
    return next;
  }
  skipNode* getPrev(){
    return prev;
  }
  SkiplistHeader* getItem(){
    return item;
  }
  void setNext(skipNode* n){
    next = n;
  }
  void setPrev(skipNode* p){
    prev = p;
  }

  void removeFirst(){
    item->removeFirst();
  }

  void print();
  void testPrint();
};

class skipHeader{//list of lists
  skipNode* start;
  skipNode* end;
  int lvlnum;
  int max_lvl;
  void addLayer();
public:
  skipHeader();
  ~skipHeader();
  bool searchItem(int i);
  bool insertItem(int* i, citizenRecord* c, string* dv);
  SkiplistNode* deleteItem(int i);
  void print();
  void testPrint();
};
#endif
