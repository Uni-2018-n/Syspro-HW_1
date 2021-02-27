#include <iostream>
#include "skipList.hpp"
#include <math.h>
using namespace std;


List::List(int* i){
  item = i;
  lower_level = NULL;
  next = NULL;
}

List::List(List* i){
  item = i->item;
  lower_level = i;
  next = NULL;
}

List::List(List* i, List* n){
  item = i->item;
  next = n;
}

List::List(int* i, List* n){
  item = i;
  next = n;
}

List::~List(){
}

void List::testPrint(){
  cout << *item << " ";
}

//////////////////////////// listHeader

listHeader::listHeader(){
  start = NULL;
  pl =0;
}

listHeader::~listHeader(){
  List* temp = start;
  List* tmp = NULL;
  while(temp != NULL){
    tmp = temp->next;
    delete temp;
    temp= tmp;
  }
}

void listHeader::insertItem(int* i){
  if(start == NULL){
    List *new_item = new List(i);
    start = new_item;
    pl++;
  }else if(*(start->item) > *i){
    List *new_item = new List(i, start);
    start = new_item;
    pl++;
  }else{
    List* temp = start;
    while(temp->next != NULL){
      if(*i < *(temp->next->item)){
        List *new_item = new List(i, temp->next);
        temp->next = new_item;
        pl++;
        return;
      }
      temp = temp->next;
    }
    List *new_item = new List(i);
    temp->next = new_item;
    pl++;
  }
}

void listHeader::insertItem(List* i){
  if(start == NULL){
    List *new_item = new List(i);
    start = new_item;
    pl++;
  }else if(*(start->item) > *(i->item)){
    List *new_item = new List(i, start);
    start = new_item;
    pl++;
  }else{
    List* temp = start;
    while(temp->next != NULL){
      if(*(i->item) < *(temp->next->item)){
        List *new_item = new List(i, temp->next);
        temp->next = new_item;
        pl++;
        return;
      }
      temp = temp->next;
    }
    List *new_item = new List(i);
    temp->next = new_item;
    pl++;
  }
}

void listHeader::testPrint(){
  List* temp = start;
  while(temp != NULL){
    temp->testPrint();
    temp = temp->next;
  }
}

listHeader* listHeader::forNextLayer(){
  listHeader* to_return = new listHeader();
  List* temp = start;
  while(temp != NULL){
    if((random() % 100 + 0) < 70){//might also need to make it more flip a coin like
      to_return->insertItem(temp);
    }
    temp = temp->next;
  }
  return to_return;
}




//////////////////////////////////////// skipNode
skipNode::skipNode(listHeader* i){
  item = i;
  next = NULL;
}

skipNode::skipNode(){
  // item = new listHeader();
  item =NULL;
  next= NULL;
}

skipNode::skipNode(listHeader* i, skipNode* n){
  item = i;
  next = n;
}

skipNode::~skipNode(){
  delete item;
}

void skipNode::testPrint(){
  item->testPrint();
}

///////////////////////////////////// skipHeader
skipHeader::skipHeader(listHeader* i){
  skipNode* temp = new skipNode(i);
  start = temp;
  end = temp;
  lvlnum = 1;
  max_lvl = log(i->pl)+1; //TODO might need to change here something
  // max_lvl = 1;// TODO fix this
  for(int i=0;i<max_lvl;i++){
    addLayer();
  }

  {
    skipNode* temp= start;
    while(temp->next != NULL){
      temp->next->item = temp->item->forNextLayer();
      temp = temp->next;
    }
  }
}

skipHeader::~skipHeader(){
  skipNode* temp = start;
  skipNode* tmp = NULL;
  while(temp != NULL){
    tmp = temp->next;
    delete temp;
    temp = tmp;
  }
}

void skipHeader::addLayer(){
  skipNode* temp = new skipNode();
  end->next = temp;
  end = end->next;
}

void skipHeader::insertItem(int* i){

}

void skipHeader::testPrint(){
  skipNode* temp = start;
  while(temp != NULL){
    temp->item->testPrint();
    temp = temp->next;
    cout << endl;
  }
}


//
