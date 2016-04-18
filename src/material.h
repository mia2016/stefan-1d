#pragma once

/**
 * Defines a material by its properties.
 */
typedef struct {

	// Thermal diffusivity
	double alpha; //TODO: Better name

	// Density
	double rho; //TODO: Better name

	// Latent heat
	double L; //TODO: Better name
	
	// Conductivity
	double kappa; //TODO: Better name

} material_t;
