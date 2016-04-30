#pragma once
typedef struct{
    // Non reduced grid size
    double dt, dx;
    
    // Reduced units
    double q_bs, e_o, em_s, sigma, v_luft, albedo, clength, k_luft, ls, R, xi, y, rho_l, cp_luft;
    
    // Variables dependant on weather
    double h_ls, e_l, cover, windspeed, Rf, q_sol;

} constants;

constants get_constants();
