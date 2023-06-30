#pragma once
#include "prmthfn.hpp"
#include <cstring> // for memory operation.
#include "simd.hpp"
namespace force {
    // base class of vector.
    // Do not use this base class directly use its sub classes for safe simd support and better syntax.
    template <typename Ty>
    class basic_vec128 { // 128 bit (16 byte) aligned vector
    protected:
        static constexpr unsigned int m_size() {
            if constexpr (sizeof(Ty) == 1) return 16;
            if constexpr (sizeof(Ty) == 2) return 8;
            if constexpr (sizeof(Ty) == 4) return 4;
            if constexpr (sizeof(Ty) == 8) return 2;
        }
        union {
            alignas(16) Ty m_data[basic_vec128::m_size()];
#if defined FORCE_USE_SIMD_VECTOR
            alignas(16) simd::vec128<Ty>::type m_vdata;
#endif
        };
        // Constructor for converting arrays to a vector.
    public:
        template <typename ArgTy>
        friend const ArgTy dot(const basic_vec128<ArgTy>&, const basic_vec128<ArgTy>&);
        template <typename ArgTy>
        friend const ArgTy modulus(const basic_vec128<ArgTy>&);
        template <typename ArgTy>
        friend const basic_vec128<ArgTy> normallize(const basic_vec128<ArgTy>&);
        template <typename ArgTy>
        friend const bool operator==(const basic_vec128<ArgTy>&, const basic_vec128<ArgTy>&);

        using value_type = Ty;
        static constexpr unsigned int memsize = 16;
        static constexpr Ty zero[4] = { 0,0,0,1 };

        constexpr basic_vec128() :m_data()                           { std::memset(m_data, 0, memsize); }
        constexpr basic_vec128(const basic_vec128& right) : m_data() { std::memcpy(m_data, right.m_data, memsize); }
        constexpr basic_vec128(basic_vec128&& right) :m_data()       { std::memcpy(m_data, right.m_data, memsize); }
        constexpr basic_vec128(const Ty* v)          :m_data()       { std::memcpy(m_data, v, memsize); }
#if defined FORCE_USE_SIMD_VECTOR && ((BOOST_HW_SIMD_X86 >= BOOST_HW_SIMD_X86_SSE_VERSION))
        basic_vec128& operator= (const basic_vec128& right) { simd::a_init_vec128<Ty>(m_data, right.m_data);  return *this; }
        basic_vec128& operator+=(const basic_vec128& right) { simd::a_vec128_add_sub<Ty, simd::c_add>(m_vdata, right.m_vdata, m_vdata); return *this; }
        basic_vec128& operator-=(const basic_vec128& right) { simd::a_vec128_add_sub<Ty, simd::c_sub>(m_vdata, right.m_vdata, m_vdata); return *this; }
        basic_vec128& operator*=(value_type k) { simd::a_vec128_mul_div_s<Ty, simd::c_mul>(m_vdata, k, m_vdata); return *this; }
        basic_vec128& operator/=(value_type k) { simd::a_vec128_mul_div_s<Ty, simd::c_div>(m_vdata, k, m_vdata); return *this; }
        basic_vec128& operator-() {
            auto v = simd::vec128<Ty>::set1_p(static_cast<Ty>(0));
            simd::a_vec128_add_sub<Ty, simd::c_sub>(v, m_vdata, m_vdata);
            return *this;
        }
#else
        // When you turn on release mode, compiler will optimized all loops.
        basic_vec128& operator= (const basic_vec128& right) { std::memcpy(m_data, right.m_data, memsize); return *this; }
        basic_vec128& operator+=(const basic_vec128& right) { for (std::size_t i = 0; i < basic_vec128::m_size(); ++i) m_data[i] += right.m_data[i]; return *this; }
        basic_vec128& operator-=(const basic_vec128& right) { for (std::size_t i = 0; i < basic_vec128::m_size(); ++i) m_data[i] -= right.m_data[i]; return *this; }
        basic_vec128& operator*=(value_type k) { for (std::size_t i = 0; i < basic_vec128::m_size(); ++i) m_data[i] *= k; return *this; }
        basic_vec128& operator/=(value_type k) { for (std::size_t i = 0; i < basic_vec128::m_size(); ++i) m_data[i] /= k; return *this; }
        basic_vec128& operator-() { for (std::size_t i = 0; i < basic_vec128::m_size(); ++i) m_data[i] = -m_data[i]; return *this; }
#endif  
        const Ty* data() const { return m_data; }

        virtual ~basic_vec128() = default;
    };
    template <typename Ty>
    [[nodiscard]] constexpr basic_vec128<Ty> operator+(const basic_vec128<Ty>& a, const basic_vec128<Ty>& b) {
        basic_vec128<Ty> tmp(a); tmp += b; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_vec128<Ty> operator-(const basic_vec128<Ty>& a, const basic_vec128<Ty>& b) {
        basic_vec128<Ty> tmp(a); tmp -= b; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_vec128<Ty> operator*(const basic_vec128<Ty>& a, Ty k) {
        basic_vec128<Ty> tmp(a); tmp *= k; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_vec128<Ty> operator/(const basic_vec128<Ty>& a, Ty k) {
        basic_vec128<Ty> tmp(a); tmp /= k; return tmp;
    }
// If your platform is intel, then you must atleast supports SSE for basic basic_vec128<float>
// Optimization. Intel SSE provides __m128 which is float[4] simd.
#if defined FORCE_USE_SIMD_VECTOR && ((BOOST_HW_SIMD_X86 >= BOOST_HW_SIMD_X86_SSE_VERSION))
    template <typename Ty>
    inline const Ty dot(const basic_vec128<Ty>& v1, const basic_vec128<Ty>& v2) {
        return simd::a_dot_product_vec128<Ty>(v1.m_vdata, v2.m_vdata);
    }
    template <typename Ty>
    inline const Ty modulus(const basic_vec128<Ty>& v) {
        return ::force::sqrt(simd::a_dot_product_vec128<Ty>(v.m_vdata, v.m_vdata));
    }
    template <typename Ty>
    inline const basic_vec128<Ty> normallize(const basic_vec128<Ty>& v) {
        basic_vec128<Ty> tmp = v;
        tmp *= ::force::rsqrt(simd::a_dot_product_vec128<Ty>(v.m_vdata, v.m_vdata));
        return tmp;
    }
    template <typename Ty>
    inline const bool operator==(const basic_vec128<Ty>& v1, const basic_vec128<Ty>& v2) {
        return simd::a_compare_vec128<Ty>(v1.m_vdata, v2.m_vdata);
    }
#endif

} //! namespace force.