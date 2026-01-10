add_library(libbase STATIC
        libbase/bbox2.cpp
        libbase/configure_working_directory.cpp
        libbase/disjoint_set.cpp
        libbase/fast_random.cpp
        libbase/point2.cpp
        libbase/stats.cpp
        libbase/timer.cpp
)

target_include_directories(libbase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (BUILD_TESTING)
    add_executable(libbase_tests
            libbase/bbox2_tests.cpp
            libbase/configure_working_directory_tests.cpp
            libbase/disjoint_set_tests.cpp
            libbase/fast_random_tests.cpp
            libbase/point2_tests.cpp
            libbase/stats_tests.cpp
            libbase/timer_tests.cpp
    )
    target_link_libraries(libbase_tests PRIVATE libbase GTest::gtest_main)
    add_test(NAME libbase_tests COMMAND libbase_tests)
endif ()
