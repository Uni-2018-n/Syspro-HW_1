#include "generalList.hpp"

////////////////////////////listNode
listNode::listNode(citizenRecord* c){
  citizen = c;
  next = NULL;
}

listNode::~listNode(){
  delete citizen;
}

citizenRecord* listNode::getCitizen(){
  return citizen;
}
void listNode::setNext(listNode* n){
  next = n;
}
listNode* listNode::getNext(){
  return next;
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
    temp = temp->getNext();
    delete tmp;
  }
  delete countries;
  delete viruses;
}

listNode* GlistHeader::searchCitizen(int id){
  listNode* temp = start;
  while(temp != NULL){
    if(*(temp->getCitizen()->citizenId) == id){
      return temp;
    }
    temp = temp->getNext();
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
    if(tmp->getCitizen()->firstName.compare(temp[1]) !=0 ||
      tmp->getCitizen()->lastName.compare(temp[2]) !=0 ||
      tmp->getCitizen()->country->compare(temp[3]) !=0 ||
      tmp->getCitizen()->age != stoi(temp[4])){
        cout << "ERROR found record with same id but different data " << line << endl;
        return;
    }

    VarlistNode* temp_virus = viruses->searchVirus(temp[5]);
    if(temp_virus == NULL){
      temp_virus = viruses->insertVirus(temp[5]);
    }
    temp_virus->insertRecord(tmp->getCitizen()->citizenId, tmp->getCitizen(), temp[6], temp[7]);
  }else{//first time we see this citizen
    string* temp_country = countries->searchItem(temp[3]);
    if(temp_country == NULL){
      temp_country = countries->insertItem(temp[3]);
    }
    citizenRecord*  temp_citizen = new citizenRecord(temp[0], temp[1], temp[2], temp_country, temp[4]);

    listNode* new_node = new listNode(temp_citizen);
    if(start == NULL){//case citizen is first to be inserted
      start = new_node;
      end = new_node;
    }else{//if not, just insert citizen at end of list
      end->setNext(new_node);
      end = new_node;
    }

    VarlistNode* temp_virus = viruses->searchVirus(temp[5]);
    if(temp_virus == NULL){
      temp_virus = viruses->insertVirus(temp[5]);
    }
    temp_virus->insertRecord(new_node->getCitizen()->citizenId, new_node->getCitizen(), temp[6], temp[7]);
  }
}

void GlistHeader::vaccineStatusBloom(int i, string v){
  viruses->vaccineStatusBloom(i,v);
}

void GlistHeader::vaccineStatus(int i, string v){
  viruses->vaccineStatus(i, v);
}

void GlistHeader::vaccineStatus(int i){
  viruses->vaccineStatus(i);
}

void GlistHeader::insertCitizenRecord(string line){
  insertRecord(line);
}

void GlistHeader::populationStatus(string vn, string don, string dt, string c, bool t){//with country
  VarlistNode* temp = viruses->searchVirus(vn);
  if(temp == NULL){
    cout << "ERROR VIRUS NOT FOUND" << endl;
  }else{
    if(!t){
      countryStatsNode* stats = temp->getVacced()->populationStatus(don, dt, c);
      stats = temp->getNotVacced()->populationStatus(stats, c);
      stats->print();
      delete stats;
    }else{//case age

    }
  }
}

void GlistHeader::populationStatus(string vn, string don, string dt, bool t){//without country
  VarlistNode* temp = viruses->searchVirus(vn);
  if(temp == NULL){
    cout << "ERROR VIRUS NOT FOUND" << endl;
  }else{
    if(!t){
      countryStatsHeader* stats = temp->getVacced()->populationStatus(don, dt);
      stats = temp->getNotVacced()->populationStatus(stats);
      stats->print();
      delete stats;
    }else{//case age

    }
  }
}

void GlistHeader::vaccinateNow(int i, string fn, string ln, string c, string a, string v){
  if(!viruses->vaccinateNow(i, fn, ln, c, a, v)){
    time_t t= time(0);
    tm* n = localtime(&t);
    string dv = to_string(n->tm_year + 1900) + "-" + to_string(n->tm_mon+1) + "-" + to_string(n->tm_mday);
    insertRecord(i + " " + fn + " " + ln + " " + a + " " + v + "YES " + dv);
  }
}

void GlistHeader::listNonVaccinatedPersons(string v){
  viruses->listNonVaccinatedPersons(v);
}

void GlistHeader::testPrint(){
  listNode* temp = start;
  while(temp != NULL){
    cout << *(temp->getCitizen()->citizenId) << "-> ";
    temp = temp->getNext();
  }
  cout << endl;
  countries->testPrint();
  viruses->testPrint();
}
