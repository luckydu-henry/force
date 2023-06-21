#pragma once
#include <concepts>
#include "simd.hpp"
#include "prmthfn.hpp"
namespace force {

    // The base class of all four vectors.
    template <typename Ty>
    class basic_vector4;

    template <>
    class alignas(16) basic_vector4<float> {
    protected:
        float m_data[4];
    public:

        // Two useful friend functions.
        friend float dot(const basic_vector4<float>&, const basic_vector4<float>&);
        friend float modulus(const basic_vector4<float>&);

        constexpr explicit basic_vector4() :m_data() {}
        constexpr explicit basic_vector4(float x, float y, float z, float w) noexcept :m_data() {
            m_data[0] = x;
            m_data[1] = y;
            m_data[2] = z;
            m_data[3] = w;
        }
        basic_vector4(const basic_vector4& right) noexcept :m_data() {
            m_data[0] = right.m_data[0];
            m_data[1] = right.m_data[1];
            m_data[2] = right.m_data[2];
            m_data[3] = right.m_data[3];
        }
        basic_vector4(basic_vector4&&) = default;


#if defined FORCE_USE_SIMD_VECTOR
        basic_vector4& operator=(const basic_vector4& right) {
            simd::a_init_vec4f(m_data, right.m_data);
            return *this;
        }
        basic_vector4& operator+=(const basic_vector4& right) {
            simd::a_vec4f_add_sub<simd::c_add>(m_data, right.m_data, m_data);
            return *this;
        }
        basic_vector4& operator-=(const basic_vector4& right) {
            simd::a_vec4f_add_sub<simd::c_sub>(m_data, right.m_data, m_data);
            return *this;
        }
        basic_vector4& operator*=(float k) {
            simd::a_vec4f_mul_div_s<simd::c_mul>(m_data, k, m_data);
            return *this;
        }
        basic_vector4& operator/=(float k) {
            simd::a_vec4f_mul_div_s<simd::c_div>(m_data, k, m_data);
            return *this;
        }
#else
        constexpr basic_vector4& operator=(const basic_vector4& right) {
            m_data[0] = right.m_data[0];
            m_data[1] = right.m_data[1];
            m_data[2] = right.m_data[2];
            m_data[3] = right.m_data[3];
            return *this;
        }
        constexpr basic_vector4& operator+=(const basic_vector4& right) {
            m_data[0] += right.m_data[0];
            m_data[1] += right.m_data[1];
            m_data[2] += right.m_data[2];
            m_data[3] += right.m_data[3];
            return *this;
        }
        constexpr basic_vector4& operator-=(const basic_vector4& right) {
            m_data[0] -= right.m_data[0];
            m_data[1] -= right.m_data[1];
            m_data[2] -= right.m_data[2];
            m_data[3] -= right.m_data[3];
            return *this;
        }
        constexpr basic_vector4& operator*=(float k) {
            m_data[0] *= k;
            m_data[1] *= k;
            m_data[2] *= k;
            m_data[3] *= k;
            return *this;
        }
        constexpr basic_vector4& operator/=(float k) {
            m_data[0] /= k;
            m_data[1] /= k;
            m_data[2] /= k;
            m_data[3] /= k;
            return *this;
        }
#endif
        const float* data() const { return &(m_data[0]); }

        virtual ~basic_vector4() = default;
    };

    template <typename Ty>
    class vec2;
    template <>
    class vec2<float> : public basic_vector4<float> {
    public:
        vec2() : basic_vector4<float>() {}
        vec2(float x, float y) : basic_vector4<float>(x, y, 0.f, 0.f) {}
        vec2(const basic_vector4<float>& right) : basic_vector4<float>(right) {
            m_data[2] = 0.f;
            m_data[3] = 0.f;
        }
        vec2(basic_vector4<float>&& right) : basic_vector4<float>(right) {
            m_data[2] = 0.f;
            m_data[3] = 0.f;
        }

        float& x() { return m_data[0]; }
        const float& x() const { return m_data[0]; }
        float& y() { return m_data[1]; }
        const float& y() const { return m_data[1]; }

        ~vec2() override = default;
    };


