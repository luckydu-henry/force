#pragma once
#include "primary.hpp"
#include "pipe.hpp"
namespace force::math {
    // basic_vector class is the template for all Vectors.
    // Ty is the element type and Dimension is the array size.
    // VecPipeT is the middle viewer Vector type.
    // If Vectors want to do conversions, they have to make sure their pipe_type has the same type and same max size.
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    class basic_vector {
    public:
        // Array to store the Data.
        Ty vdata[Dimension];
        using value_type = Ty;
        using pipe_type  = VecPipeT;

        static constexpr std::size_t dimension = Dimension;

        basic_vector() {
            std::fill(vdata, vdata + dimension, static_cast<value_type>(0));
        }
        // Initializer_list can copy elements to Data.
        // It's safe if you don't pass in any parameter or you list's len
        // is greater than Vector's actual dimension.
        basic_vector(std::initializer_list<value_type> lst) {
            std::fill(vdata, vdata + dimension, static_cast<value_type>(0));
            std::copy(lst.begin(), lst.end(), vdata);
        }
        // pipe constructor can use to do conversions.
        basic_vector(const pipe_type& v) {
            std::fill(vdata, vdata + dimension, static_cast<value_type>(0));
            std::copy(v.vdata, v.vdata + std::min(dimension, v.vsize), vdata);
        }
        basic_vector(const basic_vector& right) noexcept {
            std::copy(right.vdata, right.vdata + dimension, vdata);
        }
        basic_vector(basic_vector&& right)      noexcept {
            std::move(right.vdata, right.vdata + dimension, vdata);
        }
        // operator= can use to assign value without using constructors.
        basic_vector& operator=(const basic_vector& right) {
            std::copy(right.vdata, right.vdata + dimension, vdata);
            return *this;
        }
        basic_vector& operator=(const pipe_type& v) {
            std::copy(v.vdata, v.vdata + std::min(dimension, v.vsize), vdata);
            return *this;
        }
        // All commands below can turn on simd optimization by default.
        // You don't have to use simd macros to turn them on any more - they are autoMaticly.
        basic_vector& operator+=(const basic_vector& right) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) vdata[i] += right.vdata[i];
            return *this;
        }
        basic_vector& operator-=(const basic_vector& right) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) vdata[i] -= right.vdata[i];
            return *this;
        }
        basic_vector& operator*=(const value_type& k) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) vdata[i] *= k;
            return *this;
        }
        basic_vector& operator/=(const value_type& k) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) vdata[i] /= k;
            return *this;
        }
        value_type&       operator[](size_t i)       { return  vdata[i]; }
        const value_type& operator[](size_t i) const { return  vdata[i]; }
        // Dereference operator returns the pipe required.
        // Vectors can do conversions with pipe_type.
        // Only Vectors has the same pipe_type can do conversions.
        pipe_type         operator*() const               { return pipe_type(vdata, dimension); }
        // Shuffle operator can give back a new Vector using this Vector to construct.
        // To use this just simply give ArgDim parameter(this is neccesarry) and give in initalizer_list
        // Which has the exact same size as ArgDim.
        template <typename ... Indecies, std::size_t ArgDim = sizeof...(Indecies)>
        basic_vector<Ty, ArgDim, VecPipeT>        operator()(Indecies ... idx) const {
            basic_vector<Ty, ArgDim, VecPipeT>  rVec{};
            std::initializer_list<std::size_t>  ids = { (std::size_t)idx... };
            for (std::size_t i = 0; i < ArgDim; ++i) rVec[i] = vdata[*(ids.begin() + i)];
            return rVec;
        }

        // Since there is no dynamic allocation
        // The deconstructor needs to do nothing.
        ~basic_vector() = default;
    };

    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const basic_vector<Ty, Dimension, VecPipeT> operator+(const basic_vector<Ty, Dimension, VecPipeT>& a,
        const basic_vector<Ty, Dimension, VecPipeT>& b) {
        basic_vector<Ty, Dimension, VecPipeT> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const basic_vector<Ty, Dimension, VecPipeT> operator-(const basic_vector<Ty, Dimension, VecPipeT>& a,
        const basic_vector<Ty, Dimension, VecPipeT>& b) {
        basic_vector<Ty, Dimension, VecPipeT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const basic_vector<Ty, Dimension, VecPipeT> operator*(const basic_vector<Ty, Dimension, VecPipeT>& a, Ty k) {
        basic_vector<Ty, Dimension, VecPipeT> tmp(a);
        tmp *= k;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const basic_vector<Ty, Dimension, VecPipeT> operator/(const basic_vector<Ty, Dimension, VecPipeT>& a, Ty k) {
        basic_vector<Ty, Dimension, VecPipeT> tmp(a);
        tmp /= k;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const basic_vector<Ty, Dimension, VecPipeT> operator+(const basic_vector<Ty, Dimension, VecPipeT>& a) {
        return a;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] const basic_vector<Ty, Dimension, VecPipeT> operator-(const basic_vector<Ty, Dimension, VecPipeT>& a) {
        basic_vector<Ty, Dimension, VecPipeT> v{ static_cast<Ty>(0) }; v -= a; return v;
    }
    ///////////////////////////////////
    // Algorithms for basic_vectors. //
    //////////////////////////////////
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] bool operator==(const basic_vector<Ty, Dimension, VecPipeT>& a,
        const basic_vector<Ty, Dimension, VecPipeT>& b) {
        bool state = true;
        for (int32_t i = 0; i < Dimension; ++i)
            if (abs(a[i] - b[i]) > std::numeric_limits<Ty>::epsilon()) return false;
        return true;
    }
    // Two functions to do Vector calculation.
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    const Ty dot(const basic_vector<Ty, Dimension, VecPipeT>& a, const basic_vector<Ty, Dimension, VecPipeT>& b) {
        auto s = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) s += (a[i] * b[i]);
        return s;
    }
    // length here is use to get the length(modulus) of a Vector.
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    const Ty length(const basic_vector<Ty, Dimension, VecPipeT>& a) {
        auto s = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) s += (a[i] * a[i]);
        return sqrt(s);
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    basic_vector<Ty, Dimension, VecPipeT> norm(const basic_vector<Ty, Dimension, VecPipeT>& a) {
        auto esqd = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) esqd += (a[i] * a[i]);
        basic_vector<Ty, Dimension, VecPipeT> k(a); k *= rsqrt(esqd);
        return k;
    }
    // cross product is only avalible for 3 dimensional Vectors.
    template <typename Ty, class VecPipeT>
    basic_vector<Ty, 3, VecPipeT> cross(const basic_vector<Ty, 3, VecPipeT>& a, const basic_vector<Ty, 3, VecPipeT>& b) {
        return {
            a[1] * b[2] - b[1] * a[2],
            a[2] * b[0] - b[2] * a[0],
            a[0] * b[1] - b[0] * a[1]
        };
    }
}