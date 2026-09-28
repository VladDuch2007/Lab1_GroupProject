#include <iomanip>
#include <iostream>

#include "shared_types.h"

int main()
{
    auto data =
        std::make_shared<const InputData>(
            InputData{
                1.0,
                -6.0,
                11.0,
                -6.0,
                {0.5, 2.2, 3.5},
                1e-10,
                100
            });

    auto resultA = calculateA(data);

    auto [rootsA, residualsA, iterationsA] =
        *resultA;

    std::cout
        << std::fixed
        << std::setprecision(10);

    std::cout
        << "Student A - Cardano method\n";

    for (std::size_t i = 0;
         i < rootsA.size();
         ++i)
    {
        std::cout
            << "x" << i + 1
            << " = " << rootsA[i]
            << ", residual = "
            << residualsA[i]
            << '\n';
    }

    std::cout
        << "Iterations: "
        << iterationsA
        << '\n';

    return 0;
}