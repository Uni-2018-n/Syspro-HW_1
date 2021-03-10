#include <iostream>
#include "populationStatistics.hpp"
using namespace std;

//////////////////countryStatsNode
countryStatsNode::countryStatsNode(string n){
  item = n;
  vacced = 0;
  pl = 0;
  next = NULL;
}

countryStatsNode::countryStatsNode(string n, bool b){
  item = n;
  if(b){
    vacced = 1;
  }else{
    vacced = 0;
  }
  pl = 1;
  next = NULL;
}

void countryStatsNode::print(){
  printf("%s %d %.2f%%\n", item.c_str(), vacced, (vacced != 0) ? ((float)vacced/(float)pl)*100.0 : 0.0);
  // printf("%s %d %d%%\n", item.c_str(), vacced, pl);

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
    temp = temp->next;
    delete tmp;
  }
}

void countryStatsHeader::insertItem(string i, bool b){
  countryStatsNode* temp = start;
  if(temp == NULL){
    start = new countryStatsNode(i, b);
    return;
  }else{
    while(temp->next != NULL){
      if(temp->next->item == i){
        if(b){
          temp->next->vacced++;
        }
        temp->next->pl++;
        return;
      }
      temp = temp->next;
    }
    temp->next = new countryStatsNode(i, b);
  }

}

void countryStatsHeader::print(){
  countryStatsNode* temp = start;
  while(temp != NULL){
    temp->print();
    temp = temp->next;
  }
}














//
