#pragma once

#include <memory>
#include <vector>

struct InputData
{
    double a;
    double b;
    double c;
    double d;

    std::vector<double> initialGuesses;
    double epsilon;
    int maxIterations;
};

struct Result
{
    std::vector<double> roots;
    std::vector<double> residuals;
    int iterations;
};

std::unique_ptr<Result> calculateA(
    std::shared_ptr<const InputData> data);

std::unique_ptr<Result> calculateB(
    std::shared_ptr<const InputData> data);