#include "Str.h"
#include <iostream>

using namespace std;

// length Str constructor
Str::Str(int leng){
	if (leng < 0){
		cerr << "Str length error!\nlength must be bigger than or equal to 0\n";
	}
	else{
		len = leng;
		str = new char[leng+1];
		str[leng]='\0';
	}
 
}

// string Str constructor
Str::Str(char *neyong){
	if(neyong == NULL){
		cerr << "NULL pointer error!\n";
	}
	else{
		len = strlen(neyong);
		str = new char[len+1];
		strcpy(str, neyong);
	}
}

// Str destructor
Str::~Str(){
	delete[] str;
}

// return length of string(len)
int Str::length(void){
	return len;
}

// return string(str)
char* Str::contents(void){
	return str;
}

// strcmp with Str
int Str::compare(class Str& a){
	return strcmp(str, a.contents());
}

// strcmp with string
int Str::compare(char *a){
	return strcmp(str, a);

}

// change str to string argument
void Str::operator=(char *a){
	if (a == NULL){
		cerr << "NULL pointer error!\n";
	}
	else{
		delete[] str;
		len = strlen(a);
		str = new char[len+1];
		strcpy(str, a);
	}

}

// change str to Str instance's contents
void Str::operator=(class Str& a){
	delete[] str;
	len = a.length();
	str = new char[len+1];
	strcpy(str, a.contents());
}






