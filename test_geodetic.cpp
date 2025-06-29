#include "geodetic.h"
#include <iostream>
#include <iomanip>
#include <vector>

void test_known_points() {
    struct TestPoint {
        std::string name;
        double x, y, z;
        double lat_deg;
        double lon_deg;
        double height;
        double tol_deg;
        double tol_height;
    };
    
    std::vector<TestPoint> points = {
        {"Эйфелева башня (основание)", 4201151.381, 168330.344, 4780454.847,
         48.858370, 2.294481, 324.0, 1e-5, 1.0},
        {"Красная площадь, Москва", 2849817.751, 2196042.006, 5249081.754,
         55.752023, 37.617499, 155.0, 1e-5, 1.0},
        {"Северный полюс (поверхность)", 0.0, 0.0, WGS84_B,
         90.0, 0.0, 0.0, 1e-9, 1e-3},
        {"Точка на экваторе", WGS84_A, 0.0, 0.0,
         0.0, 0.0, 0.0, 1e-9, 1e-3}
    };
    
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "\nТЕСТИРОВАНИЕ ИЗВЕСТНЫХ ТОЧЕК\n";
    std::cout << "========================================\n";
    
    int passed = 0;
    for (const auto& tp : points) {
        double lat, lon, h;
        cartesianToGeodetic(tp.x, tp.y, tp.z, lat, lon, h);
        
        const double lat_deg = lat * RAD_TO_DEG;
        const double lon_deg = lon * RAD_TO_DEG;
        
        const double lat_diff = std::abs(lat_deg - tp.lat_deg);
        const double lon_diff = std::abs(lon_deg - tp.lon_deg);
        const double h_diff = std::abs(h - tp.height);
        
        const bool lat_ok = lat_diff <= tp.tol_deg;
        const bool lon_ok = lon_diff <= tp.tol_deg;
        const bool h_ok = h_diff <= tp.tol_height;
        
        if (lat_ok && lon_ok && h_ok) {
            std::cout << "[УСПЕХ] " << tp.name 
                      << "\n  Ожидалось: " << tp.lat_deg << "°, " 
                      << tp.lon_deg << "°, " << tp.height << " м"
                      << "\n  Получено:  " << lat_deg << "°, " 
                      << lon_deg << "°, " << h << " м\n";
            passed++;
        } else {
            std::cout << "[ОШИБКА] " << tp.name 
                      << "\n  Ожидалось: " << tp.lat_deg << "°, " 
                      << tp.lon_deg << "°, " << tp.height << " м"
                      << "\n  Получено:  " << lat_deg << "°, " 
                      << lon_deg << "°, " << h << " м"
                      << "\n  Отклонение: " << lat_diff << "°, " 
                      << lon_diff << "°, " << h_diff << " м\n";
        }
        std::cout << "----------------------------------------\n";
    }
    
    std::cout << "РЕЗЮМЕ: " << passed << "/" << points.size() 
              << " тестов пройдено успешно\n";
    std::cout << "========================================\n";
}

int main() {
    test_known_points();
    return 0;
}