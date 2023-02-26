#ifndef _FORCE_CORE_HPP_
#define _FORCE_CORE_HPP_

namespace force {
    template <
        typename _Subclass, typename _ValueType,
        unsigned int dimension>
    class basic_vector {
    protected:
        _ValueType _M_vec[dimension];
    public:
        static constexpr unsigned int vec_dimension = dimension;

        _Subclass             operator+(const _Subclass& v) noexcept {
            return static_cast<_Subclass*>(this)->operator+(v);
        }
        _Subclass             operator+(_ValueType s)  noexcept {
            return static_cast<_Subclass*>(this)->operator+(s);
        }
        _Subclass             operator-(const _Subclass& v) noexcept {
            return static_cast<_Subclass*>(this)->operator-(v);
        }
        _Subclass             operator-(_ValueType s)  noexcept {
            return static_cast<_Subclass*>(this)->operator-(s);
        }
        _Subclass             operator*(_ValueType s)  noexcept {
            return static_cast<_Subclass*>(this)->operator*(s);
        }
        _Subclass             operator/(_ValueType s)  noexcept {
            return static_cast<_Subclass*>(this)->operator/(s);
        }
        _Subclass&            operator+=(const _Subclass& _right)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) + _right;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass&            operator-=(const _Subclass& _right)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) - _right;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass&            operator+=(_ValueType s)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) + s;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass&            operator-=(_ValueType s)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) - s;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass&            operator*=(_ValueType s)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) * s;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass&            operator/=(_ValueType s)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) / s;
            return *static_cast<_Subclass*>(this);
        }
        _ValueType&           at(unsigned int index)  noexcept {
            return _M_vec[index];
        }
        const _ValueType&     at(unsigned int index) const noexcept {
            return _M_vec[index];
        }
        _ValueType&           operator[](unsigned int index)  noexcept {
            return _M_vec[index];
        }
        const _ValueType&     operator[](unsigned int index) const noexcept {
            return _M_vec[index];
        }
        const _ValueType*     data() const  noexcept {
            return _M_vec;
        }
    };

    template <
        typename _Subclass, typename _ValueType, 
        unsigned int row, unsigned int column>
    class basic_matrix {
    protected:
        _ValueType _M_mat[row * column];
    public:
        static constexpr unsigned int mat_row = row;
        static constexpr unsigned int mat_col = column;

        _Subclass             operator+(const _Subclass& v) noexcept {
            return static_cast<_Subclass*>(this)->operator+(v);
        }
        _Subclass             operator+(_ValueType s)  noexcept {
            return static_cast<_Subclass*>(this)->operator+(s);
        }
        _Subclass             operator-(const _Subclass& v) noexcept {
            return static_cast<_Subclass*>(this)->operator-(v);
        }
        _Subclass             operator-(_ValueType s)  noexcept {
            return static_cast<_Subclass*>(this)->operator-(s);
        }
        _Subclass             operator*(_ValueType s)  noexcept {
            return static_cast<_Subclass*>(this)->operator*(s);
        }
        _Subclass             operator/(_ValueType s)  noexcept {
            return static_cast<_Subclass*>(this)->operator/(s);
        }
        _Subclass             operator*(const _Subclass& v) noexcept {
            return static_cast<_Subclass*>(this)->operator*(v);
        }
        _Subclass& operator+=(const _Subclass& _right)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) + _right;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass& operator+=(_ValueType s)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) + s;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass& operator-=(const _Subclass& _right)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) - _right;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass& operator-=(_ValueType s)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) - s;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass& operator*=(_ValueType s)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) * s;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass& operator/=(_ValueType s)  noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) / s;
            return *static_cast<_Subclass*>(this);
        }
        _Subclass& operator*=(const _Subclass& v) noexcept {
            *static_cast<_Subclass*>(this) = *static_cast<_Subclass*>(this) * v;
            return *static_cast<_Subclass*>(this);
        }
        _ValueType&            at(unsigned int r, unsigned int c) {
            return _M_mat[r * column + c];
        }
        const _ValueType&      at(unsigned int r, unsigned int c) const {
            return _M_mat[r * column + c];
        }
    };

    template <
        typename _Subclass, typename _ValueType,
        unsigned int dimension>
    inline _ValueType xof(basic_vector<_Subclass, _ValueType, dimension>& vec) {
        return vec[0];
    }
    template <
        typename _Subclass, typename _ValueType,
        unsigned int dimension>
    inline _ValueType yof(basic_vector<_Subclass, _ValueType, dimension>& vec) {
        return vec[1];
    }
    template <
        typename _Subclass, typename _ValueType,
        unsigned int dimension>
    inline _ValueType zof(basic_vector<_Subclass, _ValueType, dimension>& vec) {
        return vec[2];
    }
    template <
        typename _Subclass, typename _ValueType,
        unsigned int dimension>
    inline _ValueType wof(basic_vector<_Subclass, _ValueType, dimension>& vec) {
        return vec[3];
    }


    namespace f32 {
        constexpr float unit_vec[4] = { 1.f, 1.f, 1.f, 1.f };
        constexpr float zero_vec[4] = { 1.f, 1.f, 1.f, 1.f };
    }

    namespace f64 {
        constexpr double unit_vec[4] = { 1.0, 1.0, 1.0, 1.0 };
        constexpr double zero_vec[4] = { 0.0, 0.0, 0.0, 0.0 };
    }

}
#endif //! _FORCE_CORE_HPP_