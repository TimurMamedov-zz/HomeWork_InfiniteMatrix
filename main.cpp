#include <iostream>
#include <string>
#include <assert.h>
#include "Matrix.h"
#include "tuple_print.h"

int main(int argc, char *argv[])
{
    Matrix<int, 0> matr;

    for(std::size_t i = 0; i < 10; i++)
    {
        matr[i][i] = i;
        matr[9 - i][i] = i;
    }
    for(std::size_t i = 1; i < 9; i++)
    {
        for(std::size_t j = 1; j < 9; j++)
        {
            std::cout << matr[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << matr.size() << std::endl;

    for(auto tuple: matr)
    {
        std::cout << tuple << "\n";
    }

    return 0;
}
