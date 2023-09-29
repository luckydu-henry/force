#include <iostream>

#include <fmath/primary.hpp>
#include <fmath/matrices.hpp>
#include <fmath/complex.hpp>
#include <fmath/math_format.hpp>

int main(int argc, char* argv[]) {
    namespace ffm = force::math;

    // namespace ffg = force::geom; // Geometry library
    // namespace ffp = force::phys; // Physics library
    // namespace ffv = force::vibr; // Audio and wave handling library

    ffm::vec4f a = { 1.f, 2.f, 3.f, 4.f};

    std::cout << a << std::endl;
}