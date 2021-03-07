#include <iostream>
#include "virusesList.hpp"


VarlistNode::VarlistNode(string* i, int l){
  item = i;
  bloom = new bloomFilter(l);
  next = NULL;
}

VarlistNode::~VarlistNode(){
  delete item;
  delete bloom;
}


VarlistHeader::VarlistHeader(int i):
bloom_len(i){
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
  VarlistNode* new_node = new VarlistNode(i, bloom_len);
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
