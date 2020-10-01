/* ********* * ********* * ********* * ********* * *********
 *
 * int_safe_queue.hpp
 *
 * proj: proj_00_sdk_component_120_utils
 * desc: thread-safe fifo queue
 * autr: dexterdreeeam
 * date: 20200927
 * tips: \
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_SAFE_QUEUE_HPP__)
#define __INT_SAFE_QUEUE_HPP__

namespace std
{

constexpr u64 ceil_pow2(u64 num)
{
    if ((num & (num - 1)) == 0)
    {
        return num;
    }
    u64 ret = 1ULL;
    while ((~ret + 1) & num)
    {
        ret = ret << 1;
    }
    return ret;
}

template<typename Ty, s64 Cap, s64 ExtremeThreadCnt = 8ULL>
class safe_queue
{
    struct token
    {
        token() :
            t(0)
        {}

        volatile s32 t;
    };

public:
    safe_queue() :
        tks(),
        head(0),
        tail(0)
    {
    }

    ~safe_queue()
    {
        clear();
    }

    bool enqueue(const Ty &in)
    {
        if (_overload())
        {
            return false;
        }
        u64 holder = atom_increment(*pointer_convert(&tail, 0, s64*)) - 1;
        new (_at(holder & _mask())) Ty(in);
        tks[holder & _mask()].t = 1;
        return true;
    }

    bool dequeue(Ty *out)
    {
        u64 holder = head;
        if (atom_compare_exchange(tks[holder & _mask()].t, 1, 0) == 1)
        {
            while ((holder & _mask()) != (head & _mask()))
            {
                yield();
            }
            new (out) Ty(*_at(holder & _mask()));
            ++head;
            _at(holder & _mask())->~Ty();
            return true;
        }
        else
        {
            return false;
        }
    }

    void clear()
    {
        while (head != tail)
        {
            _at(head & _mask())->~Ty();
            ++head;
        }
    }

private:
    bool _overload()
    {
        return (u64)tail - (u64)head >= (s64)_size() - (s64)ExtremeThreadCnt;
    }

    Ty *_at(s64 idx)
    {
        return pointer_convert(data, sizeof(Ty) * idx, Ty*);
    }

    s64 _size()
    {
        return ceil_pow2(Cap);
    }

    u64 _mask()
    {
        return (u64)_size() - 1;
    }

private:
    char data[sizeof(Ty) * ceil_pow2(Cap)];
    token tks[ceil_pow2(Cap)];
    u64 head;
    u64 tail;
};

}

#endif //# __INT_SAFE_QUEUE_HPP__ ends
