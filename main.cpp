#include <iostream>
#include <cstring>
#include <fstream>

#include "classes.hpp"

using namespace std;

int main(int argc, char* argv[]){
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

  ifstream records(pathToRecords);
  {
    string line;
    while(getline(records, line)){
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
      citizenRecord*  temp_citizen = new citizenRecord(temp[0], temp[1], temp[2], temp[3], temp[4]);
      if(temp_citizen->check_error()){
        cout << "ERROR citizen" << endl << endl;
      }

      vaccinateRecord* temp_vaccinate = new vaccinateRecord(temp_citizen, temp[5], temp[6], temp[7]);
      if(temp_vaccinate->check_error()){
        cout << "ERROR vaccinate" << endl << endl;
      }else{
        temp_vaccinate->testPrint();
      }

      delete temp_vaccinate;
    }
  }





  delete[] pathToRecords;
  records.close();
	return 0;
}
