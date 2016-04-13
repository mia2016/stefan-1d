#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "problem.h"

int main(int argv, char ** argc) {


    problem_t problem = problem_create(80, 0.0);

	//TODO: Continue initialization
	problem.s[2] = 10.0;
	problem.dt = 0.01;

    problem_iterate(&problem, 0.5);

    problem_print(&problem);

	problem_destroy(&problem);

    return EXIT_SUCCESS;
}
