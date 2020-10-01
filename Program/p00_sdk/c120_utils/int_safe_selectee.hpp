/* ********* * ********* * ********* * ********* * *********
 *
 * int_safe_selectee.hpp
 *
 * proj: proj_00_sdk_component_120_utils
 * desc: thread-safe item select container
 * autr: dexterdreeeam
 * date: 20200926
 * tips: select one idle item to work with multi-thread-safety
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_SAFE_SELECTEE_HPP__)
#define __INT_SAFE_SELECTEE_HPP__

namespace std
{

namespace std_safe_selectee
{

constexpr s64 safe_selectee_layer(u64 cap)
{
    s64 current_cap = 1LL;
    s64 lay = 1LL;
    while (current_cap < cap)
    {
        ++lay;
        current_cap = current_cap << 1;
    }
    return lay;
}

constexpr s64 safe_selectee_length(u64 cap)
{
    s64 lay = safe_selectee_layer(cap);
    return (1LL << lay) - 1;
}

constexpr s64 safe_selectee_last_layer_head(u64 cap)
{
    s64 lay = safe_selectee_layer(cap);
    return (1LL << (lay - 1)) - 1;
}

s64 safe_selectee_myleft(s64 idx)
{
    return (idx << 1) + 1;
}

s64 safe_selectee_myright(s64 idx)
{
    return (idx << 1) + 2;
}

s64 safe_selectee_myparent(s64 idx)
{
    return idx > 0 ? ((idx - 1) >> 1) : -1;
}

template<typename Ty>
class safe_selectee_node
{
public:
    safe_selectee_node() :
        signal(0),
        ptr(nullptr)
    {}

    ~safe_selectee_node()
    {
        if (ptr)
        {
            ptr->~Ty();
            memory_free(ptr);
            ptr = nullptr;
        }
    }

public:
    volatile s64 signal;
    Ty  *ptr;
};

}

template<typename Ty, u64 Cap, bool InitSignal>
class safe_selectee
{
    using Node_Ty = std_safe_selectee::safe_selectee_node<Ty>;

public:
    safe_selectee() :
        data()
    {
        s64 idx = std_safe_selectee::safe_selectee_last_layer_head(Cap);
        for (; idx < _length(); ++idx)
        {
            data[idx].ptr = (Ty*)memory_alloc(sizeof(Ty));
            new (data[idx].ptr) Ty();
            data[idx].signal = InitSignal;
        }
        if (InitSignal)
        {
            idx = std_safe_selectee::safe_selectee_last_layer_head(Cap);
            while (--idx >= 0)
            {
                s64 left = std_safe_selectee::safe_selectee_myleft(idx);
                s64 right = std_safe_selectee::safe_selectee_myright(idx);
                data[idx].signal = data[left].signal + data[right].signal;
            }
        }
    }

    ~safe_selectee()
    {
    }

    Ty &at(s64 ext_idx)
    {
        assert(ext_idx >= 0 && ext_idx < Cap);
        return *data[_ext_to_int(ext_idx)].ptr;
    }

    s64 get()
    {
        if (atom_decrement(data[0].signal) < 0)
        {
            atom_increment(data[0].signal);
            return -1;
        }
        s64 idx = 0;
        while (idx < std_safe_selectee::safe_selectee_last_layer_head(Cap))
        {
            s64 left = std_safe_selectee::safe_selectee_myleft(idx);
            s64 right = std_safe_selectee::safe_selectee_myright(idx);
            assert(left < _length() && right < _length());
            if (atom_decrement(data[left].signal) >= 0)
            {
                idx = left;
                continue;
            }
            else
            {
                atom_increment(data[left].signal);
            }
            if (atom_decrement(data[right].signal) >= 0)
            {
                idx = right;
                continue;
            }
            else
            {
                atom_increment(data[right].signal);
            }
            assert(0);
        }
        return _int_to_ext(idx);
    }

    void put(s64 ext_idx)
    {
        assert(ext_idx >= 0 && ext_idx < Cap);
        s64 idx = _ext_to_int(ext_idx);
        if (atom_increment(data[idx].signal) > 1)
        {
            //# error instance, put one idx twice, return immediately
            atom_decrement(data[idx].signal);
            assert(0);
            return;
        }
        idx = std_safe_selectee::safe_selectee_myparent(idx);
        while (idx >= 0)
        {
            atom_increment(data[idx].signal);
            idx = std_safe_selectee::safe_selectee_myparent(idx);
        }
    }

private:
    s64 _length() const
    {
        return std_safe_selectee::safe_selectee_length(Cap);
    }

    s64 _ext_to_int(s64 idx)
    {
        return std_safe_selectee::safe_selectee_last_layer_head(Cap) + idx;
    }

    s64 _int_to_ext(s64 idx)
    {
        return idx - std_safe_selectee::safe_selectee_last_layer_head(Cap);
    }

private:
    Node_Ty data[std_safe_selectee::safe_selectee_length(Cap)];
};

}

#endif //# __INT_SAFE_SELECTEE_HPP__ ends
