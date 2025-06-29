#ifndef GEODETIC_HPP
#define GEODETIC_HPP

// Определяем математические константы
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

constexpr double WGS84_A = 6378137.0;
constexpr double WGS84_F = 1.0 / 298.257223563;
constexpr double WGS84_B = WGS84_A * (1.0 - WGS84_F);
constexpr double WGS84_E2 = 1.0 - (WGS84_B * WGS84_B) / (WGS84_A * WGS84_A);
constexpr double DEG_TO_RAD = M_PI / 180.0;
constexpr double RAD_TO_DEG = 180.0 / M_PI;

void cartesianToGeodetic(
    double x, double y, double z,
    double& latitude, double& longitude, double& height);

#endif