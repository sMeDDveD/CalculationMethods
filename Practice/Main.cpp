#include <iostream>
#include <functional>

#include "ConditionNumber.h"
#include "Matrix.h"
#include "Utils.h"
#include "Gauss.h"
#include "LUP.h"
#include "Cholesky.h"
#include "Relaxation.h"
#include "Householder.h"
#include "LeastSquares.h"
#include "GMRES.h"

constexpr double EPS = 0.00001;

void tests(const Matrix A, const Vector b, const Vector x)
{
    std::cout << "Condition number:" << std::endl;
    std::cout << GetConditionNumber(A);
    std::cout << std::endl;

    std::cout << "Gauss: " << std::endl;
    std::cout << Utils::EuclideanNorm(Utils::SubVectors(x, SolveGauss(A, b)));
    std::cout << std::endl;

    std::cout << "LUP: " << std::endl;
    auto [LU, P] = BuildLUP(A);
    std::cout << Utils::EuclideanNorm(Utils::SubVectors(x, SolveLUP(LU, P, b)));
    std::cout << std::endl;

    std::cout << "Cholesky:" << std::endl;
    auto [LT, D] = BuildCholesky(A);
    std::cout << Utils::EuclideanNorm(Utils::SubVectors(x, SolveCholesky(LT, D, b)));
    std::cout << std::endl;

    std::cout << "Relaxation:" << std::endl;
    std::cout << Utils::EuclideanNorm(Utils::SubVectors(x, SolveRelaxation(A, b, EPS, 1.2)));
    std::cout << std::endl;

    std::cout << "Householder:" << std::endl;
    std::cout << Utils::EuclideanNorm(Utils::SubVectors(x, SolveHouseholder(A, b)));
    std::cout << std::endl;

    std::cout << "LeastSquares (GaussT):" << std::endl;
    std::cout << Utils::EuclideanNorm(Utils::SubVectors(x, SolveLeastSquares(A, b, false)));
    std::cout << std::endl;

    std::cout << "LeastSquares (QR):" << std::endl;
    std::cout << Utils::EuclideanNorm(Utils::SubVectors(x, SolveLeastSquares(A, b, true)));
    std::cout << std::endl;

    std::cout << "GMRES:" << std::endl;
    std::cout << Utils::EuclideanNorm(Utils::SubVectors(x, SolveGMRES(A, b, EPS)));
    std::cout << std::endl;


}


int main()
{
    int n = 256;
    double arr[] = {
            10, 1, 2,
            1, 6, 3,
            2, 3, 7
    };
    Matrix A = Matrix::GenerateMatrix(n, Matrix::variant);
    Vector x(A.GetCols());
    std::iota(x.begin(), x.end(), 1);
    Vector b = A * x;

    tests(A, b, x);
    return 0;
}
