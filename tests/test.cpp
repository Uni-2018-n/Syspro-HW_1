#include <iostream>
#include <cstring>

using namespace std;

string formatDate(string t){
  for(int i=0;i<(int)t.length();i++){
    int x = t[i];
    if(x != '-'){
      if(x < '0' || x > '9'){
        return "";
      }
    }
  }
  string new_date  = "";

  if(t.find('-') != 2 && t.find('-') != 1){
    string to_return = "";
    string temp="";
    for (int i=0;i<(int)t.length();i++) {
      if(t[i] == '-'){
        to_return = '-' + temp + to_return ;
        temp = "";
        continue;
      }
      temp = temp+t[i];
    }
    to_return = temp + to_return;
    t= to_return;
    if(t.find('-') == 1){
      new_date.append('0' + t.substr(0,t.find('-')+1));
    }else{
      new_date.append(t.substr(0,t.find('-')+1));
    }
    t=t.substr(t.find('-')+1);
    if(t.find('-') == 1){
      new_date.append('0' + t.substr(0,t.find('-')+1));
    }else{
      new_date.append(t.substr(0,t.find('-')+1));
    }
    t=t.substr(t.find('-')+1);
    new_date.append(t);
    to_return = "";
    temp = "";
    for (int i=0;i<(int)new_date.length();i++) {
      if(new_date[i] == '-'){
        to_return = '-' + temp + to_return ;
        temp = "";
        continue;
      }
      temp = temp+new_date[i];
    }
    to_return = temp + to_return;
    return to_return;
  }else{
    if(t.find('-') == 1){
      new_date.append('0' + t.substr(0,t.find('-')+1));
    }else{
      new_date.append(t.substr(0,t.find('-')+1));
    }
    t=t.substr(t.find('-')+1);
    if(t.find('-') == 1){
      new_date.append('0' + t.substr(0,t.find('-')+1));
    }else{
      new_date.append(t.substr(0,t.find('-')+1));
    }
    t=t.substr(t.find('-')+1);
    new_date.append(t);

    string to_return = "";
    string temp="";
    for (int i=0;i<(int)new_date.length();i++) {
      if(new_date[i] == '-'){
        to_return = '-' + temp + to_return ;
        temp = "";
        continue;
      }
      temp = temp+new_date[i];
    }
    to_return = temp + to_return;
    return to_return;
  }
}


int main(){
  cout << formatDate("02-01-2000") << endl;
	return 0;
}
