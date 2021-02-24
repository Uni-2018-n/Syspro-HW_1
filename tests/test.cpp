#include <iostream>
#include "../bloomFilter.hpp"
using namespace std;

int main(){

  bloomFilter t(2);
  t.insert(6);
  cout << t.is_inside(6) << endl;

	return 0;
}
