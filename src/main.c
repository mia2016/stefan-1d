#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "problem.h"

int main(int argv, char ** argc) {


    problem_t problem = problem_create(10, 270.15);

	material_t ice = {
		.alpha = 5.81*pow(10.0, -7.0),
		.rho = 887.0,
		.L = 1.0,
		.kappa = 2.04
	};

	material_t snow = {
		.alpha = 8.6*pow(10.0, -7.0),
		.rho = 450.0,
		.L = 1.0,
		.kappa = 0.80
	};


	//TODO: Continue initialization

	problem.borders[0].position = 0.4;
	problem.borders[1].position = 4.5;
	problem.borders[2].position = 9.5;

	problem.materials[0] = ice;
	problem.materials[1] = snow;
	problem.beta = 0.3;

    problem_print_header(&problem);
    problem_iterate(&problem, 100000);
	problem_destroy(&problem);

    return EXIT_SUCCESS;
}
