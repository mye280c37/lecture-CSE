#include "Header.h"

int main(){
	int T,N;

	// the number of testcase T
	scanf("%d", &T);

	for(int t = 1; t <= T; t++){
		// the number of page N
		scanf("%d", &N);
		Count_Digits(N);
		Print_Output();
	}

	return 0;
}
