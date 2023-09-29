#include <bit>
#include <limits>

#include <fmath/primary.hpp>

using std::bit_cast;

namespace force::math {
    float32_t mod(float32_t x, float32_t y) {
        float32_t f = x / y;
        int32_t   q = (int32_t)f;
        float32_t r = (f - q) * y;
        return r;
    }
    int32_t trunc(float32_t x) {
        return static_cast<int32_t>(x);
    }
    int32_t ceil(float32_t x) {
        return static_cast<int32_t>(x + 0.5f);
    }
    int32_t floor(float32_t x) {
        return static_cast<int32_t>(x - 0.5f);
    }
    int32_t round(float32_t x) {
        int32_t   i = bit_cast<int32_t>(x);
        float32_t s = bit_cast<float32_t>((i & 0x8000'0000) | 0x3f80'0000);
        return static_cast<int32_t>(x + s * 0.5f);
    }
    int32_t bround(float32_t x) {
        int32_t   k = ((int32_t)x) & 1;
        int32_t   i = bit_cast<int32_t>(x);
        float32_t s = bit_cast<float32_t>((i & 0x8000'0000) | 0x3f80'0000);
        return static_cast<int32_t>(x + s * ((float32_t)k - 0.5f));
    }
    float32_t abs(float32_t x) {
        int32_t i = bit_cast<int32_t>(x);
        i = i & 0x7fff'ffff;
        return  bit_cast<float32_t>(i);
    }
    int32_t abs(int32_t x) {
        return ((x >> 31) ^ x) - (x >> 31);
    }
    float32_t recp(float32_t x) {
        return 1.f / x;
    }
    float32_t inv(float32_t x) {
        int32_t i = bit_cast<int32_t>(x);
        i = i ^ 0x8000'0000;
        return  bit_cast<float32_t>(i);
    }
    float32_t sqrt(float32_t x) {
        float32_t n = 0.5f * x;
        // Bit approxiMation
        int32_t   i = bit_cast<int32_t>(x);
        i = 0x1fbd'1df5 + (i >> 1);
        float32_t y = bit_cast<float32_t>(i);
        // Newton method approxiMation.
        y = 0.5f * y + n / y;
        y = 0.5f * y + n / y;

        return y;
    }
    float32_t rsqrt(float32_t x) {
        float32_t n = 0.5f * x;

        int32_t   i = bit_cast<int32_t>(x);
        i = 0x5f37'5a86 - (i >> 1); // wtf, this is better?
        float32_t y = bit_cast<float32_t>(i);

        y = y * (1.5f - n * y * y);
        y = y * (1.5f - n * y * y);

        return y;
    }
    float32_t cbrt(float32_t x) {

        int32_t   h = bit_cast<int32_t>(x);
        float32_t s = bit_cast<float32_t>((h & 0x8000'0000) | 0x3f80'0000);

        float32_t x0 = bit_cast<float32_t>(h & 0x7fff'ffff);
        float32_t n = 0.333333f * x0;

        int32_t   i = bit_cast<int32_t>(x0);
        i = 0x2a2e'5c2f + (i / 3);
        float32_t y = bit_cast<float32_t>(i);

        y = 0.666666f * y + n * (1.f / (y * y));
        y = 0.666666f * y + n * (1.f / (y * y));
        y = 0.666666f * y + n * (1.f / (y * y));

        return s * y;
    }
    float32_t log(float32_t x) {
        float32_t ln2 = 0.693'1471'8055'9945'3094'1723f;
        // Evil floating point bit hacking.
        int32_t   i = bit_cast<int32_t>(x);
        int32_t   e = (i >> 23) - 0x7f;
        int32_t   f = (((i << 1) & 0x00ff'ffff) >> 1) | 0x3f80'0000;
        float32_t m = bit_cast<float32_t>(f);

        // ApproxiMation using talor expination.
        float32_t t = (m - 1.f) / (m + 1.f);
        float32_t t2 = t * t;
        float32_t y = 2.f * (t + t2 * t * (0.333333f + t2 * (0.2f + t2 * (0.142857f + t2 * (0.111111f + t2 * 0.090909f)))));

        return ln2 * (float32_t)e + y;
    }
    float32_t log2(float32_t x) {
        float32_t rln2 = 1.4'4269'5021'6293'3349'6093f;
        return rln2 * log(x);
    }
    uint32_t log2(uint32_t x) {
        return 31u - std::countl_zero(x);
    }
    float32_t log10(float32_t x) {
        float32_t rln10 = 0.4'3429'4481'9032'5182'7651f;
        return rln10 * log(x);
    }
    float32_t exp(float32_t x) {
        float32_t ln2 = 0.6'9314'7182'4645'9960'9375f; // actual ieee754 value of ln2.
        // Split exponent to interger part and floating point part.
        // Since x = i + f
        // 2^(x) = 2^(i + f) = 2^i * 2^f.
        float32_t t = x / ln2;
        // Can be replaced by split but I don't do it here.
        int32_t   i = (int32_t)t;
        float32_t f = t - (float32_t)i;

        int32_t   a = (i + 0x7f) << 23;
        float32_t b = ln2 * f;      // 2^f = e^(ln2 * f) = e^b
        // Calculates e^b using talor expination since b : (-ln2, ln2)-
        // expination can be very approxiMate.
        float32_t y = 1.f + b * (1.f + b * (0.5f + b * (0.166666f + b * (0.0416666f + b * (0.0083333f + b * 0.0013888f)))));
        return bit_cast<float32_t>(a) * y;
    }
    float32_t exp2(float32_t x) {
        float32_t ln2 = 0.6'9314'7182'4645'9960'9375f;
        return exp(x * ln2);
    }
    float32_t exp10(float32_t x) {
        float32_t ln10 = 2.3'0258'5124'9694'8242'1875f;
        return exp(x * ln10);
    }
    // Log in any base.
    float32_t loga(float32_t a, float32_t b) {
        float32_t lnb = log(b);
        float32_t lna = log(a);
        return lnb / lna;
    }
    // Real exponent power function.
    float32_t pow(float32_t a, float32_t b) {
        float32_t lna = log(a);
        return exp(b * lna);
    }
    float32_t sin(float32_t x) {

        int32_t   i = bit_cast<int32_t>(x);
        int32_t   g = (i & 0x8000'0000) | 0x3f80'0000;
        float32_t s = bit_cast<float32_t>(g);               // Original angle's sign.
        float32_t k = bit_cast<float32_t>(i & 0x7fff'ffff); // Absoulute value.
        float32_t f = k / halfpi<float32_t>;                // raction is the result.
        int32_t   q = (int32_t)f;                           // Quotient is int32_t part of f.
        float32_t r = (f - q) * halfpi<float32_t>;          // Remainder is a the angle remainded.
        int32_t   d = q & 3;                            // q mod 4.
        float32_t a = 1.5f - (float32_t)d;
        int32_t   b = bit_cast<int32_t>(a) & 0x7fff'ffff;   // Distance between 1.5 and 0, 1, 2, 3.
        int32_t   e = (int32_t)(bit_cast<float32_t>(b) + 1.f);  // Translate sign's exponent
        float32_t m = (r - (d & 1) * halfpi<float32_t>);    // Translate angle.
        int32_t   p = ((e & 1) << 31) | 0x3f80'0000;
        float32_t t = bit_cast<float32_t>(p) * m;           // theta is the angle translated between [-pi/2, pi/2].

        float32_t h = t / 9;
        float32_t h2 = h * h;
        float32_t l = (((0.000027553f * h2 - 0.0001984f) * h2 + 0.0083333f) * h2 - 0.1666666f) * h * h2 + h;
        float32_t j = l * (3.f - 4.f * l * l);
        float32_t y = j * (3.f - 4.f * j * j);

        // ix sign accoeding to original sign.
        return s * y;
    }
    float32_t cos(float32_t x) {
        int32_t   i = bit_cast<int32_t>(x);
        float32_t a = bit_cast<float32_t>(i & 0x7fff'ffff); // Absolute.
        float32_t f = x / pi<float32_t>;
        int32_t   q = (int32_t)f;
        float32_t r = (f - q) * pi<float32_t>;
        int32_t   d = q & 1;
        float32_t s = bit_cast<float32_t>((d << 31) | 0x3f80'0000);
        float32_t t = s * r + (float32_t)d * pi<float32_t>;
        // 1/27x Talor expination approxiMation.
        float32_t h = t / 27;
        float32_t h2 = h * h;
        float32_t l = (((0.000024797f * h2 - 0.001388888f) * h2 + 0.04166666f) * h2 - 0.49999999f) * h2 + 1.f;
        // 27x angle approxiMation.
        float32_t b = l * (4.f * l * l - 3.f);
        float32_t e = b * (4.f * b * b - 3.f);
        float32_t y = e * (4.f * e * e - 3.f);

        return y;
    }
    float32_t tan(float32_t x) {
        int32_t   i = bit_cast<int32_t>(x);
        int32_t   g = (i & 0x8000'0000) | 0x3f80'0000;
        float32_t s = bit_cast<float32_t>(g);
        float32_t v = bit_cast<float32_t>(i & 0x7fffffff); // Absolute value.
        float32_t f = x / halfpi<float32_t>;
        int32_t   q = (int32_t)f;
        float32_t r = (f - q) * halfpi<float32_t>;
        int32_t   d = q & 1;
        float32_t t = r - (float32_t)d * halfpi<float32_t>;

        float32_t h = t / 4;
        float32_t h2 = h * h;
        float32_t l = h * (1.f + h2 * (0.333333f + h2 * (0.1333333f + h2 * 0.05396825f)));
        float32_t l2 = l * l;
        float32_t y = (4 * l * (1 - l2)) / (1 - 6 * l2 + l2 * l2);

        return s * y;
    }
    float32_t cot(float32_t x) {
        return 1.f / tan(x);
    }
    float32_t sec(float32_t x) {
        return 1.f / cos(x);
    }
    float32_t csc(float32_t x) {
        return 1.f / sin(x);
    }
    float32_t asin(float32_t x) {

        uint32_t ix = std::bit_cast<uint32_t>(x);
        float32_t sn = std::bit_cast<float32_t>(ix & 0x8000'0000 | 0x3f80'0000);
        float32_t fx = std::bit_cast<float32_t>(ix & 0x7fff'ffff);

        // Since we can't just evaluate in only one equation.
        // We have to split our equation into three range.
        // Each range will have its best approximation.
        float32_t y = 0.f;

        if (fx <= 0.7f) {
            // Newton iteration.
            y = fx;
            y -= ((y * (1.f - 0.1666666f * y * y * (1.f - 0.05f * y * y)) - fx) / (1.f - 0.5f * y * y * (1.f - 0.08333333f * y * y)));
            y -= ((y * (1.f - 0.1666666f * y * y * (1.f - 0.05f * y * y)) - fx) / (1.f - 0.5f * y * y * (1.f - 0.08333333f * y * y)));
        }
        else if (fx > 0.7f and fx <= 0.9f) {
            // Talor series at x = 0.8
            y = fx - 0.8f;
            y = 0.927295f + 1.66667f * y + 1.85185f * y * y + 4.88683f * y * y * y;
        }
        else if (fx > 0.9f and x < 1.f) {
            // Talor series at x = 0.95
            y = fx - 0.95f;
            y = 1.25323589f + 3.20256f * y + 15.6022f * y * y + 157.496 * y * y * y + 1971.56 * y * y * y * y;
        }
        // This one is special because we can't have series approximation at x = 1.f;
        // Because it's not differentiable.
        else if (1.f - fx <= std::numeric_limits<float32_t>::epsilon()) y = 1.570796326794f; // pi / 2.

        return sn * (y);
    }
    float32_t acos(float32_t x) {
        // Simply use this conversion.
        return force::math::halfpi<float32_t> -asin(x);
    }
    float32_t atan(float32_t x) {
        return x * (-0.1784f * abs(x) - 0.0663f * x * x + 1.0301f);
    }
}