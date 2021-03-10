#ifndef _SKIPLIST_HPP_
#define _SKIPLIST_HPP_

#include <iostream>
#include "../classes.hpp"
#include "populationStatistics.hpp"
using namespace std;

#define MAXIMUM 3


class SkiplistNode{//nodes
  int* item;
  citizenRecord* citizen;
  string* date_vaccinated;
  SkiplistNode* next;
  SkiplistNode* prev;
  SkiplistNode* lower_level;
public:
  SkiplistNode(int* i, citizenRecord* c, string* dv);
  SkiplistNode(SkiplistNode* i);
  SkiplistNode(SkiplistNode* i, SkiplistNode* n);
  SkiplistNode(int* i, citizenRecord* c, string* dv, SkiplistNode* n);
  ~SkiplistNode();

  int getItem();
  citizenRecord* getCitizen();
  string getDateVaccinated();
  SkiplistNode* getNext();
  SkiplistNode* getPrev();
  SkiplistNode* getLowerLevel();
  void setNext(SkiplistNode* n);
  void setPrev(SkiplistNode* p);

  void print();
  void testPrint();
};

class SkiplistHeader{//list
  SkiplistNode* start;
public:
  SkiplistHeader();
  ~SkiplistHeader();
  SkiplistNode* insertAtStart(SkiplistNode* i);
  SkiplistNode* insertItem(int* i, citizenRecord* c, string* dv, int top_lvl);
  SkiplistNode* searchItem(int i);
  SkiplistNode* deleteItem(int i);

  SkiplistNode* getFirst();
  void removeFirst();
  void print();

  void testPrint();
};
/////////////////////////////////////
class skipNode{//nodes of lists
  SkiplistHeader* item;
  skipNode* prev;
  skipNode* next;
public:
  skipNode();
  ~skipNode();
  SkiplistNode* insertAtStart(SkiplistNode* i);

  skipNode* getNext();
  skipNode* getPrev();
  SkiplistHeader* getItem();
  void setNext(skipNode* n);
  void setPrev(skipNode* p);

  void removeFirst();
  void print();

  void testPrint();
};

class skipHeader{//list of lists
  skipNode* start;
  skipNode* end;
  int lvlnum;
  int max_lvl;
  void addLayer();
public:
  skipHeader();
  ~skipHeader();
  SkiplistNode* searchItem(int i);
  SkiplistNode* insertItem(int* i, citizenRecord* c, string* dv);
  SkiplistNode* deleteItem(int i);
  
  countryStatsNode* populationStatus(string don, string dt, string c);//for vacced
  countryStatsNode* populationStatus(countryStatsNode* stats, string c);//for not vacced
  countryStatsHeader* populationStatus(string don, string dt);//for vacced
  countryStatsHeader* populationStatus(countryStatsHeader* stats);//for not vacced

  void print();

  void testPrint();
};
#endif
