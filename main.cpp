#include <iostream>
#include <string>
#include <assert.h>
#include "Matrix.h"

int main(int argc, char *argv[])
{
    Matrix<int, -1> matr;

    assert(matr.size() == 0);
    auto a = matr[0][0];
    assert(a == -1);
    assert(matr.size() == 0);
    matr[100][100] = 314;
    assert(matr[100][100] == 314);
    assert(matr.size() == 1);

    return 0;
}
