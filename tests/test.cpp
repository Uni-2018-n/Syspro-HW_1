#include <iostream>
#include <time.h>
using namespace std;

int main(){
  srand(time(NULL));
  int t=0;
  for(int i=0;i<100;i++){
    if((random() % 100 + 0) > 50){
      t++;
    }
  }

  cout << t << endl;

	return 0;
}
