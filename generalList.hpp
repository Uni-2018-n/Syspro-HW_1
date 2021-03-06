#ifndef _GENERALLIST_HPP_
#define _GENERALLIST_HPP_
#include <iostream>

#include "classes.hpp"
#include "Structures/vacList.hpp"

using namespace std;

class listNode{
public:
  citizenRecord* citizen;
  VlistHeader* vaccs;
  listNode* next;
  listNode(citizenRecord*, vaccinateRecord*);
  ~listNode();
};

class GlistHeader{
  listNode* start;
  listNode* end;
public:
  GlistHeader();
  ~GlistHeader();
  listNode* searchCitizen(int);
  void insertRecord(string line);
  //get string with line, search with citizen ID,
  //if not exists return NULL, if exists return
  //the node with the record, check if already vaccinated or not,
  // make new record, add it next to the found record....
  void testPrint();
};

#endif
