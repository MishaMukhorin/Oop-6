cmake_minimum_required(VERSION 3.24)
project(Oop_6)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Oop_6-1 1-7/CHttpUrlOut.cpp 1-7/CHttpUrl.cpp 1-7/CHttpUrl.h 1-7/CUrlParsingError.h)
add_executable(Oop_6-1_tests 1-7/tests/CHttpURLTests.cpp 1-7/CHttpURL.cpp 1-7/CHttpUrl.h 1-7/CUrlParsingError.h)

add_executable(Oop_6-2 2-2/CStringListOut.cpp 2-2/CStringList.cpp )
add_executable(Oop_6-2_tests 2-2/tests/CStringListsTests.cpp 2-2/CStringList.cpp)

target_link_libraries(Oop_6-1_tests gtest_main)
target_link_libraries(Oop_6-2_tests gtest_main)


