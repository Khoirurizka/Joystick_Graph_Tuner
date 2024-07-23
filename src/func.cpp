#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <functional>

// Linear Curve with gradient
double f_linear(double x, double a = 1, double b = 0) {
    return a * x + b;
}

// Exponential Curve with base and scale
double f_exponential(double x, double a = M_E, double b = 1) {
    return b * (pow(a, x) - 1);
}

// Logarithmic Curve with base and scale
double f_logarithmic(double x, double a = M_E, double b = 1) {
    return b * (log(x + 1) / log(a));
}

// S-Curve (Sigmoid Curve) with steepness and midpoint
double f_s_curve(double x, double a = 1, double b = 0) {
    return 1 / (1 + exp(-a * (x - b)));
}

// Parabolic Curve with coefficient and offset
double f_parabolic(double x, double a = 1, double b = 0) {
    return a * pow(x, 2) + b;
}

// Cubic Curve with coefficient and offset
double f_cubic(double x, double a = 1, double b = 0) {
    return a * pow(x, 3) + b * pow(x, 2);
}

// Quadratic Curve with coefficients
double f_quadratic(double x, double a = 1, double b = 0) {
    return a * pow(x, 2) + b * x;
}

// Step Curve with number of steps and scale
double f_step(double x, double a = 10, double b = 1) {
    double step_size = 1.0 / a;
    return b * floor(x / step_size) * step_size;
}

// Dead Zone Curve with threshold and scale
double f_dead_zone(double x, double a = 0.1, double b = 1) {
    if (abs(x) < a) {
        return 0;
    } else {
        return b * x;
    }
}

// Sensitivity Curve with sensitivity level and offset
double f_sensitivity(double x, double a = 2.0, double b = 0) {
    return pow(x, a) + b;
}

// Mapping function names to their corresponding implementations
std::map<std::string, std::function<double(double, double, double)>> functions = {
    {"Linear", f_linear},
    {"Exponential", f_exponential},
    {"Logarithmic", f_logarithmic},
    {"S-Curve", f_s_curve},
    {"Parabolic", f_parabolic},
    {"Cubic", f_cubic},
    {"Quadratic", f_quadratic},
    {"Step", f_step},
    {"Dead Zone", f_dead_zone},
    {"Sensitivity", f_sensitivity}
};

int main() {
    std::string function_name;
    double x, a, b;
    
    std::cout << "Enter the function name (Linear, Exponential, Logarithmic, S-Curve, Parabolic, Cubic, Quadratic, Step, Dead Zone, Sensitivity): ";
    std::cin >> function_name;
    
    std::cout << "Enter the value of x: ";
    std::cin >> x;

    std::cout << "Enter the parameter a: ";
    std::cin >> a;

    std::cout << "Enter the parameter b: ";
    std::cin >> b;

    if (functions.find(function_name) != functions.end()) {
        double result = functions[function_name](x, a, b);
        std::cout << "Result: " << result << std::endl;
    } else {
        std::cout << "Invalid function name!" << std::endl;
    }

    return 0;
}

