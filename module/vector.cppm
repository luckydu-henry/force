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

export module zen.vector;

#if defined(_MSC_VER) || defined(__GNUC__)
#  if _MSC_VER >= 1930 || __GNUC__ >= 8

import <cmath>;
import <numbers>;
import <stdexcept>;
import zen.utility;

namespace zen {
    /////////////////////////////////
    ////////// VECTOR2 //////////////
    /////////////////////////////////

    export
        template <typename _Ty>
    class vec2 final {
    public:
        // type_traits.
        using elem_t = std::enable_if_t<std::is_arithmetic_v<_Ty>, _Ty>;
        using self_t = vec2<elem_t>;
        using self_lref_t = typename std::add_const_t<std::add_lvalue_reference_t<self_t>>;

        // dimention
        static constexpr std::size_t dimention = 2u;
    public:

        elem_t x, y;

        vec2(const elem_t& _1, const elem_t& _2)
            :x(_1), y(_2) {}
        vec2(const vec2<elem_t>& _Right)
            :x(_Right.x), y(_Right.y) {}
        vec2(vec2<elem_t>&& _Right)
            :x(_Right.x), y(_Right.y) {
            _Right.x = 0;
            _Right.y = 0;
        }

        ////////////////////////////////
        // OPERATORS
        ////////////////////////////////

        // Assign operator
        self_t& operator=(self_lref_t _Right) {
            return _Right;
        }
        self_t& operator=(self_t&& _Right) {
            return _Right;
        }

        // Flip the vector to the opposite direction.
        self_t operator-() const {
            return { -x, -y };
        }
        // Plus two vectos.
        self_t operator+(self_lref_t _v) const noexcept {
            return { this->x + _v.x, this->y + _v.y };
        }
        // Minus two vectors.
        self_t operator-(self_lref_t _v) const noexcept {
            return { this->x - _v.x, this->y - _v.y };
        }
        // Multiply two vectos by a scalar.
        self_t operator*(elem_t _v) const noexcept {
            return { this->x * _v, this->y * _v };
        }
        // Multiply two vectos by a scalar 1/_v.
        self_t operator/(elem_t _v) const noexcept {
            return { this->x / _v, this->y / _v };
        }
        // Compare two vectors.
        bool operator==(self_lref_t _v) const noexcept {
            constexpr elem_t epsilon = 1e-8;

            if constexpr (std::is_floating_point_v<elem_t>)
                return is_near(this->x, _v.x, epsilon) && is_near(this->y, _v.y, epsilon);

            return (this->x == _v.x) && (this->y == _v.y);
        }

        // Get the length(modulus) of the vector.
        elem_t modulus(void) const noexcept {
            return std::sqrt(x * x + y * y);
        }

        // Get the angle between vector and x axis.
        elem_t angle(void) const noexcept {
            return to_angle(std::atan(y / x));
        }

        ~vec2() = default;
    };

    ////////////////////
    /// VEC2 VIEW //////
    ////////////////////

    // Can use to clip bigger vectors.
    // No copy, and behave well.
    template <typename _Ty>
    struct vec2_view {
        using ptr_t = std::add_pointer_t<_Ty>;

        // get_value pass in 0 get x and 1 get y.
        _Ty& get(const std::size_t _pos) {
            if (_pos == 0) return *x;
            else if (_pos == 1) return *y;
            else throw std::bad_exception();
        }

        vec2_view(ptr_t _1, ptr_t _2)
            :x(_1), y(_2) {}

    private:
        ptr_t x, y;
    };

    // Dot product of this vec2 vector.
    export template <typename _Ty>
        _Ty dot(const vec2<_Ty>& _v1, const vec2<_Ty>& _v2) noexcept {
        return _v1.x * _v2.x + _v2.y * _v2.y;
    }

    /// 2nd coordinate vector doesn't have a cross product.
    /// But use the formula of cross, we can get the area.
    /// Of the parallorgram the two vector shaped.
    export template <typename _Ty>
        _Ty cross(const vec2<_Ty>& _v1, const vec2<_Ty>& _v2) noexcept {
        return _v1.x * _v2.y - _v2.x * _v1.y;
    }

