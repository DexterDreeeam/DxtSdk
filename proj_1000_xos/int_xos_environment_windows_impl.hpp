/* ********* * ********* * ********* * ********* * *********
 *
 * int_xos_environment_windows.impl
 *
 * proj: proj_1000_xos
 * desc: Windows OS environment function interface nested implementations
 * autr: dexterdreeeam
 * date: 20200828
 * tips: \
 *
 ********* * ********* * ********* * ********* * ********* */

#pragma warning (push)
#pragma warning (disable : 6011)
#pragma warning (disable : 28182)
#pragma warning (disable : 4244)
#pragma warning (disable : 4551)

 _INLINE_ s32 atom_increment(s32 volatile &x)
{
    return windows_ns::InterlockedIncrement(&x);
}

_INLINE_ s64 atom_increment(s64 volatile &x)
{
    return windows_ns::InterlockedIncrement64(&x);
}

_INLINE_ s32 atom_decrement(s32 volatile &x)
{
    return windows_ns::InterlockedDecrement(&x);
}

_INLINE_ s64 atom_decrement(s64 volatile &x)
{
    return windows_ns::InterlockedDecrement64(&x);
}

_INLINE_ s32 atom_exchange(s32 volatile &x, s32 replace)
{
    return windows_ns::InterlockedExchange(&x, replace);
}

_INLINE_ s64 atom_exchange(s64 volatile &x, s64 replace)
{
    return windows_ns::InterlockedExchange64(&x, replace);
}

_INLINE_ void *atom_exchange(void *volatile &x, void *replace)
{
    return windows_ns::InterlockedExchangePointer(&x, replace);
}

_INLINE_ s32 atom_compare_exchange(s32 volatile &x, s32 compare, s32 replace)
{
    return windows_ns::InterlockedCompareExchange(&x, replace, compare);
}

_INLINE_ s64 atom_compare_exchange(s64 volatile &x, s64 compare, s64 replace)
{
    return windows_ns::InterlockedCompareExchange64(&x, replace, compare);
}

_INLINE_ void *atom_compare_exchange(void *volatile &x, void *compare, void *replace)
{
    return windows_ns::InterlockedCompareExchangePointer(&x, replace, compare);
}

_INLINE_ void yield()
{
    windows_ns::SwitchToThread();
}

_INLINE_ u64 random(u64 mod)
{
    return windows_ns::rand() % (mod);
}

_INLINE_ void *memory_alloc(u64 sz)
{
    void *p = reinterpret_cast<void*>(windows_ns::malloc(sz));
    assert(p);
    return p;
}

_INLINE_ void *memory_alloc_zero(u64 sz)
{
    void *p = reinterpret_cast<void*>(windows_ns::malloc(sz));
    assert(p);
    windows_ns::memset(p, 0, sz);
    return p;
}

_INLINE_ void memory_free(void *addr)
{
    assert(addr);
    windows_ns::free(addr);
}

_INLINE_ void memory_set(void *addr, u8 val, u64 sz)
{
    windows_ns::memset(addr, val, sz);
}

_INLINE_ void memory_copy(const void *src, void *dst, u64 sz)
{
    windows_ns::memcpy(dst, src, sz);
}

_INLINE_ void *memory_alloc_copy(const void *src, u64 alloc_sz, u64 copy_sz)
{
    assert(alloc_sz >= copy_sz);
    void *p = memory_alloc(alloc_sz);
    assert(p);
    memory_copy(src, p, copy_sz);
    return p;
}

_INLINE_ void memory_barrier(void)
{
    windows_ns::MemoryBarrier;
}

struct thrd_windows_cb_input
{
    thrd_windows_cb_input(Callback_Func *f, void *p) : fn(f), param(p) {}
    Callback_Func *fn;
    void *param;
};

unsigned long __stdcall thrd_windows_cb(void *p)
{
    auto *input = (thrd_windows_cb_input *)p;
    (input->fn)(input->param);
    delete input;
    return 0;
}

_INLINE_ thrd thrd_create(Callback_Func *fn, void *param)
{
    assert(fn);
    auto *input = new thrd_windows_cb_input(fn, param);
    return windows_ns::CreateThread(NULL, 0, thrd_windows_cb, input, 0, NULL);
}

_INLINE_ u64 thrd_myid()
{
    return static_cast<u64>(windows_ns::GetCurrentThreadId());
}

#pragma warning (push)
#pragma warning (disable : 6258)

_INLINE_ void thrd_enforce_exit(thrd td)
{
    assert(td);
    windows_ns::TerminateThread(td, 0);
}

#pragma warning (pop)

_INLINE_ void thrd_wait_exit(thrd td)
{
    assert(td);
    windows_ns::WaitForSingleObject(td, INFINITE);
}

