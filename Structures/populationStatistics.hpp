#ifndef _POPULATIONSTATISTICS_HPP_
#define _POPULATIONSTATISTICS_HPP_

#include <iostream>

using namespace std;

class countryStatsNode{
public:
  string item;
  int vacced;
  int pl;
  countryStatsNode* next;
  countryStatsNode(string n);
  countryStatsNode(string n, bool b);
  void print();
};

class countryStatsHeader{
  countryStatsNode* start;
public:
  countryStatsHeader();
  ~countryStatsHeader();
  void insertItem(string i, bool b);
  void print();
};

#endif
