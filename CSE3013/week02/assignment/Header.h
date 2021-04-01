#include <stdio.h>
#include <stdlib.h>

// the number of digits (0~9)
#define DIGITS 10

// array of the number of each digit	
int result[DIGITS];

/*
    <input> 
        N (int): a page to be counted
    count all digits in page 1 from N
*/
void Count_Digits(int N);

/*
    print all elements of array result
    each index means the number of digit same with the index
*/
void Print_Output();
