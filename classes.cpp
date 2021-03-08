#include <cstring>

#include "classes.hpp"
citizenRecord::citizenRecord(string id, string fn, string ln, string* ct, string a){
  citizenId = new int(stoi(id));
  firstName = fn;
  lastName= ln;
  country= ct;
  age = stoi(a);
}

citizenRecord::~citizenRecord(){
  delete citizenId;
}

void citizenRecord::print(){
  cout << *citizenId << " " <<
  firstName << " " <<
  lastName << " " <<
  *country << " " <<
  age << endl;
}
