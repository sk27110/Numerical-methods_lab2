#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H

#include <cmath>
#include <iostream>

class ISA {
public:
    static constexpr double R_air = 287.0528;   
    static constexpr double g0 = 9.80665;       
    static constexpr double gamma = 1.4;         
    
    static constexpr double h0 = 0;
    static constexpr double h1 = 11000;
    static constexpr double h2 = 20000;
    static constexpr double h3 = 32000;
    static constexpr double h4 = 47000;
    static constexpr double h5 = 51000;
    static constexpr double h6 = 71000;

    static constexpr double T0 = 288.15;         
    static constexpr double p0 = 101325;         
    static constexpr double T1 = 216.65;         
    static constexpr double T2 = 216.65;         
    static constexpr double T3 = 228.65;         
    static constexpr double T4 = 270.65;         
    static constexpr double T5 = 270.65;         

    static constexpr double k0 = -0.0065;
    static constexpr double k2 = 0.001;
    static constexpr double k3 = 0.0028;
    static constexpr double k5 = -0.0028;

    static constexpr double temperature(double h) noexcept {
        if (h < h1) return T0 + k0 * h;
        if (h < h2) return T1;
        if (h < h3) return T2 + k2 * (h - h2);
        if (h < h4) return T3 + k3 * (h - h3);
        if (h < h5) return T4;
        if (h <= h6) return T5 + k5 * (h - h5);
        return T5 + k5 * (h6 - h5); 
    }

    static double pressure(double h) noexcept {
        const double p1 = p0 * std::pow(T1/T0, -g0/(k0*R_air));
        const double p2 = p1 * std::exp(-g0*(h2-h1)/(R_air*T1));
        const double p3 = p2 * std::pow(T3/T2, -g0/(k2*R_air));
        const double p4 = p3 * std::pow(T4/T3, -g0/(k3*R_air));
        const double p5 = p4 * std::exp(-g0*(h5-h4)/(R_air*T4));
        
        if (h < h1) {
            double T = temperature(h);
            return p0 * std::pow(T/T0, -g0/(k0*R_air));
        }
        if (h < h2) {
            return p1 * std::exp(-g0*(h - h1)/(R_air*T1));
        }
        if (h < h3) {
            double T = temperature(h);
            return p2 * std::pow(T/T2, -g0/(k2*R_air));
        }
        if (h < h4) {
            double T = temperature(h);
            return p3 * std::pow(T/T3, -g0/(k3*R_air));
        }
        if (h < h5) {
            return p4 * std::exp(-g0*(h - h4)/(R_air*T4));
        }
        if (h <= h6) {
            double T = temperature(h);
            return p5 * std::pow(T/T5, -g0/(k5*R_air));
        }
        double T = temperature(h);
        return p5 * std::pow(T/T5, -g0/(k5*R_air));
    }

    static double density(double h) noexcept {
        double T = temperature(h);
        double p = pressure(h);
        return p/(R_air*T);
    }

    static double soundSpeed(double h) noexcept {
        double T = temperature(h);
        return std::sqrt(gamma*R_air*T);
    }
};

#endif