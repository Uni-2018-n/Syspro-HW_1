#ifndef _SKIPLIST_HPP_
#define _SKIPLIST_HPP_

#include <iostream>
#include "../classes.hpp"
using namespace std;

#define MAXIMUM 3

class SkiplistNode{//nodes
  int* item;//id TODO use citizens id not diffrent variable
  citizenRecord* citizen;
  string* date_vaccinated;
  SkiplistNode* next;
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
  SkiplistNode* getNext(){
    return next;
  }
  void setNext(SkiplistNode* n){
    next = n;
  }
  SkiplistNode* getLowerLevel(){
    return lower_level;
  }

  void print();
  void testPrint();
};

class SkiplistHeader{//list
  SkiplistNode* start;
  int pl;
public:
  SkiplistHeader();
  ~SkiplistHeader();
  SkiplistNode* insertAtStart(SkiplistNode* i);
  SkiplistNode* insertItem(int* i, citizenRecord* c, string* dv, int top_lvl);
  SkiplistNode* searchItem(int i);

  int getPl(){
    return pl;
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
  void print();
  void testPrint();
};
#endif
