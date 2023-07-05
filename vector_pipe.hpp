#pragma once
#include <algorithm> // for min copy and move.
namespace force {
    // Vector pipe is used to do conversion between vectors.
    // This class has now extra pay off because it's very light.
    template <typename Ty, std::size_t MaxSize>
    class basic_vector_pipe {
        Ty          m_data[MaxSize];
        std::size_t m_size;
    public:
        using value_type = Ty;
        static constexpr std::size_t max_size = MaxSize;

        constexpr basic_vector_pipe(const value_type* d, size_t s) {
            m_size = s;
            std::copy(d, d + m_size, m_data);
        }
        basic_vector_pipe(const basic_vector_pipe& right) {
            std::copy(right.m_data, right.m_data + std::min(m_size, right.m_size), m_data);
            m_size = right.m_size;
        }
        basic_vector_pipe(basic_vector_pipe&& right) noexcept {
            std::move(right.m_data, right.m_data + std::min(m_size, right.m_size), m_data);
            m_size = right.m_size;
        }
        // Append operator can use to cat two basic_vector_pipe.
        // Vectors don't have mod operations so this operator is fine. 
        basic_vector_pipe& operator|(const value_type& v) {
            if (m_size > max_size - 1) throw "Too large to combine a vector.";
            m_data[m_size++] = v;
            return *this;
        }
        basic_vector_pipe& operator|(const basic_vector_pipe& v) {
            if (m_size + v.m_size > max_size) throw "Too large to combine a vector.";
            std::copy(v.data(), v.data() + v.m_size, m_data + m_size);
            m_size += v.m_size;
            return *this;
        }

        const size_t      size() const { return m_size; }
        const value_type* data() const { return m_data; }

        ~basic_vector_pipe() = default;
    };

    // Useful functions to do vector combined and vector clip.
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr basic_vector_pipe<Ty, MaxSize> operator|(const basic_vector_pipe<Ty, MaxSize>& a, const Ty& b) {
        basic_vector_pipe<Ty, MaxSize> v(a); v /= b; return v;
    }
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr basic_vector_pipe<Ty, MaxSize> operator|(const basic_vector_pipe<Ty, MaxSize>& a,
        const basic_vector_pipe<Ty, MaxSize>& b) {
        basic_vector_pipe<Ty, MaxSize>v(a); v /= b; return v;
    }
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr basic_vector_pipe<Ty, MaxSize> operator|(const Ty& a, const basic_vector_pipe<Ty, MaxSize>& b) {
        basic_vector_pipe<Ty, MaxSize>v(&a, 1); v /= b; return v;
    }

    // pipe types for common vectors.
    using vec4f_pipe  = typename basic_vector_pipe<float, 4>;
    using vec4i_pipe  = typename basic_vector_pipe<int, 4>;
    using vec4u_pipe  = typename basic_vector_pipe<unsigned int, 4>;
}