#ifndef _CLASSES_HPP_
#define _CLASSES_HPP_
#include <iostream>

using namespace std;

class citizenRecord{
public:
  int citizenId;
  string firstName;
  string lastName;
  string country;
  int age;
  int ERROR;
  citizenRecord(string, string, string, string, string);
  void testPrint();
  bool check_error();
};

class vaccinateRecord{
public:
  // citizenRecord* citizen;
  string virusName;
  int vaccinated;
  string dateVaccinated;
  int ERROR;
  vaccinateRecord(string, string, string);
  ~vaccinateRecord();
  void testPrint();
  bool check_error();
};

#endif