_INLINE_ void thrd_destroy(thrd td)
{
    assert(td);
    windows_ns::CloseHandle(td);
}

_INLINE_ void tick_sleep(u64 ms)
{
    windows_ns::Sleep(ms);
}

_INLINE_ u64 tick_count()
{
    return windows_ns::GetTickCount64();
}

_INLINE_ u64 tick_record(u64 rec)
{
    static u64 myrec = 0;
    return rec == 0 ? myrec : (myrec = rec);
}

_INLINE_ void tick_start()
{
    tick_record(tick_count());
}

_INLINE_ u64 tick_elapse()
{
    assert_info(tick_record(0), "call tick_start() first before tick_elapse()");
    return tick_count() - tick_record(0);
}

_INLINE_ void  tick_elapse_print()
{
    print("Time elapse is: %llums.\n", tick_elapse());
}

_INLINE_ lock lock_create(void)
{
    return windows_ns::CreateMutex(NULL, FALSE, NULL);
}

typedef unsigned long DWORD;

_INLINE_ RET lock_try_get(lock lk)
{
    assert(lk);
    return windows_ns::WaitForSingleObject(lk, 0) == WAIT_OBJECT_0 ? RET_SUCCESS : RET_FAILED;
}

_INLINE_ void lock_wait_get(lock lk)
{
    assert(lk);
    windows_ns::WaitForSingleObject(lk, INFINITE);
}

_INLINE_ void lock_put(lock lk)
{
    assert(lk);
    windows_ns::ReleaseMutex(lk);
}

_INLINE_ void lock_destroy(lock lk)
{
    assert(lk);
    windows_ns::CloseHandle(lk);
}

_INLINE_ spin spin_create(void)
{
    return new s64(0);
}

_INLINE_ RET spin_try_get(spin sp)
{
    return atom_exchange(*reinterpret_cast<volatile s64*>(sp), 1LL) == 0 ? RET_SUCCESS : RET_FAILED;
}

_INLINE_ void spin_wait_get(spin sp)
{
    while (spin_try_get(sp) == RET_FAILED)
    {
        ;
    }
}

_INLINE_ void spin_put(spin sp)
{
    *reinterpret_cast<volatile s64*>(sp) = 0;
}

_INLINE_ void spin_destroy(spin sp)
{
    delete sp;
}

_INLINE_ evnt evnt_create(void)
{
    return windows_ns::CreateEvent(NULL, FALSE, NULL, NULL);
}

_INLINE_ void evnt_set(evnt ev)
{
    assert(ev);
    windows_ns::SetEvent(ev);
}

_INLINE_ void evnt_wait(evnt ev)
{
    assert(ev);
    windows_ns::WaitForSingleObject(ev, INFINITE);
}

_INLINE_ void evnt_destroy(evnt ev)
{
    assert(ev);
    windows_ns::CloseHandle(ev);
}

struct timr_cb_execute_desc
{
    timr_cb_execute_desc(Callback_Func *f, void *p) : fn(f), param(p), my_handle(0) {}
    Callback_Func *const fn;
    void *param;
    volatile thrd my_handle;
};

static void timr_execute(void *p)
{
    auto *execute_desc = reinterpret_cast<timr_cb_execute_desc*>(p);
    (execute_desc->fn)(execute_desc->param);
    while (!execute_desc->my_handle)
    {
        ;
    }
    thrd_destroy(execute_desc->my_handle);
    delete execute_desc;
}

struct timr_cb_desc
{
    timr_cb_desc(Callback_Func *f) : fn(f), oplock(spin_create()), running_thread(0), running(false), param(nullptr), delay(0) {}
    ~timr_cb_desc() { spin_destroy(oplock); }
    Callback_Func *const fn;
    const spin oplock;
    thrd running_thread;
    boole running;
    void *param;
    u64 delay;
};

static void timr_cb(void *p)
{
    auto *desc = reinterpret_cast<volatile timr_cb_desc*>(p);
    auto *func = desc->fn;
    void *param = desc->param;
    spin sp = desc->oplock;
    u64 delay = desc->delay;
    desc->running = true;
    spin_put(sp);

    tick_sleep(delay);

    spin_wait_get(sp);
    auto *execute_desc = new timr_cb_execute_desc(func, param);
    execute_desc->my_handle = thrd_create(timr_execute, execute_desc);
    desc->running = false;
    spin_put(sp);
}

_INLINE_ timr timr_create(Callback_Func *fn)
{
    assert(fn);
    auto *desc = new timr_cb_desc(fn);
    return reinterpret_cast<timr>(desc);
}

