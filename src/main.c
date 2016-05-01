#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "problem.h"
#include "error.h"

int main(int argv, char ** argc) {


    problem_t problem = problem_create(20, 0.0);

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

	problem.borders[0].position = 2.0;
	problem.borders[1].position = 10.0;
	problem.borders[2].position = 20.0;
	problem.borders[2].u[1] = 10.0;

	problem.materials[0] = ice;
	problem.materials[1] = snow;
	problem.beta = 0.0;

	// Read and create dataset
	FILE * datafile = fopen("data.txt", "r");
	if (datafile == NULL) {
		error_warning("Could not open input file. Using fake values.");
		problem.dataset = dataset_create(3);
	} else {
		problem.dataset = dataset_read(datafile, 3);
		fclose(datafile);
	}


    problem_iterate(&problem, 100000);
    problem_print(&problem);
	problem_destroy(&problem);

    return EXIT_SUCCESS;
}
