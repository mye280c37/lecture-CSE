#include "Str.h"
#include <iostream>

using namespace std;

int main(void){
	Str a("I'm a girl");
	cout << a.contents() << " " << a.length() <<"\n";
	a = "I'm a boyssssssss\n";
	cout << a.contents() << " " << a.length() <<"\n";
	cout << a.compare("I'm a a")<<endl;
	Str b(" ");
	cout << b.contents() << "\n" << b.length() << endl;
	char* c = NULL;
	b = c;
	return 0;
}
