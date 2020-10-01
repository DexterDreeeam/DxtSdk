/* ********* * ********* * ********* * ********* * *********
 *
 * int_xos_definition.hpp
 *
 * proj: proj_00_sdk_component_100_xos
 * desc: common definitions for build-in types
 * autr: dexterdreeeam
 * date: 20200810
 * tips: \
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_XOS_DEFINITION_HPP__)
#define __INT_XOS_DEFINITION_HPP__

#define _IN_
#define _OUT_
#define _C_CALL_        __cdecl                //# for C/Cpp function call format
#define _STD_CALL_      __stdcall              //# for Standard call format
#define _FAST_CALL_     __fastcall             //# for Fast call format, register store argument
#define _INLINE_        __inline               //# for inline function declare
#define _NOINLINE_      __declspec(noinline)   //# for not inline function declare
#define _ALIGN_(x)      __declspec(align(x))   //# for data alignment minimum in struct/class
#define _DLL_IMPORT_    __declspec(dllimport)  //# for dll import declare
#define _DLL_EXPORT_    __declspec(dllexport)  //# for dll export declare
#define _NAKED_         __declspec(naked)      //# for not store register when enter function
#define _VAR_RESTRICT_  __restrict             //# for variable restrict 
#define _RESTRICT_      __declspec(restrict)   //# for function with a return pointer and this return pointer is not aliased
#define _NOALIAS_       __declspec(noalias)    //# for function insure that only function internal data or the data internal pointer point to are used in function
#define _NORETURN_      __declspec(noreturn)   //# for function without return value
#define _NOTHROW_       __declspec(nothrow)    //# for function insure that no exception would be throw internally
#define _NOVTABLE_      __declspec(novtable)   //# for class that no virtual function table, only used in non-virtual class or pure-virtual class
#define _SELECTANY_     __declspec(selectany)  //# for variable definition in header file without causing redefine error

#define POINTER_BYTES (8)
#define POINTER_BITS  (64)

typedef    unsigned               char  u8;
typedef      signed               char  s8;
typedef    unsigned  short         int  u16;
typedef      signed  short         int  s16;
typedef    unsigned       long     int  u32;
typedef      signed       long     int  s32;
typedef    unsigned  long long     int  u64;
typedef      signed  long long     int  s64;
typedef                          float  f32;
typedef                         double  f64;
typedef                            u64  uint;
typedef                            s64  sint;
typedef                            s32  boole;

#pragma warning (push)
#pragma warning (disable : 26450)
#pragma warning (disable : 26454)
#pragma warning (disable : 4307)

const u8  u8_max = (u8)0 - 1;
const u8  u8_min = (u8)0;
const s8  s8_max = (s8)(((s8)1 << 7) - 1);
const s8  s8_min = (s8)((s8)1 << 7);
const u16 u16_max = (u16)0 - 1;
const u16 u16_min = (u16)0;
const s16 s16_max = (s16)(((s16)1 << 15) - 1);
const s16 s16_min = (s16)((s16)1 << 15);
const u32 u32_max = (u32)0 - 1;
const u32 u32_min = (u32)0;
const s32 s32_max = (s32)(((s32)1 << 31) - 1);
const s32 s32_min = (s32)((s32)1 << 31);
const u64 u64_max = (u64)0 - 1;
const u64 u64_min = (u64)0;
const s64 s64_max = (s64)(((s64)1 << 63) - 1);
const s64 s64_min = (s64)((s64)1 << 63);
const f32 f32_pos_min = (1.0e-30f);
const f32 f32_pos_max = (1.0e30f);
const f32 f32_epsilon = (1.0e-5f);
const boole boole_true = ((s32)1);
const boole boole_false = ((s32)0);

#pragma warning (pop)

typedef enum : s32
{
    RET_FAILED = 0,
    RET_FALSE = 0,
    RET_SUCCESS = 1,
    RET_TRUE = 1,

    RET_FAILURE_BASE = 1L << 31,
    RET_NOSENSE,
    RET_OUT_OF_TIME,
    RET_INVALID_PARAM,

    RET_SUCCEED_BASE = 1L << 30,
    RET_NOT_IMMEDIATE,
} RET;

_INLINE_ _NOALIAS_ boole is_success(RET rt) noexcept
{
    return rt > 0L ? boole_true : boole_false;
}

template<typename Ty1, typename Ty2>
_INLINE_ _NOALIAS_ void swap(Ty1 &e1, Ty2 &e2) noexcept
{
    Ty1 tmp = e1;
    e1 = e2;
    e2 = tmp;
}

_INLINE_ _NOALIAS_ s64 str_len(const char *s) noexcept
{
    s64 i = 0;
    while(*(s + i) != '\0')
    {
        ++i;
    }
    return i;
}

_INLINE_ _NOALIAS_ boole str_equal(const char *s1, const char *s2) noexcept
{
    while (*s1 == *s2)
    {
        if (*s1 == '\0')
        {
            return boole_true;
        }
        ++s1;
        ++s2;
    }
    return boole_false;
}

_INLINE_ _NOALIAS_ s64 str_compare(const char *s1, const char *s2) noexcept
{
    s64 i = 0;
    while (*s1 == *s2)
    {
        if (*s1 == 0)
        {
            return 0; //# equal
        }
        ++s1;
        ++s2;
    }
    return (s64)*s1 - (s64)*s2;
}

_INLINE_ s64 s32_to_text(s32 v, char *text)
{
    if (v == 0)
    {
        text[0] = '0';
        return 1;
    }
    if (v == s32_min)
    {
        text[0] = '-';
        text[1] = '2';
        text[2] = '1';
        text[3] = '4';
        text[4] = '7';
        text[5] = '4';
        text[6] = '8';
        text[7] = '3';
        text[8] = '6';
        text[9] = '4';
        text[10] = '8';
        return 11;
    }
    s64 digits = 0;
    if (v < 0)
    {
        ++digits;
        text[0] = '-';
        v = -v;
    }
    s32 num = v;
    while (num)
    {
        ++digits;
        num /= 10;
    }
    s64 write_len = digits;
    while (v)
    {
        --digits;
        text[digits] = '0' + v % 10;
        v /= 10;
    }
    return write_len;
}

_INLINE_ s64 u32_to_text(u32 v, char *text)
{
    if (v == 0)
    {
        text[0] = '0';
        return 1;
    }
    s64 digits = 0;
    u32 num = v;
    while (num)
    {
        ++digits;
        num /= 10;
    }
    s64 write_len = digits;
    while (v)
    {
        --digits;
        text[digits] = '0' + v % 10;
        v /= 10;
    }
    return write_len;
}

_INLINE_ s64 u32_to_text_padding(u32 v, char *text, s64 holds)
{
    s64 myhold = holds;
    while (--myhold >= 0)
    {
        text[myhold] = '0' + v % 10;
        v /= 10;
    }
    return holds;
}

_INLINE_ s64 s64_to_text(s64 v, char *text)
{
    if (v == 0)
    {
        text[0] = '0';
        return 1;
    }
    if (v == s64_min)
    {
        text[0] = '-';
        text[1] = '9';
        text[2] = '2';
        text[3] = '2';
        text[4] = '3';
        text[5] = '3';
        text[6] = '7';
        text[7] = '2';
        text[8] = '0';
        text[9] = '3';
        text[10] = '6';
        text[11] = '8';
        text[12] = '5';
        text[13] = '4';
        text[14] = '7';
        text[15] = '7';
        text[16] = '5';
        text[17] = '8';
        text[18] = '0';
        text[19] = '8';
        return 20;
    }
    s64 digits = 0;
    if (v < 0)
    {
        ++digits;
        text[0] = '-';
        v = -v;
    }
    s64 num = v;
    while (num)
    {
        ++digits;
        num /= 10;
    }
    s64 write_len = digits;
    while (v)
    {
        --digits;
        text[digits] = '0' + v % 10;
        v /= 10;
    }
    return write_len;
}

_INLINE_ s64 u64_to_text(u64 v, char *text)
{
    if (v == 0)
    {
        text[0] = '0';
        return 1;
    }
    s64 digits = 0;
    u64 num = v;
    while (num)
    {
        ++digits;
        num /= 10;
    }
    s64 write_len = digits;
    while (v)
    {
        --digits;
        text[digits] = '0' + v % 10;
        v /= 10;
    }
    return write_len;
}

_INLINE_ s64 u64_to_text_padding(u64 v, char *text, s64 holds)
{
    s64 myholds = holds;
    while (--myholds >= 0)
    {
        text[myholds] = '0' + v % 10;
        v /= 10;
    }
    return holds;
}

_INLINE_ s64 u64_to_text_hex(u64 v, char *text)
{
    text[0] = '0';
    text[1] = 'x';
    text += 2;
    if (v == 0)
    {
        text[0] = '0';
        return 3;
    }
    s64 digits = 0;
    u64 num = v;
    while (num)
    {
        ++digits;
        num /= 16;
    }
    s64 write_len = digits + 2;
    while (v)
    {
        --digits;
        s64 rem = v % 16;
        text[digits] = (v % 16) >= 10 ? (v % 16) - 10 + 'a' : '0' + (v % 16);
        v /= 16;
    }
    return write_len;
}

_INLINE_ s64 u64_to_text_hex_padding(u64 v, char *text, s64 holds)
{
    s64 myhold = holds;
    while (--myhold >= 0)
    {
        s64 rem = v % 16;
        text[myhold] = rem >= 10 ? rem - 10 + 'a' : '0' + rem;
        v /= 16;
    }
    return holds;
}

#endif //# __INT_XOS_DEFINITION_HPP__ ends
