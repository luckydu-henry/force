#pragma once
#include <ostream>
#include "fmath/Complex.hpp"
#include "fmath/Vector.hpp"
#include "fmath/Matrix.hpp"

template <typename Ty, class VecPipeT>
std::ostream& operator<<(std::ostream& stream, const ::Fma::Complex<Ty, VecPipeT>& z) {
    stream << z.real;
    stream.setf(std::ostream::showpos);
    stream << z.imag << "i";
    return stream;
}

template <typename Ty, std::size_t Dimension, class VecPipeT>
std::ostream& operator<<(std::ostream& stream, const ::Fma::BasicVector<Ty, Dimension, VecPipeT>& vec) {
    stream << '[';
    for (size_t i = 0; i < Dimension - 1; ++i) stream << vec[i] << ", ";
    stream << vec[Dimension - 1] << ']';
    return stream;
}

#if defined SIMD_VECTOR4x32
template <typename Ty>
std::ostream& operator<<(std::ostream& stream, const Fma::SIMDVector4<Ty>& vec) {
    stream << "[" << vec[0] << ", " << vec[1] << ", " << vec[2] << ", " << vec[3] << "]";
    return stream;
}
#endif

template <typename Ty, std::size_t Col, std::size_t Row, class VecPipeT> 
std::ostream& operator<<(std::ostream& stream, const ::Fma::BasicMatrix<Ty, Col, Row, VecPipeT>& M) {
    for (std::size_t i = 0; i < Col; ++i)
        stream << M[i] << std::endl;
    return stream;
}
