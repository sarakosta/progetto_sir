cmake_minimum_required(VERSION 3.16)
project(Epidemic)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sir sir.cpp main.cpp)
target_compile_options(sir PRIVATE -Wall -Wextra -fsanitize=address)

add_executable(sir.t sir.test.cpp sir.cpp)
target_compile_options(sir.t PRIVATE -Wall -Wextra -fsanitize=address)
add_test(COMMAND sir.t)
