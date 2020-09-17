/* ********* * ********* * ********* * ********* * *********
 *
 * int_string.hpp
 *
 * proj: proj_2000_utils
 * desc: string container
 * autr: dexterdreeeam
 * date: 20200902
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_STRING_HPP__)
#define __INT_STRING_HPP__

START_NS(std)

class string;
class string_iter;
class string_ritr;
class string_const_iter;
class string_const_ritr;

class string_iter
{
    friend class string;
    using Self_Ty = string_iter;

public:
    string_iter() :
        ptr(nullptr)
    {}

    string_iter(const Self_Ty &rhs) :
        ptr(rhs.ptr)
    {}

    ~string_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        ptr = rhs.ptr;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        ptr = pointer_convert(ptr, 1, char*);
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        ptr = pointer_convert(ptr, -1, char*);
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(ptr);
        ptr = pointer_convert(ptr, 1, char*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(ptr);
        ptr = pointer_convert(ptr, -1, char*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return ptr == rhs.ptr;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return ptr != rhs.ptr;
    }

    char &operator *() noexcept
    {
        return *ptr;
    }

    s64 operator -(const Self_Ty &rhs) const noexcept
    {
        s64 diff = reinterpret_cast<s64>(ptr) - reinterpret_cast<s64>(rhs.ptr);
        return diff;
    }

private:
    string_iter(char *p) :
        ptr(p)
    {}

private:
    char *ptr;
};

class string_ritr
{
    friend class string;
    using Self_Ty = string_ritr;

public:
    string_ritr() :
        ptr(nullptr)
    {}

    string_ritr(const Self_Ty &rhs) :
        ptr(rhs.ptr)
    {}

    ~string_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        ptr = rhs.ptr;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        ptr = pointer_convert(ptr, -1, char*);
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        ptr = pointer_convert(ptr, 1, char*);
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(ptr);
        ptr = pointer_convert(ptr, -1, char*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(ptr);
        ptr = pointer_convert(ptr, 1, char*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return ptr == rhs.ptr;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return ptr != rhs.ptr;
    }

    char &operator *() noexcept
    {
        return *ptr;
    }

    s64 operator -(const Self_Ty &rhs) const noexcept
    {
        s64 diff = reinterpret_cast<s64>(ptr) - reinterpret_cast<s64>(rhs.ptr);
        return diff;
    }

private:
    string_ritr(char *p) :
        ptr(p)
    {}

private:
    char *ptr;
};

class string_const_iter
{
    friend class string;
    using Self_Ty = string_const_iter;

public:
    string_const_iter() :
        ptr(nullptr)
    {}

    string_const_iter(const Self_Ty &rhs) :
        ptr(rhs.ptr)
    {}

    ~string_const_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        ptr = rhs.ptr;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        ptr = pointer_convert(ptr, 1, char*);
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        ptr = pointer_convert(ptr, -1, char*);
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(ptr);
        ptr = pointer_convert(ptr, 1, char*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(ptr);
        ptr = pointer_convert(ptr, -1, char*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return ptr == rhs.ptr;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return ptr != rhs.ptr;
    }

    const char &operator *() const noexcept
    {
        return *ptr;
    }

    s64 operator -(const Self_Ty &rhs) const noexcept
    {
        s64 diff = reinterpret_cast<s64>(ptr) - reinterpret_cast<s64>(rhs.ptr);
        return diff;
    }

private:
    string_const_iter(char *p) :
        ptr(p)
    {}

private:
    char *ptr;
};

class string_const_ritr
{
    friend class string;
    using Self_Ty = string_const_ritr;

public:
    string_const_ritr() :
        ptr(nullptr)
    {}

    string_const_ritr(const Self_Ty &rhs) :
        ptr(rhs.ptr)
    {}

    ~string_const_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        ptr = rhs.ptr;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        ptr = pointer_convert(ptr, -1, char*);
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        ptr = pointer_convert(ptr, 1, char*);
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(ptr);
        ptr = pointer_convert(ptr, -1, char*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(ptr);
        ptr = pointer_convert(ptr, 1, char*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return ptr == rhs.ptr;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return ptr != rhs.ptr;
    }

    const char &operator *() const noexcept
    {
        return *ptr;
    }

    s64 operator -(const Self_Ty &rhs) const noexcept
    {
        s64 diff = reinterpret_cast<s64>(ptr) - reinterpret_cast<s64>(rhs.ptr);
        return diff;
    }

private:
    string_const_ritr(char *p) :
        ptr(p)
    {}

private:
    char *ptr;
};

const s64 string_unit_extent = 4LL;
const s64 string_cap_max = 1LL << 30;

class string
{
    friend class string_iter;
    friend class string_ritr;
    friend class string_const_iter;
    friend class string_const_ritr;

    friend string operator +(char c, const string &s) noexcept;
    friend string operator +(const char *cstr, const string &s) noexcept;
    friend bool operator ==(const char *cstr, const string &s) noexcept;
    friend bool operator !=(const char *cstr, const string &s) noexcept;
    friend bool operator <(const char *cstr, const string &s) noexcept;
    friend bool operator >(const char *cstr, const string &s) noexcept;
    friend bool operator <=(const char *cstr, const string &s) noexcept;
    friend bool operator >=(const char *cstr, const string &s) noexcept;

public:
    string() noexcept:
        cap(0),
        len(0),
        ch(nullptr)
    {
        assert(_validation());
    }

    string(s64 vol) :
        cap(_ceil_align(vol + 1)),
        len(0),
        ch((char*)memory_alloc(cap))
    {}

    string(s64 vol, char init_char) :
        cap(_ceil_align(vol + 1)),
        len(vol),
        ch((char*)memory_alloc(cap))
    {
        memory_set(ch, init_char, vol);
        _set_tail_zero();
    }

    string(const char *s)
    {
        s64 s_len = str_len(s);
        cap = _ceil_align(s_len + 1);
        len = s_len;
        ch = (char*)memory_alloc_copy(s, cap, len + 1);
        assert(_validation());
    }

    string(const string &rhs) :
        cap(_ceil_align(rhs.len + 1)),
        len(rhs.len),
        ch((char*)memory_alloc_copy(rhs.ch, cap, len + 1))
    {
        assert(_validation());
    }

    string(string &&rhs) noexcept:
        cap(rhs.cap),
        len(rhs.len),
        ch(rhs.ch)
    {
        rhs.cap = 0;
        rhs.len = 0;
        rhs.ch = nullptr;
        assert(_validation());
    }

    ~string() noexcept
    {
        assert(_validation());
        clear();
    }

    string &operator =(const string &rhs) noexcept
    {
        clear();
        cap = _ceil_align(rhs.len + 1);
        len = rhs.len;
        ch = (char*)memory_alloc_copy(rhs.ch, cap, len + 1);
        assert(_validation());
    }

    string &operator =(string &&rhs) noexcept
    {
        clear();
        cap = rhs.cap;
        len = rhs.len;
        ch = rhs.ch;
        rhs.cap = 0;
        rhs.len = 0;
        rhs.ch = nullptr;
        assert(_validation());
    }

    bool operator ==(const string &rhs) const noexcept
    {
        return str_equal(ch, rhs.ch);
    }

    bool operator !=(const string &rhs) const noexcept
    {
        return !str_equal(ch, rhs.ch);
    }

    bool operator <(const string &rhs) const noexcept
    {
        s64 idx = 0;
        while (ch[idx] == rhs.ch[idx])
        {
            if (ch[idx] != 0)
            {
                ++idx;
            }
            else
            {
                return false;
            }
        }
        return ch[idx] < rhs.ch[idx];
    }

    bool operator <(const char *cstr) const noexcept
    {
        s64 idx = 0;
        while (ch[idx] == cstr[idx])
        {
            if (ch[idx] != 0)
            {
                ++idx;
            }
            else
            {
                return false;
            }
        }
        return ch[idx] < cstr[idx];
    }

    bool operator >(const string &rhs) const noexcept
    {
        s64 idx = 0;
        while (ch[idx] == rhs.ch[idx])
        {
            if (ch[idx] != 0)
            {
                ++idx;
            }
            else
            {
                return false;
            }
        }
        return ch[idx] > rhs.ch[idx];
    }

    bool operator >(const char *cstr) const noexcept
    {
        s64 idx = 0;
        while (ch[idx] == cstr[idx])
        {
            if (ch[idx] != 0)
            {
                ++idx;
            }
            else
            {
                return false;
            }
        }
        return ch[idx] > cstr[idx];
    }

    bool operator <=(const string &rhs) const noexcept
    {
        return !this->operator >(rhs);
    }

    bool operator <=(const char *cstr) const noexcept
    {
        return !this->operator >(cstr);
    }

    bool operator >=(const string &rhs) const noexcept
    {
        return !this->operator <(rhs);
    }

    bool operator >=(const char *cstr) const noexcept
    {
        return !this->operator <(cstr);
    }

    char &operator [](s64 pos) noexcept
    {
        assert(_validation());
        return ch[pos];
    }

    string operator +(const string &rhs) const noexcept
    {
        string ret(len + rhs.len);
        memory_copy(ch, ret.ch, len);
        memory_copy(rhs.ch, pointer_convert(ret.ch, len, void*), rhs.len + 1);
        ret.len = len + rhs.len;
        return ret;
    }

    string operator +(const char *cstr) const noexcept
    {
        s64 cstr_len = str_len(cstr);
        string ret(len + cstr_len);
        memory_copy(ch, ret.ch, len);
        memory_copy(cstr, pointer_convert(ret.ch, len, void*), cstr_len + 1);
        ret.len = len + cstr_len;
        return ret;
    }

    string operator +(char c) noexcept
    {
        string ret(len + 1);
        memory_copy(ch, ret.ch, len);
        ret.ch[len] = c;
        ret.ch[len + 1] = 0;
        ret.len = len + 1;
        return ret;
    }

    string &operator +=(char c) noexcept
    {
        assert(_validation());
        _push_back(c);
        return *this;
    }

    string &operator +=(const string &rhs) noexcept
    {
        assert(_validation());
        _push_back(rhs);
        return *this;
    }

    string &operator +=(const char *cstr) noexcept
    {
        assert(_validation());
        _push_back(cstr);
        return *this;
    }

    void clear()
    {
        assert(_validation());
        cap = 0;
        len = 0;
        if (ch)
        {
            memory_free(ch);
            ch = nullptr;
        }
    }

    s64 size() const noexcept
    {
        assert(_validation());
        return len;
    }

    bool empty() const noexcept
    {
        assert(_validation());
        return len == 0;
    }

    char *data() noexcept
    {
        assert(_validation());
        return ch;
    }

    const char *data() const noexcept
    {
        assert(_validation());
        return ch;
    }

    const char *c_str() const noexcept
    {
        assert(_validation());
        return ch;
    }

    void swap(string &rhs) noexcept
    {
        assert(_validation());
        ::swap(cap, rhs.cap);
        ::swap(len, rhs.len);
        ::swap(ch, rhs.ch);
    }

    char &front() noexcept
    {
        assert(len > 0);
        return ch[0];
    }

    const char &front() const noexcept
    {
        assert(len > 0);
        return ch[0];
    }

    char &back() noexcept
    {
        assert(len > 0);
        return ch[len - 1];
    }

    const char &back() const noexcept
    {
        assert(len > 0);
        return ch[len - 1];
    }

    void push_back(char c) noexcept
    {
        assert(_validation());
        _push_back(c);
    }

    void pop_back() noexcept
    {
        assert(_validation());
        assert(len > 0);
        --len;
        _set_tail_zero();
    }

    void pop_back(s64 pop_number) noexcept
    {
        assert(_validation());
        assert(len >= pop_number);
        len -= pop_number;
        _set_tail_zero();
    }

    string_iter begin() noexcept
    {
        return string_iter(ch);
    }

    string_iter end() noexcept
    {
        return string_iter(ch + len);
    }

    string_ritr rbegin() noexcept
    {
        return string_ritr(ch + len - 1);
    }

    string_ritr rend() noexcept
    {
        return string_ritr(ch - 1);
    }

    string_const_iter cbegin() noexcept
    {
        return string_const_iter(ch);
    }

    string_const_iter cend() noexcept
    {
        return string_const_iter(ch + len);
    }

    string_const_ritr crbegin() noexcept
    {
        return string_const_ritr(ch + len - 1);
    }

    string_const_ritr crend() noexcept
    {
        return string_const_ritr(ch - 1);
    }

private:
    static s64 _ceil_align(s64 len) noexcept
    {
        return ceil(len, string_unit_extent);
    }

    bool _validation() const noexcept
    {
        if (cap == 0)
        {
            if (len != 0 || ch)
            {
                assert_info(0, "Invalid string internal state.");
                return false;
            }
        }
        else if (ch == nullptr)
        {
            assert_info(0, "Invalid string internal state.");
            return false;
        }
        else if (len >= cap)
        {
            assert_info(0, "Invalid string internal state.");
            return false;
        }
        else if (ch[len] != 0)
        {
            assert_info(0, "String tail charactor should be '\\0'");
            return false;
        }
        else
        {
            for (s64 i = 0; i < len; ++i)
            {
                if (ch[i] == 0 || (ch[i] & (1 << 7)))
                {
                    assert_info(0, "String every charactor should not be '\\0' and in range of '\\1' to '\\127'");
                    return false;
                }
            }
        }
        return true;
    }

    void _set_tail_zero() noexcept
    {
        assert(len < cap);
        ch[len] = 0;
    }

    void _need_space(s64 add) noexcept
    {
        if (len + add < cap)
        {
            return;
        }
        while (len + add >= cap)
        {
            cap = cap == 0 ? string_unit_extent : (cap << 1);
            assert(cap <= string_cap_max);
        }
        char *new_ch = (char*)memory_alloc_copy(ch, cap, len);
        if (ch)
        {
            memory_free(ch);
        }
        ch = new_ch;
        _set_tail_zero();
    }

    void _push_back(char c) noexcept
    {
        _need_space(1);
        ch[len] = c;
        ++len;
        _set_tail_zero();
    }

    void _push_back(const string &rhs) noexcept
    {
        _need_space(rhs.len);
        memory_copy(rhs.ch, &ch[len], rhs.len + 1);
        len += rhs.len;
    }

    void _push_back(const char *cstr) noexcept
    {
        s64 cstr_len = str_len(cstr);
        _need_space(cstr_len);
        memory_copy(cstr, &ch[len], cstr_len + 1);
        len += cstr_len;
    }

private:
    s64 cap;
    s64 len;
    char *ch;
};

string operator +(char c, const string &s) noexcept
{
    string ret(s.len + 1);
    ret.ch[0] = c;
    memory_copy(s.ch, &ret.ch[1], s.len + 1);
    ret.len = s.len + 1;
    return ret;
}

string operator +(const char *cstr, const string &s) noexcept
{
    s64 cstr_len = str_len(cstr);
    string ret(cstr_len + s.len);
    memory_copy(cstr, ret.ch, cstr_len);
    memory_copy(s.ch, pointer_convert(ret.ch, cstr_len, void*), s.len + 1);
    ret.len = cstr_len + s.len;
    return ret;
}

bool operator ==(const char *cstr, const string &s) noexcept
{
    return str_equal(cstr, s.ch);
}

bool operator !=(const char *cstr, const string &s) noexcept
{
    return !str_equal(cstr, s.ch);
}

bool operator <(const char *cstr, const string &s) noexcept
{
    s64 idx = 0;
    while (cstr[idx] == s.ch[idx])
    {
        if (cstr[idx] != 0)
        {
            ++idx;
        }
        else
        {
            return false;
        }
    }
    return cstr[idx] < s.ch[idx];
}

bool operator >(const char *cstr, const string &s) noexcept
{
    s64 idx = 0;
    while (cstr[idx] == s.ch[idx])
    {
        if (cstr[idx] != 0)
        {
            ++idx;
        }
        else
        {
            return false;
        }
    }
    return cstr[idx] > s.ch[idx];
}

bool operator <=(const char *cstr, const string &s) noexcept
{
    return !operator >(cstr, s);
}

bool operator >=(const char *cstr, const string &s) noexcept
{
    return !operator <(cstr, s);
}

END_NS(std)

#endif //# __INT_STRING_HPP__ ends
