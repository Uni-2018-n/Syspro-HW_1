#ifndef _POPULATIONSTATISTICS_HPP_
#define _POPULATIONSTATISTICS_HPP_

#include <iostream>

using namespace std;

class countryStatsNode{
  string item;
  int Datevacced;
  int v;
  int pl;
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

  void topCorrectCat(int b, int a){
    if(a >=0 && a <=19){
      if(b==2){
        DateZT++;
        ZT++;
      }else if(b ==1){
        ZT++;
      }
      plZT++;
    }else if(a >=20 && a <=39){
      if(b==2){
        DateTF++;
        TF++;
      }else if(b ==1){
        TF++;
      }
      plTF++;
    }else if(a >=40 && a <=59){
      if(b==2){
        DateFS++;
        FS++;
      }else if(b ==1){
        FS++;
      }
      plFS++;
    }else if(a >=60){
      if(b==2){
        DateS++;
        S++;
      }else if(b ==1){
        S++;
      }
      plS++;
    }

  }
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
};

#endif
//b=2 d+v+p
//b=1 v+p
//b=0 p
