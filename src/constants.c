#include <math.h>

#include "constants.h"

constants get_constants(){
    constants a;
    
    // Constants in SI units (Not reduced)
    double dt           = 0.001;                    // Grid size [s]
    double dx           = 0.005;                     // Grid size [m]
    unsigned dump_rate  = 86400/(10*dt);            // Outputs every hour

    double effect   = -500;                         // Maximum cooling effect
    double q_sol    = -53.47;
    double u_e      = 30;                          // Target temperature for cooling
    double h_si     = 200.0;                      // Heat transfer coefficient ice/water [W/m²K]
    double e_a      = 0.73;                         // epsilon_atmosfære (Emissivity)
    double e_o      = 0.611;                        // e_overflate (Vapor pressure) [kPa]
    double em_s     = 0.96;                         // epsilon_snø (Emissivity)
    double sigma    = 5.67036713*pow(10.0, -8.0);   // Stefan-Boltzmann constant [W/m²K^4]
    double v_luft   = 13.30*pow(10.0, -6.0);        // Kinematisk viskositet [m²/s]
    double albedo   = 0.6;                          // Albedo
    double clength  = 1.0;                          // Characteristic length of system [m]
    double k_luft   = 0.0243;                       // Thermal conductivity of air [W/mK]
    double ls       = 5.107*pow(10.0, 4.0);         // Latent heat of sublimation of water [J/mol]
    double R        = 8.3144598;                    // Gas constant [J/K*mol]
    double xi       = 0.622;                        // Forhold i molekylmasser
    double y        = 0.0578;                       // Psychometric constant [kPa/K]
    double rho_l    = 1.293;                        // Density air [kg/m³]
    double cp_luft  = 1005;                         // Spesifikk varmekapasitet til luft [J/kg*K]
    
    a.dt            = dt;
    a.dx            = dx;
    a.dump_rate     = dump_rate;

    // Constants in reduced units
    a.q_sol         = q_sol*pow(dt, 3.0);
    a.u_e           = u_e;
    a.effect        = effect*pow(dt, 3.0);
    a.h_si          = h_si*pow(dt, 3.0);
    a.e_a           = e_a;
    a.e_o           = e_o*dx*dt*dt;
    a.em_s          = em_s;
    a.sigma         = sigma*pow(dt, 3.0);
    a.v_luft        = v_luft*dt/(dx*dx);
    a.albedo        = albedo;
    a.clength       = clength/dx;
    a.k_luft        = k_luft*pow(dt, 3.0)/dx;
    a.ls            = ls*dt*dt/(dx*dx);
    a.R             = R*(dt*dt)/(dx*dx);
    a.xi            = xi;
    a.y             = y*dx*dt*dt;
    a.rho_l         = rho_l*pow(dx, 3.0);
    a.cp_luft       = cp_luft*(dt*dt)/(dx*dx);

    return a;
}
