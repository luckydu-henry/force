#pragma once
#include "complex.hpp"
#include <ostream>

template <std::floating_point Ty>
std::ostream& operator<<(std::ostream& stream, const ::force::complex<Ty>& C) {
    stream << C.real();
    stream.setf(std::ostream::showpos);
    stream << C.imag() << 'i';
    return stream;
}
