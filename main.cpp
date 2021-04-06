#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include <errno.h>

#include "classes.hpp"
#include "generalList.hpp"

using namespace std;

int main(int argc, char* argv[]){
  srand(time(NULL));
  char* pathToRecords;
  int bloomSize;
  if(argc != 5){//simple input error checking
    cout << "wrong input try: \"-c citizenRecordsFile -b bloomSize\"" << endl;
    return 1;
  }
  for(int i=1;i<argc;i++){
    if(strcmp(argv[i], "-c") ==0){//used this method for possibility that the input is in wrong order etc
      pathToRecords = new char[strlen(argv[i+1])+1]();
      strcpy(pathToRecords, argv[i+1]);
    }else if(strcmp(argv[i], "-b") ==0){
      bloomSize = atoi(argv[i+1]) *8;
      break;
    }
  }
  GlistHeader* main_list = new GlistHeader(bloomSize);//initialize the general list
  ifstream records(pathToRecords);//start reading from input file and inserting records to the general list
  if(records.fail()){
    perror(pathToRecords);
    delete main_list;
    delete[] pathToRecords;
    records.close();
    return 1;
  }
  {
    string line;
    while(getline(records, line)){
      main_list->insertRecord(line, false);
    }
  }
  delete[] pathToRecords;
  records.close();//since we are done with reading from the file we wont be needing the file


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


  while(true){//simple switch-case but for strings
    string command;
    cin >> command;
    if(command == "/exit"){
      delete main_list;
      return 0;
    }
    cin.get();
    string line;
    getline(cin, line);
    string temp[8];//convert the readed string to a string array for more simplicity
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
      cout << "Done!" << endl;
    }else if(command == "/vaccineStatus"){
      if(i == 2){
        main_list->vaccineStatus(stoi(temp[0]), temp[1]);
        cout << "Done!" << endl;
      }else{
        main_list->vaccineStatus(stoi(temp[0]));
        cout << "Done!" << endl;
      }
    }else if(command == "/populationStatus"){
      if(i == 4){
        temp[2] = checkAndFormatDate(temp[2]);//error checking and converting to programm-friendly the date
        temp[3] = checkAndFormatDate(temp[3]);//(we need to be like yyyy-mm-dd because its comparable)
        if(temp[2] == "" || temp[3] == ""){//if checkAndFormatDate returned an empty string we had a problem with reading the date and abandoned we command
          cout << "ERROR WRONG DATE FORMAT" <<endl;
          continue;
        }
        main_list->populationStatus(temp[1], temp[2], temp[3], temp[0], false);
        cout << "Done!" << endl;
      }else if(i==3){
        temp[1] = checkAndFormatDate(temp[1]);
        temp[2] = checkAndFormatDate(temp[2]);
        if(temp[1] == "" || temp[2] == ""){
          cout << "ERROR WRONG DATE FORMAT" <<endl;
          continue;
        }
        main_list->populationStatus(temp[0], temp[1], temp[2], false);
        cout << "Done!" << endl;
      }else{
        cout << "ERROR WRONG FORMAT" << endl;
      }
    }else if(command == "/popStatusByAge"){
      if(i == 4){
        temp[2] = checkAndFormatDate(temp[2]);
        temp[3] = checkAndFormatDate(temp[3]);
        if(temp[2] == "" || temp[3] == ""){
          cout << "ERROR WRONG DATE FORMAT" <<endl;
          continue;
        }
        main_list->populationStatus(temp[1], temp[2], temp[3], temp[0], true);
        cout << "Done!" << endl;
      }else if(i==3){
        temp[1] = checkAndFormatDate(temp[1]);
        temp[2] = checkAndFormatDate(temp[2]);
        if(temp[1] == "" || temp[2] == ""){
          cout << "ERROR WRONG DATE FORMAT" <<endl;
          continue;
        }
        main_list->populationStatus(temp[0], temp[1], temp[2], true);
        cout << "Done!" << endl;
      }else{
        cout << "ERROR WRONG FORMAT" << endl;
      }
    }else if(command == "/insertCitizenRecord"){
      main_list->insertCitizenRecord(line);
      cout << "Done!" << endl;
    }else if(command == "/vaccinateNow"){
      main_list->vaccinateNow(stoi(temp[0]), temp[1], temp[2], temp[3], temp[4], temp[5]);
      cout << "Done!" << endl;
    }else if(command == "/list-nonVaccinated-Persons"){
      main_list->listNonVaccinatedPersons(temp[0]);
      cout << "Done!" << endl;
    }
    cout << endl;
  }
}
