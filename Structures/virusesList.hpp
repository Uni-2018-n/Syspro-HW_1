#ifndef _VIRUSESLIST_HPP_
#define _VIRUSESLIST_HPP_
#include <iostream>

#include "bloomFilter.hpp"
#include "skipList.hpp"
#include "../classes.hpp"
using namespace std;

class VirlistNode{
  string item;
  bloomFilter* bloom;
  skipHeader* vaccinated;
  skipHeader* notVaccinated;
  VirlistNode* next;
public:
  VirlistNode(string i, int l);
  ~VirlistNode();

  string getItem();
  bloomFilter* getBloom();
  skipHeader* getVacced();
  skipHeader* getNotVacced();
  VirlistNode* getNext();

  void setItem(string i);
  void setNext(VirlistNode* n);

  void insertRecord(int* id, citizenRecord* c, string v, string dv, bool flag);
};

class VirlistHeader{
  VirlistNode* start;
  VirlistNode* end;
  int bloom_len;
public:
  VirlistHeader(int);
  ~VirlistHeader();

  VirlistNode* insertVirus(string i);
  VirlistNode* searchVirus(string);
  void vaccineStatusBloom(int i, string v);
  void vaccineStatus(int i, string v);
  void vaccineStatus(int i);
  bool vaccinateNow(int i, string fn, string ln, string c, string a, string v);
  void listNonVaccinatedPersons(string v);

  void testPrint();
};

#endif
