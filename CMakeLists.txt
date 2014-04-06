cmake_minimum_required(VERSION 2.8)

project(jsxx)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wfatal-errors -Wextra -pedantic -O3 -DNDEBUG")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

macro(create_test TARGET SOURCE)
  add_executable(${TARGET} test/${SOURCE})
  add_test(${TARGET} ${TARGET})
endmacro()


enable_testing()

create_test(val val.cpp)
create_test(map_val map_val.cpp)

create_test(strings strings.cpp)

create_test(perf perf.cpp)

#create_test(perf-jsoncpp perf-jsoncpp.cpp)

#create_test(numconv numconv.cpp)

