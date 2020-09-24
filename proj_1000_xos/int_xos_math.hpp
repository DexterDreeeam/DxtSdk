/* ********* * ********* * ********* * ********* * *********
 *
 * int_xos_math.hpp
 *
 * proj: proj_1000_xos
 * desc: bisic math function and api
 * autr: dexterdreeeam
 * date: 20200827
 * tips: \
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_XOS_MATH_HPP__)
#define __INT_XOS_MATH_HPP__

#pragma warning (push)
#pragma warning (disable : 4005)

namespace windows_ns
{
#include <math.h>
}

#include "int_xos_math_impl.hpp"

#define magic_s32                         ( 0x7a9f82e3L )
#define magic_s64                         ( 0x7a9f82e301d65c4bLL )
#define abs(x)                            ( (x) >= (0) ? (x) : (-x) )
#define min(x,y)                          ( (x) < (y) ? (x) : (y) )
#define max(x,y)                          ( (x) > (y) ? (x) : (y) )
#define clamp(n,_min,_max)                ( (n < _min) ? _min : (n > _max) ? _max : n )
#define around(x,mod)                     ( (x + mod - 1) / mod * mod )
#define floor(x,mod)                      ( (x / mod) * mod )
#define ceil(x,mod)                       ( around(x,mod) )
#define _KB                               (1024ULL)
#define _MB                               (1024ULL * 1024ULL)
#define _GB                               (1024ULL * 1024ULL * 1024ULL)
#define class_offset(cls, ele)            reinterpret_cast<unsigned long long>(&(reinterpret_cast<cls*>(nullptr)->ele))
#define pointer_convert(p, offset, newp)  reinterpret_cast<newp>(const_cast<char*>(reinterpret_cast<const char*>(p)) + (s64(offset)))
#define sq(x)                             __sq(x)
#define sqrt(x)                           __sqrt(x)
#define sqrt_inv(x)                       __sqrt_inv(x)
#define degree_radian(x)                  __degree_radian(x)
#define radian_degree(x)                  __radian_degree(x)
#define tan_radian(x)                     windows_ns::tan(x)
#define tan_degree(x)                     windows_ns::tan(degree_radian(x))
#define sin_radian(x)                     windows_ns::sin(x)
#define sin_degree(x)                     windows_ns::sin(degree_radian(x))
#define cos_radian(x)                     windows_ns::cos(x)
#define cos_degree(x)                     windows_ns::cos(degree_radian(x))
#define atan2_radian(x,y)                 __atan2(x, y)                    //# (x != 0 || y != 0) : (-Pi, +Pi]
#define atan2_degree(x,y)                 __radian_degree(__atan2(x, y))   //# (x != 0 || y != 0) : (-180, 180]
#define asin_radian(x)                    __asin(x)                        //# [-1, 1] : [-0.5 * Pi, 0.5 * Pi]
#define asin_degree(x)                    __radian_degree(__asin(x))       //# [-1, 1] : [-90, 90]
#define acos_radian(x)                    __acos(x)                        //# [-1, 1] : [0, +Pi]
#define acos_degree(x)                    __radian_degree(__acos(x))       //# [-1, 1] : [0, 180]
#define pi                                (3.1415926535897932384626433832795f)

_INLINE_ void simd_write  (const f32 *src, simd4xf32 *dst);
_INLINE_ void simd_write  (const f64 *src, simd4xf64 *dst);
_INLINE_ void simd_read   (const simd4xf32 *src, f32 *dst);
_INLINE_ void simd_read   (const simd4xf64 *src, f64 *dst);
_INLINE_ void simd_add    (simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result);
_INLINE_ void simd_add    (simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result);
_INLINE_ void simd_sub    (simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result);
_INLINE_ void simd_sub    (simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result);
_INLINE_ void simd_mul    (simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result);
_INLINE_ void simd_mul    (simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result);
_INLINE_ void simd_div    (simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result);
_INLINE_ void simd_div    (simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result);
_INLINE_ void simd_and    (simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result);
_INLINE_ void simd_and    (simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result);
_INLINE_ void simd_andnot (simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result);
_INLINE_ void simd_andnot (simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result);
_INLINE_ void simd_or     (simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result);
_INLINE_ void simd_or     (simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result);
_INLINE_ void simd_xor    (simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result);
_INLINE_ void simd_xor    (simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result);
_INLINE_ void simd_sqrt   (simd4xf32 *operand1, simd4xf32 *result);
_INLINE_ void simd_sqrt   (simd4xf64 *operand1, simd4xf64 *result);
_INLINE_ void simd_rcp    (simd4xf32 *operand1, simd4xf32 *result);
_INLINE_ void simd_rcp    (simd4xf64 *operand1, simd4xf64 *result);
_INLINE_ void simd_min    (simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result);
_INLINE_ void simd_min    (simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result);
_INLINE_ void simd_max    (simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result);
_INLINE_ void simd_max    (simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result);

#pragma warning (pop)

#endif //# __INT_XOS_MATH_HPP__ ends
