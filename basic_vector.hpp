#pragma once
#include "prmthfn.hpp"
#include <algorithm> // for copy fill and min
namespace force {

    // Vector view is used to do conversion between vectors.
    // This class has now extra pay off because it's very light.
    template <typename Ty, std::size_t MaxSize>
    class basic_vector_view {
        Ty          m_data[MaxSize];
        std::size_t m_size;
    public:
        using value_type = Ty;
        static constexpr std::size_t max_size = MaxSize;

        constexpr basic_vector_view(const value_type* d, size_t s) {
            m_size = s;
            std::copy(d, d + m_size, m_data);
        }
        basic_vector_view(const basic_vector_view& right) {
            std::copy(right.m_data, right.m_data + std::min(m_size, right.m_size), m_data);
            m_size = right.m_size;
        }
        basic_vector_view(basic_vector_view&& right) noexcept {
            std::move(right.m_data, right.m_data + std::min(m_size, right.m_size), m_data);
            m_size = right.m_size;
        }
        // Append operator can use to cat two basic_vector_view.
        // Vectors don't have division so this operator is fine.
        basic_vector_view& operator/=(const value_type& v) {
            if (m_size > max_size - 1) throw "Too large to combine a vector.";
            m_data[m_size++] = v;
            return *this;
        }
        basic_vector_view& operator/=(const basic_vector_view& v) {
            if (m_size + v.m_size > max_size) throw "Too large to combine a vector.";
            std::copy(v.data(), v.data() + v.m_size, m_data + m_size);
            m_size += v.m_size;
            return *this;
        }

        const size_t      size() const { return m_size; }
        const value_type* data() const { return m_data; }

        ~basic_vector_view() = default;
    };

    // Useful functions to do vector combined and vector clip.
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr basic_vector_view<Ty, MaxSize> operator/(const basic_vector_view<Ty, MaxSize>& a, const Ty& b) {
        basic_vector_view<Ty, MaxSize> v(a); v /= b; return v;
    }
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr basic_vector_view<Ty, MaxSize> operator/(const basic_vector_view<Ty, MaxSize>& a,
                                                                     const basic_vector_view<Ty, MaxSize>& b) {
        basic_vector_view<Ty, MaxSize>v(a); v /= b; return v;
    }
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr basic_vector_view<Ty, MaxSize> operator/(const Ty& a, const basic_vector_view<Ty, MaxSize>& b) {
        basic_vector_view<Ty, MaxSize>v(&a, 1); v /= b; return v;
    }

    // basic_vector class is the template for all vectors.
    // Ty is the element type and Dimension is the array size.
    // VecViewT is the middle viewer vector type.
    // If vectors want to do conversions, they have to make sure their view_type has the same type and same max size.
    template <typename Ty, std::size_t Dimension, class VecViewT>
    class basic_vector {
        // Array to store the data.
        Ty m_data[Dimension];
    public:
        using value_type = Ty;
        using view_type  = VecViewT;
        static constexpr std::size_t dimension = Dimension;

        // Initializer_list can copy elements to data.
        // It's safe if you don't pass in any parameter or you list's len
        // is greater than vector's actual dimension.
        constexpr basic_vector(std::initializer_list<value_type> lst) {
            std::fill(m_data, m_data + dimension, static_cast<value_type>(0));
            std::copy(lst.begin(), lst.end(), m_data);
        }
        // View constructor can use to do conversions.
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
        // Dereference operator returns the view required.
        // Vectors can do conversions with view_type.
        // Only vectors has the same view_type can do conversions.
        view_type         operator*()                     { return view_type(m_data, dimension); }
        // Shuffle operator can give back a new vector using this vector to construct.
        // To use this just simply give ArgDim parameter(this is neccesarry) and give in initalizer_list
        // Which has the exact same size as ArgDim.
        template <std::size_t ArgDim, typename RetVectorT = basic_vector<Ty, ArgDim, VecViewT>>
        RetVectorT        clip(std::initializer_list<std::size_t> ids) {
            RetVectorT rvec{};
            if (ids.size() != ArgDim)
                throw "Error: indexes is neq to parameters!";
            for (std::size_t i = 0; i < ArgDim; ++i)
                rvec[i] = m_data[*(ids.begin() + i)];
            return rvec;
        }
        // Since there is no dynamic allocation
        // The deconstructor needs to do nothing.
        ~basic_vector() = default;
    };

    template <typename Ty, std::size_t Dimension, class VecViewT, typename Ret = basic_vector<Ty, Dimension, VecViewT>>
    [[nodiscard]] constexpr Ret operator+(const Ret& a, const Ret& b) {
        Ret tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecViewT, typename Ret = basic_vector<Ty, Dimension, VecViewT>>
    [[nodiscard]] constexpr Ret operator-(const Ret& a, const Ret& b) {
        Ret tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecViewT, typename Ret = basic_vector<Ty, Dimension, VecViewT>>
    [[nodiscard]] constexpr Ret operator*(const Ret& a, const Ret& b) {
        Ret tmp(a);
        tmp *= b;
        return tmp;
    }
    template <typename Ty, std::size_t Dimension, class VecViewT, typename Ret = basic_vector<Ty, Dimension, VecViewT>>
    [[nodiscard]] constexpr Ret operator+(const Ret& a) {
        return a;
    }
    template <typename Ty, std::size_t Dimension, class VecViewT, typename Ret = basic_vector<Ty, Dimension, VecViewT>>
    [[nodiscard]] constexpr Ret operator-(const Ret& a) {
        Ret v{ static_cast<Ty>(0) }; v -= a; return v;
    }

    template <typename Ty, std::size_t Dimension, class VecViewT, typename Ret = basic_vector<Ty, Dimension, VecViewT>>
    [[nodiscard]] constexpr bool operator==(const Ret& a, const Ret& b) {
        bool state = true;
        for (int i = 0; i < Dimension; ++i)
            if (std::abs(a[i] - b[i]) > std::numeric_limits<Ty>::epsilon()) return false;
        return true;
    }

    // Two functions to do vector calculation.
    template <typename Ty, std::size_t Dimension, class VecViewT>
    const Ty dot(const basic_vector<Ty, Dimension, VecViewT>& a, const basic_vector<Ty, Dimension, VecViewT>& b) {
        auto s = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) s += (a[i] * b[i]);
        return s;
    }
    template <typename Ty, std::size_t Dimension, class VecViewT>
    const Ty modulus(const basic_vector<Ty, Dimension, VecViewT>& a) {
        auto s = static_cast<Ty>(0);
        #pragma omp simd
        for (std::size_t i = 0; i < Dimension; ++i) s += (a[i] * a[i]);
        return ::force::sqrt(s);
    }
}