#ifndef _COUNTRYLIST_HPP_
#define _COUNTRYLIST_HPP_

#include <iostream>
using namespace std;

class ClistNode{
public:
  string* item;
  ClistNode* next;

  ClistNode(string*);
  ~ClistNode();
};

class ClistHeader{
public:
  ClistNode* start;
  ClistNode* end;
  ClistHeader();
  ~ClistHeader();
  string* searchItem(string);
  void insertItem(string* i);
  void testPrint();
};
#endif
