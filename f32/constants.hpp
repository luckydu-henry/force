#ifndef _FORCE_F32_CONSTANTS_HPP_
#define _FORCE_F32_CONSTANTS_HPP_
//
// Some useful math constants
// All constants begin with c_
//
namespace force {
    namespace __opm32 {
        constexpr float c_pi      = 3.1415927f; // 180d
        constexpr float c_twopi   = 6.2831853f; // 360d
        constexpr float c_halfpi  = 1.5707963f; // 90d
        constexpr float c_quatpi  = 0.7853982f; // 45d
        constexpr float c_1thrdpi = 1.0471976f; // 60d
        constexpr float c_1sixpi  = 0.5235988f; // 30d
        constexpr float c_rpi     = 0.3183099f; // 1 / pi
        constexpr float c_sqrtpi  = 1.7724539f; // sqrt(pi)
        constexpr float c_rsqrtpi = 0.5641896f; // 1 / sqrt(pi)
        constexpr float c_e       = 2.7182818f; // euler number.
        constexpr float c_re      = 0.3678794f; // 1 / e
        constexpr float c_sqrte   = 1.6487213f; // sqrt(e)
        constexpr float c_sqrt2   = 1.4142135f;
        constexpr float c_sqrt3   = 1.7320508f;
        constexpr float c_rsqrt2  = 0.7071068f;
        constexpr float c_rsqrt3  = 0.5773503f;
        constexpr float c_rsqrte  = 0.6065307f;
    }
}

#endif //! _FORCE_F32_CONSTANTS_H_