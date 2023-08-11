#pragma once
#include "BasicVector.hpp"
namespace Fma {

    template <typename Ty,
              std::size_t Col, std::size_t Row, 
              class VecPipeT>
    class BasicMatrix {
        // Vector class stores actual Data.
        BasicVector<Ty, Row, VecPipeT> mData[Col];
#define SBEG_PTR    (&(mData[0][0]))
#define SEND_PTR    (&(mData[0][0]) + Col * Row)
#define RBEG_PTR    (&(right.mData[0][0]))
#define REND_PTR    (&(right.mData[0][0]) + Col * Row)
    public:
        using value_type = Ty;
        using Vec_type   = BasicVector<Ty, Row, VecPipeT>;
        using vpipe_type = VecPipeT;

        static constexpr std::size_t col = Col;
        static constexpr std::size_t row = Row;
        // Value constructor.
        // All lst elements should be Ty values. Initalizer_list has no size bound.
        // So make sure your size is always in the acceptable range.
        constexpr BasicMatrix(std::initializer_list<Ty> lst) {
            std::fill(SBEG_PTR, SEND_PTR, static_cast<value_type>(0));
            std::copy(lst.begin(), lst.end(), SBEG_PTR);
        }
        // ArgPipes are all BasicVector<Ty, Row, VecPipeT>
        // Make sure all parameters are this type. I don't know
        // what will happen if you pass in other types.
        // And make sure your parameter count is less or equal than Mat's column size.
        template <typename ... ArgVecs>
        constexpr BasicMatrix(const ArgVecs& ... avs) {
            // List that stores all Vectors.
            std::initializer_list<BasicVector<Ty, Row, VecPipeT>> init_lst = { (BasicVector<Ty, Row, VecPipeT>)avs... };
            std::fill(SBEG_PTR, SEND_PTR, static_cast<value_type>(0));
            std::copy(init_lst.begin(), init_lst.end(), mData);
        }
        BasicMatrix(const BasicMatrix& right) {
            std::fill(SBEG_PTR, SEND_PTR, static_cast<value_type>(0));
            std::copy(RBEG_PTR, REND_PTR, SBEG_PTR);
        }
        BasicMatrix(BasicMatrix&& right) {
            std::fill(SBEG_PTR, SEND_PTR, static_cast<value_type>(0));
            std::move(RBEG_PTR, REND_PTR, SBEG_PTR);
        }

        BasicMatrix& operator=(const BasicMatrix& right) {
            std::copy(RBEG_PTR, REND_PTR, SBEG_PTR);
            return *this;
        }
        BasicMatrix& operator=(BasicMatrix&& right) {
            std::move(RBEG_PTR, REND_PTR, SBEG_PTR);
            return *this;
        }
        BasicMatrix& operator+=(const BasicMatrix& right) {
            #pragma omp simd
            for (std::size_t i = 0; i < col; ++i) mData[i] += right.mData[i];
            return *this;
        }
        BasicMatrix& operator-=(const BasicMatrix& right) {
            #pragma omp simd
            for (std::size_t i = 0; i < col; ++i) mData[i] -= right.mData[i];
            return *this;
        }
        BasicMatrix& operator*=(const value_type& k) {
            #pragma omp simd
            for (std::size_t i = 0; i < col; ++i) mData[i] *= k;
            return *this;
        }
        BasicMatrix& operator/=(const value_type& k) {
            #pragma omp simd
            for (std::size_t i = 0; i < col; ++i) mData[i] /= k;
            return *this;
        }
        
        Vec_type&       operator[](size_t i)       { return mData[i]; }
        const Vec_type& operator[](size_t i) const { return mData[i]; }
        const value_type* Data()                         { return &mData[0][0]; }

        ~BasicMatrix() = default;

    };
// Undef all helper macros.
#undef SBEG_PTR
#undef SEND_PTR
#undef RBEG_PTR
#undef REND_PTR

