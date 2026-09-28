#include "shared_types.h"

#include <algorithm>
#include <cmath>

static double cubicFunction(
    double x,
    double a,
    double b,
    double c,
    double d)
{
    return a * x * x * x
         + b * x * x
         + c * x
         + d;
}

static double cubicDerivative(
    double x,
    double a,
    double b,
    double c)
{
    return 3.0 * a * x * x
         + 2.0 * b * x
         + c;
}

std::unique_ptr<Result> calculateB(
    std::shared_ptr<const InputData> data)
{
    const double a = data->a;
    const double b = data->b;
    const double c = data->c;
    const double d = data->d;

    const double epsilon = data->epsilon;
    const int maxIterations = data->maxIterations;

    std::vector<double> roots;
    std::vector<double> residuals;

    int totalIterations = 0;

    for (double initialGuess : data->initialGuesses)
    {
        double x = initialGuess;
        bool converged = false;

        for (int i = 0; i < maxIterations; ++i)
        {
            const double fx =
                cubicFunction(x, a, b, c, d);

            if (std::abs(fx) <= epsilon)
            {
                converged = true;
                break;
            }

            const double derivative =
                cubicDerivative(x, a, b, c);

            if (std::abs(derivative) <= epsilon)
            {
                break;
            }

            const double nextX =
                x - fx / derivative;

            ++totalIterations;

            if (std::abs(nextX - x) <= epsilon)
            {
                x = nextX;
                converged = true;
                break;
            }

            x = nextX;
        }

        const double residual =
            std::abs(
                cubicFunction(
                    x,
                    a,
                    b,
                    c,
                    d));

        if (residual <= epsilon * 10.0)
        {
            converged = true;
        }

        if (converged)
        {
            bool alreadyExists = false;

            for (double root : roots)
            {
                if (std::abs(root - x) <= 1e-7)
                {
                    alreadyExists = true;
                    break;
                }
            }

            if (!alreadyExists)
            {
                roots.push_back(x);
            }
        }
    }

    std::sort(
        roots.begin(),
        roots.end());

    for (double root : roots)
    {
        const double residual =
            std::abs(
                cubicFunction(
                    root,
                    a,
                    b,
                    c,
                    d));

        residuals.push_back(residual);
    }

    return std::make_unique<Result>(
        Result{
            roots,
            residuals,
            totalIterations
        });
}