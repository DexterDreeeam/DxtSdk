/* ********* * ********* * ********* * ********* * *********
 *
 * int_basic_new.hpp
 *
 * proj: proj_2000_utils
 * desc: basic new operator
 * autr: dexterdreeeam
 * date: 20200907
 * tips: \
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_BASIC_NEW_HPP__)
#define __INT_BASIC_NEW_HPP__

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

#endif //# __INT_BASIC_NEW_HPP__ ends
