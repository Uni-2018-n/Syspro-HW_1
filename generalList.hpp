#ifndef _GENERALLIST_HPP_
#define _GENERALLIST_HPP_
#include <iostream>

#include "classes.hpp"
#include "Structures/countryList.hpp"
#include "Structures/virusesList.hpp"

using namespace std;

class listNode{
  citizenRecord* citizen;
  listNode* next;
public:
  listNode(citizenRecord*);
  ~listNode();

  citizenRecord* getCitizen();
  void setNext(listNode* n);
  listNode* getNext();
};

class GlistHeader{
  listNode* start;
  listNode* end;
  ClistHeader* countries;
  VirlistHeader* viruses;
public:
  GlistHeader(int bloom);
  ~GlistHeader();

  listNode* searchCitizen(int);
  void insertRecord(string line, bool flag);

  void vaccineStatusBloom(int i, string v);
  void vaccineStatus(int i, string v);
  void vaccineStatus(int i);

  void populationStatus(string vn, string don, string dt, string c, bool t);
  void populationStatus(string vn, string don, string dt, bool t);

  void vaccinateNow(int i, string fn, string ln, string c, string a, string v);
  void insertCitizenRecord(string line);
  void listNonVaccinatedPersons(string v);

  void testPrint();
};

#endif
