#ifndef _CLASSES_HPP_
#define _CLASSES_HPP_
#include <iostream>

using namespace std;

class citizenRecord{
public:
  int* citizenId;
  string firstName;
  string lastName;
  string* country;
  int age;
  citizenRecord(string, string, string, string*, string);
  ~citizenRecord();
  void print();
};

#endif