_INLINE_ void timr_trigger(timr tm, void *param, u64 ms)
{
    assert(tm);
    auto *desc = reinterpret_cast<timr_cb_desc*>(tm);
    spin_wait_get(desc->oplock);
    if (desc->running)
    {
        desc->running = false;
        thrd_enforce_exit(desc->running_thread);
    }
    if (desc->running_thread)
    {
        thrd td = desc->running_thread;
        desc->running_thread = 0;
        thrd_destroy(td);
    }
    memory_barrier();
    desc->param = param;
    desc->delay = ms;
    desc->running_thread = thrd_create(timr_cb, desc);
}

_INLINE_ void timr_destroy(timr tm)
{
    assert(tm);
    auto *desc = reinterpret_cast<timr_cb_desc*>(tm);
    spin_wait_get(desc->oplock);
    if (desc->running)
    {
        desc->running = false;
        thrd_enforce_exit(desc->running_thread);
    }
    if (desc->running_thread)
    {
        thrd td = desc->running_thread;
        desc->running_thread = 0;
        thrd_destroy(td);
    }
    spin_put(desc->oplock);
    delete reinterpret_cast<timr_cb_desc*>(tm);
}

_INLINE_ date date_query()
{
    date rst = {};
    windows_ns::SYSTEMTIME sys;
    windows_ns::GetLocalTime(&sys);
    rst.year = sys.wYear;
    rst.month = sys.wMonth;
    rst.day = sys.wDay;
    rst.week_day = sys.wDayOfWeek;
    rst.hour = sys.wHour;
    rst.minute = sys.wMinute;
    rst.second = sys.wSecond;
    rst.millisec = sys.wMilliseconds;
    return rst;
}

_INLINE_ outf output_file_create(const char *path)
{
    char path_buf[512] = {};
    s64 len = str_len(path);
    assert(len < 512);
    memory_copy(path, path_buf, len);
    s64 last_inexist_directory_idx = 0;
    s64 idx = len - 1;
    windows_ns::WIN32_FIND_DATAA FindFileData;
    while (idx >= 0)
    {
        if (path_buf[idx] == '/')
        {
            path_buf[idx] = 0;
            windows_ns::HANDLE hFind = windows_ns::FindFirstFileA(path_buf, &FindFileData);
            path_buf[idx] = '/';
            if (hFind != (windows_ns::HANDLE)(windows_ns::LONG_PTR)-1)
            {
                //# not INVALID_HANDLE_VALUE
                windows_ns::FindClose(hFind);
                last_inexist_directory_idx = idx;
                break;
            }
        }
        --idx;
    }
    assert(last_inexist_directory_idx);
    while (last_inexist_directory_idx < len)
    {
        idx = last_inexist_directory_idx + 1;
        while (idx < len && path_buf[idx] != '/')
        {
            ++idx;
        }
        if (idx >= len)
        {
            break;
        }
        path_buf[idx] = 0;
        if (!windows_ns::CreateDirectoryA(path_buf, nullptr))
        {
            assert(0);
        }
        path_buf[idx] = '/';
        last_inexist_directory_idx = idx;
    }
    outf f = windows_ns::CreateFileA(
        path, STANDARD_RIGHTS_WRITE | FILE_APPEND_DATA, FILE_SHARE_WRITE, nullptr,
        OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    return f;
}

_INLINE_ boole output_file_write(outf f, const char *content)
{
    if (windows_ns::WriteFile(f, content, str_len(content), nullptr, nullptr))
    {
        return boole_true;
    }
    else
    {
        return boole_false;
    }
}

_INLINE_ boole output_file_write(outf f, const char *content, s64 write_len)
{
    if (windows_ns::WriteFile(f, content, write_len, nullptr, nullptr))
    {
        return boole_true;
    }
    else
    {
        return boole_false;
    }
}

_INLINE_ boole output_file_destroy(outf f)
{
    windows_ns::FlushFileBuffers(f);
    if (windows_ns::CloseHandle(f))
    {
        return boole_true;
    }
    else
    {
        return boole_false;
    }
}

_INLINE_ inpf input_file_create(const char *path)
{
    inpf f = windows_ns::CreateFileA(
        path, FILE_GENERIC_READ, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    assert(f);
    return f;
}

_INLINE_ s64 input_file_read(inpf f, void *buf, s64 want_read)
{
    u32 actual_read = 0;
    if (windows_ns::ReadFile(f, buf, want_read, &actual_read, nullptr) == 0)
    {
        assert(0);
    }
    return actual_read;
}

_INLINE_ boole input_file_destroy(inpf f)
{
    if (windows_ns::CloseHandle(f))
    {
        return boole_true;
    }
    else
    {
        return boole_false;
    }
}

_INLINE_ boole delete_file(const char *path)
{
    if (windows_ns::DeleteFileA(path))
    {
        return boole_true;
    }
    else
    {
        return boole_false;
    }
}

#pragma warning (pop)
