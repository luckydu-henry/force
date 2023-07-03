#pragma once
#include <ostream>
#include "vector.hpp"

template <typename Ty, std::size_t Dimension, class VecViewT>
std::ostream& operator<<(std::ostream& stream, const ::force::basic_vector<Ty, Dimension, VecViewT>& vec) {
    stream << '[';
    for (size_t i = 0; i < Dimension - 1; ++i) stream << vec[i] << ", ";
    stream << vec[Dimension - 1] << ']';
    return stream;
}