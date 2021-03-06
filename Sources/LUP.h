#pragma once

#include <numeric>

#include "Utils.h"
#include "Matrix.h"

struct P
{
    std::vector<int> cols;
    std::vector<int> rows;

    explicit P(int n);
};

std::pair<Matrix, P> BuildLUP(Matrix m);

Vector SolveLUP(const Matrix& LU, P p, const Vector& b);
