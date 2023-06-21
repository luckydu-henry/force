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

std::ostream& operator<<(std::ostream& stream, const ::force::vec2<float>& v) {
    stream << '[' << v.x() << ", " << v.y() << ']';
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const ::force::vec3<float>& v) {
    stream << '[' << v.x() << ", " << v.y() << ", " << v.z() << ']';
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const ::force::vec4<float>& v) {
    stream << '[' << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.w() << ']';
    return stream;
}
