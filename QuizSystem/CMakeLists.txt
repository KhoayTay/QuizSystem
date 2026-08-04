cmake_minimum_required(VERSION 3.10)

project(QuizSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(QuizSystem ${SOURCES})


//add_subdirectory(test)
//uncomment nếu muốn thêm thư mục test vào build