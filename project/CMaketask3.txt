cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Указываем, что будем использовать Google Test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Указываем исходные файлы и библиотеки
add_executable(MyTest test_main3.cpp)
target_link_libraries(MyTest ${GTEST_LIBRARIES} pthread)

add_test(NAME MyTest COMMAND MyTest)
