cmake_minimum_required(VERSION 3.2)

#project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
project(matrix)
#SET (BOOST_ROOT "C:/boost/build-boost")
#SET (BOOST_INCLUDEDIR "C:/boost/include")
#SET (BOOST_LIBRARYDIR "C:/boost/lib")
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

set(HEADERS Matrix.h tuple_print.h)

add_executable(InfiniteMatrix ${HEADERS} main.cpp)

set (TEST test_InfiniteMatrix)
add_executable (${TEST} test_InfiniteMatrix.cpp)

set_target_properties (InfiniteMatrix ${TEST} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties (${TEST} PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(${TEST}
        ${Boost_LIBRARIES}
)

install(TARGETS InfiniteMatrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT tima_mamedxp@mail.ru)

include(CPack)

enable_testing()

add_test (${TEST} ${TEST})
