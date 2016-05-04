#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "problem.h"
#include "error.h"

int main(int argv, char ** argc) {


    problem_t problem = problem_create(201, 270);

	material_t ice = {
		.alpha = 1.1965*pow(10.0, -6.0),
		.rho = 917.3,
		.L = 334000.0,
		.kappa = 2.246
	};

	material_t snow = {
		.alpha = 6.6671*pow(10.0, -7.0),
		.rho = 584,
		.L = 334000.0,
		.kappa = 0.8048
	};


	problem.borders[0].position = 0.0;
	problem.borders[1].position = 2.5;
	problem.borders[2].position = 199.5;

	problem.materials[0] = ice;
	problem.materials[1] = snow;
	problem.beta = 0.3;

	// Read and create dataset
	FILE * datafile = fopen("data.csv", "r");
	if (datafile == NULL) {
		error_warning("Could not open input file. Using fake values.");
		problem.dataset = dataset_create(4);
	} else {
		problem.dataset = dataset_read(datafile, 4);
		fclose(datafile);
	}

    problem_print_header(&problem);
    problem_iterate(&problem, (unsigned)(24*8.64*pow(10.0, 7.0))); // 24 dag
	problem_destroy(&problem);

    return EXIT_SUCCESS;
}
