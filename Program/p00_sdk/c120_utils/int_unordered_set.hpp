/* ********* * ********* * ********* * ********* * *********
 *
 * int_unordered_set.hpp
 *
 * proj: proj_00_sdk_component_120_utils
 * desc: unordered_set container
 * autr: dexterdreeeam
 * date: 20200902
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_UNORDERED_SET_HPP__)
#define __INT_UNORDERED_SET_HPP__

#include "int_basic_hashmap.hpp"

namespace std
{

template<typename Key_Ty>
class unordered_set : protected std_hashmap::hashmap<Key_Ty>
{
    using Self_Ty = unordered_set<Key_Ty>;
    using Base_Ty = std_hashmap::hashmap<Key_Ty>;
    using Node_Ty = typename Base_Ty::Node_Ty;

    using Iter_Ty = typename Base_Ty::Iter_Ty;
    using Ritr_Ty = typename Base_Ty::Ritr_Ty;
    using cIter_Ty = typename Base_Ty::cIter_Ty;
    using cRitr_Ty = typename Base_Ty::cRitr_Ty;

public:
    unordered_set() :
        Base_Ty()
    {}

    unordered_set(const Self_Ty &rhs) :
        Base_Ty(static_cast<const Base_Ty&>(rhs))
    {}

    unordered_set(Self_Ty &&rhs) noexcept :
        Base_Ty(static_cast<Base_Ty&&>(rhs))
    {}

    ~unordered_set() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        Base_Ty::operator =(static_cast<const Base_Ty&>(rhs));
        return *this;
    }

    Self_Ty &operator =(Self_Ty &&rhs) noexcept
    {
        Base_Ty::operator =(static_cast<Base_Ty&&>(rhs));
        return *this;
    }

    void clear() noexcept
    {
        Base_Ty::_clear();
    }

    s64 size() const noexcept
    {
        return Base_Ty::_size();
    }

    s64 count(const Key_Ty &k) const noexcept
    {
        return Base_Ty::_peek_node(k) ? 1 : 0;
    }

    void insert(const Key_Ty &k) noexcept
    {
        u64 hs = Hash(k);
        Base_Ty::_check_insert(k, hs);
    }

    Iter_Ty find(const Key_Ty &k) noexcept
    {
        u64 hs = Hash(k);
        return Base_Ty::_find(k, hs);
    }

    bool erase(const Key_Ty &k) noexcept
    {
        u64 hs = Hash(k);
        return Base_Ty::_check_erase(k, hs);
    }

    void erase(Iter_Ty itr) noexcept
    {
        Base_Ty::_erase_iterator(itr);
    }

    Iter_Ty begin() const noexcept
    {
        return Base_Ty::_begin();
    }

    Iter_Ty end() const noexcept
    {
        return Base_Ty::_end();
    }

    Ritr_Ty rbegin() const noexcept
    {
        return Base_Ty::_rbegin();
    }

    Ritr_Ty rend() const noexcept
    {
        return Base_Ty::_rend();
    }

    cIter_Ty cbegin() const noexcept
    {
        return Base_Ty::_cbegin();
    }

    cIter_Ty cend() const noexcept
    {
        return Base_Ty::_cend();
    }

    cRitr_Ty crbegin() const noexcept
    {
        return Base_Ty::_crbegin();
    }

    cRitr_Ty crend() const noexcept
    {
        return Base_Ty::_crend();
    }
};

}

#endif //# __INT_UNORDERED_SET_HPP__ ends
