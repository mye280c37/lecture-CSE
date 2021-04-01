#include "Header.h"

void Print_Output(){
	for( int i = 0;  i<DIGITS; i++ ){
		printf("%d ", result[i]);
		if ( i == 9 ) printf("%d", result[i]);
	}
	printf("\n");
}
