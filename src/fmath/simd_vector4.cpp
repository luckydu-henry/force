#include <fmath/simd_vector4.hpp>
#include <fmath/simd_decl.hpp>
#include <emmintrin.h>

#if FMA_COMPILER & FMA_COMPILER_VC
#pragma warning(disable:4661)
#endif

namespace force::math {
    // Only supports this two types.
    template class SIMDVector4<float>;
    template class SIMDVector4<int>;

    template <typename Ty>
    using SIMDType = SIMDVector4<Ty>::SIMDType;

    template <typename Ty>
    inline SIMDType<Ty> Intrin_set1(Ty v) {
        if constexpr (std::is_same_v<Ty, float>)    return _mm_set_ps1(v);
        else if constexpr (std::is_same_v<Ty, int>) return _mm_set1_epi32(v);
    }
    template <typename Ty>
    inline SIMDType<Ty> Intrin_load(const Ty* const d) {
        if constexpr (std::is_same_v<Ty, float>)    return _mm_loadu_ps(d);
        else if constexpr (std::is_same_v<Ty, int>) return _mm_loadu_epi32(d);
    }
    template <typename Ty>
    inline SIMDType<Ty> Intrin_add(const SIMDType<Ty>& a, const SIMDType<Ty>& b) {
        if constexpr (std::is_same_v<Ty, float>)    return _mm_add_ps(a, b);
        else if constexpr (std::is_same_v<Ty, int>)  return _mm_add_epi32(a, b);
    }
    template <typename Ty>
    inline SIMDType<Ty> Intrin_sub(const SIMDType<Ty>& a, const SIMDType<Ty>& b) {
        if constexpr (std::is_same_v<Ty, float>)    return _mm_sub_ps(a, b);
        else if constexpr (std::is_same_v<Ty, int>)  return _mm_sub_epi32(a, b);
    }
    template <typename Ty>
    inline SIMDType<Ty> Intrin_mul(const SIMDType<Ty>& a, const SIMDType<Ty>& b) {
        if constexpr (std::is_same_v<Ty, float>)    return _mm_mul_ps(a, b);
        else if constexpr (std::is_same_v<Ty, int>)  return _mm_mul_epi32(a, b);
    }
    template <typename Ty>
    inline SIMDType<Ty> Intrin_div(const SIMDType<Ty>& a, const SIMDType<Ty>& b) {
        if constexpr (std::is_same_v<Ty, float>)    return _mm_div_ps(a, b);
        else if constexpr (std::is_same_v<Ty, int>)  return _mm_div_epi32(a, b);
    }
    template <typename Ty>
    inline Ty Intrin_dot(const SIMDType<Ty>& a, const SIMDType<Ty>& b) {
        static_assert(std::is_same_v<Ty, float>, "Interger vector does not support dot product!");

        if constexpr (std::is_same_v<Ty, float>) {
            auto c = _mm_mul_ps(a, b);
            auto shuf = _mm_shuffle_ps(c, c, 0xb1);
            auto sums = _mm_add_ps(c, shuf);
            shuf = _mm_movehl_ps(shuf, sums);
            sums = _mm_add_ps(sums, shuf);
            return _mm_cvtss_f32(sums);
        }
    }

    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4(SIMDVector4<Ty>::SIMDType t) : idata(t) {}

    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4() : idata(Intrin_set1<Ty>(static_cast<Ty>(0))) {}

    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4(std::initializer_list<Ty> lst) : idata(Intrin_set1<Ty>(static_cast<Ty>(0))) {
        // Then create cache
        auto a = Intrin_load<Ty>(lst.begin());
        // Then copy data
        idata = a;
    }
    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4(const pipe_type& p) : idata(Intrin_set1<Ty>(0)) {
        // Then load data.
        auto a = Intrin_load<Ty>(p.vdata);
        // Then copy data.
        idata = a;
    }
    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4(const SIMDVector4<Ty>& right) noexcept : idata(right.idata) {}
    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4(SIMDVector4<Ty>&& right) noexcept : idata(right.idata) {}

    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator=(const SIMDVector4<Ty>& right) {
        idata = Intrin_load(right.vdata);
        return *this;
    }
    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator=(const pipe_type& right) {
        idata = Intrin_load(right.vdata);
        return *this;
    }
    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator+=(const SIMDVector4<Ty>& right) {
        idata = Intrin_add<Ty>(idata, right.idata);
        return *this;
    }
    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator-=(const SIMDVector4<Ty>& right) {
        idata = Intrin_sub<Ty>(idata, right.idata);
        return *this;
    }
    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator*=(const Ty& right) {
        idata = Intrin_mul<Ty>(idata, Intrin_set1<Ty>(right));
        return *this;
    }
    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator/=(const Ty& right) {
        idata = Intrin_div<Ty>(idata, Intrin_set1<Ty>(right));
        return *this;
    }
    template <typename Ty>
    const SIMDVector4<Ty> SIMDVector4<Ty>::operator+(const SIMDVector4<Ty>& right) {
        return Intrin_add<Ty>(idata, right.idata);
    }
    template <typename Ty>
    const SIMDVector4<Ty> SIMDVector4<Ty>::operator-(const SIMDVector4<Ty>& right) {
        return Intrin_sub<Ty>(idata, right.idata);
    }
    template <typename Ty>
    const SIMDVector4<Ty> SIMDVector4<Ty>::operator*(const Ty& right) {
        return Intrin_mul<Ty>(idata, Intrin_set1<Ty>(right));
    }
    template <typename Ty>
    const SIMDVector4<Ty> SIMDVector4<Ty>::operator/(const Ty& right) {
        return Intrin_div<Ty>(idata, Intrin_set1<Ty>(right));
    }

    // Functions.
    template <typename Ty> const SIMDVector4<Ty> operator+(const SIMDVector4<Ty>& a) {
        return a;
    }
    template <typename Ty> const SIMDVector4<Ty> operator-(const SIMDVector4<Ty>& a) {
        return Intrin_sub<Ty>(Intrin_set1<Ty>(0), a.idata);
    }
    template <typename Ty> const Ty              dot(const SIMDVector4<Ty>& a, const SIMDVector4<Ty>& b) {
        return Intrin_dot<Ty>(a.idata, b.idata);
    }
    template <typename Ty> const Ty              length(const SIMDVector4<Ty>& a) {
        auto k = Intrin_dot<Ty>(a.idata, a.idata);
        return sqrt(k);
    }
    template <typename Ty> const SIMDVector4<Ty> norm(const SIMDVector4<Ty>& a) {
        auto k = Intrin_dot<Ty>(a.idata, a.idata);
        k = rsqrt(k);
        return Intrin_mul<Ty>(a.idata, Intrin_set1<Ty>(k));
    }
    template <typename Ty>
    const bool operator==(const SIMDVector4<Ty>& a, const SIMDVector4<Ty>& b) {
        if constexpr (std::is_same_v<Ty, int>)
            return _mm_movemask_epi8(_mm_cmpeq_epi32(a.idata, b.idata)) == 0xffff;
        else if constexpr (std::is_same_v<Ty, float>)
            return _mm_movemask_ps(_mm_cmpeq_ps(a.idata, b.idata)) == 0xf;
    }
}