/* ********* * ********* * ********* * ********* * *********
 *
 * int_stack.hpp
 *
 * proj: proj_00_sdk_component_120_utils
 * desc: stack container
 * autr: dexterdreeeam
 * date: 20200902
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_STACK_HPP__)
#define __INT_STACK_HPP__

#include "int_vector.hpp"

namespace std
{

template<typename Ty>
class stack
{
    using Self_Ty = stack<Ty>;

public:
    stack() :
        vec()
    {}

    template<typename ...Args>
    stack(Args...args) :
        vec(args...)
    {}

    stack(const Self_Ty &rhs) :
        vec(rhs.vec)
    {}

    stack(Self_Ty &&rhs) noexcept :
        vec(right_value_type(rhs.vec))
    {}

    ~stack() noexcept
    {}

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        vec = rhs.vec;
        return *this;
    }

    Self_Ty &operator =(Self_Ty &&rhs) noexcept
    {
        vec = right_value_type(rhs.vec);
        return *this;
    }

    s64 size() const noexcept
    {
        return vec.size();
    }

    void push(const Ty &e) noexcept
    {
        vec.push_back(e);
    }

    void push(Ty &&e) noexcept
    {
        vec.push_back(right_value_type(e));
    }

    template<typename ...Args>
    void push(Args...args) noexcept
    {
        vec.push_back(args...);
    }

    void pop() noexcept
    {
        assert(size() > 0);
        vec.pop_back();
    }

    Ty &top() noexcept
    {
        assert(size() > 0);
        return vec.back();
    }

    const Ty &top() const noexcept
    {
        assert(vec.size() > 0);
        return vec.back();
    }

    typename vector<Ty>::Iter_Ty begin() noexcept
    {
        return vec.begin();
    }

    typename vector<Ty>::Iter_Ty end() noexcept
    {
        return vec.end();
    }

private:
    vector<Ty> vec;
};

}

#endif //# __INT_STACK_HPP__ ends
