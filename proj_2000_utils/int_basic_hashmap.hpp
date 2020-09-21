/* ********* * ********* * ********* * ********* * *********
 *
 * int_basic_hashmap.hpp
 *
 * proj: proj_2000_utils
 * desc: basic hashmap struct for other container
 * autr: dexterdreeeam
 * date: 20200902
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_BASIC_HASHMAP_HPP__)
#define __INT_BASIC_HASHMAP_HPP__

START_NS(std)

struct hashmap_dummy_type
{};

class hashmap_base_node;

template<typename Key_Ty, typename Val_Ty>
class hashmap_node;

template<typename Container_Ty>
class hashmap_base_iter;

template<typename Container_Ty>
class hashmap_iter;

template<typename Container_Ty>
class hashmap_ritr;

template<typename Container_Ty>
class hashmap_const_iter;

template<typename Container_Ty>
class hashmap_const_ritr;

template<typename Key_Ty, typename Val_Ty = hashmap_dummy_type>
class hashmap;

class hashmap_base_node
{
    template<typename Key_Ty, typename Val_Ty> friend class hashmap;
    template<typename Key_Ty> friend class unordered_set;
    template<typename Key_Ty, typename Val_Ty> friend class unordered_map;

protected:
    hashmap_base_node(u64 hs, hashmap_base_node *p, hashmap_base_node *n) :
        hash_val(hs),
        prev(p),
        next(n)
    {}

    ~hashmap_base_node() noexcept = default;

    u64 myhash() const noexcept
    {
        return hash_val;
    }

    hashmap_base_node *&myprev() noexcept
    {
        return prev;
    }

    hashmap_base_node *&mynext() noexcept
    {
        return next;
    }

private:
    u64 hash_val;
    hashmap_base_node *prev;
    hashmap_base_node *next;
};

template<typename Key_Ty>
class hashmap_node<Key_Ty, hashmap_dummy_type> : public hashmap_base_node
{
public:
    using Self_Ty = hashmap_node<Key_Ty, hashmap_dummy_type>;
    using NodeData_Ty = const Key_Ty;

public:
    hashmap_node(const Key_Ty &k, u64 hs, hashmap_base_node *p, hashmap_base_node *n) noexcept :
        hashmap_base_node(hs, p, n),
        key(k)
    {}

    hashmap_node(Key_Ty &&k, u64 hs, hashmap_base_node *p, hashmap_base_node *n) noexcept :
        hashmap_base_node(hs, p, n),
        key(k)
    {}

    ~hashmap_node() noexcept = default;

    const Key_Ty &mykey() const noexcept
    {
        return key;
    }

    const Key_Ty *mydata() noexcept
    {
        return &key;
    }

private:
    Key_Ty key;
};

template<typename Key_Ty, typename Val_Ty>
class hashmap_node : public hashmap_base_node
{
public:
    using Self_Ty = hashmap_node<Key_Ty, Val_Ty>;
    using NodeData_Ty = pair<const Key_Ty, Val_Ty>;

public:
    hashmap_node(const Key_Ty &k, u64 hs, hashmap_base_node *p, hashmap_base_node *n) noexcept :
        hashmap_base_node(hs, p, n),
        duo(k)
    {}

    hashmap_node(Key_Ty &&k, u64 hs, hashmap_base_node *p, hashmap_base_node *n) noexcept :
        hashmap_base_node(hs, p, n),
        duo(k)
    {}

    hashmap_node(const Key_Ty &k, const Val_Ty &v, u64 hs, hashmap_base_node *p, hashmap_base_node *n) noexcept :
        hashmap_base_node(hs, p, n),
        duo(k, v)
    {}

    hashmap_node(Key_Ty &&k, const Val_Ty &v, u64 hs, hashmap_base_node *p, hashmap_base_node *n) noexcept :
        hashmap_base_node(hs, p, n),
        duo(k, v)
    {}

    hashmap_node(const Key_Ty &k, Val_Ty &&v, u64 hs, hashmap_base_node *p, hashmap_base_node *n) noexcept :
        hashmap_base_node(hs, p, n),
        duo(k, v)
    {}

    hashmap_node(Key_Ty &&k, Val_Ty &&v, u64 hs, hashmap_base_node *p, hashmap_base_node *n) noexcept :
        hashmap_base_node(hs, p, n),
        duo(k, v)
    {}

    hashmap_node(const NodeData_Ty &node_data, u64 hs, hashmap_base_node *p, hashmap_base_node *n) noexcept :
        hashmap_base_node(hs, p, n),
        duo(node_data)
    {}

    ~hashmap_node() noexcept = default;

    const Key_Ty &mykey() const noexcept
    {
        return duo.first;
    }

    Val_Ty &myval() noexcept
    {
        return duo.second;
    }

    pair<const Key_Ty, Val_Ty> &mypair() noexcept
    {
        return duo;
    }

    pair<const Key_Ty, Val_Ty> *mydata() noexcept
    {
        return reinterpret_cast<pair<const Key_Ty, Val_Ty>*>(&duo);
    }

private:
    pair<Key_Ty, Val_Ty> duo;
};

template<typename Key_Ty, typename Val_Ty>
class hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>
{
    friend class unordered_set<Key_Ty>;
    friend class unordered_map<Key_Ty, Val_Ty>;
    friend class hashmap<Key_Ty, Val_Ty>;

    using Self_Ty = hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>;
    using Container_Ty = hashmap<Key_Ty, Val_Ty>;

public:
    void _search_next() noexcept
    {
        assert_info(hsmap, "Non-initialized iterator.");
        node = hsmap->_next_node(node);
    }

    void _search_prev() noexcept
    {
        assert_info(hsmap, "Non-initialized iterator.");
        node = hsmap->_prev_node(node);
    }

    hashmap_base_iter(const Container_Ty *ctnr, hashmap_base_node *p_nod) :
        node(p_nod),
        hsmap(ctnr)
    {}

    hashmap_base_iter(const Self_Ty &rhs) :
        hsmap(rhs.hsmap),
        node(rhs.node)
    {}

    ~hashmap_base_iter() = default;

    Self_Ty &operator =(const Self_Ty &rhs)
    {
        hsmap = rhs.hsmap;
        node = rhs.node;
        return *this;
    }

protected:
    const Container_Ty *hsmap;
    hashmap_base_node *node;
};

template<typename Key_Ty, typename Val_Ty>
class hashmap_iter<hashmap<Key_Ty, Val_Ty>> : protected hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>
{
    friend class hashmap<Key_Ty, Val_Ty>;
    template<typename Key_Ty> friend class unordered_set;
    template<typename Key_Ty, typename Val_Ty> friend class unordered_map;

    using Container_Ty = hashmap<Key_Ty, Val_Ty>;
    using Self_Ty = hashmap_iter<Container_Ty>;
    using BaseIter_Ty = hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>;
    using BaseNode_Ty = typename Container_Ty::BaseNode_Ty;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using NodeData_Ty = typename Node_Ty::NodeData_Ty;

public:
    hashmap_iter() :
        BaseIter_Ty(nullptr, nullptr)
    {}

    hashmap_iter(const Self_Ty &rhs) :
        BaseIter_Ty(rhs)
    {}

    hashmap_iter(const Container_Ty *ctnr, BaseNode_Ty *p_nod) :
        BaseIter_Ty(ctnr, p_nod)
    {}

    ~hashmap_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        BaseIter_Ty::operator =(rhs);
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        BaseIter_Ty::_search_next();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        BaseIter_Ty::_search_prev();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(*this);
        BaseIter_Ty::_search_next();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(*this);
        BaseIter_Ty::_search_prev();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::hsmap && BaseIter_Ty::hsmap == rhs.hsmap && BaseIter_Ty::node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::hsmap == nullptr || BaseIter_Ty::hsmap != rhs.hsmap || BaseIter_Ty::node != rhs.node;
    }

    NodeData_Ty *operator ->() const noexcept
    {
        assert_info(BaseIter_Ty::hsmap, "Non-initialized iterator.");
        return reinterpret_cast<NodeData_Ty*>(((Node_Ty*)BaseIter_Ty::node)->mydata());
    }

    NodeData_Ty &operator *() const noexcept
    {
        assert_info(BaseIter_Ty::hsmap, "Non-initialized iterator.");
        return *reinterpret_cast<NodeData_Ty*>(((Node_Ty*)BaseIter_Ty::node)->mydata());
    }
};

template<typename Key_Ty, typename Val_Ty>
class hashmap_ritr<hashmap<Key_Ty, Val_Ty>> : protected hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>
{
    friend class hashmap<Key_Ty, Val_Ty>;
    template<typename Key_Ty> friend class unordered_set;
    template<typename Key_Ty, typename Val_Ty> friend class unordered_map;

    using Container_Ty = hashmap<Key_Ty, Val_Ty>;
    using Self_Ty = hashmap_ritr<Container_Ty>;
    using BaseIter_Ty = hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>;
    using BaseNode_Ty = typename Container_Ty::BaseNode_Ty;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using NodeData_Ty = typename Node_Ty::NodeData_Ty;

public:
    hashmap_ritr() :
        BaseIter_Ty(nullptr, nullptr)
    {}

    hashmap_ritr(const Self_Ty &rhs) :
        BaseIter_Ty(rhs)
    {}

    hashmap_ritr(const Container_Ty *ctnr, BaseNode_Ty *p_nod) :
        BaseIter_Ty(ctnr, p_nod)
    {}

    ~hashmap_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        BaseIter_Ty::operator =(rhs);
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        BaseIter_Ty::_search_prev();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        BaseIter_Ty::_search_next();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(*this);
        BaseIter_Ty::_search_prev();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(*this);
        BaseIter_Ty::_search_next();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::hsmap && BaseIter_Ty::hsmap == rhs.hsmap && BaseIter_Ty::node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::hsmap == nullptr || BaseIter_Ty::hsmap != rhs.hsmap || BaseIter_Ty::node != rhs.node;
    }

    NodeData_Ty *operator ->() const noexcept
    {
        assert_info(BaseIter_Ty::hsmap, "Non-initialized iterator.");
        return reinterpret_cast<NodeData_Ty*>(((Node_Ty*)BaseIter_Ty::node)->mydata());
    }

    NodeData_Ty &operator *() const noexcept
    {
        assert_info(BaseIter_Ty::hsmap, "Non-initialized iterator.");
        return *reinterpret_cast<NodeData_Ty*>(((Node_Ty*)BaseIter_Ty::node)->mydata());
    }
};

template<typename Key_Ty, typename Val_Ty>
class hashmap_const_iter<hashmap<Key_Ty, Val_Ty>> : protected hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>
{
    friend class hashmap<Key_Ty, Val_Ty>;
    template<typename Key_Ty> friend class unordered_set;
    template<typename Key_Ty, typename Val_Ty> friend class unordered_map;

    using Container_Ty = hashmap<Key_Ty, Val_Ty>;
    using Self_Ty = hashmap_const_iter<Container_Ty>;
    using BaseIter_Ty = hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>;
    using BaseNode_Ty = typename Container_Ty::BaseNode_Ty;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using NodeData_Ty = typename Node_Ty::NodeData_Ty;

public:
    hashmap_const_iter() :
        BaseIter_Ty(nullptr, nullptr)
    {}

    hashmap_const_iter(const Self_Ty &rhs) :
        BaseIter_Ty(rhs)
    {}

    hashmap_const_iter(const Container_Ty *ctnr, BaseNode_Ty *p_nod) :
        BaseIter_Ty(ctnr, p_nod)
    {}

    ~hashmap_const_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        BaseIter_Ty::operator =(rhs);
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        BaseIter_Ty::_search_next();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        BaseIter_Ty::_search_prev();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(*this);
        BaseIter_Ty::_search_next();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(*this);
        BaseIter_Ty::_search_prev();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::hsmap && BaseIter_Ty::hsmap == rhs.hsmap && BaseIter_Ty::node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::hsmap == nullptr || BaseIter_Ty::hsmap != rhs.hsmap || BaseIter_Ty::node != rhs.node;
    }

    NodeData_Ty *operator ->() const noexcept
    {
        assert_info(BaseIter_Ty::hsmap, "Non-initialized iterator.");
        return reinterpret_cast<NodeData_Ty*>(((Node_Ty*)BaseIter_Ty::node)->mydata());
    }

    NodeData_Ty &operator *() const noexcept
    {
        assert_info(BaseIter_Ty::hsmap, "Non-initialized iterator.");
        return *reinterpret_cast<NodeData_Ty*>(((Node_Ty*)BaseIter_Ty::node)->mydata());
    }
};

template<typename Key_Ty, typename Val_Ty>
class hashmap_const_ritr<hashmap<Key_Ty, Val_Ty>> : protected hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>
{
    friend class hashmap<Key_Ty, Val_Ty>;
    template<typename Key_Ty> friend class unordered_set;
    template<typename Key_Ty, typename Val_Ty> friend class unordered_map;

    using Container_Ty = hashmap<Key_Ty, Val_Ty>;
    using Self_Ty = hashmap_const_ritr<Container_Ty>;
    using BaseIter_Ty = hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>;
    using BaseNode_Ty = typename Container_Ty::BaseNode_Ty;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using NodeData_Ty = typename Node_Ty::NodeData_Ty;

public:
    hashmap_const_ritr() :
        BaseIter_Ty(nullptr, nullptr)
    {}

    hashmap_const_ritr(const Self_Ty &rhs) :
        BaseIter_Ty(rhs)
    {}

    hashmap_const_ritr(const Container_Ty *ctnr, BaseNode_Ty *p_nod) :
        BaseIter_Ty(ctnr, p_nod)
    {}

    ~hashmap_const_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        BaseIter_Ty::operator =(rhs);
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        BaseIter_Ty::_search_prev();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        BaseIter_Ty::_search_next();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(*this);
        BaseIter_Ty::_search_prev();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(*this);
        BaseIter_Ty::_search_next();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::hsmap && BaseIter_Ty::hsmap == rhs.hsmap && BaseIter_Ty::node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::hsmap == nullptr || BaseIter_Ty::hsmap != rhs.hsmap || BaseIter_Ty::node != rhs.node;
    }

    NodeData_Ty *operator ->() const noexcept
    {
        assert_info(BaseIter_Ty::hsmap, "Non-initialized iterator.");
        return reinterpret_cast<NodeData_Ty*>(((Node_Ty*)BaseIter_Ty::node)->mydata());
    }

    NodeData_Ty &operator *() const noexcept
    {
        assert_info(BaseIter_Ty::hsmap, "Non-initialized iterator.");
        return *reinterpret_cast<NodeData_Ty*>(((Node_Ty*)BaseIter_Ty::node)->mydata());
    }
};

const s64 hashmap_least_maplen = 16LL;
const s64 hashmap_most_maplen = 1LL << 30;
const s64 hashmap_max_pile_up_limitation = 4LL;

template<typename Key_Ty, typename Val_Ty>
class hashmap
{
    friend class hashmap_base_iter<hashmap<Key_Ty, Val_Ty>>;

public:
    using Self_Ty = hashmap<Key_Ty, Val_Ty>;
    using Node_Ty = hashmap_node<Key_Ty, Val_Ty>;
    using BaseNode_Ty = hashmap_base_node;
    using NodeData_Ty = typename Node_Ty::NodeData_Ty;

    using Iter_Ty = hashmap_iter<Self_Ty>;
    using Ritr_Ty = hashmap_ritr<Self_Ty>;
    using cIter_Ty = hashmap_const_iter<Self_Ty>;
    using cRitr_Ty = hashmap_const_ritr<Self_Ty>;

protected:
    hashmap() noexcept :
        allocator(),
        maplen(hashmap_least_maplen),
        sz(0),
        slots((hashmap_base_node**)memory_alloc_zero(sizeof(void*) * maplen))
    {
        assert(_self_exam());
    }

    hashmap(s64 expected_maplen) noexcept :
        allocator(),
        maplen(max(expected_maplen, hashmap_least_maplen)),
        sz(0),
        slots((hashmap_base_node**)memory_alloc_zero(sizeof(void*) * maplen))
    {
        assert(_self_exam());
    }

    hashmap(const Self_Ty &rhs) noexcept :
        allocator(rhs.sz),
        maplen(rhs.maplen),
        sz(rhs.sz),
        slots((hashmap_base_node**)memory_alloc_zero(sizeof(void*) * maplen))
    {
        for (s64 i = 0; i < maplen; ++i)
        {
            hashmap_base_node *nod = rhs.slots[i];
            while (nod)
            {
                _insert_node_data_type(*((Node_Ty*)nod)->mydata(), nod->myhash());
                nod = nod->mynext();
            }
        }
        assert(_self_exam());
    }

    hashmap(Self_Ty &&rhs) noexcept :
        allocator(right_value_type(rhs.allocator)),
        maplen(rhs.maplen),
        sz(rhs.sz),
        slots((hashmap_base_node**)memory_alloc_zero(sizeof(void*) * maplen))
    {
        for (s64 i = 0; i < maplen; ++i)
        {
            slots[i] = rhs.slots[i];
        }
        memory_set(rhs.slots, 0, sizeof(void*) * maplen);
        rhs.sz = 0;
        assert(_self_exam());
    }

    ~hashmap() noexcept
    {
        assert(_self_exam());
        memory_free(slots);
    }

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        assert(slots);
        sz = 0;
        for (s64 i = 0; i < maplen; ++i)
        {
            hashmap_base_node *nod = slots[i];
            while (nod)
            {
                hashmap_base_node *next_nod = nod->mynext();
                ((Node_Ty*)nod)->~Node_Ty();
                allocator.put(nod);
                nod = next_nod;
            }
        }
        memory_free(slots);

        maplen = rhs.maplen;
        slots = (hashmap_base_node**)memory_alloc_zero(sizeof(void*) * maplen);
        for (s64 i = 0; i < maplen; ++i)
        {
            hashmap_base_node *nod = rhs.slots[i];
            while (nod)
            {
                _insert_node_data_type(*((Node_Ty*)nod)->mydata(), nod->myhash());
                nod = nod->mynext();
            }
        }
        sz = rhs.sz;
        assert(_self_exam());
        return *this;
    }

    Self_Ty &operator =(Self_Ty &&rhs) noexcept
    {
        allocator = right_value_type(rhs.allocator);
        maplen = rhs.maplen;
        slots = (hashmap_base_node**)memory_alloc_zero(sizeof(void*) * maplen);
        for (s64 i = 0; i < maplen; ++i)
        {
            slots[i] = rhs.slots[i];
        }
        sz = rhs.sz;
        memory_set(rhs.slots, 0, sizeof(void*) * maplen);
        rhs.sz = 0;
        assert(_self_exam());
        return *this;
    }

    void _clear() noexcept
    {
        maplen = hashmap_least_maplen;
        sz = 0;
        memory_free(slots);
        slots = (hashmap_base_node**)memory_alloc_zero(sizeof(void*) * maplen);
        assert(_self_exam());
    }

    s64 _size() const noexcept
    {
        return sz;
    }

    bool _self_exam() noexcept
    {
        for (s64 i = 0; i < maplen; ++i)
        {
            s64 pile_up_cnt = 0;
            Node_Ty *nod = (Node_Ty*)slots[i];
            assert(nod == nullptr || nod->myprev() == nullptr);
            while (nod)
            {
                ++pile_up_cnt;
                u64 myhash = Hash(nod->mykey());
                assert_info(myhash % maplen == i, "Hash map node key value's hash value is incoherence.");
                if (myhash % maplen != i)
                {
                    return false;
                }
                assert(nod->mynext() == nullptr || nod->mynext()->myprev() == nod);
                if (nod->mynext() && nod->mynext()->myprev() != nod)
                {
                    return false;
                }
                nod = (Node_Ty*)nod->mynext();
            }
            assert_info(pile_up_cnt <= hashmap_max_pile_up_limitation, "Hash map one hash value's chain length should be limited.");
            if (pile_up_cnt > hashmap_max_pile_up_limitation)
            {
                return false;
            }
        }
        return true;
    }

    hashmap_base_node *_peek_node(const Key_Ty &k, u64 hs) noexcept
    {
        s64 slot_idx = hs % maplen;
        hashmap_base_node *ptr = slots[slot_idx];
        while (ptr && ((Node_Ty*)ptr)->mykey() != k)
        {
            ptr = ptr->mynext();
        }
        return ptr;
    }

    hashmap_base_node *_insert_node(const Key_Ty &k, u64 hs) noexcept
    {
        s64 slot_idx = hs % maplen;
        hashmap_base_node *nod = (hashmap_base_node*)allocator.get();
        new (nod) Node_Ty(k, hs, nullptr, slots[slot_idx]);
        if (slots[slot_idx])
        {
            slots[slot_idx]->myprev() = nod;
        }
        slots[slot_idx] = nod;
        ++sz;
        s64 chain_len = 1;
        hashmap_base_node *next = nod->mynext();
        while (next)
        {
            ++chain_len;
            next = next->mynext();
        }
        if (chain_len > hashmap_max_pile_up_limitation)
        {
            _reorg();
        }
        assert(_self_exam());
        return nod;
    }

    hashmap_base_node *_insert_node(const Key_Ty &k, const Val_Ty &v, u64 hs) noexcept
    {
        s64 slot_idx = hs % maplen;
        hashmap_base_node *nod = (hashmap_base_node*)allocator.get();
        new (nod) Node_Ty(k, v, hs, nullptr, slots[slot_idx]);
        if (slots[slot_idx])
        {
            slots[slot_idx]->myprev() = nod;
        }
        slots[slot_idx] = nod;
        ++sz;
        s64 chain_len = 1;
        hashmap_base_node *next = nod->mynext();
        while (next)
        {
            ++chain_len;
            next = next->mynext();
        }
        if (chain_len > hashmap_max_pile_up_limitation)
        {
            _reorg();
        }
        assert(_self_exam());
        return nod;
    }

    hashmap_base_node *_insert_node(const Key_Ty &k, Val_Ty &&v, u64 hs) noexcept
    {
        s64 slot_idx = hs % maplen;
        hashmap_base_node *nod = (hashmap_base_node*)allocator.get();
        new (nod) Node_Ty(k, v, hs, nullptr, slots[slot_idx]);
        if (slots[slot_idx])
        {
            slots[slot_idx]->myprev() = nod;
        }
        slots[slot_idx] = nod;
        ++sz;
        s64 chain_len = 1;
        hashmap_base_node *next = nod->mynext();
        while (next)
        {
            ++chain_len;
            next = next->mynext();
        }
        if (chain_len > hashmap_max_pile_up_limitation)
        {
            _reorg();
        }
        assert(_self_exam());
        return nod;
    }

    void _insert_node_data_type(const NodeData_Ty &node_data, u64 hs) noexcept
    {
        s64 slot_idx = hs % maplen;
        hashmap_base_node *nod = (hashmap_base_node*)allocator.get();
        new (nod) Node_Ty(node_data, hs, nullptr, slots[slot_idx]);
        if (slots[slot_idx])
        {
            slots[slot_idx]->myprev() = nod;
        }
        slots[slot_idx] = nod;
        ++sz;
        s64 chain_len = 1;
        hashmap_base_node *next = nod->mynext();
        while (next)
        {
            ++chain_len;
            next = next->mynext();
        }
        if (chain_len > hashmap_max_pile_up_limitation)
        {
            _reorg();
        }
        assert(_self_exam());
    }

    hashmap_base_node *_check_insert(const Key_Ty &k, u64 hs) noexcept
    {
        hashmap_base_node *nod = _peek_node(k, hs);
        if (!nod)
        {
            nod = _insert_node(k, hs);
        }
        assert(_self_exam());
        return nod;
    }

    hashmap_base_node *_check_insert(const Key_Ty &k, const Val_Ty &v, u64 hs) noexcept
    {
        hashmap_base_node *nod = _peek_node(k, hs);
        s64 slot_idx = hs % maplen;
        if (nod)
        {
            ((Node_Ty*)nod)->myval() = v;
        }
        else
        {
            nod = _insert_node(k, v, hs);
        }
        assert(_self_exam());
        return nod;
    }

    hashmap_base_node *_check_insert(const Key_Ty &k, Val_Ty &&v, u64 hs) noexcept
    {
        hashmap_base_node *nod = _peek_node(k, hs);
        s64 slot_idx = hs % maplen;
        if (nod)
        {
            ((Node_Ty*)nod)->myval() = v;
        }
        else
        {
            nod = _insert_node(k, v, hs);
        }
        assert(_self_exam());
        return nod;
    }

    void _erase_node(hashmap_base_node *nod)
    {
        assert(nod);
        s64 slot_idx = nod->myhash() % maplen;
        if (nod->mynext())
        {
            nod->mynext()->myprev() = nod->myprev();
        }
        if (nod == slots[slot_idx])
        {
            slots[slot_idx] = nod->mynext();
        }
        else
        {
            nod->myprev()->mynext() = nod->mynext();
        }
        --sz;
        ((Node_Ty*)nod)->~Node_Ty();
        allocator.put(nod);
        assert(_self_exam());
    }

    void _erase_iterator(Iter_Ty itr)
    {
        assert_info(itr.hsmap == this, "This iterator doesn't belong to mine.");
        assert_info(itr.node, "This is not a data valid iterator.");
        _erase_node(itr.node);
    }

    bool _check_erase(const Key_Ty &k, u64 hs) noexcept
    {
        hashmap_base_node *nod = _peek_node(k, hs);
        if (nod)
        {
            _erase_node(nod);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool _reorg(s64 new_maplen) noexcept
    {
        assert(new_maplen > maplen);
        hashmap_base_node **new_slots = (hashmap_base_node**)memory_alloc_zero(sizeof(void*) * new_maplen);
        bool good_reorg = true;
        for (s64 i = 0; i < maplen; ++i)
        {
            hashmap_base_node *nod = slots[i];
            while (nod)
            {
                hashmap_base_node *next = nod->mynext();
                s64 slot_idx = nod->myhash() % new_maplen;
                hashmap_base_node *new_nod = (hashmap_base_node*)allocator.get();
                new (new_nod) Node_Ty(*((Node_Ty*)nod)->mydata(), nod->myhash(), nullptr, new_slots[slot_idx]);
                if (new_slots[slot_idx])
                {
                    new_slots[slot_idx]->myprev() = new_nod;
                }
                new_slots[slot_idx] = new_nod;
                s64 chain_len = 1;
                while (new_nod->mynext())
                {
                    ++chain_len;
                    new_nod = new_nod->mynext();
                }
                good_reorg = chain_len > hashmap_max_pile_up_limitation ? false : good_reorg;
                pointer_convert(nod, 0, Node_Ty*)->~Node_Ty();
                allocator.put(nod);
                nod = next;
            }
        }
        memory_free(slots);
        slots = new_slots;
        maplen = new_maplen;
        return good_reorg;
    }

    void _reorg() noexcept
    {
        s64 mymaplen = maplen;
        if (_reorg(mymaplen * 4 - 1) || _reorg(mymaplen * 7 - 1))
        {
            return;
        }
        assert_info(0, "Optimize your Hash() function to make it distributed better.");
    }

    hashmap_base_node *_next_node(hashmap_base_node *nod) const noexcept
    {
        if (nod && nod->mynext())
        {
            return nod->mynext();
        }
        s64 slot_idx = nod ? nod->myhash() % maplen : -1;
        ++slot_idx;
        assert(slot_idx <= maplen);
        hashmap_base_node *next = nullptr;
        while (next == nullptr && slot_idx < maplen)
        {
            next = slots[slot_idx];
            ++slot_idx;
        }
        return next;
    }

    hashmap_base_node *_prev_node(hashmap_base_node *nod) const noexcept
    {
        if (nod && nod->myprev())
        {
            return nod->myprev();
        }
        s64 slot_idx = nod ? nod->myhash() % maplen : maplen;
        --slot_idx;
        hashmap_base_node *prev = nullptr;
        while (prev == nullptr && slot_idx >= 0)
        {
            prev = slots[slot_idx];
            ++slot_idx;
        }
        while (prev && prev->mynext())
        {
            prev = prev->mynext();
        }
        return prev;
    }

    Iter_Ty _find(const Key_Ty &k, u64 hs) noexcept
    {
        hashmap_base_node *nod = _peek_node(k, hs);
        return Iter_Ty(this, nod);
    }

    Iter_Ty _begin() const noexcept
    {
        Iter_Ty itr(this, nullptr);
        ++itr;
        return itr;
    }

    Iter_Ty _end() const noexcept
    {
        return Iter_Ty(this, nullptr);
    }

    Ritr_Ty _rbegin() const noexcept
    {
        Ritr_Ty itr(this, nullptr);
        ++itr;
        return itr;
    }

    Ritr_Ty _rend() const noexcept
    {
        return Ritr_Ty(this, nullptr);
    }

    cIter_Ty _cbegin() const noexcept
    {
        cIter_Ty itr(this, nullptr);
        ++itr;
        return itr;
    }

    cIter_Ty _cend() const noexcept
    {
        return cIter_Ty(this, nullptr);
    }

    cRitr_Ty _crbegin() const noexcept
    {
        cRitr_Ty itr(this, nullptr);
        ++itr;
        return itr;
    }

    cRitr_Ty _crend() const noexcept
    {
        return cRitr_Ty(this, nullptr);
    }

private:
    slot_allocator<sizeof(Node_Ty)> allocator;
    s64 maplen;
    s64 sz;
    hashmap_base_node **slots;
};

END_NS(std)

#endif //# __INT_BASIC_HASHMAP_HPP__ ends