    // Get the value ptr of vec2.
    // It's the array of actual data.
    export template <typename _Ty>
        const _Ty* value_ptr(const vec2<_Ty>& _vec) {
        return &(_vec.x);
    }

    // Factory vector function can use this instead of constructor.
    export template<typename _Ty>
        vec2<_Ty>&& make_vec(const _Ty& _x, const _Ty& _y) {
        return std::move(vec2<_Ty>(_x, _y));
    }

    // Some constants that could be useful.
    export using vec2f = vec2<float>;
    export using vec2lf = vec2<long double>;

    export template <typename _Ty>
        constinit const vec2<_Ty> zero_vec2{ 0,0 };

    /////////////////////////////////
    ////////// VECTOR3 //////////////
    /////////////////////////////////

    export
        template <typename _Ty>
    class vec3 final {
    public:
        // type_traits.
        using elem_t = std::enable_if_t<std::is_arithmetic_v<_Ty>, _Ty>;
        using self_t = vec3<elem_t>;
        using self_lref_t = typename std::add_const_t<std::add_lvalue_reference_t<self_t>>;

        // get dimention.
        static constexpr std::size_t dimention = 3u;
    public:

        elem_t x, y, z;

        vec3(const elem_t& _1, const elem_t& _2, const elem_t& _3)
            :x(_1), y(_2), z(_3) {}
        vec3(const vec3<elem_t>& _Right)
            :x(_Right.x), y(_Right.y), z(_Right.z) {}
        vec3(vec3<elem_t>&& _Right)
            :x(_Right.x), y(_Right.y), z(_Right.z) {
            _Right.x = 0;
            _Right.y = 0;
            _Right.z = 0;
        }

        ////////////////////////////////
        // OPERATORS
        ////////////////////////////////

        // Assign operator
        self_t& operator=(self_lref_t _Right) {
            return _Right;
        }

        self_t& operator=(self_t&& _Right) {
            return _Right;
        }

        // Flip the vector to the opposite direction.
        self_t operator-() const noexcept {
            return { -x, -y, -z };
        }
        // Plus two vectos.
        self_t operator+(self_lref_t _v) const noexcept {
            return { this->x + _v.x, this->y + _v.y, this->z + _v.z };
        }
        // Minus two vectors.
        self_t operator-(self_lref_t _v) const noexcept {
            return { this->x - _v.x, this->y - _v.y, this->z - _v.z };
        }
        // Multiply two vectos by a scalar.
        self_t operator*(elem_t _v) const noexcept {
            return { this->x * _v, this->y * _v, this->z * _v };
        }
        // Multiply two vectos by a scalar 1/_v.
        self_t operator/(elem_t _v) const noexcept {
            return { this->x / _v, this->y / _v, this->z / _v };
        }
        // Compare two vectors.
        bool operator==(self_lref_t _v) const noexcept {
            constexpr elem_t epsilon = 1e-8;

            if constexpr (std::is_floating_point_v<elem_t>)
                return is_near(this->x, _v.x, epsilon) &&
                is_near(this->y, _v.y, epsilon) && is_near(this->z, _v.z, epsilon);

            return (this->x == _v.x) && (this->y == _v.y) && (this->z == _v.z);
        }

        // Get vector3's xy or yz element into a vector2
        // Parameter can only be 0 or 1, 0 gets xy and 1 gets yz.
        vec2<elem_t> clip_vec2(const std::size_t _pos) const {
            if (_pos == 0) return { x, y };
            else if (_pos == 1) return { y, z };
            else throw std::bad_exception();
        }

        vec2_view<elem_t> clip_vec2_view(const std::size_t _pos) {
            if (_pos == 0) return { &x, &y };
            else if (_pos == 1) return { &y, &z };
            else throw std::bad_exception();
        }

        // Get the length(modulus) of the vector.
        elem_t modulus(void) const noexcept {
            return std::sqrt(x * x + y * y + z * z);
        }

        ~vec3() = default;
    };

    ////////////////////////////////
    ///// VEC3VIEW /////////////////
    ////////////////////////////////

