#include <iostream>
using namespace std;

class temp{
public:
  int* t;
  temp(int* f){
    t= f;
  }
  ~temp(){
    delete t;
  }
  void testprint(){
    cout << *t << endl;
  }
  void set(int i){
    *t=i;
  }
};

int main(){
  int* k =new int(5);
  temp* z = new temp(k);
  z->testprint();
  z->set(4);
  cout << *k << endl;

  temp* f =new temp(k);
  f->testprint();
  delete z;
  delete f;
	return 0;
}
