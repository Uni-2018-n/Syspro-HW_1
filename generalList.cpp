#include "generalList.hpp"


////////////////////////////listNode
listNode::listNode(citizenRecord* c, string* v){
  citizen = c;
  vaccs= new SlistHeader();
  vaccs->insertItem(v);
  next = NULL;
}

listNode::~listNode(){
  delete citizen;
  delete vaccs;
}


////////////////////////////GlistHeader
GlistHeader::GlistHeader(int bloom){
  start = NULL;
  end = NULL;
  countries = new ClistHeader();
  viruses = new VarlistHeader(bloom);
}

GlistHeader::~GlistHeader(){
  listNode* temp = start;
  listNode* tmp = NULL;
  while(temp != NULL){
    tmp = temp;
    temp = temp->next;
    delete tmp;
  }
  delete countries;
  delete viruses;
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

  {
    int errors = stoi(temp[4]);
    if(errors < 1 || errors > 120){
      cout << "ERROR found record with age out of boundaries " << line << endl;
      return;
    }
    if((temp[6] == "YES" && temp[7] == "") || (temp[6] == "NO" && temp[7] != "")){
      cout << "ERROR found record with wrong vaccination input " << line << endl;
      return;
    }
  }

  listNode* tmp = searchCitizen(stoi(temp[0]));
  if(tmp != NULL){
    if(tmp->citizen->firstName.compare(temp[1]) !=0 ||
      tmp->citizen->lastName.compare(temp[2]) !=0 ||
      tmp->citizen->country->compare(temp[3]) !=0 ||
      tmp->citizen->age != stoi(temp[4])){
        cout << "ERROR found record with same id but different data " << line << endl;
        return;
    }

    SlistNode* tvac = tmp->vaccs->start;
    while(tvac != NULL){
      if(tvac->item->compare(temp[5]) ==0){
        cout << "ERROR record already inside " << line << endl;
        return;
      }
      tvac =tvac->next;
    }

    string* temp_virus = viruses->searchVirus(temp[5]);
    if(temp_virus == NULL){
      temp_virus = new string(temp[5]);
      viruses->insertVirus(temp_virus);
    }
    tmp->vaccs->insertItem(temp_virus);
  }else{//first time we see this citizen
    string* temp_country = countries->searchItem(temp[3]);
    if(temp_country == NULL){
      temp_country = new string(temp[3]);
      countries->insertItem(temp_country);
    }
    citizenRecord*  temp_citizen = new citizenRecord(temp[0], temp[1], temp[2], temp_country, temp[4]);

    string* temp_virus = viruses->searchVirus(temp[5]);
    if(temp_virus == NULL){
      temp_virus = new string(temp[5]);
      viruses->insertVirus(temp_virus);
    }

    listNode* new_node = new listNode(temp_citizen, temp_virus);
    if(start == NULL){//case citizen is first to be inserted
      start = new_node;
      end = new_node;
    }else{//if not, just insert citizen at end of list
      end->next = new_node;
      end = new_node;
    }
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
  countries->testPrint();
  viruses->testPrint();
}














//