    export
        template <typename _Ty>
    struct vec3_view {
        using ptr_t = std::add_pointer_t<_Ty>;

        // get_value pass in 0 get x and 1 get y and 2 get z.
        _Ty& get(const std::size_t _pos) {
            if (_pos == 0) return *x;
            else if (_pos == 1) return *y;
            else if (_pos == 2) return *z;
            else throw std::bad_exception();
        }

        vec3_view(ptr_t _1, ptr_t _2, ptr_t _3)
            :x(_1), y(_2), z(_3) {}

    private:
        ptr_t x, y, z;
    };

    export // Get the dot product of vector3.
        template <typename _Ty>
    _Ty dot(const vec3<_Ty>& _v1, const vec3<_Ty>& _v2) {
        return _v1.x * _v2.x + _v2.y * _v2.y + _v1.z * _v2.z;
    }

    export // Get the cross product of vector3.
        template <typename _Ty>
    vec3<_Ty> cross(const vec3<_Ty>& _v1, const vec3<_Ty>& _v2) {
        return { _v1.y * _v2.z - _v1.z * _v2.y,
                 _v1.x * _v2.z - _v1.z * _v2.x,
                 _v1.x * _v2.y - _v1.y * _v2.x };
    }

    export
        template <typename _Ty>
    vec3<_Ty>&& make_vec(const _Ty& _x, const _Ty& _y, const _Ty& _z) {
        return std::move(vec3<_Ty>(_x, _y, _z));
    }

    export // Use this two construct a vector3 by vector2.
        template <typename _Ty>
    vec3<_Ty>&& make_vec(const _Ty& _x, const vec2<_Ty>& _yz) {
        return std::move(vec3<_Ty>(_x, _yz.x, _yz.y));
    }

    export // Use this two construct a vector3 by vector2.
        template <typename _Ty>
    vec3<_Ty>&& make_vec(const vec2<_Ty>& _xy, const _Ty& _z) {
        return std::move(vec3<_Ty>(_xy.x, _xy.y, _z));
    }

    export // Get the value ptr of vec3
        template <typename _Ty>
    const _Ty* value_ptr(const vec3<_Ty>& _vec) {
        return &(_vec.x);
    }

    // Some constants that could be useful.
    export using vec3f = vec3<float>;
    export using vec3lf = vec3<long double>;

    export template <typename _Ty>
        constinit const vec3<_Ty> zero_vec3{ 0,0,0 };

    ////////////////////////
    //// VECTOR4 ///////////
    ////////////////////////

    export
        template <typename _Ty>
    class vec4 final {
    public:
        // type_traits.
        using elem_t = std::enable_if_t<std::is_arithmetic_v<_Ty>, _Ty>;
        using self_t = vec4<elem_t>;
        using self_lref_t = typename std::add_const_t<std::add_lvalue_reference_t<self_t>>;

        // get dimention.
        static constexpr std::size_t dimention = 4u;
    public:
        elem_t x, y, z, w;

        vec4(const elem_t& _x, const elem_t& _y, const elem_t& _z, const elem_t& _w)
            :x(_x), y(_y), z(_z), w(_w) {}
        vec4(const self_t& _self)
            :x(_self.x), y(_self.y), z(_self.z), w(_self.w) {}
        vec4(self_t&& _self)
            :x(_self.x), y(_self.y), z(_self.z), w(_self.w) {
            _self.x = 0;
            _self.y = 0;
            _self.z = 0;
            _self.w = 0;
        }

        /////////////////////////////
        /// OPERATORS
        /////////////////////////////

        // Assign operator
        self_t& operator=(self_lref_t _Right) {
            return _Right;
        }

        self_t& operator=(self_t&& _Right) {
            return _Right;
        }

