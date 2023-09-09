cmake_minimum_required(VERSION 3.15)

project(Force VERSION 1.0
              DESCRIPTION "Free Opensource Rapid Calculation Engine."
              LANGUAGES C CXX)

set(FORCE_TEST_ENABLE       ON CACHE BOOL "" FORCE)

file(GLOB FMATH_HEADER "include/fmath/*.hpp")
file(GLOB FMATH_SOURCE "src/fmath/*.cpp")

set(INC_PATH "include/")

source_group(fmath FILES ${FMATH_HEADER} ${FMATH_SOURCE})

add_library               (Force_lib STATIC ${FMATH_HEADER} ${FMATH_SOURCE})
target_compile_features   (Force_lib PUBLIC cxx_std_20)
target_include_directories(Force_lib PUBLIC ${INC_PATH})

# Test can be avalable.
if(FORCE_TEST_ENABLE)
add_executable            (Force_FMath_test "test/FMathTest.cpp")
target_compile_features   (Force_FMath_test PUBLIC cxx_std_20)
target_include_directories(Force_FMath_test PUBLIC ${INC_PATH})
target_link_libraries     (Force_FMath_test PUBLIC Force_lib)
endif()