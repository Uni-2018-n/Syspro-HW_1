#include <iostream>
#include "vacList.hpp"


VlistNode::VlistNode(vaccinateRecord* i){
  item = i;
  next = NULL;
}

VlistNode::~VlistNode(){
  delete item;
}


VlistHeader::VlistHeader(){
  start = NULL;
  end = NULL;
}

VlistHeader::~VlistHeader(){
  VlistNode* temp = start;
  VlistNode* tmp = NULL;
  while(temp != NULL){
    tmp = temp;
    temp= temp->next;
    delete tmp;
  }
}

void VlistHeader::insertItem(vaccinateRecord* i){
  VlistNode* new_node = new VlistNode(i);
  if(start == NULL){
    start = new_node;
    end = new_node;
  }else{
    end->next = new_node;
    end = new_node;
  }
  return;
}

void VlistHeader::testPrint(){
  VlistNode* temp = start;
  cout << "(";
  while(temp != NULL){
    cout << *(temp->item->virusName) << "-> ";
    temp = temp->next;
  }
  cout << ")";
  return;
}
