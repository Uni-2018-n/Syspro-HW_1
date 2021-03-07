#include <iostream>
#include "virusesList.hpp"


VarlistNode::VarlistNode(string* i){
  item = i;
  next = NULL;
}

VarlistNode::~VarlistNode(){
  delete item;
}


VarlistHeader::VarlistHeader(){
  start = NULL;
  end = NULL;
}

VarlistHeader::~VarlistHeader(){
  VarlistNode* temp = start;
  VarlistNode* tmp = NULL;
  while(temp != NULL){
    tmp = temp;
    temp= temp->next;
    delete tmp;
  }
}

void VarlistHeader::insertVirus(string* i){
  VarlistNode* new_node = new VarlistNode(i);
  if(start == NULL){
    start = new_node;
    end = new_node;
  }else{
    end->next = new_node;
    end = new_node;
  }
  return;
}

string* VarlistHeader::searchVirus(string i){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->item->compare(i) ==0){
      return temp->item;
    }
    temp = temp->next;
  }
  return NULL;
}

void VarlistHeader::testPrint(){
  VarlistNode* temp = start;
  while(temp != NULL){
    cout << *(temp->item) << "-> ";
    temp = temp->next;
  }
  cout << endl;
  return;
}
