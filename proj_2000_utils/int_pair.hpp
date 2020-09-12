/* ********* * ********* * ********* * ********* * *********
 *
 * int_pair.hpp
 *
 * proj: proj_2000_utils
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

    pair(const Self_Ty &rhs) :
        first(rhs.first),
        second(rhs.second)
    {}

    pair(Self_Ty &&rhs) :
        first(right_value_type(rhs.first)),
        second(right_value_type(rhs.second))
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

}

#endif //# __INT_PAIR_HPP__ ends
