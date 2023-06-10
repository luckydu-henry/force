#ifndef _FORCE_F32_EXT_OUTPUT_HPP_
#define _FORCE_F32_EXT_OUTPUT_HPP_
#include <iostream>
namespace force {
    namespace __opm32 {
        typedef class vec2 vec2;
        typedef class mat2x2 mat2x2;
    }
}
std::ostream& operator<<(std::ostream& _Stream, const force::__opm32::vec2& v) {
    _Stream << "[" << v[0] << ", " << v[1] << "]";
    return _Stream;
}

std::ostream& operator<<(std::ostream& _Stream, const force::__opm32::mat2x2& v) {
    _Stream << "([" << v.at(0, 0) << "," << v.at(1, 0) << "],[" << v.at(0, 1) << "," << v.at(1, 1) << "])";
    return _Stream;
}
#endif //! _FORCE_F32_EXT_OUTPUT_HPP_
