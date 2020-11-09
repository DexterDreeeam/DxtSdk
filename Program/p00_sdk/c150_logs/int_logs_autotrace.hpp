/* ********* * ********* * ********* * ********* * *********
 *
 * int_logs_autotrace.hpp
 *
 * proj: proj_00_sdk_component_150_logs
 * desc: automatic function trace for tracking
 * autr: dexterdreeeam
 * date: 20200930
 * tips: function auto stack trace
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_LOGS_AUTOTRACE_HPP__)
#define __INT_LOGS_AUTOTRACE_HPP__

const s64 max_function_name_len = 63LL;

class auto_trace
{
public:
    auto_trace(const char *func_name) :
        start_time(tick_elapse())
    {
        s64 slen = str_len(func_name);
        slen = min(slen, max_function_name_len);
        memory_copy(func_name, name, slen);
        name[slen] = 0;
        log("%s+", name);
    }

    ~auto_trace() noexcept
    {
        u64 duration = tick_elapse() - start_time;
        log("%s- [%ullms]", name, duration);
    }

private:
    char name[max_function_name_len + 1];
    u64  start_time;
};

#if DEBUG_LEVEL >= DEBUG_LEVEL_CALIBRATION_LOG_CALLSTACK

#define AUTO_TRACE auto_trace __auto_trace__(__FUNCTION__)

#else

#define AUTO_TRACE ((void)0)

#endif

#endif //# __INT_LOGS_AUTOTRACE_HPP__ ends
