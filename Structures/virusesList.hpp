#ifndef _VIRUSESLIST_HPP_
#define _VIRUSESLIST_HPP_
#include <iostream>

#include "bloomFilter.hpp"
#include "skipList.hpp"
#include "../classes.hpp"
using namespace std;

class VarlistNode{
  string item;
  bloomFilter* bloom;
  skipHeader* vaccinated;
  skipHeader* notVaccinated;
  VarlistNode* next;
public:
  VarlistNode(string i, int l);
  ~VarlistNode();

  string getItem();
  bloomFilter* getBloom();
  skipHeader* getVacced();
  skipHeader* getNotVacced();
  VarlistNode* getNext();

  void setItem(string i);
  void setNext(VarlistNode* n);

  void insertRecord(int* id, citizenRecord* c, string v, string dv, bool flag);
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
