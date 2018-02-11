#define BOOST_TEST_MODULE matrix_test

#include <boost/test/unit_test.hpp>
#include "Matrix.h"

#include "version.h"

BOOST_AUTO_TEST_CASE(version_test)
{
    BOOST_CHECK( version() > 0 );
}

BOOST_AUTO_TEST_SUITE(Test_Matrix)

BOOST_AUTO_TEST_CASE(test_Indexes)
{
    BOOST_CHECK(std::tuple_size<decltype(Indexes::gen<std::size_t, 0>())>::value == 0);
    BOOST_CHECK(std::tuple_size<decltype(Indexes::gen<std::size_t, 1>())>::value == 1);
    BOOST_CHECK(std::tuple_size<decltype(Indexes::gen<std::size_t, 2>())>::value == 2);
    BOOST_CHECK(std::tuple_size<decltype(Indexes::gen<std::size_t, 3>())>::value == 3);
    BOOST_CHECK(std::tuple_size<decltype(Indexes::gen<std::size_t, 4>())>::value == 4);
    BOOST_CHECK(std::tuple_size<decltype(Indexes::gen<std::size_t, 5>())>::value == 5);
}

BOOST_AUTO_TEST_CASE(test_Matr)
{
    Matrix<int, -1, 3> matr;
    BOOST_CHECK(matr.size() == 0);

    matr[0][0][0] = -1;
    BOOST_CHECK(matr.size() == 0);

    matr[0][0][0] = 1;
    BOOST_CHECK(matr.size() == 1);

    auto a = matr[0][0][0];
    BOOST_CHECK(a == 1);

    matr[0][0][0] = -1;
    BOOST_CHECK(matr.size() == 0);

    matr[10][10][10] = 10;
    std::size_t ind1, ind2, ind3;
    int val;
    auto it = matr.begin();
    std::tie(ind1, ind2, ind3, val) = *it;
    BOOST_CHECK(ind1 == 10);
    BOOST_CHECK(ind2 == 10);
    BOOST_CHECK(ind3 == 10);
    BOOST_CHECK(val == 10);
}

BOOST_AUTO_TEST_SUITE_END()
