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

void citizenRecord::testPrint(){
  cout << citizenId << endl;
  cout << firstName << endl;
  cout << lastName << endl;
  cout << country << endl;
  cout << age << endl;
}
