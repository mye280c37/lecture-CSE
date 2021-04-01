#include <iostream>
#include <cstdlib>
#include "RangeArray.h"

using namespace std;

RangeArray::RangeArray(int low, int high) : Array(high-low+1){
	l = low;
	h = high;
}

RangeArray::~RangeArray(){
}

int RangeArray::baseValue(){
	return l;
}

int RangeArray::endValue() {
	return h;
}

int & RangeArray::operator[] (int i) {
	static int tmp;
	if(i >= l && i <= h){
		return data[i-l];
	}
	else{
		cerr << "Array bound error!\n";
		return tmp;
	}
}

int RangeArray::operator[] (int i) const {
	if(i >= l && i <= h){
		return data[i-l];
	}
	else{
		cerr << "Array bound error!\n";
		return 0;
	}
}


