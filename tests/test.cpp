#include <iostream>
using namespace std;

int main(){
	const char date1[] = "10/10/2000";
const char date2[] = "31/2/2012";
struct tm tm;

if (!strptime(date1, "%d/%m/%Y", &tm)) std::cout << "date1 isn't valid\n";
if (!strptime(date2, "%d/%m/%Y", &tm)) std::cout << "date2 isn't valid\n";
	return 0;
}
