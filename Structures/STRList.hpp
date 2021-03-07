#ifndef _STRLIST_HPP_
#define _STRLIST_HPP_

#include <iostream>
using namespace std;

class SlistNode{
public:
  string* item;
  SlistNode* next;

  SlistNode(string*);
  ~SlistNode();
};

class SlistHeader{
public:
  SlistNode* start;
  SlistNode* end;
  SlistHeader();
  ~SlistHeader();
  string* searchItem(string);
  void insertItem(string* i);
  void testPrint();
};
#endif
