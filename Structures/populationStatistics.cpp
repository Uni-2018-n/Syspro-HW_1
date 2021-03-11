#include <iostream>
#include "populationStatistics.hpp"
using namespace std;

//////////////////countryStatsNode
countryStatsNode::countryStatsNode(string n){
  item = n;
  Datevacced = 0;
  v = 0;
  pl = 0;
  DateZT=0;
  ZT=0;
  plZT =0;
  DateTF=0;
  TF=0;
  plTF =0;
  DateFS=0;
  FS=0;
  plFS =0;
  DateS=0;
  S=0;
  plS=0;
  next = NULL;
}

countryStatsNode::countryStatsNode(string n, int b){
  item = n;
  Datevacced = 0;
  v = 0;
  pl = 0;
  if(b==2){
    Datevacced = 1;
    v=1;
  }else if(b==1){
    v = 1;
  }
  pl = 1;
  next = NULL;
}

string countryStatsNode::getItem(){
  return item;
}
void countryStatsNode::topDateVacced(){
  Datevacced++;
}
void countryStatsNode::topV(){
  v++;
}
void countryStatsNode::topPl(){
  pl++;
}
countryStatsNode* countryStatsNode::getNext(){
  return next;
}

void countryStatsNode::setNext(countryStatsNode* n){
  next = n;
}


void countryStatsNode::print(){
  printf("%s %d %.2f%%\n", item.c_str(), Datevacced, (v != 0) ? ((float)v/(float)pl)*100.0 : 0.0);
  // printf("%s %d %d %d%%\n", item.c_str(), Datevacced, v, pl);

}

void countryStatsNode::printAge(){
  cout << item << endl;
  printf("0-20 %d %.2f%%\n", ZT, (DateZT != 0) ? ((float)DateZT/(float)plZT)*100.0 : 0.0);
  printf("20-40 %d %.2f%%\n", TF, (DateTF != 0) ? ((float)DateTF/(float)plTF)*100.0 : 0.0);
  printf("40-60 %d %.2f%%\n", FS, (DateFS != 0) ? ((float)DateFS/(float)plFS)*100.0 : 0.0);
  printf("60++ %d %.2f%%\n", S, (DateS != 0) ? ((float)DateS/(float)plS)*100.0 : 0.0);
  cout << endl;

  // cout << item << endl;
  // printf("0-20 %d %d %d\n", ZT, DateZT, plZT);
  // printf("20-40 %d %d %d\n", TF, DateTF, plTF);
  // printf("40-60 %d %d %d\n", FS, DateFS, plFS);
  // printf("60++ %d %d %d\n", S, DateS, plS);
  // cout << endl;
}


//////////////////countryStatsHeader
countryStatsHeader::countryStatsHeader(){
  start = NULL;
}

countryStatsHeader::~countryStatsHeader(){
  countryStatsNode* temp = start;
  countryStatsNode* tmp;
  while(temp != NULL){
    tmp = temp;
    temp = temp->getNext();
    delete tmp;
  }
}

void countryStatsHeader::insertItem(string i, int b){
  countryStatsNode* temp = start;
  if(temp == NULL){
    start = new countryStatsNode(i, b);
    return;
  }else{
    while(temp != NULL){
      if(temp->getItem() == i){
        if(b==2){
          temp->topDateVacced();
          temp->topV();
        }else if(b==1){
          temp->topV();
        }
        temp->topPl();
        return;
      }
      if(temp->getNext() == NULL){
        temp->setNext(new countryStatsNode(i, b));
        return;
      }
      temp= temp->getNext();
    }
  }
}

void countryStatsHeader::insertItemAge(string i, int b, int a){
  countryStatsNode* temp = start;
  if(temp == NULL){
    start = new countryStatsNode(i);
    start->topCorrectCat(b,a);
    return;
  }else{
    while(temp != NULL){
      if(temp->getItem() == i){
        temp->topCorrectCat(b,a);
        return;
      }
      if(temp->getNext() == NULL){;
        temp->setNext(new countryStatsNode(i));
        temp->getNext()->topCorrectCat(b,a);
        return;
      }
      temp= temp->getNext();
    }
  }
}

void countryStatsHeader::print(){
  countryStatsNode* temp = start;
  while(temp != NULL){
    temp->print();
    temp = temp->getNext();
  }
}

void countryStatsHeader::printAge(){
  countryStatsNode* temp = start;
  while(temp != NULL){
    temp->printAge();
    temp = temp->getNext();
  }
}













//
