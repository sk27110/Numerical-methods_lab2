#include "geodetic.h"
#include <cmath>
#include <stdexcept>

void cartesianToGeodetic(
    double x, double y, double z,
    double& latitude, double& longitude, double& height)
{
    const double u = std::hypot(x, y);
    longitude = std::atan2(y, x);
    
    if (u < 1e-12) {
        latitude = (z >= 0) ? M_PI/2 : -M_PI/2;
        height = std::abs(z) - WGS84_B;
        return;
    }
    
    double theta = std::atan2(z, u);
    double last_theta;
    double N = WGS84_A;
    
    for (int i = 0; i < 10; ++i) {
        last_theta = theta;
        const double sin_theta = std::sin(theta);
        N = WGS84_A / std::sqrt(1.0 - WGS84_E2 * sin_theta * sin_theta);
        theta = std::atan2(z + WGS84_E2 * N * sin_theta, u);
        if (std::abs(theta - last_theta) < 1e-12) break;
    }
    
    const double sin_theta = std::sin(theta);
    N = WGS84_A / std::sqrt(1.0 - WGS84_E2 * sin_theta * sin_theta);
    height = u / std::cos(theta) - N;
    
    if (height < 0) {
        const double M = WGS84_A * (1 - WGS84_E2) 
                       / std::pow(1 - WGS84_E2 * sin_theta * sin_theta, 1.5);
        height = z / sin_theta - M;
    }
    
    latitude = theta;
}