#pragma once
#include "basic_vector.hpp"
#include <iostream>
namespace force {

    template <typename Ty,
              std::size_t Col, std::size_t Row, 
              class VecPipeT>
    class basic_matrix {
        // Vector class stores actual data.
        basic_vector<Ty, Row, VecPipeT> m_data[Col];
#define SBEG_PTR    (&(m_data[0][0]))
#define SEND_PTR    (&(m_data[0][0]) + Col * Row)
#define RBEG_PTR    (&(right.m_data[0][0]))
#define REND_PTR    (&(right.m_data[0][0]) + Col * Row)
    public:
        using value_type = Ty;
        using vec_type   = basic_vector<Ty, Row, VecPipeT>;
        using vpipe_type = VecPipeT;

        static constexpr std::size_t col = Col;
        static constexpr std::size_t row = Row;
        // Value constructor.
        // All lst elements should be Ty values. Initalizer_list has no size bound.
        // So make sure your size is always in the acceptable range.
        constexpr basic_matrix(std::initializer_list<Ty> lst) {
            std::fill(SBEG_PTR, SEND_PTR, static_cast<value_type>(0));
            std::copy(lst.begin(), lst.end(), SBEG_PTR);
        }
        // ArgPipes are all basic_vector<Ty, Row, VecPipeT>
        // Make sure all parameters are this type. I don't know
        // what will happen if you pass in other types.
        // And make sure your parameter count is less or equal than mat's column size.
        template <typename ... ArgVecs>
        constexpr basic_matrix(const ArgVecs& ... avs) {
            // List that stores all vectors.
            std::initializer_list<basic_vector<Ty, Row, VecPipeT>> init_lst = { (basic_vector<Ty, Row, VecPipeT>)avs... };
            std::fill(SBEG_PTR, SEND_PTR, static_cast<value_type>(0));
            std::copy(init_lst.begin(), init_lst.end(), m_data);
        }
        basic_matrix(const basic_matrix& right) {
            std::fill(SBEG_PTR, SEND_PTR, static_cast<value_type>(0));
            std::copy(RBEG_PTR, REND_PTR, SBEG_PTR);
        }
        basic_matrix(basic_matrix&& right) {
            std::fill(SBEG_PTR, SEND_PTR, static_cast<value_type>(0));
            std::move(RBEG_PTR, REND_PTR, SBEG_PTR);
        }

        basic_matrix& operator=(const basic_matrix& right) {
            std::copy(RBEG_PTR, REND_PTR, SBEG_PTR);
            return *this;
        }
        basic_matrix& operator=(basic_matrix&& right) {
            std::move(RBEG_PTR, REND_PTR, SBEG_PTR);
            return *this;
        }
        basic_matrix& operator+=(const basic_matrix& right) {
            #pragma omp simd
            for (std::size_t i = 0; i < col; ++i) m_data[i] += right.m_data[i];
            return *this;
        }
        basic_matrix& operator-=(const basic_matrix& right) {
            #pragma omp simd
            for (std::size_t i = 0; i < col; ++i) m_data[i] -= right.m_data[i];
            return *this;
        }
        basic_matrix& operator*=(const value_type& k) {
            #pragma omp simd
            for (std::size_t i = 0; i < col; ++i) m_data[i] *= k;
            return *this;
        }
        basic_matrix& operator/=(const value_type& k) {
            #pragma omp simd
            for (std::size_t i = 0; i < col; ++i) m_data[i] /= k;
            return *this;
        }

        const vec_type& operator[](std::size_t i) const  { return m_data[i]; }
        vec_type&       operator[](std::size_t i)        { return m_data[i]; }
        const value_type* data()                         { return &m_data[0][0]; }

        ~basic_matrix() = default;

    };
// Undef all helper macros.
#undef SBEG_PTR
#undef SEND_PTR
#undef RBEG_PTR
#undef REND_PTR

