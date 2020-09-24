/* ********* * ********* * ********* * ********* * *********
 *
 * int_vector.hpp
 *
 * proj: proj_2000_utils
 * desc: vector container
 * autr: dexterdreeeam
 * date: 20200902
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_VECTOR_HPP__)
#define __INT_VECTOR_HPP__

namespace std
{

template<typename Ty>
class vector;

namespace std_vector
{

template<typename Ctnr_Ty>
class vector_iter;

template<typename Ctnr_Ty>
class vector_ritr;

template<typename Ctnr_Ty>
class vector_const_iter;

template<typename Ctnr_Ty>
class vector_const_ritr;


template<typename Ty>
class vector_iter<vector<Ty>>
{
    friend class vector<Ty>;

    using Container_Ty = vector<Ty>;
    using Self_Ty = vector_iter<Container_Ty>;
    using Data_Ty = Ty;

public:
    vector_iter() :
        data(nullptr)
    {}

    vector_iter(const Self_Ty &rhs) :
        data(rhs.data)
    {}

    ~vector_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        data = rhs.data;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        data = pointer_convert(data, sizeof(Ty), Ty*);
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        data = pointer_convert(data, -(s64)sizeof(Ty), Ty*);
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, sizeof(Ty), Ty*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, -(s64)sizeof(Ty), Ty*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return data == rhs.data;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return data != rhs.data;
    }

    Data_Ty *operator ->() noexcept
    {
        return data;
    }

    Data_Ty &operator *() noexcept
    {
        return *data;
    }

    s64 operator -(const Self_Ty &rhs) const noexcept
    {
        s64 diff = reinterpret_cast<s64>(data) - reinterpret_cast<s64>(rhs.data);
        return diff / sizeof(Data_Ty);
    }

private:
    vector_iter(Data_Ty *ptr) :
        data(ptr)
    {}

    Data_Ty *data;
};

template<typename Ty>
class vector_ritr<vector<Ty>>
{
    friend class vector<Ty>;

    using Container_Ty = vector<Ty>;
    using Self_Ty = vector_ritr<Container_Ty>;
    using Data_Ty = Ty;

public:
    vector_ritr() :
        data(nullptr)
    {}

    vector_ritr(const Self_Ty &rhs) :
        data(rhs.data)
    {}

    ~vector_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        data = rhs.data;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        data = pointer_convert(data, -(s64)sizeof(Ty), Ty*);
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        data = pointer_convert(data, sizeof(Ty), Ty*);
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, -(s64)sizeof(Ty), Ty*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, sizeof(Ty), Ty*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs)
    {
        return data == rhs.data;
    }

    bool operator !=(const Self_Ty &rhs)
    {
        return data != rhs.data;
    }

    Data_Ty *operator ->()
    {
        return data;
    }

    Data_Ty &operator *()
    {
        return *data;
    }

private:
    vector_ritr(Data_Ty *ptr) :
        data(ptr)
    {}

    Data_Ty *data;
};

template<typename Ty>
class vector_const_iter<vector<Ty>>
{
    friend class vector<Ty>;

    using Container_Ty = vector<Ty>;
    using Self_Ty = vector_const_iter<Container_Ty>;
    using Data_Ty = Ty;

public:
    vector_const_iter() :
        data(nullptr)
    {}

    vector_const_iter(const Self_Ty &rhs) :
        data(rhs.data)
    {}

    ~vector_const_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        data = rhs.data;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        data = pointer_convert(data, sizeof(Ty), Ty*);
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        data = pointer_convert(data, -(s64)sizeof(Ty), Ty*);
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, sizeof(Ty), Ty*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, -(s64)sizeof(Ty), Ty*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs)
    {
        return data == rhs.data;
    }

    bool operator !=(const Self_Ty &rhs)
    {
        return data != rhs.data;
    }

    const Data_Ty *operator ->()
    {
        return data;
    }

    const Data_Ty &operator *()
    {
        return *data;
    }

private:
    vector_const_iter(const Data_Ty *ptr) :
        data(ptr)
    {}

    const Data_Ty *data;
};

template<typename Ty>
class vector_const_ritr<vector<Ty>>
{
    friend class vector<Ty>;

    using Container_Ty = vector<Ty>;
    using Self_Ty = vector_const_ritr<Container_Ty>;
    using Data_Ty = Ty;

public:
    vector_const_ritr() :
        data(nullptr)
    {}

    vector_const_ritr(const Self_Ty &rhs) :
        data(rhs.data)
    {}

    ~vector_const_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        data = rhs.data;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        data = pointer_convert(data, -(s64)sizeof(Ty), Ty*);
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        data = pointer_convert(data, sizeof(Ty), Ty*);
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, -(s64)sizeof(Ty), Ty*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, sizeof(Ty), Ty*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs)
    {
        return data == rhs.data;
    }

    bool operator !=(const Self_Ty &rhs)
    {
        return data != rhs.data;
    }

    const Data_Ty *operator ->()
    {
        return data;
    }

    const Data_Ty &operator *()
    {
        return *data;
    }

private:
    vector_const_ritr(const Data_Ty *ptr) :
        data(ptr)
    {}

    const Data_Ty *data;
};

}

const s64 vector_unit_extent = 4LL;
const s64 vector_cap_max = 1LL << 30;

template<typename Ty>
class stack;

template<typename Ty>
class vector
{
    friend class stack<Ty>;

    using Self_Ty = vector<Ty>;
    using Data_Ty = Ty;
    using Iter_Ty = std_vector::vector_iter<Self_Ty>;
    using Ritr_Ty = std_vector::vector_ritr<Self_Ty>;
    using cIter_Ty = std_vector::vector_const_iter<Self_Ty>;
    using cRitr_Ty = std_vector::vector_const_ritr<Self_Ty>;

    friend class std_vector::vector_iter<Self_Ty>;
    friend class std_vector::vector_ritr<Self_Ty>;
    friend class std_vector::vector_const_iter<Self_Ty>;
    friend class std_vector::vector_const_ritr<Self_Ty>;

public:
    vector() :
        elem(nullptr),
        cap(0),
        sz(0)
    {
        assert(sz >= 0 && sz <= cap);
    }

    template<typename ...Args>
    vector(Args...args) :
        elem((Ty*)memory_alloc(sizeof(Ty) * _ceil_align(sizeof...(args)))),
        cap(_ceil_align(sizeof...(args))),
        sz(sizeof...(args))
    {
        assert(sz >= 0 && sz <= cap);
        _construct_tuple(args...);
        assert(sz >= 0 && sz <= cap);
    }

    template<s64 ArraySz>
    vector(const array<Ty, ArraySz> &arr) :
        elem((Ty*)memory_alloc(sizeof(Ty) * _ceil_align(ArraySz))),
        cap(_ceil_align(ArraySz)),
        sz(ArraySz)
    {
        assert(sz >= 0 && sz <= cap);
        for (s64 i = 0; i < ArraySz; ++i)
        {
            new (&elem[i]) Ty(arr[i]);
        }
    }

    vector(const Self_Ty &rhs) :
        elem((Ty*)memory_alloc_copy(rhs.elem, sizeof(Ty) * _ceil_align(rhs.sz), sizeof(Ty) * rhs.sz)),
        cap(_ceil_align(rhs.sz)),
        sz(rhs.sz)
    {
        assert(sz >= 0 && sz <= cap);
    }

    vector(Self_Ty &&rhs) :
        elem(rhs.elem),
        cap(rhs.cap),
        sz(rhs.sz)
    {
        assert(sz >= 0 && sz <= cap);
        rhs.elem = nullptr;
        rhs.cap = 0;
        rhs.sz = 0;
    }

    ~vector() noexcept
    {
        assert(sz >= 0 && sz <= cap);
        _deconstruct();
    }

    template<s64 ArraySz>
    Self_Ty &operator =(const array<Ty, ArraySz> &arr)
    {
        assert(sz >= 0 && sz <= cap);
        _deconstruct();
        elem = (Ty*)memory_alloc(sizeof(Ty) * _ceil_align(ArraySz));
        cap = _ceil_align(ArraySz);
        sz = ArraySz;
        return *this;
    }

    Self_Ty &operator =(const Self_Ty &rhs)
    {
        assert(sz >= 0 && sz <= cap);
        _deconstruct();
        elem = (Ty*)memory_alloc_copy(rhs.elem, sizeof(Ty) * _ceil_align(rhs.sz), sizeof(Ty) * rhs.sz);
        cap = _ceil_align(rhs.sz);
        sz = rhs.sz;
        return *this;
    }

    Self_Ty &operator =(Self_Ty &&rhs) noexcept
    {
        assert(sz >= 0 && sz <= cap);
        _deconstruct();
        elem = (Ty*)memory_alloc_copy(rhs.elem, sizeof(Ty) * _ceil_align(rhs.sz), sizeof(Ty) * rhs.sz);
        cap = _ceil_align(rhs.sz);
        sz = rhs.sz;
        rhs.elem = nullptr;
        rhs.cap = 0;
        rhs.sz = 0;
        return *this;
    }

    Ty &operator [](s64 pos) noexcept
    {
        assert(sz > 0 && pos >= 0 && pos < sz && sz <= cap);
        return elem[pos];
    }

    const Ty &operator [](s64 pos) const noexcept
    {
        assert(sz > 0 && pos >= 0 && pos < sz && sz <= cap);
        return elem[pos];
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        assert(sz >= 0 && sz <= cap);
        if (this == &rhs)
        {
            return true;
        }
        if (sz != rhs.sz)
        {
            return false;
        }
        for (s64 i = 0, n = sz; i != n; ++i)
        {
            if (elem[i] != rhs.elem[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return !(*this == rhs);
    }

    Ty *data() noexcept
    {
        assert(sz > 0 && sz <= cap);
        return elem;
    }

    const Ty *data() const noexcept
    {
        assert(sz > 0 && sz <= cap);
        return elem;
    }

    s64 size() const noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return sz;
    }

    bool empty() const noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return sz == 0;
    }

    const s64 capacity() const noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return cap;
    }

    Ty &front() noexcept
    {
        assert(sz > 0 && sz <= cap);
        return elem[0];
    }

    const Ty &front() const noexcept
    {
        assert(sz > 0 && sz <= cap);
        return elem[0];
    }

    Ty &back() noexcept
    {
        assert(sz > 0 && sz <= cap);
        return elem[sz - 1];
    }

    const Ty &back() const noexcept
    {
        assert(sz > 0 && sz <= cap);
        return elem[sz - 1];
    }

    void push_back(const Ty &one) noexcept
    {
        assert(sz >= 0 && sz <= cap);
        _need_space(1);
        new (&elem[sz]) Ty(one);
        ++sz;
    }

    void push_back(Ty &&one) noexcept
    {
        assert(sz >= 0 && sz <= cap);
        _need_space(1);
        new (&elem[sz]) Ty(one);
        ++sz;
    }

    template<typename ...Args>
    void push_back(Args... args) noexcept
    {
        assert(sz >= 0 && sz <= cap);
        _need_space(sizeof...(args));
        _push_back_tuple(args...);
    }

    void pop_back() noexcept
    {
        assert(sz > 0 && sz <= cap);
        --sz;
        (&elem[sz])->~Ty();
    }

    template<typename ...Args>
    void insert(s64 pos, Args...args)
    {
        assert(pos >= 0 && pos <= sz);
        s64 add = sizeof...(args);
        s64 fore_sz = pos;
        s64 rear_sz = sz - pos;

        void *p_tobe_release = elem;
        while (sz + add > cap)
        {
            cap = cap == 0 ? vector_unit_extent : (cap << 1);
            assert(cap <= vector_cap_max);
        }
        elem = (Ty*)memory_alloc(sizeof(Ty) * cap);
        if (fore_sz)
        {
            memory_copy(p_tobe_release, elem, sizeof(Ty) * fore_sz);
        }
        sz = fore_sz;
        _push_back_tuple(args...);
        if (rear_sz)
        {
            memory_copy(pointer_convert(p_tobe_release, sizeof(Ty) * fore_sz, void*), pointer_convert(elem, sizeof(Ty) * sz, void*), sizeof(Ty) * rear_sz);
            sz += rear_sz;
        }
        if (p_tobe_release)
        {
            memory_free(p_tobe_release);
        }
    }

    void erase(s64 pos, s64 erase_cnt) noexcept
    {
        assert(sz >= 0 && sz <= cap);
        assert(pos >= 0 && pos < sz);
        assert(erase_cnt >= 0);
        s64 rear_sz = sz - pos - erase_cnt;
        s64 release_cnt = rear_sz >= 0 ? erase_cnt : sz - pos;
        sz -= release_cnt;
        for (s64 i = 0; i != release_cnt; ++i)
        {
            (&elem[pos + i])->~Ty();
        }
        if (rear_sz > 0)
        {
            memory_copy(&elem[pos + release_cnt], &elem[pos], sizeof(Ty) * rear_sz);
        }
    }

    void swap(Self_Ty &rhs) noexcept
    {
        assert(sz >= 0 && sz <= cap);
        assert(rhs.sz >= 0 && rhs.sz <= rhs.cap);
        Ty *tmp_p = elem;
        elem = rhs.elem;
        rhs.elem = tmp_p;

        s64 tmp = cap;
        cap = rhs.cap;
        rhs.cap = tmp;

        tmp = sz;
        sz = rhs.sz;
        rhs.sz = tmp;
    }

    void clear() noexcept
    {
        assert(sz >= 0 && sz <= cap);
        while (sz)
        {
            --sz;
            (&elem[sz])->~Ty();
        }
    }

    void resize(s64 new_sz, const Ty &val) noexcept
    {
        assert(sz >= 0 && sz <= cap);
        assert(new_sz >= 0);
        if (new_sz > sz)
        {
            _need_space(new_sz - sz);
            for (s64 i = 0, n = new_sz - sz; i != n; ++i)
            {
                new (&elem[sz]) Ty(val);
                ++sz;
            }
        }
        else
        {
            for (s64 i = 0, n = sz - new_sz; i != n; ++i)
            {
                --sz;
                (&elem[sz])->~Ty();
            }
        }
    }

    void swap(s64 pos1, s64 pos2) noexcept
    {
        assert(0 <= pos1 && pos1 < sz);
        assert(0 <= pos2 && pos2 < sz);
        u8 buf[sizeof(Ty)];
        memory_copy(pointer_convert(elem, sizeof(Ty) * pos1, void*), buf, sizeof(Ty));
        memory_copy(pointer_convert(elem, sizeof(Ty) * pos2, void*), pointer_convert(elem, sizeof(Ty) * pos1, void*), sizeof(Ty));
        memory_copy(buf, pointer_convert(elem, sizeof(Ty) * pos2, void*), sizeof(Ty));
    }

    Iter_Ty begin() noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return Iter_Ty(elem);
    }

    const cIter_Ty cbegin() const noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return cIter_Ty(elem);
    }

    Iter_Ty end() noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return Iter_Ty(pointer_convert(elem, sizeof(Ty) * sz, Ty*));
    }

    const cIter_Ty cend() const noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return cIter_Ty(pointer_convert(elem, sizeof(Ty) * sz, Ty*));
    }

    Ritr_Ty rbegin() noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return Ritr_Ty(pointer_convert(elem, sizeof(Ty) * (sz - 1), Ty*));
    }

    const cRitr_Ty crbegin() const noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return cRitr_Ty(pointer_convert(elem, sizeof(Ty) * (sz - 1), Ty*));
    }

    Ritr_Ty rend() noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return Ritr_Ty(pointer_convert(elem, -(s64)sizeof(Ty), Ty*));
    }

    cRitr_Ty crend() const noexcept
    {
        assert(sz >= 0 && sz <= cap);
        return cRitr_Ty(pointer_convert(elem, -(s64)sizeof(Ty), Ty*));
    }

    Iter_Ty find(const Ty &e)
    {
        Iter_Ty itr = begin();
        const Iter_Ty eitr = end();
        while (itr != eitr && *itr != e)
        {
            ++itr;
        }
        return itr;
    }

    template<typename Cmp_Op>
    void sort(s64 head_idx, s64 tail_idx, const Cmp_Op &op) noexcept
    {
        assert_info(0 <= head_idx && head_idx <= tail_idx && tail_idx < sz, "Sort() need valid index number.");
        _quick_sort(head_idx, tail_idx, op);
    }

    void sort(s64 head_idx, s64 tail_idx) noexcept
    {
        assert_info(0 <= head_idx && head_idx <= tail_idx && tail_idx < sz, "Sort() need valid index number.");
        sort(head_idx, tail_idx, _default_cmp_op);
    }

    template<typename Cmp_Op>
    void sort(const Cmp_Op &op) noexcept
    {
        if (sz == 0)
        {
            return;
        }
        sort(0, sz - 1, op);
    }

    void sort() noexcept
    {
        if (sz == 0)
        {
            return;
        }
        sort(0, sz - 1, _default_cmp_op);
    }

private:
    static s64 _ceil_align(s64 len) noexcept
    {
        return ceil(len, vector_unit_extent);
    }

    static bool _default_cmp_op(const Ty &e1, const Ty &e2) noexcept
    {
        return e1 < e2;
    }

    template<typename ...Args>
    void _construct_tuple(const Ty &first, Args...args)
    {
        new (&elem[sz - sizeof...(args) - 1]) Ty(first);
        _construct_tuple(args...);
    }

    template<typename ...Args>
    void _construct_tuple(Ty &&first, Args...args)
    {
        new (&elem[sz - sizeof...(args) - 1]) Ty(first);
        _construct_tuple(args...);
    }

    void _construct_tuple(const Ty &last)
    {
        new (&elem[sz - 1]) Ty(last);
    }

    void _construct_tuple(Ty &&last)
    {
        new (&elem[sz - 1]) Ty(last);
    }

    void _deconstruct() noexcept
    {
        assert(sz >= 0 && sz <= cap);
        if (elem)
        {
            while (sz)
            {
                --sz;
                (&elem[sz])->~Ty();
            }
            memory_free(elem);
            elem = nullptr;
        }
    }

    void _need_space(s64 add)
    {
        assert(sz <= cap);
        if (sz + add <= cap)
        {
            return;
        }
        void *p_tobe_release = elem;
        while (sz + add > cap)
        {
            cap = cap == 0 ? vector_unit_extent : (cap << 1);
            assert(cap <= vector_cap_max);
        }
        if (p_tobe_release)
        {
            elem = (Ty*)memory_alloc_copy(p_tobe_release, sizeof(Ty) * cap, sizeof(Ty) * sz);
            memory_free(p_tobe_release);
        }
        else
        {
            elem = (Ty*)memory_alloc(sizeof(Ty) * cap);
        }
    }

    template<typename ...Args>
    void _push_back_tuple(const Ty &first, Args...args) noexcept
    {
        new (&elem[sz]) Ty(first);
        ++sz;
        _push_back_tuple(args...);
    }

    void _push_back_tuple(const Ty &last) noexcept
    {
        new (&elem[sz]) Ty(last);
        ++sz;
    }

    template<typename ...Args>
    void _push_back_tuple(Ty &&first, Args...args) noexcept
    {
        new (&elem[sz]) Ty(first);
        ++sz;
        _push_back_tuple(args...);
    }

    void _push_back_tuple(Ty &&last) noexcept
    {
        new (&elem[sz]) Ty(last);
        ++sz;
    }

    template<typename Cmp_Op>
    void _quick_sort(s64 head_idx, s64 tail_idx, const Cmp_Op &op) noexcept
    {
        if (head_idx >= tail_idx)
        {
            return;
        }
        s64 idx = head_idx;
        s64 less_before_idx = head_idx;
        while (idx < tail_idx)
        {
            if (op(elem[idx], elem[tail_idx]))
            {
                swap(less_before_idx, idx);
                ++less_before_idx;
            }
            ++idx;
        }
        swap(less_before_idx, tail_idx);
        _quick_sort(head_idx, less_before_idx - 1, op);
        _quick_sort(less_before_idx + 1, tail_idx, op);
    }

private:
    Ty *elem;
    s64 cap;
    s64 sz;
};

}

#endif //# __INT_VECTOR_HPP__ ends
