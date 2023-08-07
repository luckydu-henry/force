#include <bit>
#include <limits>

#include <fmath/PrMathFn.hpp>

using std::bit_cast;

namespace Fma {
    float Fmod(float x, float y) {
        float f = x / y;
        int   q = (int)f;
        float r = (f - q) * y;
        return r;
    }
    int Ftrunc(float x) {
        return static_cast<int>(x);
    }
    int Fceil(float x) {
        return static_cast<int>(x + 0.5f);
    }
    int Ffloor(float x) {
        return static_cast<int>(x - 0.5f);
    }
    int Fround(float x) {
        int   i = bit_cast<int>(x);
        float s = bit_cast<float>((i & 0x8000'0000) | 0x3f80'0000);
        return static_cast<int>(x + s * 0.5f);
    }
    int Fbround(float x) {
        int   k = ((int)x) & 1;
        int   i = bit_cast<int>(x);
        float s = bit_cast<float>((i & 0x8000'0000) | 0x3f80'0000);
        return static_cast<int>(x + s * ((float)k - 0.5f));
    }
    float Fabs(float x) {
        int i = bit_cast<int>(x);
        i = i & 0x7fff'ffff;
        return  bit_cast<float>(i);
    }
    int Fabs(int x) {
        return ((x >> 31) ^ x) - (x >> 31);
    }
    float Frecp(float x) {
        return 1.f / x;
    }
    float Finv(float x) {
        int i = bit_cast<int>(x);
        i = i ^ 0x8000'0000;
        return  bit_cast<float>(i);
    }
    float Fsqrt(float x) {
        float n = 0.5f * x;
        // Bit approxiMation
        int   i = bit_cast<int>(x);
        i = 0x1fbd'1df5 + (i >> 1);
        float y = bit_cast<float>(i);
        // Newton method approxiMation.
        y = 0.5f * y + n / y;
        y = 0.5f * y + n / y;

        return y;
    }
    float Frsqrt(float x) {
        float n = 0.5f * x;

        int   i = bit_cast<int>(x);
        i = 0x5f37'5a86 - (i >> 1); // wtf, this is better?
        float y = bit_cast<float>(i);

        y = y * (1.5f - n * y * y);
        y = y * (1.5f - n * y * y);

        return y;
    }
    float Fcbrt(float x) {

        int   h = bit_cast<int>(x);
        float s = bit_cast<float>((h & 0x8000'0000) | 0x3f80'0000);

        float x0 = bit_cast<float>(h & 0x7fff'ffff);
        float n = 0.333333f * x0;

        int   i = bit_cast<int>(x0);
        i = 0x2a2e'5c2f + (i / 3);
        float y = bit_cast<float>(i);

        y = 0.666666f * y + n * (1.f / (y * y));
        y = 0.666666f * y + n * (1.f / (y * y));
        y = 0.666666f * y + n * (1.f / (y * y));

        return s * y;
    }
    float Flog(float x) {
        float ln2 = 0.693'1471'8055'9945'3094'1723f;
        // Evil floating point bit hacking.
        int   i = bit_cast<int>(x);
        int   e = (i >> 23) - 0x7f;
        int   f = (((i << 1) & 0x00ff'ffff) >> 1) | 0x3f80'0000;
        float m = bit_cast<float>(f);

        // ApproxiMation using talor expination.
        float t = (m - 1.f) / (m + 1.f);
        float t2 = t * t;
        float y = 2.f * (t + t2 * t * (0.333333f + t2 * (0.2f + t2 * (0.142857f + t2 * (0.111111f + t2 * 0.090909f)))));

        return ln2 * (float)e + y;
    }
    float Flog2(float x) {
        float rln2 = 1.4'4269'5021'6293'3349'6093f;
        return rln2 * Flog(x);
    }
    uint32_t Flog2(uint32_t x) {
        return 31u - std::countl_zero(x);
    }
    float Flog10(float x) {
        float rln10 = 0.4'3429'4481'9032'5182'7651f;
        return rln10 * Flog(x);
    }
    float Fexp(float x) {
        float ln2 = 0.6'9314'7182'4645'9960'9375f; // actual ieee754 value of ln2.
        // Split exponent to interger part and floating point part.
        // Since x = i + f
        // 2^(x) = 2^(i + f) = 2^i * 2^f.
        float t = x / ln2;
        // Can be replaced by split but I don't do it here.
        int   i = (int)t;
        float f = t - (float)i;

        int   a = (i + 0x7f) << 23;
        float b = ln2 * f;      // 2^f = e^(ln2 * f) = e^b
        // Calculates e^b using talor expination since b : (-ln2, ln2)-
        // expination can be very approxiMate.
        float y = 1.f + b * (1.f + b * (0.5f + b * (0.166666f + b * (0.0416666f + b * (0.0083333f + b * 0.0013888f)))));
        return bit_cast<float>(a) * y;
    }
    float Fexp2(float x) {
        float ln2 = 0.6'9314'7182'4645'9960'9375f;
        return Fexp(x * ln2);
    }
    float Fexp10(float x) {
        float ln10 = 2.3'0258'5124'9694'8242'1875f;
        return Fexp(x * ln10);
    }
    // Log in any base.
    float Floga(float a, float b) {
        float lnb = Flog(b);
        float lna = Flog(a);
        return lnb / lna;
    }
    // Real exponent power function.
    float Fpow(float a, float b) {
        float lna = Flog(a);
        return Fexp(b * lna);
    }
    float Fsin(float x) {

        int   i = bit_cast<int>(x);
        int   g = (i & 0x8000'0000) | 0x3f80'0000;
        float s = bit_cast<float>(g);               // Original angle's sign.
        float k = bit_cast<float>(i & 0x7fff'ffff); // Absoulute value.
        float f = k / halfpi<float>;                // Fraction is the result.
        int   q = (int)f;                           // Quotient is int part of f.
        float r = (f - q) * halfpi<float>;          // Remainder is a the angle remainded.
        int   d = q & 3;                            // q mod 4.
        float a = 1.5f - (float)d;
        int   b = bit_cast<int>(a) & 0x7fff'ffff;   // Distance between 1.5 and 0, 1, 2, 3.
        int   e = (int)(bit_cast<float>(b) + 1.f);  // Translate sign's exponent
        float m = (r - (d & 1) * halfpi<float>);    // Translate angle.
        int   p = ((e & 1) << 31) | 0x3f80'0000;
        float t = bit_cast<float>(p) * m;           // theta is the angle translated between [-pi/2, pi/2].

        float h = t / 9;
        float h2 = h * h;
        float l = (((0.000027553f * h2 - 0.0001984f) * h2 + 0.0083333f) * h2 - 0.1666666f) * h * h2 + h;
        float j = l * (3.f - 4.f * l * l);
        float y = j * (3.f - 4.f * j * j);

        // Fix sign accoeding to original sign.
        return s * y;
    }
    float Fcos(float x) {
        int   i = bit_cast<int>(x);
        float a = bit_cast<float>(i & 0x7fff'ffff); // Absolute.
        float f = x / pi<float>;
        int   q = (int)f;
        float r = (f - q) * pi<float>;
        int   d = q & 1;
        float s = bit_cast<float>((d << 31) | 0x3f80'0000);
        float t = s * r + (float)d * pi<float>;
        // 1/27x Talor expination approxiMation.
        float h = t / 27;
        float h2 = h * h;
        float l = (((0.000024797f * h2 - 0.001388888f) * h2 + 0.04166666f) * h2 - 0.49999999f) * h2 + 1.f;
        // 27x angle approxiMation.
        float b = l * (4.f * l * l - 3.f);
        float e = b * (4.f * b * b - 3.f);
        float y = e * (4.f * e * e - 3.f);

        return y;
    }
    float Ftan(float x) {
        int   i = bit_cast<int>(x);
        int   g = (i & 0x8000'0000) | 0x3f80'0000;
        float s = bit_cast<float>(g);
        float v = bit_cast<float>(i & 0x7fffffff); // Absolute value.
        float f = x / halfpi<float>;
        int   q = (int)f;
        float r = (f - q) * halfpi<float>;
        int   d = q & 1;
        float t = r - (float)d * halfpi<float>;

        float h = t / 4;
        float h2 = h * h;
        float l = h * (1.f + h2 * (0.333333f + h2 * (0.1333333f + h2 * 0.05396825f)));
        float l2 = l * l;
        float y = (4 * l * (1 - l2)) / (1 - 6 * l2 + l2 * l2);

        return s * y;
    }
    float Fcot(float x) {
        return 1.f / Ftan(x);
    }
    float Fsec(float x) {
        return 1.f / Fcos(x);
    }
    float Fcsc(float x) {
        return 1.f / Fsin(x);
    }
    float Fasin(float x) {

        uint32_t ix = std::bit_cast<uint32_t>(x);
        float sn = std::bit_cast<float>(ix & 0x8000'0000 | 0x3f80'0000);
        float fx = std::bit_cast<float>(ix & 0x7fff'ffff);

        // Since we can't just evaluate in only one equation.
        // We have to split our equation into three range.
        // Each range will have its best approximation.
        float y = 0.f;

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
        else if (1.f - fx <= std::numeric_limits<float>::epsilon()) y = 1.570796326794f; // pi / 2.

        return sn * (y);
    }
    float Facos(float x) {
        // Simply use this conversion.
        return Fma::halfpi<float> -Fasin(x);
    }
}