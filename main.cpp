#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include "classes.hpp"
#include "generalList.hpp"

using namespace std;

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

    if(command == "/vaccineStatusBloom"){
      main_list->vaccineStatusBloom(stoi(temp[0]), temp[1]);
    }else if(command == "/vaccineStatus"){
      if(i == 1){
        main_list->vaccineStatus(stoi(temp[0]), temp[1]);
      }else{
        main_list->vaccineStatus(stoi(temp[0]));
      }
    }else if(command == "/populationStatus"){
      if(i == 3){
        main_list->populationStatus(temp[1], temp[2], temp[3], temp[0]);
      }else if(i==2){
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
