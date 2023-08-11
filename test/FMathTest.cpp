#include <iostream>

#include <fmath/PrMathFn.hpp>
#include <fmath/Matrix.hpp>
#include <fmath/Matrices.hpp>
#include <fmath/Vector.hpp>
#include <Format.hpp>

int main(int argc, char* argv[]) {

    Fma::Mat4x4f m = Fma::IdMat<Fma::Mat4x4f>();
    Fma::Vec4f v = { 1,2,3,4 };
    std::cout << v << std::endl;

    std::cout << Fma::Dot(v, v) << std::endl;
}