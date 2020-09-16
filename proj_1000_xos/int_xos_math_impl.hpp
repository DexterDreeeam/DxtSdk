/* ********* * ********* * ********* * ********* * *********
 *
 * int_xos_math_impl.impl
 *
 * proj: proj_1000_xos
 * desc: bisic math function and api nested implementations
 * autr: dexterdreeeam
 * date: 20200901
 * tips: \
 *
 ********* * ********* * ********* * ********* * ********* */

static _INLINE_ _NOALIAS_ f32 __degree_radian(f32 degree)
{
    return static_cast<f32>(0.01745329251994329576923690768489f) * degree;
}

static _INLINE_ _NOALIAS_ f64 __degree_radian(f64 degree)
{
    return static_cast<f64>(0.01745329251994329576923690768489) * degree;
}
static _INLINE_ _NOALIAS_ f32 __radian_degree(f32 radian)
{
    return static_cast<f32>(57.295779513082320876798154814105f) * radian;
}

static _INLINE_ _NOALIAS_ f64 __radian_degree(f64 radian)
{
    return static_cast<f64>(57.295779513082320876798154814105) * radian;
}

static _INLINE_ _NOTHROW_ _NOALIAS_ f32 __sqrt_inv(f32 n)
{
    s32 i;
    f32 x;
    const f32 threehalfs = 1.5f;
    x = n * 0.5f;
    i = *reinterpret_cast<s32*>(&n);
    i = 0x5f3759df - (i >> 1);
    n = *reinterpret_cast<f32*>(&i);
    n = n * (threehalfs - (x * n * n));
    //n = n * (threehalfs - (x * n * n));
    return n;
}

static _INLINE_ _NOTHROW_ _NOALIAS_ f64 __sqrt_inv(f64 n)
{
    s64 i;
    f64 x;
    const f64 threehalfs = 1.5;
    x = n * 0.5;
    i = *reinterpret_cast<s64*>(&n);
    i = 0x5fe6ec85e7de30da - (i >> 1);
    n = *reinterpret_cast<f64*>(&i);
    n = n * (threehalfs - (x * n * n));
    //n = n * (threehalfs - (x * n * n));
    //n = n * (threehalfs - (x * n * n));
    return n;
}

static _INLINE_ _NOTHROW_ _NOALIAS_ f32 __sq(f32 n)
{
    return n * n;
}

static _INLINE_ _NOTHROW_ _NOALIAS_ f32 __sqrt(f32 n)
{
    assert(__sqrt_inv(n) > f32_pos_min);
    return 1.0f / __sqrt_inv(n);
}

static _INLINE_ _NOTHROW_ _NOALIAS_ f64 __sq(f64 n)
{
    return n * n;
}

static _INLINE_ _NOTHROW_ _NOALIAS_ f64 __sqrt(f64 n)
{
    assert(__sqrt_inv(n) > f32_pos_min);
    return 1.0 / __sqrt_inv(n);
}

static _INLINE_ _NOALIAS_ f32 __acos(f32 n)
{
    return windows_ns::acosf(n);
}

static _INLINE_ _NOALIAS_ f32 __asin(f32 n)
{
    return windows_ns::asinf(n);
}

static _INLINE_ _NOALIAS_ f32 __atan2(f32 x, f32 y)
{
    return windows_ns::atan2f(x, y);
}

static _INLINE_ _NOALIAS_ f64 __acos(f64 n)
{
    return windows_ns::acos(n);
}

static _INLINE_ _NOALIAS_ f64 __asin(f64 n)
{
    return windows_ns::asin(n);
}

static _INLINE_ _NOALIAS_ f64 __atan2(f64 x, f64 y)
{
    return windows_ns::atan2(x, y);
}

START_NS(windows_ns)
#include <intrin.h>
END_NS(windows_ns)

typedef windows_ns::__m128  simd4xf32;
typedef windows_ns::__m256d simd4xf64;

_INLINE_ void simd_write(const f32 *src, simd4xf32 *dst)
{
    *dst = windows_ns::_mm_load_ps(src);
}

