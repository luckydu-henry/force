cmake_minimum_required(VERSION 3.15)

project(force VERSION 1.0
              DESCRIPTION "ree Opensource Rapid Calculation Engine."
              LANGUAGES C CXX)

set(ORCE_TEST_ENABLE       ON CACHE BOOL "" ORCE)

file(GLOB MATH_HEADER "include/fmath/*.hpp")
file(GLOB MATH_SOURCE "src/fmath/*.cpp")

set(INC_PATH "include/")

source_group(fmath ILES ${MATH_HEADER} ${MATH_SOURCE})

add_library               (force_lib STATIC ${MATH_HEADER} ${MATH_SOURCE})
target_compile_features   (force_lib PUBLIC cxx_std_20)
target_include_directories(force_lib PUBLIC ${INC_PATH})

# Test can be avalable.
if(ORCE_TEST_ENABLE)
add_executable            (force_math_test "test/math_test.cpp")
target_compile_features   (force_math_test PUBLIC cxx_std_20)
target_include_directories(force_math_test PUBLIC ${INC_PATH})
target_link_libraries     (force_math_test PUBLIC force_lib)
endif()