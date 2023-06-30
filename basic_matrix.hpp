#pragma once
#include "simd.hpp"         // for vectorlized initialization
#include "basic_vector.hpp" // for vector multiplication.

#if defined _WIN32
#    pragma warning(disable:4996) // no warning for memcpy
#endif

namespace force {

    template <typename Ty>
    // The base of mat2x2 and mat3x3 and mat4x4
    class basic_mat32x4x4 {
    protected:
        union {
            alignas(16 * 4) Ty m_data[4][4];
#if defined FORCE_USE_SIMD_MATRIX
            alignas(16 * 4) simd::vec128<Ty>::type m_vdata[4];
#endif
        };
    public:
        using value_type = Ty;
        static constexpr unsigned int memsize = 64;

        constexpr basic_mat32x4x4() :m_data()                              { std::memset(m_data, 0, memsize); }
        constexpr basic_mat32x4x4(const basic_mat32x4x4& right) : m_data() { std::memcpy(m_data, (right.m_data), memsize); }
        constexpr basic_mat32x4x4(basic_mat32x4x4&& right) : m_data()      { std::memcpy(m_data, (right.m_data), memsize); }
#if defined FORCE_USE_SIMD_MATRIX
#else
        basic_mat32x4x4& operator= (const basic_mat32x4x4& right) {
            std::memcpy(m_data, (right.m_data), memsize);
            return *this; 
        }
        basic_mat32x4x4& operator+=(const basic_mat32x4x4& right) {
            for (std::size_t i = 0; i < 4; ++i)
                for (std::size_t j = 0; j < 4; ++j)
                    m_data[i][j] += right.m_data[i][j];
            return *this;
        }
        basic_mat32x4x4& operator-=(const basic_mat32x4x4& right) {
            for (std::size_t i = 0; i < 4; ++i)
                for (std::size_t j = 0; j < 4; ++j)
                    m_data[i][j] -= right.m_data[i][j];
            return *this;
        }
        basic_mat32x4x4& operator*=(value_type k) { 
            for (std::size_t i = 0; i < 4; ++i)
                for (std::size_t j = 0; j < 4; ++j)
                    m_data[i][j] *= k;
            return *this;
        }
        basic_mat32x4x4& operator/=(value_type k) { 
            for (std::size_t i = 0; i < 4; ++i)
                for (std::size_t j = 0; j < 4; ++j)
                    m_data[i][j] /= k;
            return *this;
        }
        basic_mat32x4x4& operator*=(const basic_mat32x4x4& right) {
            basic_mat32x4x4 tmp;
            for (std::size_t i = 0; i < 4; ++i) {
                for (std::size_t j = 0; j < 4; ++j) {
                    Ty sum = 0;
                    for (std::size_t k = 0; k < 4; ++k)
                        sum += m_data[i][k] * right.m_data[k][j];
                    tmp.m_data[i][j] = sum;
                }
            }
            *this = tmp;
            return *this;
        }
        basic_mat32x4x4 transpose() {
            basic_mat32x4x4 tmp;
            for (std::size_t i = 0; i < 4; ++i)
                for (std::size_t j = 0; j < 4; ++j)
                    tmp.m_data[i][j] = m_data[j][i];
            return tmp;
        }
#endif

        const Ty* data() const { return &m_data[0][0]; }
        virtual ~basic_mat32x4x4() = default;
    };

    template <typename Ty>
    [[nodiscard]] constexpr basic_mat32x4x4<Ty> operator+(const basic_mat32x4x4<Ty>& a, const basic_mat32x4x4<Ty>& b) {
        basic_mat32x4x4<Ty> tmp(a); tmp += b; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_mat32x4x4<Ty> operator-(const basic_mat32x4x4<Ty>& a, const basic_mat32x4x4<Ty>& b) {
        basic_mat32x4x4<Ty> tmp(a); tmp -= b; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_mat32x4x4<Ty> operator*(const basic_mat32x4x4<Ty>& a, Ty k) {
        basic_mat32x4x4<Ty> tmp(a); tmp *= k; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_mat32x4x4<Ty> operator/(const basic_mat32x4x4<Ty>& a, Ty k) {
        basic_mat32x4x4<Ty> tmp(a); tmp /= k; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_mat32x4x4<Ty> operator*(const basic_mat32x4x4<Ty>& a, const basic_mat32x4x4<Ty>& b) {
        basic_mat32x4x4<Ty> tmp(a); tmp *= b; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_vec128<Ty> operator*(const basic_mat32x4x4<Ty> a, const basic_vec128<Ty>& b) {
        auto* vdata = b.data();
        auto* mdata = a.data();
        Ty d[4] = {
            vdata[0] * mdata[0* 4 + 0] + vdata[1] * mdata[0 * 4 + 1] + vdata[2] * mdata[0 * 4 + 2] + vdata[3] * mdata[0* 4 + 3],
            vdata[0] * mdata[1* 4 + 0] + vdata[1] * mdata[1 * 4 + 1] + vdata[2] * mdata[1 * 4 + 2] + vdata[3] * mdata[1* 4 + 3],
            vdata[0] * mdata[2* 4 + 0] + vdata[1] * mdata[2 * 4 + 1] + vdata[2] * mdata[2 * 4 + 2] + vdata[3] * mdata[2* 4 + 3],
            vdata[0] * mdata[3* 4 + 0] + vdata[1] * mdata[3 * 4 + 1] + vdata[2] * mdata[3 * 4 + 2] + vdata[3] * mdata[3* 4 + 3]
        };
        return basic_vec128<Ty>(d);
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_vec128<Ty> operator*(const basic_vec128<Ty>& a, const basic_mat32x4x4<Ty>& b) {
        auto* vdata = a.data();
        auto* mdata = b.data();
        Ty d[4] = {
            vdata[0] * mdata[0 * 4 + 0] + vdata[1] * mdata[1 * 4 + 0] + vdata[2] * mdata[2 * 4 + 0] + vdata[3] * mdata[3 * 4 + 0],
            vdata[0] * mdata[0 * 4 + 1] + vdata[1] * mdata[1 * 4 + 1] + vdata[2] * mdata[2 * 4 + 1] + vdata[3] * mdata[3 * 4 + 1],
            vdata[0] * mdata[0 * 4 + 2] + vdata[1] * mdata[1 * 4 + 2] + vdata[2] * mdata[2 * 4 + 2] + vdata[3] * mdata[3 * 4 + 2],
            vdata[0] * mdata[0 * 4 + 3] + vdata[1] * mdata[1 * 4 + 3] + vdata[2] * mdata[2 * 4 + 3] + vdata[3] * mdata[3 * 4 + 3]
        };
        return basic_vec128<Ty>(d);
    }
}