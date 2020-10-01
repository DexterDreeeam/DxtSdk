/* ********* * ********* * ********* * ********* * *********
 *
 * int_pair.hpp
 *
 * proj: proj_00_sdk_component_120_utils
 * desc: pair structure
 * autr: dexterdreeeam
 * date: 20200912
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_PAIR_HPP__)
#define __INT_PAIR_HPP__

namespace std
{

template<typename Ty1, typename Ty2>
class pair
{
    using Self_Ty = pair<Ty1, Ty2>;

public:
    pair() :
        first(),
        second()
    {}

    pair(const Ty1 &e1, const Ty2 &e2) :
        first(e1),
        second(e2)
    {}

    pair(Ty1 &&e1, Ty2 &&e2) :
        first(e1),
        second(e2)
    {}

    pair(const Ty1 &e1) :
        first(e1),
        second()
    {}

    pair(Ty1 &&e1) :
        first(e1),
        second()
    {}

    pair(const Self_Ty &rhs) :
        first(rhs.first),
        second(rhs.second)
    {}

    pair(Self_Ty &&rhs) :
        first(right_value_type(rhs.first)),
        second(right_value_type(rhs.second))
    {}

    template<typename Ty3, typename Ty4>
    pair(const Ty3 &e1, const Ty4 &e2) :
        first(e1),
        second(e2)
    {}

    template<typename Ty3>
    pair(const Ty3 &e1) :
        first(e1),
        second()
    {}

    template<typename Ty3, typename Ty4>
    pair(const pair<Ty3, Ty4> &rhs) :
        first(rhs.first),
        second(rhs.second)
    {}

    template<typename Ty3, typename Ty4>
    pair(const pair<const Ty3, Ty4> &rhs) :
        first(rhs.first),
        second(rhs.second)
    {}

    template<typename Ty3, typename Ty4>
    pair(const pair<Ty3, const Ty4> &rhs) :
        first(rhs.first),
        second(rhs.second)
    {}

    template<typename Ty3, typename Ty4>
    pair(const pair<const Ty3, const Ty4> &rhs) :
        first(rhs.first),
        second(rhs.second)
    {}

    ~pair() noexcept
    {}

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        first = rhs.first;
        second = rhs.second;
        return *this;
    }

    Self_Ty &operator =(Self_Ty &&rhs) noexcept
    {
        first = right_value_type(rhs.first);
        second = right_value_type(rhs.second);
        return *this;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return first == rhs.first && second == rhs.second;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return first != rhs.first || second != rhs.second;
    }

public:
    Ty1 first;
    Ty2 second;
};

template<typename Ty1, typename Ty2>
_INLINE_ pair<Ty1, Ty2> make_pair(const Ty1 &e1, const Ty2 &e2) noexcept
{
    return pair<Ty1, Ty2>(e1, e2);
}

template<typename Ty1, typename Ty2>
_INLINE_ pair<Ty1, Ty2> make_pair(Ty1 &&e1, Ty2 &&e2) noexcept
{
    return pair<Ty1, Ty2>(e1, e2);
}

}

#endif //# __INT_PAIR_HPP__ ends
