#ifndef _FORCE_CORE_HPP_
#define _FORCE_CORE_HPP_

namespace force {

    // Using CRTP way
    template <
        typename _Subclass, typename _ValueType,
        unsigned int dimension>
    class basic_vector {
    protected:
        _ValueType _M_vec[dimension];
    public:
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
}
#endif //! _FORCE_CORE_HPP_