_INLINE_ void simd_write(const f64 *src, simd4xf64 *dst)
{
    *dst = windows_ns::_mm256_load_pd(src);
}

_INLINE_ void simd_read(const simd4xf32 *src, f32 *dst)
{
    windows_ns::_mm_store_ps(dst, *src);
}

_INLINE_ void simd_read(const simd4xf64 *src, f64 *dst)
{
    windows_ns::_mm256_store_pd(dst, *src);
}

_INLINE_ void simd_add(simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result)
{
    *result = windows_ns::_mm_add_ps(*operand1, *operand2);
}

_INLINE_ void simd_add(simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result)
{
    *result = windows_ns::_mm256_add_pd(*operand1, *operand2);
}

_INLINE_ void simd_sub(simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32* result)
{
    *result = windows_ns::_mm_sub_ps(*operand1, *operand2);
}

_INLINE_ void simd_sub(simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64* result)
{
    *result = windows_ns::_mm256_sub_pd(*operand1, *operand2);
}

_INLINE_ void simd_mul(simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result)
{
    *result = windows_ns::_mm_mul_ps(*operand1, *operand2);
}

_INLINE_ void simd_mul(simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result)
{
    *result = windows_ns::_mm256_mul_pd(*operand1, *operand2);
}

_INLINE_ void simd_div(simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result)
{
    *result = windows_ns::_mm_div_ps(*operand1, *operand2);
}

_INLINE_ void simd_div(simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result)
{
    *result = windows_ns::_mm256_div_pd(*operand1, *operand2);
}

_INLINE_ void simd_and(simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result)
{
    *result = windows_ns::_mm_and_ps(*operand1, *operand2);
}

_INLINE_ void simd_and(simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result)
{
    *result = windows_ns::_mm256_and_pd(*operand1, *operand2);
}

_INLINE_ void simd_andnot(simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result)
{
    *result = windows_ns::_mm_andnot_ps(*operand1, *operand2);
}

_INLINE_ void simd_andnot(simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result)
{
    *result = windows_ns::_mm256_andnot_pd(*operand1, *operand2);
}

_INLINE_ void simd_or(simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result)
{
    *result = windows_ns::_mm_or_ps(*operand1, *operand2);
}

_INLINE_ void simd_or(simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result)
{
    *result = windows_ns::_mm256_or_pd(*operand1, *operand2);
}

_INLINE_ void simd_xor(simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result)
{
    *result = windows_ns::_mm_xor_ps(*operand1, *operand2);
}

_INLINE_ void simd_xor(simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result)
{
    *result = windows_ns::_mm256_xor_pd(*operand1, *operand2);
}

_INLINE_ void simd_sqrt(simd4xf32 *operand1, simd4xf32 *result)
{
    *result = windows_ns::_mm_sqrt_ps(*operand1);
}

_INLINE_ void simd_sqrt(simd4xf64 *operand1, simd4xf64 *result)
{
    *result = windows_ns::_mm256_sqrt_pd(*operand1);
}

_INLINE_ void simd_rcp(simd4xf32 *operand1, simd4xf32 *result)
{
    *result = windows_ns::_mm_rcp_ps(*operand1);
}

_INLINE_ void simd_rcp(simd4xf64 *operand1, simd4xf64 *result)
{
    windows_ns::__m256d td;
    f64 unit[] = { 1.0, 1.0, 1.0, 1.0 };
    simd_write(unit, &td);
    simd_div(&td, operand1, result);
}

_INLINE_ void simd_min(simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result)
{
    *result = windows_ns::_mm_min_ps(*operand1, *operand2);
}

_INLINE_ void simd_min(simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result)
{
    *result = windows_ns::_mm256_min_pd(*operand1, *operand2);
}

_INLINE_ void simd_max(simd4xf32 *operand1, simd4xf32 *operand2, simd4xf32 *result)
{
    *result = windows_ns::_mm_max_ps(*operand1, *operand2);
}

_INLINE_ void simd_max(simd4xf64 *operand1, simd4xf64 *operand2, simd4xf64 *result)
{
    *result = windows_ns::_mm256_max_pd(*operand1, *operand2);
}