    // vector3 inheritage.
    template <typename Ty>
    class vec3;
    template <>
    class vec3<float> : public basic_vector4<float> {
    public:
        vec3() : basic_vector4<float>() {}
        vec3(float x, float y, float z) : basic_vector4<float>(x, y, z, 0.f) {}
        vec3(const basic_vector4<float>& right) : basic_vector4<float>(right) {
            m_data[3] = 0.f;
        }
        vec3(basic_vector4<float>&& right) : basic_vector4<float>(right) {
            m_data[3] = 0.f;
        }

        float& x() { return m_data[0]; }
        const float& x() const { return m_data[0]; }
        float& y() { return m_data[1]; }
        const float& y() const { return m_data[1]; }
        float& z() { return m_data[2]; }
        const float& z() const { return m_data[2]; }

        ~vec3() override = default;
    };
    // vector4 inheritage.
    template <typename Ty>
    class vec4;
    template <>
    class vec4<float> : public basic_vector4<float> {
    public:
        vec4() : basic_vector4<float>() {}
        vec4(float x, float y, float z, float w) : basic_vector4<float>(x, y, z, w) {}
        vec4(const basic_vector4<float>& right) : basic_vector4<float>(right) {}
        vec4(basic_vector4<float>&& right) : basic_vector4<float>(right) {}

        float& x() { return m_data[0]; }
        const float& x() const { return m_data[0]; }
        float& y() { return m_data[1]; }
        const float& y() const { return m_data[1]; }
        float& z() { return m_data[2]; }
        const float& z() const { return m_data[2]; }
        float& w() { return m_data[3]; }
        const float& w() const { return m_data[3]; }

        ~vec4() override = default;
    };


    [[nodiscard]]
    basic_vector4<float> operator+(const basic_vector4<float>& a, const basic_vector4<float>& b) {
        basic_vector4<float> tmp(a);
        tmp += b;
        return tmp;
    }

    [[nodiscard]]
    basic_vector4<float> operator-(const basic_vector4<float>& a, const basic_vector4<float>& b) {
        basic_vector4<float> tmp(a);
        tmp -= b;
        return tmp;
    }
    [[nodiscard]]
    basic_vector4<float> operator*(const basic_vector4<float>& a, float b) {
        basic_vector4<float> tmp(a);
        tmp *= b;
        return tmp;
    }
    [[nodiscard]]
    basic_vector4<float> operator/(const basic_vector4<float>& a, float b) {
        basic_vector4<float> tmp(a);
        tmp /= b;
        return tmp;
    }

    [[nodiscard]] float dot(const basic_vector4<float>& v1, const basic_vector4<float>& v2) {
        float _0 = v1.m_data[0] * v2.m_data[0];
        float _1 = v1.m_data[1] * v2.m_data[1];
        float _2 = v1.m_data[2] * v2.m_data[2];
        float _3 = v1.m_data[3] * v2.m_data[3];
        return _0 + _1 + _2 + _3;
    }

    [[nodiscard]] float modulus(const basic_vector4<float>& v) {
        return ::force::sqrt(
            v.m_data[0] * v.m_data[0] +
            v.m_data[1] * v.m_data[1] +
            v.m_data[2] * v.m_data[2] +
            v.m_data[3] * v.m_data[3]);
    }
#if defined FORCE_USE_SIMD_VECTOR
    [[nodiscard]] bool operator==(const basic_vector4<float>& v1, const basic_vector4<float>& v2) {
        return simd::a_compare_vec4f(v1.data(), v2.data());
    }
#else
    [[nodiscard]] bool operator==(const basic_vector4<float>& v1, const basic_vector4<float>& v2) {
        return  (v1.m_data[0] == v2.m_data[0]) &&
                (v1.m_data[1] == v2.m_data[1]) &&
                (v1.m_data[2] == v2.m_data[2]) &&
                (v1.m_data[3] == v2.m_data[3]);
    }
#endif
    // When dealing with homogeneous coordinate
    // We need to set last dimension to 1, so that we can transform a vector.
    const vec3<float>& make_homovec(float x, float y) {
        return vec3<float>(x, y, 1.f);
    }
    const vec4<float>& make_homovec(float x, float y, float z) {
        return vec4<float>(x, y, y, 1.f);
    }

    using vec2f = vec2<float>;
    using vec3f = vec3<float>;
    using vec4f = vec4<float>;
}