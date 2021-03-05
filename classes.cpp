#include <cstring>

#include "classes.hpp"
citizenRecord::citizenRecord(string id, string fn, string ln, string ct, string a){
  ERROR =0;
  citizenId = stoi(id);
  firstName = fn;
  lastName= ln;
  country= ct;
  age = stoi(a);
  if(age < 1 || age > 120){
    ERROR = 1;
  }
}

void citizenRecord::testPrint(){
  cout << citizenId << endl;
  cout << firstName << endl;
  cout << lastName << endl;
  cout << country << endl;
  cout << age << endl;
}
bool citizenRecord::check_error(){
  return (ERROR == 0) ? 0 : 1;
}

//////////////////////////////////////// vaccinateRecord
vaccinateRecord::vaccinateRecord(string vn, string v, string dv){
  // citizen = c;
  virusName= vn;
  if(v == "YES"){
    vaccinated =1;
    dateVaccinated= dv;
  }else if(v == "NO"){
    vaccinated =0;
    if(dv != ""){
      ERROR =1;
    }else{
      dateVaccinated = "-";
    }
  }
}

vaccinateRecord::~vaccinateRecord(){
  // delete citizen;
}

void vaccinateRecord::testPrint(){
  // citizen->testPrint();
  cout << virusName << endl;
  cout << vaccinated << endl;
  cout << dateVaccinated << endl;
  cout << endl;
}

bool vaccinateRecord::check_error(){
  return (ERROR == 0) ? 0 : 1;
}
