#ifndef _GENERALLIST_HPP_
#define _GENERALLIST_HPP_
#include <iostream>

#include "classes.hpp"
#include "Structures/countryList.hpp"
#include "Structures/virusesList.hpp"
#include "Structures/STRList.hpp"

using namespace std;

class listNode{
public:
  citizenRecord* citizen;
  SlistHeader* vaccs;
  listNode* next;
  listNode(citizenRecord*, string*);
  ~listNode();
};

class GlistHeader{
  listNode* start;
  listNode* end;
  ClistHeader* countries;
  VarlistHeader* viruses;
public:
  GlistHeader(int bloom);
  ~GlistHeader();
  listNode* searchCitizen(int);
  void insertRecord(string line);
  void testPrint();
};

#endif
