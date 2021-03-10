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

VarlistNode* VarlistNode::getNext(){
  return next;
}

void VarlistNode::setNext(VarlistNode* n){
  next = n;
}

string VarlistNode::getItem(){
  return item;
}
void VarlistNode::setItem(string i){
  item = i;
}

bloomFilter* VarlistNode::getBloom(){
  return bloom;
}

skipHeader* VarlistNode::getVacced(){
  return vaccinated;
}

skipHeader* VarlistNode::getNotVacced(){
  return notVaccinated;
}

void VarlistNode::insertRecord(int* id, citizenRecord* c, string v, string dv){
  if(v == "YES"){
    if(notVaccinated->searchItem(*id)){
      cout << "ERROR record cant get vaccinated because already been not vaccinated" << endl;
    }else{
      string* dateV = new string(dv);
      // cout << "test: " << *dateV << endl;
      SkiplistNode* t= vaccinated->insertItem(id, c, dateV);
      if(t != NULL){
        if(t->getDateVaccinated() == dv){
          bloom->insert(*id);
        }else{
          cout << "ERROR: citizen " << *id << " ALREADY VACCINATED ON " << t->getDateVaccinated() << endl;
          delete dateV;
        }
      }
    }
  }else{
    SkiplistNode* t= vaccinated->searchItem(*id);
    if(t != NULL){
      cout << "ERROR: citizen " << id << "ALREADY VACCINATED ON " << t->getDateVaccinated() << endl;
    }else{
      notVaccinated->insertItem(id, c, NULL);
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
    temp= temp->getNext();
    delete tmp;
  }
}

VarlistNode* VarlistHeader::insertVirus(string i){
  VarlistNode* new_node = new VarlistNode(i, bloom_len);
  if(start == NULL){
    start = new_node;
    end = new_node;
  }else{
    end->setNext(new_node);
    end = new_node;
  }
  return new_node;
}

VarlistNode* VarlistHeader::searchVirus(string i){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->getItem().compare(i) ==0){
      return temp;
    }
    temp = temp->getNext();
  }
  return NULL;
}

void VarlistHeader::vaccineStatusBloom(int i, string v){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->getItem() == v){
      break;
    }
    temp = temp->getNext();
  }
  if(temp == NULL){
    cout << "Virus not found" << endl;
  }else{
    if(temp->getBloom()->is_inside(i)){
      cout << "MAYBE" << endl;
    }else{
      cout << "NOT VACCINATED" << endl;
    }
  }
}

void VarlistHeader::vaccineStatus(int i, string v){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->getItem() == v){
      break;
    }
    temp = temp->getNext();
  }
  if(temp == NULL){
    cout << "Virus not found" << endl;
    return;
  }else{
    SkiplistNode* t = temp->getVacced()->searchItem(i);
    if(t != NULL){
      cout << "VACCINATED ON " << t->getDateVaccinated() << endl;
      return;
    }
    cout << "NOT VACCINATED" << endl;
  }
}

void VarlistHeader::vaccineStatus(int i){
  VarlistNode* temp = start;
  while(temp != NULL){
    SkiplistNode* t = temp->getVacced()->searchItem(i);
    if(t != NULL){
      cout << temp->getItem() << " YES " << t->getDateVaccinated() << endl;
    }else{
      if(temp->getNotVacced()->searchItem(i)){
        cout << temp->getItem() << " NO " << endl;
      }
    }
    temp = temp->getNext();
  }
}

bool VarlistHeader::vaccinateNow(int i, string fn, string ln, string c, string a, string v){
  VarlistNode* temp = start;
  while(temp != NULL){
    if(temp->getItem() == v){
      break;
    }
    temp = temp->getNext();
  }
  if(temp == NULL){
    return false;
  }
  SkiplistNode* t = temp->getVacced()->searchItem(i);
  if(t != NULL){
    cout << "ERROR: CITIZEN " << i << " ALREADY VACCINATED ON " << t->getDateVaccinated() << endl;
    return true;
  }

  SkiplistNode* tmp = temp->getNotVacced()->deleteItem(i);
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
    if(temp->getItem() == v){
      break;
    }
    temp = temp->getNext();
  }
  if(temp == NULL){
    cout << "Virus not found" << endl;
    return;
  }else{
    temp->getNotVacced()->print();
  }
}

void VarlistHeader::testPrint(){
  VarlistNode* temp = start;
  while(temp != NULL){
    cout << temp->getItem() << "-> ";
    temp = temp->getNext();
  }
  cout << endl;
  return;
}
