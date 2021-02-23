#ifndef _CLASSES_HPP_
#define _CLASSES_HPP_
#include <iostream>

using namespace std;

class citizenRecord{
  int citizenId;
  string firstName;
  string lastName;
  string country;
  int age;
  string virusName;
  int vaccinated;
  string dateVaccinated;
  int ERROR;
public:
  citizenRecord(string, string, string, string, string, string, string, string);
  void testPrint();
  bool check_error();
};
#endif
