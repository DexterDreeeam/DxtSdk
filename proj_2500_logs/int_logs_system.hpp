/* ********* * ********* * ********* * ********* * *********
 *
 * ext_logs_system.hpp
 *
 * proj: proj_2500_logs
 * desc: common logs output function
 * autr: dexterdreeeam
 * date: 20200924
 * tips: \
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__EXT_LOGS_SYSTEM_HPP__)
#define __EXT_LOGS_SYSTEM_HPP__

namespace log_system_ns
{

const s64 worker_count = 8LL;

class log_system_worker
{

};

class log_system
{
    template<typename ...Args>
    friend _INLINE_ void _log(const char *fmt, Args...args);
    friend _INLINE_ void _log(const char *fmt);

    template<typename ...Args>
    friend _INLINE_ void _err(const char *fmt, Args...args);
    friend _INLINE_ void _err(const char *fmt);

public:
    log_system() :
        workers()
    {}

    ~log_system()
    {
        int k = 0;
    }

private:
    void write_log(const char *text, s64 text_len)
    {
        text;
    }

private:
    log_system_worker workers[worker_count];
};

_SELECTANY_ log_system global_log_system;

template<typename Ty>
_INLINE_ void parse_args(char arg_buf[16][16], s64 arg_idx, Ty a)
{
    memory_copy(&a, arg_buf[arg_idx], min(sizeof(Ty), 16));
}

template<typename Ty>
_INLINE_ void parse_args(char arg_buf[16][16], s64 arg_idx, Ty *a)
{
    memory_copy(&a, arg_buf[arg_idx], min(sizeof(Ty*), 16));
}

template<typename Ty, typename ...Args>
_INLINE_ void parse_args(char arg_buf[16][16], s64 arg_idx, Ty a, Args...args)
{
    memory_copy(&a, arg_buf[arg_idx], min(sizeof(Ty), 16));
    parse_args(arg_buf, arg_idx + 1, args...);
}

template<typename Ty, typename ...Args>
_INLINE_ void parse_args(char arg_buf[16][16], s64 arg_idx, Ty *a, Args...args)
{
    memory_copy(&a, arg_buf[arg_idx], min(sizeof(Ty*), 16));
    parse_args(arg_buf, arg_idx + 1, args...);
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
        memory_copy("2147483648", &text[1], 10);
        return 11;
    }
    s64 digits = 0;
    s32 num = v;
    while (num)
    {
        ++digits;
        num /= 10;
    }
    if (v < 0)
    {
        ++digits;
        text[0] = '-';
        v = -v;
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
        memory_copy("9223372036854775808", &text[1], 19);
        return 20;
    }
    s64 digits = 0;
    s64 num = v;
    while (num)
    {
        ++digits;
        num /= 10;
    }
    if (v < 0)
    {
        ++digits;
        text[0] = '-';
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

/*
 * %d    s32
 * %u    u32
 * %ll   s64
 * %ull  u64
 * %p    type*
 * %s    const char*
 */
template<typename ...Args>
_INLINE_ void _log(const char *fmt, Args...args)
{
    char output_buf[256];
    s64 output_len = 0;
    char arg_buf[16][16] = {};
    s64 arg_idx = 0;
    s64 len = str_len(fmt);
    s64 last = 0;
    s64 idx = 0;
    parse_args(arg_buf, 0, args...);
    while (last < len)
    {
        while (idx < len && fmt[idx] != '%')
        {
            ++idx;
        }
        memory_copy(fmt + last, output_buf + output_len, idx - last);
        output_len += idx - last;
        if (idx >= len)
        {
            break;
        }
        if (fmt[idx + 1] == 's')
        {
            //# string
            char *arg_cursor = arg_buf[arg_idx++];
            const char *cstr = *pointer_convert(arg_cursor, 0, const char**);
            memory_copy(cstr, output_buf + output_len, str_len(cstr));
            output_len += str_len(cstr);
            last = idx + 2;
            idx = last;
        }
        else if (fmt[idx + 1] == 'p')
        {
            //# pointer
            char *arg_cursor = arg_buf[arg_idx++];
            u64 v = *pointer_convert(arg_cursor, 0, u64*);
            output_len += u64_to_text_hex(v, output_buf + output_len);
            last = idx + 2;
            idx = last;
        }
        else if (fmt[idx + 1] == 'l' && fmt[idx + 2] == 'l')
        {
            //# s64
            char *arg_cursor = arg_buf[arg_idx++];
            s64 v = *pointer_convert(arg_cursor, 0, s64*);
            output_len += s64_to_text(v, output_buf + output_len);
            last = idx + 3;
            idx = last;
        }
        else if (fmt[idx + 1] == 'u' && fmt[idx + 2] == 'l' && fmt[idx + 3] == 'l')
        {
            //# u64
            char *arg_cursor = arg_buf[arg_idx++];
            u64 v = *pointer_convert(arg_cursor, 0, u64*);
            output_len += u64_to_text(v, output_buf + output_len);
            last = idx + 4;
            idx = last;
        }
        else if (fmt[idx + 1] == 'd')
        {
            //# s32
            char *arg_cursor = arg_buf[arg_idx++];
            s32 v = *pointer_convert(arg_cursor, 0, s32*);
            output_len += s32_to_text(v, output_buf + output_len);
            last = idx + 2;
            idx = last;
        }
        else if (fmt[idx + 1] == 'u')
        {
            //# u32
            char *arg_cursor = arg_buf[arg_idx++];
            u32 v = *pointer_convert(arg_cursor, 0, u32*);
            output_len += u32_to_text(v, output_buf + output_len);
            last = idx + 2;
            idx = last;
        }
        else
        {
            ++idx;
            continue;
        }
    }
    output_buf[output_len] = 0;
    global_log_system.write_log(output_buf, output_len);
}

