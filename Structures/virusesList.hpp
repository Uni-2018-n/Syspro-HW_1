#ifndef _VIRUSESLIST_HPP_
#define _VIRUSESLIST_HPP_
#include <iostream>

#include "bloomFilter.hpp"

using namespace std;

class VarlistNode{
public:
  string* item;
  bloomFilter* bloom;
  //vaccinated skip list
  //not vaccinated skip list
  VarlistNode* next;
  VarlistNode(string* i, int l);
  ~VarlistNode();
  void insertRecord();
};

class VarlistHeader{
  VarlistNode* start;
  VarlistNode* end;
  int bloom_len;//TODO: make this without dublicates
public:
  VarlistHeader(int);
  ~VarlistHeader();
  void insertVirus(string* i);
  string* searchVirus(string);
  void testPrint();
};

#endif
