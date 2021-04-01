#include "Header.h"

void Count_Digits(int N){
    // initialize array result before count digits of page N
	for ( int i = 0; i <= DIGITS; i++){
		result[i] = 0;
	}

	// from page 1 to N, get all digits of page i and put it in a correct array element
	for ( int i = 1; i <= N; i++ ){
		int n = i;
		while( n != 0){
			// get a digit of page i
			int tmp = n % 10;
			n /= 10;
			result[tmp]++;
		}
	}
}

