#define BOOST_TEST_MODULE print_ip_test

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

}

BOOST_AUTO_TEST_CASE(test_Intermediary)
{

}

BOOST_AUTO_TEST_CASE(test_Matr)
{

}

BOOST_AUTO_TEST_SUITE_END()
