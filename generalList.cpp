#include "generalList.hpp"


////////////////////////////listNode
listNode::listNode(citizenRecord* c, vaccinateRecord* v){
  citizen = c;
  vaccs= new VlistHeader();
  vaccs->insertItem(v);
  next = NULL;
}

listNode::~listNode(){
  delete citizen;
  delete vaccs;
}


////////////////////////////GlistHeader
GlistHeader::GlistHeader(){
  start = NULL;
  end = NULL;
}

GlistHeader::~GlistHeader(){
  listNode* temp = start;
  listNode* tmp = NULL;
  while(temp != NULL){
    tmp = temp;
    temp = temp->next;
    delete tmp;
  }
}

listNode* GlistHeader::searchCitizen(int id){
  listNode* temp = start;
  while(temp != NULL){
    if(temp->citizen->citizenId == id){
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}

void GlistHeader::insertRecord(string line){
  string temp[8];
  int i=0;
  string word = "";
  for(auto x : line){
    if( x== ' '){
      temp[i] = word;
      i++;
      word ="";
    }else{
      word = word + x;
    }
  }
  temp[i] = word;
  citizenRecord*  temp_citizen = new citizenRecord(temp[0], temp[1], temp[2], temp[3], temp[4]);
  if(temp_citizen->check_error()){
    cout << "ERROR citizen: " << line << endl << endl;
    delete temp_citizen;
    return;
  }

  listNode* tmp = searchCitizen(temp_citizen->citizenId);
  if(tmp != NULL){
    if(tmp->citizen->firstName.compare(temp_citizen->firstName) !=0 ||
      tmp->citizen->lastName.compare(temp_citizen->lastName) !=0 ||
      tmp->citizen->country.compare(temp_citizen->country) !=0 ||
      tmp->citizen->age != temp_citizen->age){
        cout << "ERROR: found record with same id but different data " << line << endl << endl;
        delete temp_citizen;
        return;
    }
    delete temp_citizen;//tmp->citizen has our data, no need for temp_citizen
  }

  vaccinateRecord* temp_vaccinate = new vaccinateRecord(temp[5], temp[6], temp[7]);
  if(temp_vaccinate->check_error()){
    cout << "ERROR vaccinate: " << line << endl << endl;
    delete temp_vaccinate;
    return;
  }

  if(tmp == NULL){//first time we see this citizen
    listNode* new_node = new listNode(temp_citizen, temp_vaccinate);
    if(start == NULL){//case citizen is first to be inserted
      start = new_node;
      end = new_node;
    }else{//if not, just insert citizen at end of list
      end->next = new_node;
      end = new_node;
    }
    return;
  }

  {
    VlistNode* temp = tmp->vaccs->start;
    while(temp != NULL){
      if(temp->item->virusName.compare(temp_vaccinate->virusName) ==0){
        cout << "ERROR record already inside " << line << endl << endl;
        delete temp_vaccinate;
        return;
      }
      temp =temp->next;
    }
    tmp->vaccs->insertItem(temp_vaccinate);
    return;
  }
}

void GlistHeader::testPrint(){
  listNode* temp = start;
  while(temp != NULL){
    cout << temp->citizen->citizenId;
    temp->vaccs->testPrint();
    cout << "-> ";
    temp = temp->next;
  }
  cout << endl;
}














//
