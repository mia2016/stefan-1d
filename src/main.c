#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "problem.h"

int main(int argv, char ** argc) {


    problem_t problem = problem_create(10, 0.0);

	material_t ice = {
		.alpha = 1.0,
		.rho = 1.0,
		.L = 1.0,
		.kappa = 1.0
	};

	material_t snow = {
		.alpha = 1.0,
		.rho = 1.0,
		.L = 1.0,
		.kappa = 1.0
	};


	//TODO: Continue initialization

	problem.borders[0].position = 2.4;
	problem.borders[1].position = 5.0;
	problem.borders[2].position = 7.0;

	problem.materials[0] = ice;
	problem.materials[1] = snow;
	problem.beta = 0.0;


    problem_iterate(&problem, 100000);
    problem_print(&problem);
	problem_destroy(&problem);

    return EXIT_SUCCESS;
}