    template <class MatrixType>
    MatrixType IdMat() {
        MatrixType target{};
        for (std::size_t i = 0; i < MatrixType::col; ++i)
            for (std::size_t j = 0; j < MatrixType::row; ++j)
                target[i][j] = (i == j) ? static_cast<MatrixType::value_type>(1) : static_cast<MatrixType::value_type>(0);
        return target;
    }
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] BasicMatrix<Ty, Col, Row, VecPipeT> operator+(const BasicMatrix<Ty, Col, Row, VecPipeT>& a,
                                                                 const BasicMatrix<Ty, Col, Row, VecPipeT>& b) {
        BasicMatrix<Ty, Col, Row, VecPipeT> M = a; M += b; return M;
    }
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] BasicMatrix<Ty, Col, Row, VecPipeT> operator-(const BasicMatrix<Ty, Col, Row, VecPipeT>& a,
                                                                 const BasicMatrix<Ty, Col, Row, VecPipeT>& b) {
        BasicMatrix<Ty, Col, Row, VecPipeT> M = a; M -= b; return M;
    }
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] BasicMatrix<Ty, Col, Row, VecPipeT> operator*(const BasicMatrix<Ty, Col, Row, VecPipeT>& m, const Ty& v) {
        BasicMatrix<Ty, Col, Row, VecPipeT> M = m; M *= v; return M;
    }
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] BasicMatrix<Ty, Col, Row, VecPipeT> operator/(const BasicMatrix<Ty, Col, Row, VecPipeT>& m, const Ty& v) {
        BasicMatrix<Ty, Col, Row, VecPipeT> M = m; M /= v; return M;
    }
     // Notice, if you want to do Vector multiplication
     // Use 1xd Matrix or dx1 Matrix to do that. If I do additional operation to do that.
    template <typename Ty,
        std::size_t Col, std::size_t Row, std::size_t OutDim,
        class VecPipeT>
    [[nodiscard]] BasicMatrix<Ty, Col, OutDim, VecPipeT> operator*(const BasicMatrix<Ty, Col, Row, VecPipeT>& a,
                                                                    const BasicMatrix<Ty, Row, OutDim, VecPipeT>& b) {
        BasicMatrix<Ty, Col, OutDim, VecPipeT> target{};
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
    // This uses row Vector by default. so makesure your Vector's row size is equal to Matrix's row size.
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] BasicVector<Ty, Row, VecPipeT> operator*(const BasicMatrix<Ty, Col, Row, VecPipeT>& m,
                                                            const BasicVector<Ty, Row, VecPipeT>& v) {
        BasicVector<Ty, Row, VecPipeT> target{};
        for (std::size_t i = 0; i < Col; ++i) {
            auto s = static_cast<Ty>(0);
            for (std::size_t j = 0; j < Row; ++j)
                s += m[i][j] * v[j];
            target[i] = s;
        }
        return target;
    }
    // Vector left multiplication.
    // This uses column Vector by default. so makesure your Vector's column size is equal to Matrix's column size.
    template <typename Ty,
        std::size_t Col, std::size_t Row,
        class VecPipeT>
    [[nodiscard]] BasicVector<Ty, Col, VecPipeT> operator*(const BasicVector<Ty, Col, VecPipeT>& v,
                                                            const BasicMatrix<Ty, Col, Row, VecPipeT>& m) {
        BasicVector<Ty, Col, VecPipeT> target{};
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
    [[nodiscard]] BasicMatrix<Ty, Row, Col, VecPipeT> Transpose(const BasicMatrix<Ty, Col, Row, VecPipeT>& m) {
        BasicMatrix<Ty, Row, Col, VecPipeT> target{};
        for (std::size_t i = 0; i < Col; ++i)
            for (std::size_t j = 0; j < Row; ++j)
                target[j][i] = m[i][j];
        return target;
    }
} //!namespace Fma