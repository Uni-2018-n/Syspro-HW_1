#include <iostream>
#include "virusesList.hpp"


VarlistNode::VarlistNode(string i, int l){
  item = i;
  bloom = new bloomFilter(l);
  vaccinated = new skipHeader();
  notVaccinated = new skipHeader();
  next = NULL;
}

VarlistNode::~VarlistNode(){
  delete bloom;
  delete vaccinated;
  delete notVaccinated;
}

void VarlistNode::insertRecord(int* id, citizenRecord* c, string v, string dv){
  if(v == "YES"){
    if(notVaccinated->searchItem(*id)){
      //remove from notVaccinated and add to vaccinated
    }else{
      string* dateV = new string(dv);
      if(vaccinated->insertItem(id, c, dateV)){
        bloom->insert(*id);
      }else{
        cout << "ERROR record already inside " << endl;
      }
    }
  }else{
    if(vaccinated->searchItem(*id)){
      cout << "ERROR record already vaccinated " << endl;
    }else{
      if(!(notVaccinated->insertItem(id, c, NULL))){
        cout << "ERROR record already inside " << endl;
      }
    }
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
