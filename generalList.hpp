#ifndef _GENERALLIST_HPP_
#define _GENERALLIST_HPP_
#include <iostream>

#include "classes.hpp"
#include "Structures/countryList.hpp"
#include "Structures/virusesList.hpp"

using namespace std;

class listNode{
public:
  citizenRecord* citizen;
  listNode* next;
  listNode(citizenRecord*);
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
  void vaccineStatusBloom(int i, string v);
  void vaccineStatus(int i, string v);
  void vaccineStatus(int i);
  void insertCitizenRecord(string line);
  void listNonVaccinatedPersons(string v);
  void testPrint();
};

#endif
