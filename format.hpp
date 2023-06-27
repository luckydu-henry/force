#pragma once
#include "complex.hpp"
#include "vector.hpp"
#include <ostream>

template <std::floating_point Ty>
std::ostream& operator<<(std::ostream& stream, const ::force::complex<Ty>& C) {
    stream << C.real();
    stream.setf(std::ostream::showpos);
    stream << C.imag() << 'i';
    return stream;
}


template <::force::vector Vec>
std::ostream& operator<<(std::ostream& stream, const Vec& v) {
    stream << '[';
    for (std::size_t i = 0; i < Vec::dimension - 1; ++i) stream << v[i] << ", ";
    stream << v[Vec::dimension - 1] << ']';
    return stream;
}