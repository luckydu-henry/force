// Copyright(c) 2012 - 2022 Scott Chacon and others
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this softwareand associated documentation files(the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and /or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions :
//
// The above copyright noticeand this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef _ZEN_UTILITY_HPP_
#define _ZEN_UTILITY_HPP_

#if defined _MSC_VER
#include <yvals_core.h>
#if !_HAS_CXX20
#define pi 3.1415926535
#else
#include <numbers>
#define pi std::numbers::pi_v<_Ty>
#endif
#elif defined __GNUC__
#define pi 3.1415926535
#endif

#include <cmath>

namespace zen {
    template <typename _Ty>
    bool is_near(const _Ty& _v1, const _Ty& _v2, const _Ty& _epsilon) {
        static_assert(std::is_floating_point_v<_Ty>);
        return std::abs(_v1 - _v2) > _epsilon ? false : true;
    }

    template <typename _Ty>
    _Ty to_radius(const _Ty& _v) {
        static_assert(std::is_arithmetic_v<_Ty>);
        return _v * pi / 180;
    }

    template <typename _Ty>
    _Ty to_angle(const _Ty& _v) {
        static_assert(std::is_arithmetic_v<_Ty>);
        return _v * (_Ty)180 / pi<_Ty>;
    }
}
#endif //! _ZEN_UTILITY_HPP_