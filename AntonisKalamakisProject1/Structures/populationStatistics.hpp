#ifndef _POPULATIONSTATISTICS_HPP_
#define _POPULATIONSTATISTICS_HPP_

#include <iostream>

using namespace std;

/*this is used two ways, if the command is followed by a country then we just
create an countryStatsNode object and do everything there.
If country isnt specified we have a temporary linked list with countryStatsNode nodes
for each country that we come accross in our database.
*/
class countryStatsNode{
  string item;
  //for popStatus
  int Datevacced;//one for those who vaccinated inside the date range
  int v;//one for those who were vaccinated in general
  int pl;//and the count of all the people that were inside the database

  //for popStatusAge
  //for simplicity reasons used same 3 variables for each category
  int DateZT;
  int ZT;
  int plZT;
  int DateTF;
  int TF;
  int plTF;
  int DateFS;
  int FS;
  int plFS;
  int DateS;
  int S;
  int plS;
  countryStatsNode* next;
public:
  countryStatsNode(string n);
  countryStatsNode(string n, int b);
  string getItem();

  void topDateVacced();
  void topV();
  void topPl();

  void topCorrectCat(int b, int a);
  countryStatsNode* getNext();
  void setNext(countryStatsNode* n);
  void print();
  void printAge();
};

class countryStatsHeader{
  countryStatsNode* start;
public:
  countryStatsHeader();
  ~countryStatsHeader();
  void insertItem(string i, int b);
  void insertItemAge(string i, int b, int a);
  void print();
  void printAge();
};
#endif