#pragma once
#include "prmthfn.hpp"
#include "vector_pipe.hpp"
namespace force {
    // basic_vector class is the template for all vectors.
    // Ty is the element type and Dimension is the array size.
    // VecPipeT is the middle viewer vector type.
    // If vectors want to do conversions, they have to make sure their view_type has the same type and same max size.
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    class basic_vector {
        // Array to store the data.
        Ty m_data[Dimension];
    public:
        using value_type = Ty;
        using view_type  = VecPipeT;

        static constexpr std::size_t dimension = Dimension;

        constexpr basic_vector() {
            std::fill(m_data, m_data + dimension, static_cast<value_type>(0));
        }
        // Initializer_list can copy elements to data.
        // It's safe if you don't pass in any parameter or you list's len
        // is greater than vector's actual dimension.
        constexpr basic_vector(std::initializer_list<value_type> lst) {
            std::fill(m_data, m_data + dimension, static_cast<value_type>(0));
            std::copy(lst.begin(), lst.end(), m_data);
        }
        // pipe constructor can use to do conversions.
        constexpr basic_vector(const view_type& v) {
            std::fill(m_data, m_data + dimension, static_cast<value_type>(0));
            std::copy(v.data(), v.data() + std::min(dimension, v.size()), m_data);
        }
        basic_vector(const basic_vector& right) noexcept {
            std::copy(right.m_data, right.m_data + dimension, m_data);
        }
        basic_vector(basic_vector&& right)      noexcept {
            std::move(right.m_data, right.m_data + dimension, m_data);
        }
        // operator= can use to assign value without using constructors.
        basic_vector& operator=(const basic_vector& right) {
            std::copy(right.m_data, right.m_data + dimension, m_data);
            return *this;
        }
        basic_vector& operator=(const view_type& v) {
            std::copy(v.data(), v.data() + std::min(dimension, v.size()), m_data);
            return *this;
        }
        // All commands below can turn on simd optimization by default.
        // You don't have to use simd macros to turn them on any more - they are automaticly.
        basic_vector& operator+=(const basic_vector& right) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) m_data[i] += right.m_data[i];
            return *this;
        }
        basic_vector& operator-=(const basic_vector& right) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) m_data[i] -= right.m_data[i];
            return *this;
        }
        basic_vector& operator*=(const value_type& k) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) m_data[i] *= k;
            return *this;
        }
        basic_vector& operator/=(const value_type& k) {
            #pragma omp simd
            for (std::size_t i = 0; i < dimension; ++i) m_data[i] /= k;
            return *this;
        }
        const value_type& operator[](std::size_t i) const { return  m_data[i]; }
        value_type&       operator[](std::size_t i)       { return  m_data[i]; }
        // data operator returns the data
        // It's useful when you are passing arrays to some programs.
        const value_type* data() const                    { return  m_data; }
        // Dereference operator returns the pipe required.
        // Vectors can do conversions with view_type.
        // Only vectors has the same view_type can do conversions.
        view_type         operator*() const               { return view_type(m_data, dimension); }
        // Shuffle operator can give back a new vector using this vector to construct.
        // To use this just simply give ArgDim parameter(this is neccesarry) and give in initalizer_list
        // Which has the exact same size as ArgDim.
        template <typename ... Indecies, std::size_t ArgDim = sizeof...(Indecies)>
        basic_vector<Ty, ArgDim, VecPipeT>        operator()(Indecies ... idx) const {
            basic_vector<Ty, ArgDim, VecPipeT>  rvec{};
            std::initializer_list<std::size_t>  ids = { (std::size_t)idx... };
            for (std::size_t i = 0; i < ArgDim; ++i) rvec[i] = m_data[*(ids.begin() + i)];
            return rvec;
        }

        // Since there is no dynamic allocation
        // The deconstructor needs to do nothing.
        ~basic_vector() = default;
    };

    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] constexpr basic_vector<Ty, Dimension, VecPipeT> operator+(const basic_vector<Ty, Dimension, VecPipeT>& a,
                                                                            const basic_vector<Ty, Dimension, VecPipeT>& b) {
        basic_vector<Ty, Dimension, VecPipeT> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] constexpr basic_vector<Ty, Dimension, VecPipeT> operator-(const basic_vector<Ty, Dimension, VecPipeT>& a,
                                                                            const basic_vector<Ty, Dimension, VecPipeT>& b) {
        basic_vector<Ty, Dimension, VecPipeT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] constexpr basic_vector<Ty, Dimension, VecPipeT> operator*(const basic_vector<Ty, Dimension, VecPipeT>& a,
                                                                            const basic_vector<Ty, Dimension, VecPipeT>& b) {
        basic_vector<Ty, Dimension, VecPipeT> tmp(a);
        tmp *= b;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] constexpr basic_vector<Ty, Dimension, VecPipeT> operator+(const basic_vector<Ty, Dimension, VecPipeT>& a) {
        return a;
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] constexpr basic_vector<Ty, Dimension, VecPipeT> operator-(const basic_vector<Ty, Dimension, VecPipeT>& a) {
        basic_vector<Ty, Dimension, VecPipeT> v{ static_cast<Ty>(0) }; v -= a; return v;
    }
    ///////////////////////////////////
    // Algorithms for basic_vectors. //
    //////////////////////////////////
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    [[nodiscard]] constexpr bool operator==(const basic_vector<Ty, Dimension, VecPipeT>& a,
                                            const basic_vector<Ty, Dimension, VecPipeT>& b) {
        bool state = true;
        for (int i = 0; i < Dimension; ++i)
            if (std::abs(a[i] - b[i]) > std::numeric_limits<Ty>::epsilon()) return false;
        return true;
    }
    // Two functions to do vector calculation.
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    const Ty dot(const basic_vector<Ty, Dimension, VecPipeT>& a, const basic_vector<Ty, Dimension, VecPipeT>& b) {
        auto s = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) s += (a[i] * b[i]);
        return s;
    }
    // Length here is use to get the length(modulus) of a vector.
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    const Ty length(const basic_vector<Ty, Dimension, VecPipeT>& a) {
        auto s = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) s += (a[i] * a[i]);
        return ::force::sqrt(s);
    }
    template <typename Ty, std::size_t Dimension, class VecPipeT>
    basic_vector<Ty, Dimension, VecPipeT> normalize(const basic_vector<Ty, Dimension, VecPipeT>& a) {
        auto esqd = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) esqd += (a[i] * a[i]);
        basic_vector<Ty, Dimension, VecPipeT> k(a); k *= ::force::rsqrt(esqd);
        return k;
    }
    // Cross product is only avalible for 3 dimensional vectors.
    template <typename Ty, class VecPipeT>
    basic_vector<Ty, 3, VecPipeT> cross(const basic_vector<Ty, 3, VecPipeT>& a, const basic_vector<Ty, 3, VecPipeT>& b) {
        return {
            a[1] * b[2] - b[1] * a[2],
            a[2] * b[0] - b[2] * a[0],
            a[0] * b[1] - b[0] * a[1]
        };
    }
}