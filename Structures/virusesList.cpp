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
      cout << "ERROR record cant get vaccinated because already been not vaccinated" << endl;
    }else{
      string* dateV = new string(dv);
      // cout << "test: " << *dateV << endl;
      if(vaccinated->insertItem(id, c, dateV)){
        bloom->insert(*id);
      }else{
        cout << "ERROR: citizen " << *id << " ALREADY VACCINATED ON " << endl; //TODO: add date
        delete dateV;
      }
    }
  }else{
    if(vaccinated->searchItem(*id)){
      cout << "ERROR: citizen " << id << "ALREADY VACCINATED ON " << endl; //TODO: add date
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

void VarlistHeader::vaccineStatusBloom(int i, string v){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->item == v){
      break;
    }
    temp = temp->next;
  }
  if(temp == NULL){
    cout << "Virus not found" << endl;
  }else{
    if(temp->bloom->is_inside(i)){
      cout << "MAYBE" << endl;
    }else{
      cout << "NOT VACCINATED" << endl;
    }
  }
}

void VarlistHeader::vaccineStatus(int i, string v){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->item == v){
      break;
    }
    temp = temp->next;
  }
  if(temp == NULL){
    cout << "Virus not found" << endl;
    return;
  }else{

    if(temp->vaccinated->searchItem(i)){
      cout << "VACCINATED ON " << endl; //TODO: add date
      return;
    }
    cout << "NOT VACCINATED" << endl;
  }
}

void VarlistHeader::vaccineStatus(int i){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->vaccinated->searchItem(i)){
      cout << temp->item << " YES " << endl; //TODO: add date
    }else{
      cout << temp->item << " NO" << endl;
    }
    temp = temp->next;
  }
}

bool VarlistHeader::vaccinateNow(int i, string fn, string ln, string c, string a, string v){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->item == v){
      break;
    }
    temp = temp->next;
  }
  if(temp == NULL){
    return false;
  }
  if(temp->vaccinated->searchItem(i)){
    cout << "ERROR: CITIZEN " << i << " ALREADY VACCINATED ON " << endl; //TODO: add date
    return true;
  }

  SkiplistNode* tmp = temp->notVaccinated->deleteItem(i);
  if(tmp == NULL){
    return false;
  }else{
    time_t t= time(0);
    tm* n = localtime(&t);
    string tt = to_string(n->tm_mday) + "-" + to_string(n->tm_mon+1) + "-" + to_string(n->tm_year + 1900);
    temp->insertRecord(tmp->getCitizen()->citizenId, tmp->getCitizen(), "YES", tt);

    delete tmp;
    return true;
  }
}

void VarlistHeader::listNonVaccinatedPersons(string v){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->item == v){
      break;
    }
    temp = temp->next;
  }
  if(temp == NULL){
    cout << "Virus not found" << endl;
    return;
  }else{
    temp->notVaccinated->print();
  }
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
