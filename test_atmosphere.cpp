#include "atmosphere.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>

void run_isa_tests() {
    struct TestCase {
        std::string name;
        double h;
        double expected_T;
        double expected_p;
        double expected_rho;
        double tol_T;
        double tol_p;
        double tol_rho;
    };


    std::vector<TestCase> tests = {
        {"Sea Level", 0.0, 
         288.15, 101325.0, 1.225, 
         0.01, 1.0, 0.001},
         
        {"Tropopause", 11000.0, 
         216.65, 22632.0, 0.3639, 
         0.01, 50.0, 0.01},
         
        {"Stratosphere (20km)", 20000.0, 
         216.65, 5474.9, 0.0880, 
         0.01, 1.0, 0.001},
         
        {"Stratopause", 47000.0, 
         270.65, 110.91, 0.00143, 
         0.01, 0.1, 0.0001},
         
        {"Mesosphere (60km)", 60000.0, 
         245.45, 20.41, 0.00031,
         0.1, 0.1, 0.0001},
         
        {"Model Limit", 71000.0, 
         214.65, 3.956, 0.000064, 
         0.1, 0.1, 0.00001}
    };

    std::cout << "========================================\n";
    std::cout << "  ISA MODEL VALIDATION TESTS\n";
    std::cout << "========================================\n\n";
    
    std::cout << std::fixed << std::setprecision(3);
    
    int passed = 0;
    for (const auto& test : tests) {
        double T = ISA::temperature(test.h);
        double p = ISA::pressure(test.h);
        double rho = ISA::density(test.h);
        
        double T_diff = T - test.expected_T;
        double p_diff = p - test.expected_p;
        double rho_diff = rho - test.expected_rho;
        
        bool T_ok = std::abs(T_diff) < test.tol_T;
        bool p_ok = std::abs(p_diff) < test.tol_p;
        bool rho_ok = std::abs(rho_diff) < test.tol_rho;
        
        std::cout << "Test: " << test.name << " (" << test.h << " m)\n";
        std::cout << "  Temperature: " << T << " K"
                  << " | Expected: " << test.expected_T << " K"
                  << " | Diff: " << T_diff << " K"
                  << " [" << (T_ok ? "PASS" : "FAIL") << "]\n";
                  
        std::cout << "  Pressure:    " << p << " Pa"
                  << " | Expected: " << test.expected_p << " Pa"
                  << " | Diff: " << p_diff << " Pa"
                  << " [" << (p_ok ? "PASS" : "FAIL") << "]\n";
                  
        std::cout << "  Density:     " << rho << " kg/m³"
                  << " | Expected: " << test.expected_rho << " kg/m³"
                  << " | Diff: " << rho_diff << " kg/m³"
                  << " [" << (rho_ok ? "PASS" : "FAIL") << "]\n";
                  
        std::cout << "----------------------------------------\n";
        
        if (T_ok && p_ok && rho_ok) passed++;
    }
    
    double sea_level_sound = ISA::soundSpeed(0.0);
    double expected_sound = 340.3;
    double sound_diff = sea_level_sound - expected_sound;
    bool sound_ok = std::abs(sound_diff) < 0.1;
    
    std::cout << "Sound Speed Test (0m):\n";
    std::cout << "  Calculated: " << sea_level_sound << " m/s"
              << " | Expected: " << expected_sound << " m/s"
              << " | Diff: " << sound_diff << " m/s"
              << " [" << (sound_ok ? "PASS" : "FAIL") << "]\n";
    
    if (sound_ok) passed++;
    
    std::cout << "\nSUMMARY: " << passed << "/" << tests.size() + 1
              << " tests passed\n";
    std::cout << "========================================\n";
}

int main() {
    run_isa_tests();
    return 0;
}