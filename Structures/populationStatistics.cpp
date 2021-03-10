#include <iostream>
#include "populationStatistics.hpp"
using namespace std;

//////////////////countryStatsNode
countryStatsNode::countryStatsNode(string n){
  item = n;
  Datevacced = 0;
  v = 0;
  pl = 0;
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

void countryStatsHeader::print(){
  countryStatsNode* temp = start;
  while(temp != NULL){
    temp->print();
    temp = temp->getNext();
  }
}














//
