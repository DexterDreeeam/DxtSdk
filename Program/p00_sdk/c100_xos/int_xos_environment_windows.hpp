/* ********* * ********* * ********* * ********* * *********
 *
 * int_xos_environment_windows.hpp
 *
 * proj: proj_00_sdk_component_100_xos
 * desc: Windows OS environment configuration
 * autr: dexterdreeeam
 * date: 20200810
 * tips: \
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_XOS_ENVIRONMENT_WINDOWS_HPP__)
#define __INT_XOS_ENVIRONMENT_WINDOWS_HPP__

#include "int_xos_definition.hpp"

namespace windows_ns
{

#include <Windows.h>

#define ASSERT_EXCEPTION_CODE (0x09090909L)

#if DEBUG_LEVEL >= DEBUG_LEVEL_CALIBRATION_CHECK_ALLINPUT

    #include <stdio.h>
    #include <stdarg.h>
    #define print(...) windows_ns::printf(__VA_ARGS__)

    template<typename JudgeTy>
    _INLINE_ void dxt_assert(const JudgeTy &exp, const char *s, const char *file, s64 line)
    {
        if (!!!(exp))
        {
            print("[ERROR] Assert Failed. Condition '%s' in file: %s at line: %lld\n", s, file, line);
            throw (ASSERT_EXCEPTION_CODE);
        }
    }
    template<typename JudgeTy>
    _INLINE_ void dxt_assert(const JudgeTy &exp, const char *s, const char *info, const char *file, s64 line)
    {
        if (!!!(exp))
        {
            print("[ERROR] Assert Failed. Condition '%s', Info '%s' in file: %s at line: %lld\n", s, info, file, line);
            throw (ASSERT_EXCEPTION_CODE);
        }
    }

    //# assert check input parameter
    #define assert(exp) windows_ns::dxt_assert(exp, #exp, __FUNCTION__, __LINE__)
    #define assert_info(exp,info) windows_ns::dxt_assert(exp, #exp, info, __FUNCTION__, __LINE__)

#else

    #define print(...)
    #define assert(exp) ((void)0)
    #define assert_info(exp, info) ((void)0)

#endif

#include <stdlib.h>

}

typedef                u64  hndl;
typedef windows_ns::HANDLE  thrd;
typedef windows_ns::HANDLE  lock;
typedef windows_ns::HANDLE  evnt;
typedef windows_ns::HANDLE  outf;
typedef windows_ns::HANDLE  inpf;
typedef       volatile s64 *spin;
typedef               hndl  timr;
typedef void (Callback_Func)(void *param);

typedef struct
{
    s32 year;
    s32 month;
    s32 day;
    s32 week_day;
    s32 hour;
    s32 minute;
    s32 second;
    s32 millisec;
} date;

_INLINE_ s32   atom_increment(s32 volatile &x);
_INLINE_ s64   atom_increment(s64 volatile &x);
_INLINE_ s32   atom_decrement(s32 volatile &x);
_INLINE_ s64   atom_decrement(s64 volatile &x);
_INLINE_ s32   atom_exchange(s32 volatile &x, s32 replace);
_INLINE_ s64   atom_exchange(s64 volatile &x, s64 replace);
_INLINE_ void *atom_exchange(void *volatile &x, void *replace);
_INLINE_ s32   atom_compare_exchange(s32 volatile &x, s32 compare, s32 replace);
_INLINE_ s64   atom_compare_exchange(s64 volatile &x, s64 compare, s64 replace);
_INLINE_ void *atom_compare_exchange(void *volatile &x, void *compare, void *replace);

_INLINE_ void  yield();
_INLINE_ u64   random(u64 mod);
_INLINE_ void *memory_alloc(u64 sz);
_INLINE_ void *memory_alloc_zero(u64 sz);
_INLINE_ void  memory_free(void *addr);
_INLINE_ void  memory_set(void *addr, u8 val, u64 sz);
_INLINE_ void  memory_copy(const void *src, void *dst, u64 sz);
_INLINE_ void *memory_alloc_copy(const void *src, u64 alloc_sz, u64 copy_sz);
_INLINE_ void  memory_barrier(void);

_INLINE_ thrd  thrd_create(Callback_Func *fn, void *param);
_INLINE_ u64   thrd_myid();
_INLINE_ void  thrd_enforce_exit(thrd td);
_INLINE_ void  thrd_wait_exit(thrd td);
_INLINE_ void  thrd_destroy(thrd td);

_INLINE_ void  tick_sleep(u64 ms);
_INLINE_ void  tick_start();
_INLINE_ u64   tick_elapse();
_INLINE_ void  tick_elapse_print();

_INLINE_ lock  lock_create(void);
_INLINE_ RET   lock_try_get(lock lk);
_INLINE_ void  lock_wait_get(lock lk);
_INLINE_ void  lock_put(lock lk);
_INLINE_ void  lock_destroy(lock lk);

_INLINE_ spin  spin_create(void);
_INLINE_ RET   spin_try_get(spin sp);
_INLINE_ void  spin_wait_get(spin sp);
_INLINE_ void  spin_put(spin sp);
_INLINE_ void  spin_destroy(spin sp);

_INLINE_ evnt  evnt_create(void);
_INLINE_ void  evnt_set(evnt ev);
_INLINE_ void  evnt_wait(evnt ev);
_INLINE_ void  evnt_destroy(evnt ev);

_INLINE_ timr  timr_create(Callback_Func *fn);
_INLINE_ void  timr_trigger(timr tm, void *param, u64 ms);
_INLINE_ void  timr_destroy(timr tm);

_INLINE_ date  date_query();

_INLINE_ outf  output_file_create(const char *path);
_INLINE_ boole output_file_write(outf f, const char *content);
_INLINE_ boole output_file_write(outf f, const char *content, s64 write_len);
_INLINE_ boole output_file_destroy(outf f);

_INLINE_ inpf  input_file_create(const char *path);
_INLINE_ s64   input_file_read(inpf f, void *buf, s64 want_read);
_INLINE_ boole input_file_destroy(inpf f);

_INLINE_ boole delete_file(const char *path);

#include "int_xos_environment_windows_impl.hpp"

#endif //# __INT_XOS_ENVIRONMENT_WINDOWS_HPP__ ends
