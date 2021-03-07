#ifndef _VIRUSESLIST_HPP_
#define _VIRUSESLIST_HPP_
#include <iostream>

using namespace std;

class VarlistNode{
public:
  string* item;
  //bloom
  //vaccinated skip list
  //not vaccinated skip list
  VarlistNode* next;
  VarlistNode(string* i);
  ~VarlistNode();
};

class VarlistHeader{
  VarlistNode* start;
  VarlistNode* end;
public:
  VarlistHeader();
  ~VarlistHeader();
  void insertVirus(string* i);
  void insertRecord();
  string* searchVirus(string);
  void testPrint();
};

#endif
