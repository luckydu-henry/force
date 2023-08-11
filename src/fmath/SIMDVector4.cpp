#include <fmath/SIMDVector4.hpp>
#include <fmath/SIMD.hpp>
#include <emmintrin.h>

#if FMA_COMPILER & FMA_COMPILER_VC
#pragma warning(disable:4661)
#endif

namespace Fma {
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
        if constexpr (std::is_same_v<Ty, float>) {
            auto c = _mm_mul_ps(a, b);
            auto shuf = _mm_shuffle_ps(c, c, 0xb1);
            auto sums = _mm_add_ps(c, shuf);
            shuf      = _mm_movehl_ps(shuf, sums);
            sums      = _mm_add_ps(sums, shuf);
            return _mm_cvtss_f32(sums);
        }
        else if constexpr (std::is_same_v<Ty, int>) {
            return 0;
        }
    }

    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4(SIMDVector4<Ty>::SIMDType t) : mSVec(t) {}

    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4() : mSVec(Intrin_set1<Ty>(static_cast<Ty>(0))) {}

    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4(std::initializer_list<Ty> lst) : mSVec(Intrin_set1<Ty>(static_cast<Ty>(0))) {
        // Then create cache
        auto a = Intrin_load<Ty>(lst.begin());
        // Then copy data
        mSVec = a;
    }
    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4(const pipe_type& p) : mSVec(Intrin_set1<Ty>(0)) {
        // Then load data.
        auto a = Intrin_load<Ty>(p.Data());
        // Then copy data.
        mSVec = a;
    }
    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4(const SIMDVector4<Ty>& right) noexcept : mSVec(right.mSVec) {}
    template <typename Ty>
    SIMDVector4<Ty>::SIMDVector4(SIMDVector4<Ty>&& right) noexcept : mSVec(right.mSVec) {}

    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator=(const SIMDVector4<Ty>& right) {
        mSVec = Intrin_load(right.mData);
        return *this;
    }
    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator=(const pipe_type& right) {
        mSVec = Intrin_load(right.Data());
        return *this;
    }
    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator+=(const SIMDVector4<Ty>& right) {
        mSVec = Intrin_add<Ty>(mSVec, right.mSVec);
        return *this;
    }
    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator-=(const SIMDVector4<Ty>& right) {
        mSVec = Intrin_sub<Ty>(mSVec, right.mSVec);
        return *this;
    }
    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator*=(const Ty& right) {
        mSVec = Intrin_mul<Ty>(mSVec, Intrin_set1<Ty>(right));
        return *this;
    }
    template <typename Ty>
    SIMDVector4<Ty>& SIMDVector4<Ty>::operator/=(const Ty& right) {
        mSVec = Intrin_div<Ty>(mSVec, Intrin_set1<Ty>(right));
        return *this;
    }
    template <typename Ty>
    const SIMDVector4<Ty> SIMDVector4<Ty>::operator+(const SIMDVector4<Ty>& right) {
        return Intrin_add<Ty>(mSVec, right.mSVec);
    }
    template <typename Ty>
    const SIMDVector4<Ty> SIMDVector4<Ty>::operator-(const SIMDVector4<Ty>& right) {
        return Intrin_sub<Ty>(mSVec, right.mSVec);
    }
    template <typename Ty>
    const SIMDVector4<Ty> SIMDVector4<Ty>::operator*(const Ty& right) {
        return Intrin_mul<Ty>(mSVec, Intrin_set1<Ty>(right));
    }
    template <typename Ty>
    const SIMDVector4<Ty> SIMDVector4<Ty>::operator/(const Ty& right) {
        return Intrin_div<Ty>(mSVec, Intrin_set1<Ty>(right));
    }

    // Functions.
    template <typename Ty> const SIMDVector4<Ty> operator+(const SIMDVector4<Ty>& a) {
        return a;
    }
    template <typename Ty> const SIMDVector4<Ty> operator-(const SIMDVector4<Ty>& a) {
        return Intrin_sub<Ty>(Intrin_set1<Ty>(0), Intrin_load<Ty>(a.Data()));
    }
    template <typename Ty> const Ty              Dot(const SIMDVector4<Ty>& a, const SIMDVector4<Ty>& b) {
        return Intrin_dot<Ty>(Intrin_load<Ty>(a.Data()), Intrin_load<Ty>(b.Data()));
    }
    template <typename Ty> const Ty              Length(const SIMDVector4<Ty>& a) {
        auto k = Intrin_dot<Ty>(Intrin_load<Ty>(a.Data()), Intrin_load<Ty>(a.Data()));
        return Fsqrt(k);
    }
    template <typename Ty> const SIMDVector4<Ty> Norm(const SIMDVector4<Ty>& a) {
        auto k = Intrin_dot<Ty>(Intrin_load<Ty>(a.Data()), Intrin_load<Ty>(a.Data()));
        k = Frsqrt(k);
        return Intrin_mul<Ty>(Intrin_load<Ty>(a.Data()), Intrin_set1<Ty>(k));
    }
}