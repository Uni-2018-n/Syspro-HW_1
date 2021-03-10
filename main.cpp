#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include "classes.hpp"
#include "generalList.hpp"

using namespace std;

//0123-56-78
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

int main(int argc, char* argv[]){
  srand(time(NULL));
  char* pathToRecords;
  int bloomSize;
  if(argc != 5){
    cout << "wrong input try: \"-c citizenRecordsFile -b bloomSize\"" << endl;
    return 1;
  }
  for(int i=1;i<argc;i++){
    if(strcmp(argv[i], "-c") ==0){
      pathToRecords = new char[strlen(argv[i+1])+1]();
      strcpy(pathToRecords, argv[i+1]);
    }else if(strcmp(argv[i], "-b") ==0){
      bloomSize = atoi(argv[i+1]) *8;
      break;
    }
  }
  cout << "Input: " << pathToRecords << " " << bloomSize << endl;
  GlistHeader* main_list = new GlistHeader(bloomSize);
  ifstream records(pathToRecords);
  {
    string line;
    while(getline(records, line)){
      main_list->insertRecord(line);
    }
    // main_list->testPrint();
  }
  delete[] pathToRecords;
  records.close();

  cout <<
  "/vaccineStatusBloom citizenID virusName" << endl <<
  "/vaccineStatus citizenID virusName" << endl <<
  "/vaccineStatus citizenID" << endl <<
  "/populationStatus [country] virusName date1 date2" << endl <<
  "/popStatusByAge [country] virusName date1 date2" << endl <<
  "/insertCitizenRecord citizenID firstName lastName country age virusName YES/NO [date]" << endl <<
  "/vaccinateNow citizenID firstName lastName country age virusName" << endl <<
  "/list-nonVaccinated-Persons virusName" << endl <<
  "/exit" << endl << endl;

  // main_list->populationStatus("H1N1", "2019-01-27", "2022-01-20");
  // main_list->listNonVaccinatedPersons("H1N1");
  // delete main_list;
  // return 0;

  while(true){
    string command;
    cin >> command;
    if(command == "/exit"){
      delete main_list;
      return 0;
    }
    cin.get();
    string line;
    getline(cin, line);
    string temp[8];
    int i=0;
    string word = "";
    for(auto x : line){
      if( x== ' '){
        temp[i] = word;
        i++;
        word ="";
      }else{
        word = word + x;
      }
    }
    temp[i] = word;
    i++;
    if(command == "/vaccineStatusBloom"){
      main_list->vaccineStatusBloom(stoi(temp[0]), temp[1]);
    }else if(command == "/vaccineStatus"){
      if(i == 2){
        main_list->vaccineStatus(stoi(temp[0]), temp[1]);
      }else{
        main_list->vaccineStatus(stoi(temp[0]));
      }
    }else if(command == "/populationStatus"){
      if(i == 4){
        temp[2] = checkAndFormatDate(temp[2]);
        temp[3] = checkAndFormatDate(temp[3]);
        if(temp[2] == "" || temp[3] == ""){
          cout << "ERROR WRONG DATE FORMAT" <<endl;
          continue;
        }
        main_list->populationStatus(temp[1], temp[2], temp[3], temp[0]);
      }else if(i==3){
        temp[1] = checkAndFormatDate(temp[1]);
        temp[2] = checkAndFormatDate(temp[2]);
        if(temp[1] == "" || temp[2] == ""){
          cout << "ERROR WRONG DATE FORMAT" <<endl;
          continue;
        }
        main_list->populationStatus(temp[0], temp[1], temp[2]);
      }else{
        cout << "ERROR WRONG FORMAT" << endl;//TODO: do it correctly
      }
    }else if(command == "/popStatusByAge"){

    }else if(command == "/insertCitizenRecord"){
      main_list->insertCitizenRecord(line);
    }else if(command == "/vaccinateNow"){
      main_list->vaccinateNow(stoi(temp[0]), temp[1], temp[2], temp[3], temp[4], temp[5]);
    }else if(command == "/list-nonVaccinated-Persons"){
      main_list->listNonVaccinatedPersons(temp[0]);
    }
    cout << endl;
  }
}
