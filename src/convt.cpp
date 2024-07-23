#include <cmath>
#include <iostream>
#include <string>

// Linear Curve with gradient
double f_linear(double x, double a = 1, double b = 0) {
    return a * x + b;
}

std::string equation_linear(double a = 1, double b = 0) {
    return std::to_string(a) + " * x + " + std::to_string(b);
}

std::string equation_exponential(double a = M_E, double b = 1) {
    return std::to_string(b) + " * (std::pow(" + std::to_string(a) + ", x) - 1)";
}

std::string equation_logarithmic(double a = M_E, double b = 1) {
    return std::to_string(b) + " * (std::log(x + 1) / std::log(" + std::to_string(a) + "))";
}

std::string equation_s_curve(double a = 1, double b = 0) {
    return "1 / (1 + std::exp(-" + std::to_string(a) + " * (x - " + std::to_string(b) + ")))";
}

std::string equation_parabolic(double a = 1, double b = 0) {
    return std::to_string(a) + " * std::pow(x, 2) + " + std::to_string(b);
}

std::string equation_cubic(double a = 1, double b = 0) {
    return std::to_string(a) + " * std::pow(x, 3) + " + std::to_string(b) + " * std::pow(x, 2)";
}

std::string equation_quadratic(double a = 1, double b = 0) {
    return std::to_string(a) + " * std::pow(x, 2) + " + std::to_string(b) + " * x";
}

std::string equation_step(double a = 10, double b = 1) {
    return std::to_string(b) + " * std::floor(x / (1.0 / " + std::to_string(a) + ")) * (1.0 / " + std::to_string(a) + ")";
}

std::string equation_sensitivity(double a = 2.0, double b = 0) {
    return "pow(x, " + std::to_string(a) + ") + " + std::to_string(b);
}

int main() {
    std::cout << "Linear: " << equation_linear() << std::endl;
    std::cout << "Exponential: " << equation_exponential() << std::endl;
    std::cout << "Logarithmic: " << equation_logarithmic() << std::endl;
    std::cout << "S-Curve: " << equation_s_curve() << std::endl;
    std::cout << "Parabolic: " << equation_parabolic() << std::endl;
    std::cout << "Cubic: " << equation_cubic() << std::endl;
    std::cout << "Quadratic: " << equation_quadratic() << std::endl;
    std::cout << "Step: " << equation_step() << std::endl;
    std::cout << "Sensitivity: " << equation_sensitivity() << std::endl;

    return 0;
}

