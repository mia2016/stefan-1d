#include <math.h>

// Constants used in heat flux calculation
double q_bs     = -115.0;                       // kjøling fra betong
double e_o      = 0.611;                        // e_overflate (Vapor pressure)
double em_s     = 0.96;                         // epsilon_snø (Emissivity)
double sigma    = 5.67036713*pow(10.0, -8.0);   // Stefan-Boltzmann constant [W/m²K^4]
double v_luft   = 13.30*pow(10.0, -6.0);        // Kinematisk viskositet [m²/s]
double albedo   = 0.6;                          // Albedo []
double clength  = 1.0;                          // Characteristic length of system [m]
double k_luft   = 0.0243;                       // Thermal conductivity of air [W/mK]
double ls       = 2.834*pow(10.0, 6.0);         // Latent heat of sublimation
double R        = 8.3144598;                    // Gas constant [J/K*mol]
double xi       = 0.622;                        // Forholdet mellom molkylmassen til vanndamp og tørr luft
