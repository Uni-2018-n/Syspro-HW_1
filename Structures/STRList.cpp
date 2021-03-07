#include <iostream>
#include "STRList.hpp"


SlistNode::SlistNode(string* i){
  item = i;
  next = NULL;
}

SlistNode::~SlistNode(){
  
}


SlistHeader::SlistHeader(){
  start = NULL;
  end = NULL;
}

SlistHeader::~SlistHeader(){
  SlistNode* temp = start;
  SlistNode* tmp = NULL;
  while(temp != NULL){
    tmp = temp;
    temp= temp->next;
    delete tmp;
  }
}

string* SlistHeader::searchItem(string i){
  SlistNode* temp = start;
  while(temp != NULL){
    if(temp->item->compare(i) == 0){
      return temp->item;
    }
    temp = temp->next;
  }
  return NULL;
}

void SlistHeader::insertItem(string* i){
  SlistNode* new_node = new SlistNode(i);
  if(start == NULL){
    start = new_node;
    end = new_node;
  }else{
    end->next = new_node;
    end = new_node;
  }
  return;
}

void SlistHeader::testPrint(){
  SlistNode* temp = start;
  cout << "(";
  while(temp != NULL){
    cout << *(temp->item) << "-> ";
    temp = temp->next;
  }
  cout << ")";
  return;
}
