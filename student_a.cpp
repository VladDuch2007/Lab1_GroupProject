#include "shared_types.h"

#include <algorithm>
#include <cmath>
#include <numbers>

double evaluateCubic(
    double x,
    double a,
    double b,
    double c,
    double d)
{
    return a * x * x * x +
           b * x * x +
           c * x +
           d;
}

std::unique_ptr<Result> calculateA(
    std::shared_ptr<const InputData> data)
{
    const double a = data->a;
    const double b = data->b;
    const double c = data->c;
    const double d = data->d;
    const double eps = data->epsilon;

    const double p =
        (3.0 * a * c - b * b) /
        (3.0 * a * a);

    const double q =
        (2.0 * b * b * b -
         9.0 * a * b * c +
         27.0 * a * a * d) /
        (27.0 * a * a * a);

    const double discriminant =
        (q * q) / 4.0 +
        (p * p * p) / 27.0;

    std::vector<double> roots;

    if (discriminant > eps)
    {
        const double sqrtD =
            std::sqrt(discriminant);

        const double u =
            std::cbrt(-q / 2.0 + sqrtD);

        const double v =
            std::cbrt(-q / 2.0 - sqrtD);

        const double x =
            u + v - b / (3.0 * a);

        roots.push_back(x);
    }
    else if (std::abs(discriminant) <= eps)
    {
        const double u =
            std::cbrt(-q / 2.0);

        const double x1 =
            2.0 * u - b / (3.0 * a);

        const double x2 =
            -u - b / (3.0 * a);

        roots.push_back(x1);

        if (std::abs(x1 - x2) > eps)
        {
            roots.push_back(x2);
        }
    }
    else
    {
        const double r =
            2.0 * std::sqrt(-p / 3.0);

        double cosValue =
            (-q / 2.0) /
            std::sqrt(
                -(p * p * p) / 27.0);

        cosValue =
            std::clamp(
                cosValue,
                -1.0,
                1.0);

        const double phi =
            std::acos(cosValue);

        for (int k = 0; k < 3; ++k)
        {
            const double angle =
                (phi +
                 2.0 * std::numbers::pi * k) /
                3.0;

            const double x =
                r * std::cos(angle) -
                b / (3.0 * a);

            roots.push_back(x);
        }
    }

    std::sort(
        roots.begin(),
        roots.end());

    std::vector<double> residuals;

    for (double root : roots)
    {
        const double residual =
            std::abs(
                evaluateCubic(
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
            0
        });
}