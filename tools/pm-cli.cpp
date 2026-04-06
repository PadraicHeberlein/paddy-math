#include <iostream>
#include <vector>
#include "CLI/CLI.hpp"
#include "CLI/Timer.hpp"

#include "matrix.hpp"
#include "complex.hpp"
#include "algebra_functions.hpp"

int main(int argc, char** argv) {
    CLI::App app{"PaddyMath CLI - Fast Matrix & Complex Calculations"};

    // --- Complex Subcommand ---
    auto complex_cmd = app.add_subcommand("complex", "Complex number operations (e.g., exp)");
    double real = 0.0, imag = 0.0;
    bool benchmark_complex = false;

    complex_cmd->add_option("real", real, "Real part")->required();
    complex_cmd->add_option("imag", imag, "Imaginary part")->default_val(0.0);
    complex_cmd->add_flag("-b,--benchmark", benchmark_complex, "Run benchmark (1000 iterations)");

    auto complex_exp_cmd = complex_cmd->add_subcommand("exp", "Calculate exp(z)");
    auto complex_sin_cmd = complex_cmd->add_subcommand("sin", "Calculate sin(z)");
    auto complex_cos_cmd = complex_cmd->add_subcommand("cos", "Calculate cos(z)");

    complex_exp_cmd->callback([&]() {
        Complex z(real, imag);
        if (benchmark_complex) {
            CLI::Timer timer("Complex Exp (1000 iterations)");
            for(int i=0; i<1000; ++i) {
                auto res = exp_taylor(z);
                (void)res;
            }
            std::cout << timer << std::endl;
        } else {
            std::cout << "Input: " << z << "\n"
                      << "exp(z): " << exp_taylor(z) << std::endl;
        }
    });

    complex_sin_cmd->callback([&]() {
        Complex z(real, imag);
        std::cout << "Input: " << z << "\n"
                  << "sin(z): " << sin_taylor(z) << std::endl;
    });

    complex_cos_cmd->callback([&]() {
        Complex z(real, imag);
        std::cout << "Input: " << z << "\n"
                  << "cos(z): " << cos_taylor(z) << std::endl;
    });

    // --- Matrix Subcommand ---
    auto matrix_cmd = app.add_subcommand("matrix", "2x2 Matrix operations (e.g., exp)");
    std::vector<double> elements;
    bool benchmark_matrix = false;

    matrix_cmd->add_option("elements", elements, "Flattened list of 4 elements (e.g., 1 2 3 4 for [1 2; 3 4])")
              ->expected(4)
              ->required();
    matrix_cmd->add_flag("-b,--benchmark", benchmark_matrix, "Run benchmark (1000 iterations)");

    auto matrix_exp_cmd = matrix_cmd->add_subcommand("exp", "Calculate exp(m)");
    auto matrix_sin_cmd = matrix_cmd->add_subcommand("sin", "Calculate sin(m)");
    auto matrix_cos_cmd = matrix_cmd->add_subcommand("cos", "Calculate cos(m)");

    matrix_exp_cmd->callback([&]() {
        Matrix<double> m(2, 2);
        for(size_t i=0; i<4; ++i) m(i/2, i%2) = elements[i];

        if (benchmark_matrix) {
            CLI::Timer timer("Matrix Exp (1000 iterations)");
            for(int i=0; i<1000; ++i) {
                auto res = exp_taylor(m);
                (void)res;
            }
            std::cout << timer << std::endl;
        } else {
            std::cout << "Input Matrix:\n" << m << "\n"
                      << "Result of exp_taylor(m):\n" << exp_taylor(m) << std::endl;
        }
    });

    matrix_sin_cmd->callback([&]() {
        Matrix<double> m(2, 2);
        for(size_t i=0; i<4; ++i) m(i/2, i%2) = elements[i];
        std::cout << "Input Matrix:\n" << m << "\n"
                  << "Result of sin_taylor(m):\n" << sin_taylor(m) << std::endl;
    });

    matrix_cos_cmd->callback([&]() {
        Matrix<double> m(2, 2);
        for(size_t i=0; i<4; ++i) m(i/2, i%2) = elements[i];
        std::cout << "Input Matrix:\n" << m << "\n"
                  << "Result of cos_taylor(m):\n" << cos_taylor(m) << std::endl;
    });

    CLI11_PARSE(app, argc, argv);
    return 0;
}
