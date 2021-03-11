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
string reverse(string t){
  string temp= "";
  char c[t.length()];
  strcpy(c, t.c_str());
  if(t[2] == '-'){
    temp = temp + c[6];
    temp = temp + c[7];
    temp = temp + c[8];
    temp = temp + c[9];
    temp = temp + '-';
    temp = temp + c[3];
    temp = temp + c[4];
    temp = temp + '-';
    temp = temp + c[0];
    temp = temp + c[1];
  }else{
    temp = temp + c[7];
    temp = temp + c[8];
    temp = temp + '-';
    temp = temp + c[5];
    temp = temp + c[6];
    temp = temp + '-';
    temp = temp + c[0];
    temp = temp + c[1];
    temp = temp + c[2];
    temp = temp + c[3];
  }
  // cout << ", " << t << " reversed: " << temp << endl;
  return temp;
}

string checkAndFormatDate(string d){
  if(d[2] !='-'){
    d= reverse(d);
  }
  for(auto x : d){
    if(x != '-'){
      if(x < '0' || x > '9'){
        return "";
      }
    }
  }
  string temp = "";
  int i=0;
  if(d[i+1] >= '0' || d[i+1] <= '9'){
    temp = temp + d[0] + d[1] + '-';
    i=2;
  }else if(d[i+1] == '-'){
    temp = temp + '0' + d[0] + '-';
    i=1;
  }else{
    return "";
  }
  i++;
  if(d[i+1] >= '0' || d[i+1] <= '9'){
    temp = temp + d[i] + d[i+1] + '-';
    i+=2;
  }else if(d[i+1] == '-'){
    temp = temp + '0' + d[i] + '-';
    i+=1;
  }else{
    return "";
  }
  i++;
  while(d[i] != '\0'){
    if(d[i] >= '0' || d[i] <= '9'){
      temp = temp + d[i];
    }else{
      return "";
    }
    i++;
  }
  // cout << "before: " << d << " after: " << temp;
  return reverse(temp);
}

std::string change_date_format(const std::string& date)
{
    char delim = '-';

    std::string new_date = date.substr(0, date.find(delim));
    size_t pos = new_date.length() + 1;

    new_date.insert(0, "-");

    new_date.insert(0, date.substr(pos, date.find(delim, pos) - pos));

    new_date.insert(0, "-");
    pos = new_date.length();

    new_date.insert(0, date.substr(pos, date.length() - 1));

    return new_date;
}


//
