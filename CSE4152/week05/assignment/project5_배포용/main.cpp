#include "my_solver.h"

void (*_f2_3_2)(FILE *, double*, double, int, int);

int main() {
    program2_1(); // make pdf table
    program2_2(); // create random number

    // HOMEWORK
    for (int i = 0; i < 3; i++) {
        program2_3_1();
    }
    
    _f2_3_2 = program2_2_a;
    program2_3_2(); 

    _f2_3_2 = program2_2_b;
    program2_3_2(); 

    _f2_3_2 = program2_2_c;
    program2_3_2();
}
