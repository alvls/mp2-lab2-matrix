#include <iostream>
#include <limits>
#include <stdexcept>
#include "tmatrix.h"

int main()
{
    try
    {
        std::cout << "Matrix size (1.." << MAX_MATRIX_SIZE << "): ";
        int n;
        if (!(std::cin >> n) || n <= 0 || n > MAX_MATRIX_SIZE)
            throw std::out_of_range("Invalid matrix size");

        TDynamicMatrix<double> a(n), b(n);
        std::cout << "Enter " << n * n << " elements of A (row by row):\n";
        if (!(std::cin >> a)) throw std::runtime_error("Invalid input for A");
        std::cout << "Enter " << n * n << " elements of B (row by row):\n";
        if (!(std::cin >> b)) throw std::runtime_error("Invalid input for B");

        for (;;)
        {
            std::cout << "\n1: A+B  2: A-B  3: A*B  4: A==B  5: A*scalar  6: Show A,B  0: Exit\nChoice: ";
            int choice;
            if (!(std::cin >> choice)) break;
            if (choice == 0) break;
            switch (choice)
            {
            case 1: std::cout << a + b; break;
            case 2: std::cout << a - b; break;
            case 3: std::cout << a * b; break;
            case 4: std::cout << (a == b ? "Equal\n" : "Not equal\n"); break;
            case 5:
            {
                double value;
                std::cout << "Scalar: ";
                if (!(std::cin >> value)) throw std::runtime_error("Invalid scalar");
                std::cout << a * value;
                break;
            }
            case 6: std::cout << "A:\n" << a << "B:\n" << b; break;
            default: std::cout << "Unknown operation\n";
            }
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
