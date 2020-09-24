/* ********* * ********* * ********* * ********* * *********
 *
 * int_triple.hpp
 *
 * proj: proj_2000_utils
 * desc: triple structure
 * autr: dexterdreeeam
 * date: 20200916
 * tips: same to pair
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_TRIPLE_HPP__)
#define __INT_TRIPLE_HPP__

namespace std
{

template<typename Ty1, typename Ty2, typename Ty3>
class triple
{
    using Self_Ty = triple<Ty1, Ty2, Ty3>;

public:
    triple() :
        first(),
        second(),
        third()
    {}

    triple(const Ty1 &e1, const Ty2 &e2, const Ty3 &e3) :
        first(e1),
        second(e2),
        third(e3)
    {}

    triple(Ty1 &&e1, Ty2 &&e2, Ty3 &&e3) noexcept :
        first(e1),
        second(e2),
        third(e3)
    {}

    triple(const Ty1 &e1) :
        first(e1),
        second(),
        third()
    {}

    triple(Ty1 &&e1) noexcept :
        first(e1),
        second(),
        third()
    {}

    triple(const Self_Ty &rhs) :
        first(rhs.first),
        second(rhs.second),
        third(rhs.third)
    {}

    triple(Self_Ty &&rhs) noexcept :
        first(right_value_type(rhs.first)),
        second(right_value_type(rhs.second)),
        third(right_value_type(rhs.third))
    {}

    ~triple() noexcept
    {}

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        first = rhs.first;
        second = rhs.second;
        third = rhs.third;
        return *this;
    }

    Self_Ty &operator =(Self_Ty &&rhs) noexcept
    {
        first = right_value_type(rhs.first);
        second = right_value_type(rhs.second);
        third = right_value_type(rhs.third);
        return *this;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return first == rhs.first && second == rhs.second && third == rhs.third;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return first != rhs.first || second != rhs.second || third != rhs.third;
    }

public:
    Ty1 first;
    Ty2 second;
    Ty3 third;
};

}

#endif //# __INT_TRIPLE_HPP__ ends
