#pragma once
#include "PrMathFn.hpp"
#include "VectorPipe.hpp"
namespace Fma {
    // BasicVector class is the template for all Vectors.
    // Ty is the element type and Dimension is the array size.
    // VecPipeT is the middle viewer Vector type.
    // If Vectors want to do conversions, they have to make sure their pipe_type has the same type and same max size.
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    class BasicVector {
        // Array to store the Data.
        Ty mData[Dimension];
    public:
        using value_type = Ty;
        using pipe_type  = VecPipeT;

        static constexpr std::size_t dimension = Dimension;

        BasicVector() {
            std::fill(mData, mData + dimension, static_cast<value_type>(0));
        }
        // Initializer_list can copy elements to Data.
        // It's safe if you don't pass in any parameter or you list's len
        // is greater than Vector's actual dimension.
        BasicVector(std::initializer_list<value_type> lst) {
            std::fill(mData, mData + dimension, static_cast<value_type>(0));
            std::copy(lst.begin(), lst.end(), mData);
        }
        // pipe constructor can use to do conversions.
        BasicVector(const pipe_type& v) {
            std::fill(mData, mData + dimension, static_cast<value_type>(0));
            std::copy(v.Data(), v.Data() + std::min(dimension, v.Size()), mData);
        }
        BasicVector(const BasicVector& right) noexcept {
            std::copy(right.mData, right.mData + dimension, mData);
        }
        BasicVector(BasicVector&& right)      noexcept {
            std::move(right.mData, right.mData + dimension, mData);
        }
        // operator= can use to assign value without using constructors.
        BasicVector& operator=(const BasicVector& right) {
            std::copy(right.mData, right.mData + dimension, mData);
            return *this;
        }
        BasicVector& operator=(const pipe_type& v) {
            std::copy(v.Data(), v.Data() + std::min(dimension, v.Size()), mData);
            return *this;
        }
        // All commands below can turn on simd optimization by default.
        // You don't have to use simd macros to turn them on any more - they are autoMaticly.
        BasicVector& operator+=(const BasicVector& right) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) mData[i] += right.mData[i];
            return *this;
        }
        BasicVector& operator-=(const BasicVector& right) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) mData[i] -= right.mData[i];
            return *this;
        }
        BasicVector& operator*=(const value_type& k) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) mData[i] *= k;
            return *this;
        }
        BasicVector& operator/=(const value_type& k) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) mData[i] /= k;
            return *this;
        }
        value_type&       operator[](size_t i)       { return  mData[i]; }
        const value_type& operator[](size_t i) const { return  mData[i]; }
        // Data operator returns the Data
        // It's useful when you are passing arrays to some programs.
        const value_type* Data() const                    { return  mData; }
        // Dereference operator returns the pipe required.
        // Vectors can do conversions with pipe_type.
        // Only Vectors has the same pipe_type can do conversions.
        pipe_type         operator*() const               { return pipe_type(mData, dimension); }
        // Shuffle operator can give back a new Vector using this Vector to construct.
        // To use this just simply give ArgDim parameter(this is neccesarry) and give in initalizer_list
        // Which has the exact same size as ArgDim.
        template <typename ... Indecies, std::size_t ArgDim = sizeof...(Indecies)>
        BasicVector<Ty, ArgDim, VecPipeT>        operator()(Indecies ... idx) const {
            BasicVector<Ty, ArgDim, VecPipeT>  rVec{};
            std::initializer_list<std::size_t>  ids = { (std::size_t)idx... };
            for (std::size_t i = 0; i < ArgDim; ++i) rVec[i] = mData[*(ids.begin() + i)];
            return rVec;
        }

        // Since there is no dynamic allocation
        // The deconstructor needs to do nothing.
        ~BasicVector() = default;
    };

    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const BasicVector<Ty, Dimension, VecPipeT> operator+(const BasicVector<Ty, Dimension, VecPipeT>& a,
        const BasicVector<Ty, Dimension, VecPipeT>& b) {
        BasicVector<Ty, Dimension, VecPipeT> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const BasicVector<Ty, Dimension, VecPipeT> operator-(const BasicVector<Ty, Dimension, VecPipeT>& a,
        const BasicVector<Ty, Dimension, VecPipeT>& b) {
        BasicVector<Ty, Dimension, VecPipeT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const BasicVector<Ty, Dimension, VecPipeT> operator*(const BasicVector<Ty, Dimension, VecPipeT>& a, Ty k) {
        BasicVector<Ty, Dimension, VecPipeT> tmp(a);
        tmp *= k;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const BasicVector<Ty, Dimension, VecPipeT> operator/(const BasicVector<Ty, Dimension, VecPipeT>& a, Ty k) {
        BasicVector<Ty, Dimension, VecPipeT> tmp(a);
        tmp /= k;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const BasicVector<Ty, Dimension, VecPipeT> operator+(const BasicVector<Ty, Dimension, VecPipeT>& a) {
        return a;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const BasicVector<Ty, Dimension, VecPipeT> operator-(const BasicVector<Ty, Dimension, VecPipeT>& a) {
        BasicVector<Ty, Dimension, VecPipeT> v{ static_cast<Ty>(0) }; v -= a; return v;
    }
    ///////////////////////////////////
    // Algorithms for BasicVectors. //
    //////////////////////////////////
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] bool operator==(const BasicVector<Ty, Dimension, VecPipeT>& a,
        const BasicVector<Ty, Dimension, VecPipeT>& b) {
        bool state = true;
        for (int i = 0; i < Dimension; ++i)
            if (Fabs(a[i] - b[i]) > std::numeric_limits<Ty>::epsilon()) return false;
        return true;
    }
    // Two functions to do Vector calculation.
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    const Ty Dot(const BasicVector<Ty, Dimension, VecPipeT>& a, const BasicVector<Ty, Dimension, VecPipeT>& b) {
        auto s = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) s += (a[i] * b[i]);
        return s;
    }
    // Length here is use to get the Length(modulus) of a Vector.
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    const Ty Length(const BasicVector<Ty, Dimension, VecPipeT>& a) {
        auto s = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) s += (a[i] * a[i]);
        return Fsqrt(s);
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    BasicVector<Ty, Dimension, VecPipeT> Norm(const BasicVector<Ty, Dimension, VecPipeT>& a) {
        auto esqd = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) esqd += (a[i] * a[i]);
        BasicVector<Ty, Dimension, VecPipeT> k(a); k *= Frsqrt(esqd);
        return k;
    }
    // Cross product is only avalible for 3 dimensional Vectors.
    template <typename Ty, class VecPipeT>
    BasicVector<Ty, 3, VecPipeT> Cross(const BasicVector<Ty, 3, VecPipeT>& a, const BasicVector<Ty, 3, VecPipeT>& b) {
        return {
            a[1] * b[2] - b[1] * a[2],
            a[2] * b[0] - b[2] * a[0],
            a[0] * b[1] - b[0] * a[1]
        };
    }

}