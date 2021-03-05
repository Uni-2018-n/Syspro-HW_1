#include <iostream>
#include <cstring>
#include <fstream>

#include "classes.hpp"
#include "generalList.hpp"

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
  GlistHeader* main_list = new GlistHeader();
  ifstream records(pathToRecords);
  {
    string line;
    while(getline(records, line)){
      main_list->insertRecord(line);
    }
    main_list->testPrint();
  }




  delete main_list;
  delete[] pathToRecords;
  records.close();
	return 0;
}
