#pragma once
#include "predef.hpp"
#if defined BOOST_HW_SIMD_X86
#    if   BOOST_HW_SIMD_X86 == BOOST_HW_SIMD_X86_SSE_VERSION
#        include "simd/intel_sse.hpp"
#    elif BOOST_HW_SIMD_X86 == BOOST_HW_SIMD_X86_SSE2_VERSION
#        include "simd/intel_sse2.hpp"
#    elif BOOST_HW_SIMD_X86 == BOOST_HW_SIMD_X86_SSE3_VERSION
#        include "simd/intel_sse3.hpp"
#    endif
#endif