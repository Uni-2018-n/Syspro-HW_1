#include <iostream>
#include "virusesList.hpp"

VirlistNode::VirlistNode(string i, int l){
  item = i;
  bloom = new bloomFilter(l);
  vaccinated = new skipHeader();
  notVaccinated = new skipHeader();
  next = NULL;
}

VirlistNode::~VirlistNode(){
  delete bloom;
  delete vaccinated;
  delete notVaccinated;
}

VirlistNode* VirlistNode::getNext(){
  return next;
}

void VirlistNode::setNext(VirlistNode* n){
  next = n;
}

string VirlistNode::getItem(){
  return item;
}
void VirlistNode::setItem(string i){
  item = i;
}

bloomFilter* VirlistNode::getBloom(){
  return bloom;
}

skipHeader* VirlistNode::getVacced(){
  return vaccinated;
}

skipHeader* VirlistNode::getNotVacced(){
  return notVaccinated;
}

void VirlistNode::insertRecord(int* id, citizenRecord* c, string v, string dv, bool flag){
  if(v == "YES"){
    if(notVaccinated->searchItem(*id)){
      if(flag){
          SkiplistNode* tmp = notVaccinated->deleteItem(*id);
          this->insertRecord(tmp->getCitizen()->citizenId, tmp->getCitizen(), v, dv, false);
          delete tmp;
      }else{
        cout << "ERROR record cant get vaccinated because already been not vaccinated" << endl;
      }
    }else{
      dv = checkAndFormatDate(dv);
      string* dateV = new string(dv);
      SkiplistNode* t= vaccinated->insertItem(id, c, dateV);
      if(t != NULL){
        if(t->getDateVaccinated() == dv){
          bloom->insert(*id);
        }else{
          cout << "ERROR: citizen " << *id << " ALREADY VACCINATED ON " << flipDate(t->getDateVaccinated()) << endl;
          delete dateV;
        }
      }
    }
  }else{
    SkiplistNode* t= vaccinated->searchItem(*id);
    if(t != NULL){
      cout << "ERROR: citizen " << *id << " ALREADY VACCINATED ON " << flipDate(t->getDateVaccinated()) << endl;
    }else{
      notVaccinated->insertItem(id, c, NULL);
    }
  }
}

VirlistHeader::VirlistHeader(int i):
bloom_len(i){
  start = NULL;
  end = NULL;
}

VirlistHeader::~VirlistHeader(){
  VirlistNode* temp = start;
  VirlistNode* tmp = NULL;
  while(temp != NULL){
    tmp = temp;
    temp= temp->getNext();
    delete tmp;
  }
}

VirlistNode* VirlistHeader::insertVirus(string i){
  VirlistNode* new_node = new VirlistNode(i, bloom_len);
  if(start == NULL){
    start = new_node;
    end = new_node;
  }else{
    end->setNext(new_node);
    end = new_node;
  }
  return new_node;
}

VirlistNode* VirlistHeader::searchVirus(string i){
  VirlistNode* temp = start;
  while(temp != NULL){
    if(temp->getItem().compare(i) ==0){
      return temp;
    }
    temp = temp->getNext();
  }
  return NULL;
}

void VirlistHeader::vaccineStatusBloom(int i, string v){
  VirlistNode* temp = start;
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

void VirlistHeader::vaccineStatus(int i, string v){
  VirlistNode* temp = start;
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
      cout << "VACCINATED ON " << flipDate(t->getDateVaccinated()) << endl;
      return;
    }
    cout << "NOT VACCINATED" << endl;
  }
}

void VirlistHeader::vaccineStatus(int i){
  VirlistNode* temp = start;
  while(temp != NULL){
    SkiplistNode* t = temp->getVacced()->searchItem(i);
    if(t != NULL){
      cout << temp->getItem() << " YES " << flipDate(t->getDateVaccinated()) << endl;
    }else{
      if(temp->getNotVacced()->searchItem(i)){
        cout << temp->getItem() << " NO " << endl;
      }
    }
    temp = temp->getNext();
  }
}

bool VirlistHeader::vaccinateNow(int i, string fn, string ln, string c, string a, string v){
  VirlistNode* temp = start;
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
    cout << "ERROR: CITIZEN " << i << " ALREADY VACCINATED ON " << flipDate(t->getDateVaccinated()) << endl;
    return true;
  }

  SkiplistNode* tmp = temp->getNotVacced()->deleteItem(i);
  if(tmp == NULL){
    return false;
  }else{
    time_t t= time(0);
    tm* n = localtime(&t);
    string tt = to_string(n->tm_mday) + "-" + to_string(n->tm_mon+1) + "-" + to_string(n->tm_year + 1900);
    temp->insertRecord(tmp->getCitizen()->citizenId, tmp->getCitizen(), "YES", tt, false);

    delete tmp;
    return true;
  }
}

void VirlistHeader::listNonVaccinatedPersons(string v){
  VirlistNode* temp = start;
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

void VirlistHeader::testPrint(){
  VirlistNode* temp = start;
  while(temp != NULL){
    cout << temp->getItem() << "-> ";
    temp = temp->getNext();
  }
  cout << endl;
  return;
}
