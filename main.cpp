#include <iostream>
#include <string>
#include "Matrix.h"

int main(int argc, char *argv[])
{
    Matrix<int, -1> matr;
    matr[0][0] = 2;
    matr[0][0] = -1;

    std::cout << matr[0][0] << std::endl;

    return 0;
}