    template <class MatrixType>
    MatrixType identity() {
        MatrixType target{};
        for (std::size_t i = 0; i < MatrixType::col; ++i)
            for (std::size_t j = 0; j < MatrixType::row; ++j)
                target[i][j] = (i == j) ? static_cast<MatrixType::value_type>(1) : static_cast<MatrixType::value_type>(0);
        return target;
    }
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] basic_matrix<Ty, Col, Row, VecPipeT> operator+(const basic_matrix<Ty, Col, Row, VecPipeT>& a,
                                                                 const basic_matrix<Ty, Col, Row, VecPipeT>& b) {
        basic_matrix<Ty, Col, Row, VecPipeT> M = a; M += b; return M;
    }
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] basic_matrix<Ty, Col, Row, VecPipeT> operator-(const basic_matrix<Ty, Col, Row, VecPipeT>& a,
                                                                 const basic_matrix<Ty, Col, Row, VecPipeT>& b) {
        basic_matrix<Ty, Col, Row, VecPipeT> M = a; M -= b; return M;
    }
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] basic_matrix<Ty, Col, Row, VecPipeT> operator*(const basic_matrix<Ty, Col, Row, VecPipeT>& m, const Ty& v) {
        basic_matrix<Ty, Col, Row, VecPipeT> M = m; M *= v; return M;
    }
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] basic_matrix<Ty, Col, Row, VecPipeT> operator/(const basic_matrix<Ty, Col, Row, VecPipeT>& m, const Ty& v) {
        basic_matrix<Ty, Col, Row, VecPipeT> M = m; M /= v; return M;
    }
     // Notice, if you want to do vector multiplication
     // Use 1xd matrix or dx1 matrix to do that. If I do additional operation to do that.
    template <typename Ty,
        std::size_t Col, std::size_t Row, std::size_t OutDim,
        class VecPipeT>
    [[nodiscard]] basic_matrix<Ty, Col, OutDim, VecPipeT> operator*(const basic_matrix<Ty, Col, Row, VecPipeT>& a,
                                                                    const basic_matrix<Ty, Row, OutDim, VecPipeT>& b) {
        basic_matrix<Ty, Col, OutDim, VecPipeT> target{};
        #pragma omp simd
        for (std::size_t i = 0; i < Col; ++i) {
            #pragma omp simd
            for (std::size_t j = 0; j < OutDim; ++j) {
                auto s = static_cast<Ty>(0);
                #pragma omp simd
                for (std::size_t k = 0; k < Row; ++k)
                    s += a[i][k] * b[k][j];
                target[i][j] = s;
            }
        }
        return target;
    }
    // Verctor right multiplication.
    // This uses row vector by default. so makesure your vector's row size is equal to matrix's row size.
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] basic_vector<Ty, Row, VecPipeT> operator*(const basic_matrix<Ty, Col, Row, VecPipeT>& m,
                                                            const basic_vector<Ty, Row, VecPipeT>& v) {
        basic_vector<Ty, Row, VecPipeT> target{};
        for (std::size_t i = 0; i < Col; ++i) {
            auto s = static_cast<Ty>(0);
            for (std::size_t j = 0; j < Row; ++j)
                s += m[i][j] * v[j];
            target[i] = s;
        }
        return target;
    }
    // Vector left multiplication.
    // This uses column vector by default. so makesure your vector's column size is equal to matrix's column size.
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] basic_vector<Ty, Col, VecPipeT> operator*(const basic_vector<Ty, Col, VecPipeT>& v,
                                                            const basic_matrix<Ty, Col, Row, VecPipeT>& m) {
        basic_vector<Ty, Col, VecPipeT> target{};
        for (std::size_t i = 0; i < Row; ++i) {
            auto s = static_cast<Ty>(0);
            for (std::size_t j = 0; j < Col; ++j)
                s += m[j][i] * v[j];
            target[i] = s;
        }
        return target;
    }
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] basic_matrix<Ty, Row, Col, VecPipeT> transpose(const basic_matrix<Ty, Col, Row, VecPipeT>& m) {
        basic_matrix<Ty, Row, Col, VecPipeT> target{};
        for (std::size_t i = 0; i < Col; ++i)
            for (std::size_t j = 0; j < Row; ++j)
                target[j][i] = m[i][j];
        return target;
    }
} //!namespace force