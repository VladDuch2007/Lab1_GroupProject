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

    auto resultB = calculateB(data);

    auto [rootsB, residualsB, iterationsB] =
        *resultB;

    std::cout
        << std::fixed
        << std::setprecision(10);

    std::cout
        << "Student B - Newton method\n";

    for (std::size_t i = 0;
         i < rootsB.size();
         ++i)
    {
        std::cout
            << "x" << i + 1
            << " = " << rootsB[i]
            << ", residual = "
            << residualsB[i]
            << '\n';
    }

    std::cout
        << "Iterations: "
        << iterationsB
        << '\n';

    return 0;
}