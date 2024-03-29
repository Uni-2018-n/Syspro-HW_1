#include <iostream>
#include "skipList.hpp"
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
  //the flag parameter is used to determin if we allow the record to be vaccinated after beeing added into the not-vaccinated list
  if(v == "YES"){
    if(notVaccinated->searchItem(*id)){//see if the citizen is already inside our not vaccinated skip list
      if(flag){//if its allowed
          SkiplistNode* tmp = notVaccinated->deleteItem(*id);//remove the citizen from the not vaccinated skip list
          dv = checkAndFormatDate(dv);                       //and do as you would if citizen wos not in the not-vaccinated skip list
          if(dv == ""){
            cout << "ERROR WITH DATE FROMAT" << endl;
            return;
          }
          string* dateV = new string(dv);
          SkiplistNode* t= vaccinated->insertItem(tmp->getCitizen()->citizenId, tmp->getCitizen(), dateV);
          if(t != NULL){
            if(t->getDateVaccinated() == dv){
              bloom->insert(*(tmp->getCitizen()->citizenId));
            }else{
              cout << "ERROR: citizen " << tmp->getCitizen()->citizenId << " ALREADY VACCINATED ON " << flipDate(t->getDateVaccinated()) << endl;
              delete dateV;
            }
          }
          delete tmp;
      }else{
        cout << "ERROR record cant get vaccinated because already been not vaccinated" << endl;
      }
    }else{//if citizen not in not vaccinated skip list
      dv = checkAndFormatDate(dv);
      if(dv == ""){
        cout << "ERROR WITH DATE FORMAT" << endl;
        return;
      }
      string* dateV = new string(dv);
      SkiplistNode* t= vaccinated->insertItem(id, c, dateV);//insert the citizen in the vaccinated skip list
      if(t != NULL){//and if everything is ok
        if(t->getDateVaccinated() == dv){//and citizen not already vaccinated 
          bloom->insert(*id);//insert the citizen in the bloom filter
        }else{
          cout << "ERROR: citizen " << *id << " ALREADY VACCINATED ON " << flipDate(t->getDateVaccinated()) << endl;
          delete dateV;
        }
      }
    }
  }else{//case citizen needs to be inserted in not vaccinated list
    SkiplistNode* t= vaccinated->searchItem(*id);//check if already vaccinated
    if(t != NULL){
      cout << "ERROR: citizen " << *id << " ALREADY VACCINATED ON " << flipDate(t->getDateVaccinated()) << endl;
    }else{
      notVaccinated->insertItem(id, c, NULL);//if not insert into the not vaccinated list
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

VirlistNode* VirlistHeader::insertVirus(string i){//simple insert at end method for viruses
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

VirlistNode* VirlistHeader::searchVirus(string i){//simple search method base on virus name 
  VirlistNode* temp = start;
  while(temp != NULL){
    if(temp->getItem().compare(i) ==0){
      return temp;
    }
    temp = temp->getNext();
  }
  return NULL;
}

void VirlistHeader::vaccineStatusBloom(int i, string v){//simple method for checking the bloom filter of the virus
  VirlistNode* temp = this->searchVirus(v);
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
  VirlistNode* temp = this->searchVirus(v);
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

bool VirlistHeader::vaccinateNow(int i, string v){
  //function that checks if citizen is already set to vaccinated or not vaccinated
  VirlistNode* temp = this->searchVirus(v);
  if(temp == NULL){
    return false;
  }
  SkiplistNode* t = temp->getVacced()->searchItem(i);//search if citizen already vaccinated
  if(t != NULL){
    cout << "ERROR: CITIZEN " << i << " ALREADY VACCINATED ON " << flipDate(t->getDateVaccinated()) << endl;
    return true;
  }

  SkiplistNode* tmp = temp->getNotVacced()->deleteItem(i);//search and delete if citizen already not vaccinated
  if(tmp == NULL){
    return false;
  }else{
    time_t t= time(0);//create the date and insert to the database as normal
    tm* n = localtime(&t);
    string tt = to_string(n->tm_mday) + "-" + to_string(n->tm_mon+1) + "-" + to_string(n->tm_year + 1900);
    temp->insertRecord(tmp->getCitizen()->citizenId, tmp->getCitizen(), "YES", tt, false);

    delete tmp;
    return true;
  }
}

void VirlistHeader::listNonVaccinatedPersons(string v){
  //find the virus and print the not vaccinated skip list
  VirlistNode* temp = this->searchVirus(v);
  if(temp == NULL){
    cout << "Virus not found" << endl;
    return;
  }else{
    temp->getNotVacced()->print();
  }
}