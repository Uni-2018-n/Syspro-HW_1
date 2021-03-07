#include <iostream>
#include "virusesList.hpp"


VarlistNode::VarlistNode(string i, int l){
  item = i;
  bloom = new bloomFilter(l);
  next = NULL;
}

VarlistNode::~VarlistNode(){
  delete bloom;
}

void VarlistNode::insertRecord(int* id, string v, string dv){
  if(bloom->is_inside(*id)){
    //check if is trully inside
    cout << "ERROR record already inside " << endl;
  }else{
    bloom->insert(*id);
    //add to the correct skip list
  }
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

VarlistNode* VarlistHeader::insertVirus(string i){
  VarlistNode* new_node = new VarlistNode(i, bloom_len);
  if(start == NULL){
    start = new_node;
    end = new_node;
  }else{
    end->next = new_node;
    end = new_node;
  }
  return new_node;
}

VarlistNode* VarlistHeader::searchVirus(string i){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->item.compare(i) ==0){
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}

void VarlistHeader::testPrint(){
  VarlistNode* temp = start;
  while(temp != NULL){
    cout << temp->item << "-> ";
    temp = temp->next;
  }
  cout << endl;
  return;
}
