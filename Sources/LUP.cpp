#include "LUP.h"

#include <iostream>

P::P(int n)
{
    cols.resize(n);
    rows.resize(n);

    std::iota(cols.begin(), cols.end(), 0);
    std::iota(rows.begin(), rows.end(), 0);
}

static Matrix SetOnes(Matrix m)
{
    for (int i = 0; i < m.GetCols(); ++i)
    {
        m(i, i) = 1;
    }
    return m;
}

std::pair<Matrix, P> BuildLUP(Matrix m)
{
    const int n = m.GetCols();
    P p(n);

    for (int k = 0; k < n - 1; ++k)
    {
        auto [col, row] = Utils::FindMax(m, k);

        m.SwapColumns(k, col);
        m.SwapRows(k, row);

        std::swap(p.rows[row], p.rows[k]);
        std::swap(p.cols[col], p.cols[k]);

        for (int i = k + 1; i < n; ++i)
        {
            m(i, k) /= m(k, k);
            m.AddMultipliedRowPart(i, k, -m(i, k), k + 1, n);
        }
    }
    return {m, p};
}

Vector SolveLUP(const Matrix& LU, P p, const Vector& b)
{
    const int n = b.size();
    Vector bP(n);

    for (int i = 0; i < n; ++i)
    {
        bP[i] = b[p.rows[i]];
    }

    const auto y = Utils::SolveLowerTriangle(SetOnes(LU), bP);
    const auto shuffledX = Utils::SolveUpperTriangle(LU, y);

    Vector x(n);
    for (int i = 0; i < n; ++i)
    {
        x[p.cols[i]] = shuffledX[i];
    }

    return x;
}
