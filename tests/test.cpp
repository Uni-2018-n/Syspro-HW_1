#include <iostream>
#include <cstring>

using namespace std;
string reverse(string t){
  string temp= "";
	cout << "here:"<< t << endl;
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
    temp = temp + c[8];
    temp = temp + c[9];
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
//2020-12-27
string checkAndFormatDate(string d){
  if(d[2] !='-' || d[1] == '-'){
		// cout << d << endl;
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

int main(){
	cout << checkAndFormatDate("2020-12-27") << endl;
	return 0;
}
