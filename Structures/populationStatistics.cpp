#include <iostream>
#include "populationStatistics.hpp"
using namespace std;

//////////////////countryStatsNode
countryStatsNode::countryStatsNode(string n){//simply initialize the node
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

countryStatsNode::countryStatsNode(string n, int b){//initialize a node with tops in the correct variables
  item = n;
  Datevacced = 0;
  v = 0;
  pl = 0;
  if(b==2){
    Datevacced = 1;
    v=1;
    pl = 1;
  }else if(b==1){
    v = 1;
  }
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
  printf("%s %d %.2f%%\n", item.c_str(), Datevacced, (Datevacced != 0) ? ((float)Datevacced/(float)pl)*100.0 : 0.0);
}

void countryStatsNode::printAge(){
  cout << item << endl;
  printf("0-20 %d %.2f%%\n", DateZT, (DateZT != 0) ? ((float)DateZT/(float)plZT)*100.0 : 0.0);
  printf("20-40 %d %.2f%%\n", DateTF, (DateTF != 0) ? ((float)DateTF/(float)plTF)*100.0 : 0.0);
  printf("40-60 %d %.2f%%\n", DateFS, (DateFS != 0) ? ((float)DateFS/(float)plFS)*100.0 : 0.0);
  printf("60++ %d %.2f%%\n", DateS, (DateS != 0) ? ((float)DateS/(float)plS)*100.0 : 0.0);
  cout << endl;
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

void countryStatsHeader::insertItem(string i, int b){//insert for populationStatus
  countryStatsNode* temp = start;
  if(temp == NULL){//if list empty create a node with already toped data in it
    start = new countryStatsNode(i, b);
    return;
  }else{//if not
    while(temp != NULL){//go though the list
      if(temp->getItem() == i){//till you find the country that we need
        if(b==2){//and top the correct variables as given from the parameters
          temp->topDateVacced();
          temp->topV();
          temp->topPl();
        }else if(b==1){
          temp->topV();
        }else if(b==0){
          temp->topPl();
        }
        return;
      }
      if(temp->getNext() == NULL){//if we havent found the country simply create it and add it at the end
        temp->setNext(new countryStatsNode(i, b));
        return;
      }
      temp= temp->getNext();
    }
  }
}

void countryStatsHeader::insertItemAge(string i, int b, int a){//used for popStatusByAge
  countryStatsNode* temp = start;//same thing as before but now use topCorrectCat function to top the variables
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

void countryStatsNode::topCorrectCat(int b, int a){
    /*this function takes 2 arguments.
    first argument is the senario we have:
    if b==2 then we have someone who is vaccinated inside the date range
    so we need to top all 3 variables
    if b==1 then we have a vaccinated record but not inside the date range
    and if b==0 the record is not vaccinated

    Second argument is the age so we can add it to the desired category
    */
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