        // Flip the vector to the opposite direction.
        self_t operator-() const noexcept {
            return { -x, -y, -z, -w };
        }
        // Plus two vectos.
        self_t operator+(self_lref_t _v) const noexcept {
            return { this->x + _v.x, this->y + _v.y, this->z + _v.z, this->w + _v.w };
        }
        // Minus two vectors.
        self_t operator-(self_lref_t _v) const noexcept {
            return { this->x - _v.x, this->y - _v.y, this->z - _v.z, this->w - _v.w };
        }
        // Multiply two vectos by a scalar.
        self_t operator*(elem_t _v) const noexcept {
            return { this->x * _v, this->y * _v, this->z * _v , this->w * _v };
        }
        // Multiply two vectos by a scalar 1/_v.
        self_t operator/(elem_t _v) const noexcept {
            return { this->x / _v, this->y / _v, this->z / _v , this->z / _v };
        }
        // Compare two vectors.
        bool operator==(self_lref_t _v) const noexcept {
            constexpr elem_t epsilon = 1e-8;

            if constexpr (std::is_floating_point_v<elem_t>)
                return is_near(this->x, _v.x, epsilon) &&
                is_near(this->y, _v.y, epsilon) &&
                is_near(this->z, _v.z, epsilon) && is_near(this->w, _v.w, epsilon);

            return (this->x == _v.x) && (this->y == _v.y) && (this->z == _v.z) && (this->w == _v.w);
        }

        // Can clip a vector2 from a vector4.
        // pass in 0 to get xy, 1 to get yz, 2 to get zw.
        vec2<elem_t> clip_vec2(const std::size_t _pos) {
            if (_pos == 0) return { x, y };
            else if (_pos == 1) return { y, z };
            else if (_pos == 2) return { z, w };
            else throw std::bad_exception();
        }

        // Can clip a vector2 from a vector4.
        // pass in 0 to get xy, 1 to get yz, 2 to get zw.
        vec2_view<elem_t> clip_vec2_view(const std::size_t _pos) {
            if (_pos == 0) return { &x, &y };
            else if (_pos == 1) return { &y, &z };
            else if (_pos == 2) return { &z, &w };
            else throw std::bad_exception();
        }

        // Can clip a vector2 from a vector4.
        // pass in 0 to get xyz, 1 to get yzw.
        vec3<elem_t> clip_vec3(const std::size_t _pos) {
            if (_pos == 0) return { x, y,z };
            else if (_pos == 1) return { y, z, w };
            else throw std::bad_exception();
        }
        // Can clip a vector2 from a vector4.
        // pass in 0 to get xyz, 1 to get yzw.
        vec3_view<elem_t> clip_vec3_view(const std::size_t _pos) {
            if (_pos == 0) return { &x, &y,&z };
            else if (_pos == 1) return { &y, &z, &w };
            else throw std::bad_exception();
        }

        // Get the length(modulus) of the vector.
        elem_t modulus(void) const noexcept {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }
    };

    export
        template <typename _Ty>
    vec4<_Ty>&& make_vec(const _Ty& _1, const _Ty& _2, const _Ty& _3, const _Ty& _4) {
        return std::move({ _1, _2, _3, _4 });
    }

    export
        template <typename _Ty>
    vec4<_Ty>&& make_vec(const vec2<_Ty>& _v1, const vec2<_Ty>& _v2) {
        return std::move({ _v1.x, _v1.y, _v2.x, _v2.y });
    }

    export
        template <typename _Ty>
    vec4<_Ty>&& make_vec(const vec3<_Ty>& _v1, const _Ty& _w) {
        return std::move({ _v1.x, _v1.y, _v1.z, _w });
    }

    export
        template <typename _Ty>
    vec4<_Ty>&& make_vec(const _Ty& _w, const vec3<_Ty>& _v1) {
        return std::move({ _w, _v1.x, _v1.y, _v1.z });
    }

    export // Get the value pointer.
        template <typename _Ty>
    const _Ty* value_ptr(const vec4<_Ty>& _v) {
        return &(_v.x);
    }

    export using vec4f = vec4<float>;
    export using vec4lf = vec4<long double>;

    export template<typename _Ty>
        constinit const vec4<_Ty> zero_vec4{ 0,0,0,0 };

    export typedef vec4<float> vector;
} // namespace zen.
#  else
#  error Your compiler should supports C++20.
#  endif
#else
#error You should at least have a C++ compiler.
#endif