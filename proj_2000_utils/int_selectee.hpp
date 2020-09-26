/* ********* * ********* * ********* * ********* * *********
 *
 * int_selectee.hpp
 *
 * proj: proj_2000_utils
 * desc: thread-safe item select container
 * autr: dexterdreeeam
 * date: 20200926
 * tips: select one idle worker to work with multi-thread-safety
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_SELECTEE_HPP__)
#define __INT_SELECTEE_HPP__

#include "../proj_1000_xos/ext_xos_interface.hpp"

namespace std
{

namespace std_selectee
{

constexpr s64 selectee_layer(u64 cap)
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

constexpr s64 selectee_length(u64 cap)
{
    s64 lay = selectee_layer(cap);
    return (1LL << lay) - 1;
}

constexpr s64 selectee_last_layer_head(u64 cap)
{
    s64 lay = selectee_layer(cap);
    return (1LL << (lay - 1)) - 1;
}

s64 selectee_myleft(s64 idx)
{
    return (idx << 1) + 1;
}

s64 selectee_myright(s64 idx)
{
    return (idx << 1) + 2;
}

s64 selectee_myparent(s64 idx)
{
    return idx > 0 ? ((idx - 1) >> 1) : -1;
}

template<typename Ty>
class selectee_node
{
public:
    selectee_node() :
        idle(0),
        ptr(nullptr)
    {}

    ~selectee_node()
    {
        if (ptr)
        {
            ptr->~Ty();
            memory_free(ptr);
            ptr = nullptr;
        }
    }

public:
    volatile s64 idle;
    Ty  *ptr;
};

}

template<typename Ty, u64 Cap>
class selectee
{
    using Node_Ty = std_selectee::selectee_node<Ty>;

public:
    selectee() :
        data()
    {
        s64 idx = std_selectee::selectee_last_layer_head(Cap);
        for (; idx < _length(); ++idx)
        {
            data[idx].ptr = (Ty*)memory_alloc(sizeof(Ty));
            new (data[idx].ptr) Ty();
            ++data[idx].idle;
        }
        idx = std_selectee::selectee_last_layer_head(Cap);
        while (--idx >= 0)
        {
            s64 left = std_selectee::selectee_myleft(idx);
            s64 right = std_selectee::selectee_myright(idx);
            data[idx].idle = data[left].idle + data[right].idle;
        }
    }

    ~selectee()
    {
    }

    Ty &at(s64 ext_idx)
    {
        assert(ext_idx >= 0 && ext_idx < Cap);
        return *data[_ext_to_int(ext_idx)].ptr;
    }

    s64 get()
    {
        if (atom_decrement(data[0].idle) < 0)
        {
            atom_increment(data[0].idle);
            return -1;
        }
        s64 idx = 0;
        while (idx < std_selectee::selectee_last_layer_head(Cap))
        {
            s64 left = std_selectee::selectee_myleft(idx);
            s64 right = std_selectee::selectee_myright(idx);
            assert(left < _length() && right < _length());
            if (atom_decrement(data[left].idle) >= 0)
            {
                idx = left;
                continue;
            }
            else
            {
                atom_increment(data[left].idle);
            }
            if (atom_decrement(data[right].idle) >= 0)
            {
                idx = right;
                continue;
            }
            else
            {
                atom_increment(data[right].idle);
            }
            assert(0);
        }
        return _int_to_ext(idx);
    }

    void put(s64 ext_idx)
    {
        assert(ext_idx >= 0 && ext_idx < Cap);
        s64 idx = _ext_to_int(ext_idx);
        assert(data[idx].idle == 0 && data[idx].ptr);
        while (idx >= 0)
        {
            atom_increment(data[idx].idle);
            idx = std_selectee::selectee_myparent(idx);
        }
    }

private:
    s64 _length() const
    {
        return std_selectee::selectee_length(Cap);
    }

    s64 _ext_to_int(s64 idx)
    {
        return std_selectee::selectee_last_layer_head(Cap) + idx;
    }

    s64 _int_to_ext(s64 idx)
    {
        return idx - std_selectee::selectee_last_layer_head(Cap);
    }

private:
    Node_Ty data[std_selectee::selectee_length(Cap)];
};

}

#endif //# __INT_SELECTEE_HPP__ ends
