#include <iostream>
#include "Array.h"
#include <cstdlib>

using namespace std;

Array::Array(int size){
	if (size<=0){
		cerr << "Array size error!\n";
		exit(-1);
	}

	data = new int[size];
	// 할당에러 출력해야하나
	len = size;
}

//소멸자
Array::~Array(void){
	delete[] data;
}

int Array::length(void) const {
	return len;
}

int & Array::operator[] (int i){
	static int tmp;
	if (i >= 0 && i < len){
		return data[i];
	}
	else{
		cerr << "Array bound error!\n";
		return tmp;
	}
}

int Array::operator[] (int i) const {
	if (i >= 0 && i < len){
		return data[i];
	}
	else{
		cerr << "Array bound error!\n";
		return 0;
	}
}

void Array::print() {
	cout << "[";
	for (int i = 0; i < len; i++){
		cout << ' ' << data[i];
	}
	cout << "]\n";
}
