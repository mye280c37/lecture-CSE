#include <stdio.h>

main(void){
	int i;
	double num;

	// set breakpoint in for loop and debug,
	// we can check value of num is wrong, That's because of data type
	// so we have to cast variable i as double.

	for( i=0; i<5; i++){
		num = i/2+1;
		printf("num is %f \n", num);
	}
}
