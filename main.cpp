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
    matr[10][100][5] = 14;
    matr[100][10][0][0] = 34;
    matr[10][10] = 4;
    matr[10][100][5] = -1;
    assert(matr.size() == 3);


    for(auto c : matr)
    {
//        int x;
//        int y;
//        int v;
//        std::tie(x, y, v) = c;
//        std::cout << x << y << v << std::endl;
    }

    return 0;
}
