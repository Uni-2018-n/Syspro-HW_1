#include <iostream>
using namespace std;

int main(){
	string temp = "2021-3-9";
	string don = "2021-2-10";
	string dt = "2021-5-15";
	if(temp >= don && temp <= dt){
		cout << "true" << endl;
	}else{
		cout << "false" << endl;
	}
	return 0;
}
