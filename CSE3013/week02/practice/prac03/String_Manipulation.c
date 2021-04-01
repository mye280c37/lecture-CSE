#include "Header.h"

void Remove_Blanks_At_The_End( char *line ) {
	int i, k, newline_flag = 0;

	// 전체 문장에 대하여 line[k] 가 줄바꿈이면 flag를 1로 set, '\0'이면 ~~
	// 인자로 들어온 line이 텍스트 파일의 마지막 줄인지 아닌지 판단
	for ( k = 0; ; k++ ) {
		if ( line[k] == '\n' ) {
			newline_flag = 1;
			break;
		}
		else if ( line[k] == '\0' ) {
			break;
		}

	}
	// 전체 문장에 대하여 line[i]가 space가 아니라면 break,
	/* 
		문장의 마지막의 필요없는 blank들을 지워주는 for loop
		위의 for문에서 k가 인자로 들어온 문장의 마지막까지 갔으므로 
		바로 앞에서부터 ' '의 범위를 판단한다.
	*/
	for ( i = k-1; i >= 0; i-- ) {
		if ( line[i] != ' ' ) {
			break;
		}
	}
	/*
		바로 직전 for loop에서 i가 인자로 들어온 문장의 마지막 문자까지 이동하였으므로
		필요없는 blanks를 없애기 위해 i+1에 문장의 끝을 나타내는 '\n' 또는 '\0'을 넣어준다. 
	*/
	// i를 다음 위치로 이동
	i++;
	// flag가 1일때 문장의 마지막은 줄바꿈&space, flag가 1이 아니라면 '\0'
	// flag가 0일 경우 파일의 마지막 문장 즉, EOF를 의미하므로 ' '를 넣어줄 필요가 없이 문자 바로 뒤에 '\0'을 넣어준다.
	if ( newline_flag == 1 ) {
		line[i] = '\n';
		line[i+1] = ' ';
	}
	else {
		line[i] = '\0';
	}
}

void Get_Blanks_Chars( char *line, int Start, int *N_Blanks, int *N_Chars ) {
	int i, blank_flag = 0;

	*N_Blanks = *N_Chars = 0;
	for ( i = Start; ; i++ ) {
		if ( (line[i] == '\n') || (line[i] == '\0') ) {
			break;
		}
		else if ( line[i] == ' ' ) {
			if ( blank_flag == 0 ) {
				++(*N_Blanks);
			}
			else {
				break;
			}
		}
		else {
			blank_flag = 1;
			++(*N_Chars);
		}
	}
}
