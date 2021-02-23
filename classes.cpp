#include <cstring>

#include "classes.hpp"
citizenRecord::citizenRecord(string id, string fn, string ln, string ct, string a, string vn, string v, string dv){
  ERROR =0;
  citizenId = stoi(id);
  firstName = fn;
  lastName= ln;
  country= ct;
  age = stoi(a);
  if(age < 1 || age > 120){
    ERROR = 1;
  }
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
void citizenRecord::testPrint(){
  cout << citizenId << endl;
  cout << firstName << endl;
  cout << lastName << endl;
  cout << country << endl;
  cout << age << endl;
  cout << virusName << endl;
  cout << vaccinated << endl;
  cout << dateVaccinated << endl;
  cout << endl;
}
bool citizenRecord::check_error(){
  return (ERROR == 0) ? 0 : 1;
}
