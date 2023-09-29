#pragma once
#define  SIMD_VECTOR4x32 true
#include "basic_vector.hpp"
#include "simd_decl.hpp"

namespace force::math {

    // Specialization for SIMDVector4<float, 4, Vec4fPipe>
    // Whic is simd_vector4 uses SSE2 intrinsics (Atleast)
    template <typename Ty>
    class SIMDVector4 {
    public:
#if FMA_ARCH & FMA_ARCH_X86
        using SIMDType = typename std::conditional_t<std::is_same_v<Ty, float>, __m128, __m128i>;
#endif
        static_assert(std::is_same_v<Ty, float> | std::is_same_v<Ty, int>, "Not uint32 nor float types are not supported!");
        // Only 4byte types such as int, unsigned int, float support
        union {
            alignas(16) Ty                 vdata[4];
            SIMDType                       idata;
        };

        using value_type = Ty;
        using pipe_type = basic_pipe<Ty, 4>; ;

        static constexpr std::size_t dimension = 4;

        SIMDVector4();
        // This constructor is only avalable for simd types.
        SIMDVector4(SIMDType t);
        // Initializer_list can copy elements to Data.
        // It's safe if you don't pass in any parameter or you list's len
        // is greater than Vector's actual dimension.
        SIMDVector4(std::initializer_list<value_type> lst);
        // pipe constructor can use to do conversions.
        SIMDVector4(const pipe_type& v);
        SIMDVector4(const SIMDVector4& right) noexcept;
        SIMDVector4(SIMDVector4&& right)      noexcept;

        SIMDVector4& operator=(const SIMDVector4& right);
        SIMDVector4& operator=(const pipe_type& v);
        SIMDVector4& operator+=(const SIMDVector4& right);
        SIMDVector4& operator-=(const SIMDVector4& right);
        SIMDVector4& operator*=(const value_type& k);
        SIMDVector4& operator/=(const value_type& k);

        const SIMDVector4     operator+(const SIMDVector4& right);
        const SIMDVector4     operator-(const SIMDVector4& right);
        const SIMDVector4     operator*(const value_type& k);
        const SIMDVector4     operator/(const value_type& k);

        value_type&       operator[](size_t i) { return vdata[i]; }
        const value_type& operator[](size_t i) const { return vdata[i]; }
        pipe_type         operator*() const { return basic_pipe<Ty, 4>(vdata, 4); }

        // This one can't have simd optimization.
        template <typename ... Indecies, std::size_t ArgDim = sizeof...(Indecies)>
        basic_vector<Ty, ArgDim, basic_pipe<Ty, 4>>        operator()(Indecies ... idx) const {
            basic_vector<Ty, ArgDim, basic_pipe<Ty, 4>>  rVec{};
            std::initializer_list<std::size_t>  ids = { (std::size_t)idx... };
            for (std::size_t i = 0; i < ArgDim; ++i) rVec[i] = vdata[*(ids.begin() + i)];
            return rVec;
        }

        ~SIMDVector4() = default;
    };

    template <typename Ty> const SIMDVector4<Ty> operator+ (const SIMDVector4<Ty>& a);
    template <typename Ty> const SIMDVector4<Ty> operator- (const SIMDVector4<Ty>& a);
    template <typename Ty> const bool            operator==(const SIMDVector4<Ty>& a, const SIMDVector4<Ty>& b);

    template <typename Ty> const Ty              length(const SIMDVector4<Ty>& a);
    template <typename Ty> const Ty              dot(const SIMDVector4<Ty>& a, const SIMDVector4<Ty>& b);
    template <typename Ty> const SIMDVector4<Ty> norm(const SIMDVector4<Ty>& a);


    ////////////////////////////////////////////////////////////////////
    // Explicitly template only for these functions defined in cpp file.
    ////////////////////////////////////////////////////////////////////
    template const SIMDVector4<float> operator+ (const SIMDVector4<float>& a);
    template const SIMDVector4<int>   operator+ (const SIMDVector4<int>& a);
    template const SIMDVector4<float> operator- (const SIMDVector4<float>& a);
    template const SIMDVector4<int>   operator- (const SIMDVector4<int>& a);
    template const bool               operator==(const SIMDVector4<float>& a, const SIMDVector4<float>& b);
    template const bool               operator==(const SIMDVector4<int>& a, const SIMDVector4<int>& b);

    template const float              length(const SIMDVector4<float>& a);
    template const float              dot(const SIMDVector4<float>& a, const SIMDVector4<float>& b);
    template const SIMDVector4<float> norm(const SIMDVector4<float>& a);

}