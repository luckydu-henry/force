#ifndef _FORCE_F32_EXT_OUTPUT_HPP_
#define _FORCE_F32_EXT_OUTPUT_HPP_
#include <iostream>
#include "mat2x2.h"
#include "vec2.h"
std::ostream& operator<<(std::ostream& _Stream, const force::f32::vec2& v) {
    _Stream << "[" << v[0] << "," << v[1] << "]";
    return _Stream;
}

std::ostream& operator<<(std::ostream& _Stream, const force::f32::mat2x2& v) {
    _Stream << "([" << v.at(0, 0) << "," << v.at(1, 0) << "],[" << v.at(0, 1) << "," << v.at(1, 1) << "])";
    return _Stream;
}
#endif //! _FORCE_F32_EXT_OUTPUT_HPP_
