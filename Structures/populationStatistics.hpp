#ifndef _POPULATIONSTATISTICS_HPP_
#define _POPULATIONSTATISTICS_HPP_

#include <iostream>

using namespace std;

class countryStatsNode{
  string item;
  int Datevacced;
  int v;
  int pl;
  countryStatsNode* next;
public:
  countryStatsNode(string n);
  countryStatsNode(string n, int b);
  string getItem();
  void topDateVacced();
  void topV();
  void topPl();
  countryStatsNode* getNext();
  void setNext(countryStatsNode* n);
  void print();
};

class countryStatsHeader{
  countryStatsNode* start;
public:
  countryStatsHeader();
  ~countryStatsHeader();
  void insertItem(string i, int b);
  void print();
};

#endif
//b=2 d+v+p
//b=1 v+p
//b=0 p
