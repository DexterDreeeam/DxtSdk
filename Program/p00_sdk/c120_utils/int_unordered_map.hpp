/* ********* * ********* * ********* * ********* * *********
 *
 * int_unordered_map.hpp
 *
 * proj: proj_00_sdk_component_120_utils
 * desc: unordered_map container
 * autr: dexterdreeeam
 * date: 20200902
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_UNORDERED_MAP_HPP__)
#define __INT_UNORDERED_MAP_HPP__

#include "int_basic_hash.hpp"
#include "int_basic_hashmap.hpp"

namespace std
{

template<typename Key_Ty, typename Val_Ty>
class unordered_map : protected std_hashmap::hashmap<Key_Ty, Val_Ty>
{
    using Self_Ty = unordered_map<Key_Ty, Val_Ty>;
    using Base_Ty = std_hashmap::hashmap<Key_Ty, Val_Ty>;
    using Node_Ty = typename Base_Ty::Node_Ty;

    using Iter_Ty = typename Base_Ty::Iter_Ty;
    using Ritr_Ty = typename Base_Ty::Ritr_Ty;
    using cIter_Ty = typename Base_Ty::cIter_Ty;
    using cRitr_Ty = typename Base_Ty::cRitr_Ty;

public:
    unordered_map() :
        Base_Ty()
    {}

    unordered_map(const Self_Ty &rhs) :
        Base_Ty(static_cast<const Base_Ty&>(rhs))
    {}

    unordered_map(Self_Ty &&rhs) noexcept :
        Base_Ty(static_cast<Base_Ty&&>(rhs))
    {}

    ~unordered_map() noexcept = default;

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
        u64 hs = Hash(k);
        return Base_Ty::_peek_node(k, hs) ? 1 : 0;
    }

    Val_Ty &operator [](const Key_Ty &k) noexcept
    {
        u64 hs = Hash(k);
        Node_Ty *nod = (Node_Ty*)Base_Ty::_check_insert(k, hs);
        return nod->myval();
    }

    void insert(const Key_Ty &k) noexcept
    {
        u64 hs = Hash(k);
        Base_Ty::_check_insert(k, hs);
    }

    void insert(const Key_Ty &k, const Val_Ty &v) noexcept
    {
        u64 hs = Hash(k);
        Base_Ty::_check_insert(k, v, hs);
    }

    void insert(const Key_Ty &k, Val_Ty &&v) noexcept
    {
        u64 hs = Hash(k);
        Base_Ty::_check_insert(k, v, hs);
    }

    void insert(const pair<Key_Ty, Val_Ty> &pr) noexcept
    {
        u64 hs = Hash(pr.first);
        Base_Ty::_check_insert(pr.first, pr.second, hs);
    }

    void insert(pair<Key_Ty, Val_Ty> &&pr) noexcept
    {
        u64 hs = Hash(pr.first);
        Base_Ty::_check_insert(pr.first, right_value_type(pr.second), hs);
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
        return Base_Ty::_erase_iterator(itr);
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

#endif //# __INT_UNORDERED_MAP_HPP__ ends
