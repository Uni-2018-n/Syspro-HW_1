#ifndef _POPULATIONSTATISTICS_HPP_
#define _POPULATIONSTATISTICS_HPP_

#include <iostream>

using namespace std;

class countryStatsNode{
public:
  string item;
  int Datevacced;
  int v;
  int pl;
  countryStatsNode* next;
  countryStatsNode(string n);
  countryStatsNode(string n, int b);
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
