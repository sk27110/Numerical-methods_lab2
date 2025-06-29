#include "atmosphere.h"

constexpr double pow_const(double base, int exp) {
    return (exp == 0) ? 1.0 : base * pow_const(base, exp - 1);
}

constexpr double exp_const(double x) {
    double sum = 1.0;
    double term = 1.0;
    for(int i = 1; i < 10; ++i) {
        term *= x / i;
        sum += term;
    }
    return sum;
}

constexpr double ISA::temperature(double h) noexcept {
    if (h < h1) return T0 + k0 * h;
    if (h < h2) return T1;
    if (h < h3) return T2 + k2 * (h - h2);
    if (h < h4) return T3 + k3 * (h - h3);
    if (h < h5) return T4;
    if (h <= h6) return T5 + k5 * (h - h5);
    return 0; 
}

double ISA::pressure(double h) noexcept {
    const double p1 = p0 * pow_const(T1/T0, -g0/(k0*R_air));
    const double p2 = p1 * exp_const(-g0*(h2-h1)/(R_air*T1));
    const double p3 = p2 * pow_const(T3/T2, g0/(k2*R_air));
    const double p4 = p3 * pow_const(T4/T3, g0/(k3*R_air));
    const double p5 = p4 * exp_const(-g0*(h5-h4)/(R_air*T4));
    
    if (h < h1) {
        double T = temperature(h);
        return p0 * pow_const(T/T0, -g0/(k0*R_air));
    }
    if (h < h2) {
        return p1 * exp_const(-g0*(h - h1)/(R_air*T1));
    }
    if (h < h3) {
        double T = temperature(h);
        return p2 * pow_const(T/T2, g0/(k2*R_air));
    }
    if (h < h4) {
        double T = temperature(h);
        return p3 * pow_const(T/T3, g0/(k3*R_air));
    }
    if (h < h5) {
        return p4 * exp_const(-g0*(h - h4)/(R_air*T4));
    }
    if (h <= h6) {
        double T = temperature(h);
        return p5 * pow_const(T/T5, g0/(k5*R_air));
    }
    return 0;
}

double ISA::density(double h) noexcept {
    double T = temperature(h);
    double p = pressure(h);
    return p/(R_air*T);
}

double ISA::soundSpeed(double h) noexcept {
    double T = temperature(h);
    return std::sqrt(gamma*R_air*T);
}