/* ********* * ********* * ********* * ********* * *********
 *
 * int_xos_new.hpp
 *
 * proj: proj_1000_xos
 * desc: basic new operator
 * autr: dexterdreeeam
 * date: 20200907
 * tips: \
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_XOS_NEW_HPP__)
#define __INT_XOS_NEW_HPP__

void *operator new(size_t sz)
{
    return memory_alloc(sz);
}

void operator delete(void *ptr)
{
    memory_free(ptr);
}

void *operator new[](size_t sz)
{
    return memory_alloc(sz);
}

void operator delete[](void *ptr)
{
    memory_free(ptr);
}

void *operator new(size_t sz, void *ptr)
{
    return ptr;
}

void *operator new[](size_t sz, void *ptr)
{
    return ptr;
}

template<typename Ty>
constexpr auto right_value_type(Ty &e) noexcept -> Ty&&
{
    return static_cast<Ty&&>(e);
}

#endif //# __INT_BASIC_NEW_HPP__ ends
__INT_XOS_NEW_HPP__