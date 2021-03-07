#ifndef _VIRUSESLIST_HPP_
#define _VIRUSESLIST_HPP_
#include <iostream>

#include "bloomFilter.hpp"

using namespace std;

class VarlistNode{
public:
  string item;
  bloomFilter* bloom;
  //vaccinated skip list
  //not vaccinated skip list
  VarlistNode* next;
  VarlistNode(string i, int l);
  ~VarlistNode();
  void insertRecord(int* id, string v, string dv);
};

class VarlistHeader{
  VarlistNode* start;
  VarlistNode* end;
  int bloom_len;//TODO: make this without dublicates
public:
  VarlistHeader(int);
  ~VarlistHeader();
  VarlistNode* insertVirus(string i);
  VarlistNode* searchVirus(string);
  void testPrint();
};

#endif
