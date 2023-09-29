#pragma once
#include <xutility> // for min copy and move.
namespace force::math {
    // Vector pipe is used to do conversion between Vectors.
    // This class has now extra pay off because it's very light.
    template <typename Ty, std::size_t MaxSize>
    class basic_pipe {
    public:
        Ty          vdata[MaxSize];
        std::size_t vsize;

        using value_type = Ty;
        static constexpr std::size_t max_size = MaxSize;

        constexpr basic_pipe(const value_type* d, size_t s) {
            vsize = s;
            std::copy(d, d + vsize, vdata);
        }
        basic_pipe(const basic_pipe& right) {
            std::copy(right.vdata, right.vdata + std::min(vsize, right.vsize), vdata);
            vsize = right.vsize;
        }
        basic_pipe(basic_pipe&& right) noexcept {
            std::move(right.vdata, right.vdata + std::min(vsize, right.vsize), vdata);
            vsize = right.vsize;
        }
        // Append operator can use to cat two basic_pipe.
        // Vectors don't have mod operations so this operator is fine. 
        basic_pipe& operator|=(const value_type& v) {
            if (vsize > max_size - 1) throw "Too large to combine a Vector.";
            vdata[vsize++] = v;
            return *this;
        }
        basic_pipe& operator|=(const basic_pipe& v) {
            if (vsize + v.vsize > max_size) throw "Too large to combine a Vector.";
            std::copy(v.vdata, v.vdata + v.vsize, vdata + vsize);
            vsize += v.vsize;
            return *this;
        }

        ~basic_pipe() = default;
    };

    // Useful functions to do Vector combined and Vector clip.
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr basic_pipe<Ty, MaxSize> operator|(const basic_pipe<Ty, MaxSize>& a, const Ty& b) {
        basic_pipe<Ty, MaxSize> v(a); v |= b; return v;
    }
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr basic_pipe<Ty, MaxSize> operator|(const basic_pipe<Ty, MaxSize>& a,
        const basic_pipe<Ty, MaxSize>& b) {
        basic_pipe<Ty, MaxSize>v(a); v |= b; return v;
    }
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr basic_pipe<Ty, MaxSize> operator|(const Ty& a, const basic_pipe<Ty, MaxSize>& b) {
        basic_pipe<Ty, MaxSize>v(&a, 1); v |= b; return v;
    }
}