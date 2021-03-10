#ifndef _VIRUSESLIST_HPP_
#define _VIRUSESLIST_HPP_
#include <iostream>

#include "bloomFilter.hpp"
#include "skipList.hpp"
#include "../classes.hpp"
using namespace std;

class VarlistNode{
public:
  string item;
  bloomFilter* bloom;
  skipHeader* vaccinated;
  skipHeader* notVaccinated;
  VarlistNode* next;
  VarlistNode(string i, int l);
  ~VarlistNode();
  void insertRecord(int* id, citizenRecord* c, string v, string dv);
};

class VarlistHeader{
  VarlistNode* start;
  VarlistNode* end;
  int bloom_len;
public:
  VarlistHeader(int);
  ~VarlistHeader();
  VarlistNode* insertVirus(string i);
  VarlistNode* searchVirus(string);
  void vaccineStatusBloom(int i, string v);
  void vaccineStatus(int i, string v);
  void vaccineStatus(int i);
  bool vaccinateNow(int i, string fn, string ln, string c, string a, string v);
  void listNonVaccinatedPersons(string v);
  void testPrint();
};

#endif
