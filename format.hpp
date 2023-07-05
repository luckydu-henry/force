#pragma once
#include <ostream>
#include "complex.hpp"
#include "vector.hpp"
#include "matrix.hpp"

template <typename Ty, class VecViewT>
std::ostream& operator<<(std::ostream& stream, const ::force::complex<Ty, VecViewT>& z) {
    stream << z.real;
    stream.setf(std::ostream::showpos);
    stream << z.imag << "i";
    return stream;
}

template <typename Ty, std::size_t Dimension, class VecViewT>
std::ostream& operator<<(std::ostream& stream, const ::force::basic_vector<Ty, Dimension, VecViewT>& vec) {
    stream << '[';
    for (size_t i = 0; i < Dimension - 1; ++i) stream << vec[i] << ", ";
    stream << vec[Dimension - 1] << ']';
    return stream;
}

template <typename Ty, std::size_t Col, std::size_t Row, class VecViewT> 
std::ostream& operator<<(std::ostream& stream, const ::force::basic_matrix<Ty, Col, Row, VecViewT>& M) {
    for (std::size_t i = 0; i < Col; ++i)
        stream << M[i] << std::endl;
    return stream;
}
