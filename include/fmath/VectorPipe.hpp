#pragma once
#include <algorithm> // for min copy and move.
namespace Fma {
    // Vector pipe is used to do conversion between Vectors.
    // This class has now extra pay off because it's very light.
    template <typename Ty, std::size_t MaxSize>
    class BasicVectorPipe {
        Ty          mData[MaxSize];
        std::size_t mSize;
    public:
        using value_type = Ty;
        static constexpr std::size_t max_size = MaxSize;

        constexpr BasicVectorPipe(const value_type* d, size_t s) {
            mSize = s;
            std::copy(d, d + mSize, mData);
        }
        BasicVectorPipe(const BasicVectorPipe& right) {
            std::copy(right.mData, right.mData + std::min(mSize, right.mSize), mData);
            mSize = right.mSize;
        }
        BasicVectorPipe(BasicVectorPipe&& right) noexcept {
            std::move(right.mData, right.mData + std::min(mSize, right.mSize), mData);
            mSize = right.mSize;
        }
        // Append operator can use to cat two BasicVectorPipe.
        // Vectors don't have mod operations so this operator is fine. 
        BasicVectorPipe& operator|=(const value_type& v) {
            if (mSize > max_size - 1) throw "Too large to combine a Vector.";
            mData[mSize++] = v;
            return *this;
        }
        BasicVectorPipe& operator|=(const BasicVectorPipe& v) {
            if (mSize + v.mSize > max_size) throw "Too large to combine a Vector.";
            std::copy(v.Data(), v.Data() + v.mSize, mData + mSize);
            mSize += v.mSize;
            return *this;
        }

        const size_t      Size() const { return mSize; }
        const value_type* Data() const { return mData; }

        ~BasicVectorPipe() = default;
    };

    // Useful functions to do Vector combined and Vector clip.
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr BasicVectorPipe<Ty, MaxSize> operator|(const BasicVectorPipe<Ty, MaxSize>& a, const Ty& b) {
        BasicVectorPipe<Ty, MaxSize> v(a); v |= b; return v;
    }
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr BasicVectorPipe<Ty, MaxSize> operator|(const BasicVectorPipe<Ty, MaxSize>& a,
        const BasicVectorPipe<Ty, MaxSize>& b) {
        BasicVectorPipe<Ty, MaxSize>v(a); v |= b; return v;
    }
    template <typename Ty, std::size_t MaxSize>
    [[nodiscard]] constexpr BasicVectorPipe<Ty, MaxSize> operator|(const Ty& a, const BasicVectorPipe<Ty, MaxSize>& b) {
        BasicVectorPipe<Ty, MaxSize>v(&a, 1); v |= b; return v;
    }

    // pipe types for common Vectors.
    using Vec4fPipe  = typename BasicVectorPipe<float, 4>;
    using Vec4iPipe  = typename BasicVectorPipe<int, 4>;
    using Vec4uPipe  = typename BasicVectorPipe<unsigned int, 4>;
}