_INLINE_ void _log(const char *fmt)
{
    global_log_system.write_log(fmt, str_len(fmt));
}

template<typename ...Args>
_INLINE_ void _err(const char *fmt, Args...args)
{
    char output_buf[256] = "[ERROR] ";
    s64 output_len = 8;
    char arg_buf[16][16] = {};
    s64 arg_idx = 0;
    s64 len = str_len(fmt);
    s64 last = 0;
    s64 idx = 0;
    parse_args(arg_buf, 0, args...);
    while (last < len)
    {
        while (idx < len && fmt[idx] != '%')
        {
            ++idx;
        }
        memory_copy(fmt + last, output_buf + output_len, idx - last);
        output_len += idx - last;
        if (idx >= len)
        {
            break;
        }
        if (fmt[idx + 1] == 's')
        {
            //# string
            char *arg_cursor = arg_buf[arg_idx++];
            const char *cstr = *pointer_convert(arg_cursor, 0, const char**);
            memory_copy(cstr, output_buf + output_len, str_len(cstr));
            output_len += str_len(cstr);
            last = idx + 2;
            idx = last;
        }
        else if (fmt[idx + 1] == 'p')
        {
            //# pointer
            char *arg_cursor = arg_buf[arg_idx++];
            u64 v = *pointer_convert(arg_cursor, 0, u64*);
            output_len += u64_to_text_hex(v, output_buf + output_len);
            last = idx + 2;
            idx = last;
        }
        else if (fmt[idx + 1] == 'l' && fmt[idx + 2] == 'l')
        {
            //# s64
            char *arg_cursor = arg_buf[arg_idx++];
            s64 v = *pointer_convert(arg_cursor, 0, s64*);
            output_len += s64_to_text(v, output_buf + output_len);
            last = idx + 3;
            idx = last;
        }
        else if (fmt[idx + 1] == 'u' && fmt[idx + 2] == 'l' && fmt[idx + 3] == 'l')
        {
            //# u64
            char *arg_cursor = arg_buf[arg_idx++];
            u64 v = *pointer_convert(arg_cursor, 0, u64*);
            output_len += u64_to_text(v, output_buf + output_len);
            last = idx + 4;
            idx = last;
        }
        else if (fmt[idx + 1] == 'd')
        {
            //# s32
            char *arg_cursor = arg_buf[arg_idx++];
            s32 v = *pointer_convert(arg_cursor, 0, s32*);
            output_len += s32_to_text(v, output_buf + output_len);
            last = idx + 2;
            idx = last;
        }
        else if (fmt[idx + 1] == 'u')
        {
            //# u32
            char *arg_cursor = arg_buf[arg_idx++];
            u32 v = *pointer_convert(arg_cursor, 0, u32*);
            output_len += u32_to_text(v, output_buf + output_len);
            last = idx + 2;
            idx = last;
        }
        else
        {
            ++idx;
            continue;
        }
    }
    output_buf[output_len] = 0;
    global_log_system.write_log(output_buf, output_len);
}

_INLINE_ void _err(const char *fmt)
{
    char output_buf[256] = "[ERROR] ";
    s64 output_len = 8;
    s64 strlen = str_len(fmt);
    memory_copy(fmt, output_buf + output_len, strlen);
    output_len += strlen;
    output_buf[output_len] = 0;
    global_log_system.write_log(output_buf, output_len);
}

}

template<typename ...Args>
_INLINE_ void log(Args...args)
{
    #if DEBUG_LEVEL >= DEBUG_LEVEL_CALIBRATION_LOG_NORM

    log_system_ns::_log(args...);

    #else

    args...;

    #endif
}


template<typename ...Args>
_INLINE_ void err(Args...args)
{
    #if DEBUG_LEVEL >= DEBUG_LEVEL_CALIBRATION_LOG_ERROR

    log_system_ns::_err(args...);

    #else

    args...;

    #endif
}

#endif //# __EXT_LOGS_SYSTEM_HPP__ ends
