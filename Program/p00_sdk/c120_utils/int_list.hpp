/* ********* * ********* * ********* * ********* * *********
 *
 * int_list.hpp
 *
 * proj: proj_00_sdk_component_120_utils
 * desc: list container
 * autr: dexterdreeeam
 * date: 20200911
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_LIST_HPP__)
#define __INT_LIST_HPP__

#include "int_basic_slot_allocator.hpp"

namespace std
{

template<typename Ty>
class list;

namespace std_list
{

template<typename Ctnr_Ty>
class list_iter;

template<typename Ctnr_Ty>
class list_ritr;

template<typename Ctnr_Ty>
class list_const_iter;

template<typename Ctnr_Ty>
class list_const_ritr;


template<typename Ty>
class list_node
{
    using Self_Ty = list_node<Ty>;

public:
    list_node(const Ty &e) :
        prev(nullptr),
        next(nullptr)
    {
        new (&elem) Ty(e);
    }

    list_node(Ty &&e) :
        prev(nullptr),
        next(nullptr)
    {
        new (&elem) Ty(e);
    }

    list_node(Self_Ty *p, Self_Ty *n, const Ty &e) :
        prev(p),
        next(n)
    {
        new (&elem) Ty(e);
    }

    list_node(Self_Ty *p, Self_Ty *n, Ty &&e) :
        prev(p),
        next(n)
    {
        new (&elem) Ty(e);
    }

    list_node(const Self_Ty &rhs) :
        prev(nullptr),
        next(nullptr)
    {
        new (&elem) Ty(rhs.mydata());
    }

    ~list_node() noexcept
    {
        pointer_convert(&elem, 0, Ty*)->~Ty();
    }

    Ty &mydata() noexcept
    {
        return *pointer_convert(&elem, 0, Ty*);
    }

    const Ty &mydata() const noexcept
    {
        return *pointer_convert(&elem, 0, Ty*);
    }

    Self_Ty *&myprev() noexcept
    {
        return prev;
    }

    const Self_Ty *myprev() const noexcept
    {
        return prev;
    }

    Self_Ty *&mynext() noexcept
    {
        return next;
    }

    const Self_Ty *mynext() const noexcept
    {
        return next;
    }

private:
    Self_Ty *prev;
    Self_Ty *next;
    u8       elem[sizeof(Ty)];
};

struct list_dummy_node
{
    list_dummy_node() :
        prev(this),
        next(this)
    {}

    list_dummy_node(const list_dummy_node &rhs) :
        prev(rhs.prev),
        next(rhs.next)
    {}

    ~list_dummy_node() = default;

    void *prev;
    void *next;
};

template<typename Ty>
class list_iter<list<Ty>>
{
    friend class list<Ty>;

    using Container_Ty = list<Ty>;
    using Self_Ty = list_iter<Container_Ty>;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using Data_Ty = Ty;

public:
    list_iter() :
        node(nullptr)
    {}

    list_iter(const Self_Ty &rhs) :
        node(rhs.node)
    {}

    ~list_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        node = rhs.node;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        assert(node);
        node = node->mynext();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        assert(node);
        node = node->myprev();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(node);
        assert(node);
        node = node->mynext();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(node);
        assert(node);
        node = node->myprev();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        //assert(node);
        return node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return node != rhs.node;
    }

    Data_Ty *operator ->() const noexcept
    {
        return &node->mydata();
    }

    Data_Ty &operator *() const noexcept
    {
        return node->mydata();
    }

private:
    list_iter(Node_Ty *p_nod) :
        node(p_nod)
    {}

    Node_Ty *node;
};

template<typename Ty>
class list_ritr<list<Ty>>
{
    friend class list<Ty>;

    using Container_Ty = list<Ty>;
    using Self_Ty = list_ritr<Container_Ty>;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using Data_Ty = Ty;

public:
    list_ritr() :
        node(nullptr)
    {}

    list_ritr(const Self_Ty &rhs) :
        node(rhs.node)
    {}

    ~list_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        node = rhs.node;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        assert(node);
        node = node->myprev();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        assert(node);
        node = node->mynext();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(node);
        assert(node);
        node = node->myprev();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(node);
        assert(node);
        node = node->mynext();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        //assert(node);
        return node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return node != rhs.node;
    }

    Data_Ty *operator ->() const noexcept
    {
        return &node->mydata();
    }

    Data_Ty &operator *() const noexcept
    {
        return node->mydata();
    }

private:
    list_ritr(Node_Ty *p_nod) :
        node(p_nod)
    {}

    Node_Ty *node;
};

template<typename Ty>
class list_const_iter<list<Ty>>
{
    friend class list<Ty>;

    using Container_Ty = list<Ty>;
    using Self_Ty = list_const_iter<Container_Ty>;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using Data_Ty = Ty;

public:
    list_const_iter() :
        node(nullptr)
    {}

    list_const_iter(const Self_Ty &rhs) :
        node(rhs.node)
    {}

    ~list_const_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        node = rhs.node;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        assert(node);
        node = node->mynext();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        assert(node);
        node = node->myprev();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(node);
        assert(node);
        node = node->mynext();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(node);
        assert(node);
        node = node->myprev();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        //assert(node);
        return node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return node != rhs.node;
    }

    const Data_Ty *operator ->() const noexcept
    {
        return &node->mydata();
    }

    const Data_Ty &operator *() const noexcept
    {
        return node->mydata();
    }

private:
    list_const_iter(const Node_Ty *p_nod) :
        node(p_nod)
    {}

    const Node_Ty *node;
};

template<typename Ty>
class list_const_ritr<list<Ty>>
{
    friend class list<Ty>;

    using Container_Ty = list<Ty>;
    using Self_Ty = list_const_ritr<Container_Ty>;
    using Node_Ty = typename Container_Ty::Node_Ty;
    using Data_Ty = Ty;

public:
    list_const_ritr() :
        node(nullptr)
    {}

    list_const_ritr(const Self_Ty &rhs) :
        node(rhs.node)
    {}

    ~list_const_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        node = rhs.node;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        assert(node);
        node = node->myprev();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        assert(node);
        node = node->mynext();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(node);
        assert(node);
        node = node->myprev();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(node);
        assert(node);
        node = node->mynext();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        //assert(node);
        return node == rhs.node;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return node != rhs.node;
    }

    const Data_Ty *operator ->() const noexcept
    {
        return &node->mydata();
    }

    const Data_Ty &operator *() const noexcept
    {
        return node->mydata();
    }

private:
    list_const_ritr(const Node_Ty *p_nod) :
        node(p_nod)
    {}

    const Node_Ty *node;
};

}

template<typename Ty>
class list
{
    using Data_Ty = Ty;
    using Self_Ty = list<Ty>;
    using Node_Ty = std_list::list_node<Ty>;
    using Iter_Ty = std_list::list_iter<Self_Ty>;
    using Ritr_Ty = std_list::list_ritr<Self_Ty>;
    using cIter_Ty = std_list::list_const_iter<Self_Ty>;
    using cRitr_Ty = std_list::list_const_ritr<Self_Ty>;

    friend class std_list::list_iter<Self_Ty>;
    friend class std_list::list_ritr<Self_Ty>;
    friend class std_list::list_const_iter<Self_Ty>;
    friend class std_list::list_const_ritr<Self_Ty>;

public:
    list() :
        head(),
        allocator(),
        sz(0)
    {}

    template<typename ...Args>
    list(Args...args) :
        head(),
        allocator(sizeof...(args)),
        sz(0)
    {
        _construct_tuple(args...);
    }

    list(const Self_Ty &rhs) :
        head(),
        allocator(rhs.sz),
        sz(0)
    {
        Node_Ty *p = rhs.myhead()->mynext();
        while (p != rhs.myhead())
        {
            push_back(p->mydata());
            p = p->mynext();
        }
    }

    list(Self_Ty &&rhs) :
        head(rhs.head),
        allocator(right_value_type(rhs.allocator)),
        sz(rhs.sz)
    {
        rhs.myhead()->myprev() = rhs.myhead();
        rhs.myhead()->mynext() = rhs.myhead();
        rhs.sz = 0;
    }

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        assert(sz >= 0);
        while (sz != 0)
        {
            pop_back();
        }
        Node_Ty *p = rhs.myhead()->mynext();
        while (p != rhs.myhead())
        {
            push_back(p->mydata());
            p = p->mynext();
        }
        return *this;
    }

    Self_Ty &operator =(Self_Ty &&rhs) noexcept
    {
        myhead()->myprev() = rhs.myhead()->myprev();
        myhead()->mynext() = rhs.myhead()->mynext();
        myhead()->myprev()->mynext() = myhead();
        myhead()->mynext()->myprev() = myhead();
        allocator = right_value_type(rhs.allocator);
        sz = rhs.sz;

        rhs.myhead()->myprev() = rhs.myhead();
        rhs.myhead()->mynext() = rhs.myhead();
        rhs.sz = 0;
        return *this;
    }

    ~list() noexcept
    {
        assert(sz >= 0);
        while (sz != 0)
        {
            pop_back();
        }
    }

    s64 size() const noexcept
    {
        assert(sz >= 0);
        return sz;
    }

    bool empty() const noexcept
    {
        assert(sz >= 0);
        return sz == 0;
    }

    Ty &front() noexcept
    {
        assert(sz > 0);
        return myhead()->mynext()->mydata();
    }

    const Ty &front() const noexcept
    {
        assert(sz > 0);
        return myhead()->mynext()->mydata();
    }

    Ty &back() noexcept
    {
        assert(sz > 0);
        return myhead()->myprev()->mydata();
    }

    const Ty &back() const noexcept
    {
        assert(sz > 0);
        return myhead()->myprev()->mydata();
    }

    void push_back(const Ty &e) noexcept
    {
        _create_insert_tail(e);
        ++sz;
    }

    void push_back(Ty &&e) noexcept
    {
        _create_insert_tail(e);
        ++sz;
    }

    template<typename ...Args>
    void push_back(Args... args)
    {
        assert(sz >= 0);
        _construct_tuple(args...);
    }

    void push_front(const Ty &e) noexcept
    {
        _create_insert_head(e);
        ++sz;
    }

    void push_front(Ty &&e) noexcept
    {
        _create_insert_head(e);
        ++sz;
    }

    template<typename ...Args>
    void push_front(Args... args)
    {
        assert(sz >= 0);
        _construct_tuple_after(myhead(), args...);
        sz += sizeof...(args);
    }

    void pop_back() noexcept
    {
        assert(sz > 0);
        --sz;
        _destroy_tail();
    }

    void pop_front() noexcept
    {
        assert(sz > 0);
        --sz;
        _destroy_head();
    }

    void clear() noexcept
    {
        assert(sz >= 0);
        while (sz != 0)
        {
            pop_back();
        }
    }

    Iter_Ty begin() noexcept
    {
        assert(sz >= 0);
        return Iter_Ty(myhead()->mynext());
    }

    const cIter_Ty cbegin() const noexcept
    {
        assert(sz >= 0);
        return cIter_Ty(myhead()->mynext());
    }

    Iter_Ty end() noexcept
    {
        assert(sz >= 0);
        return Iter_Ty(myhead());
    }

    const cIter_Ty cend() const noexcept
    {
        assert(sz >= 0);
        return cIter_Ty(myhead());
    }

    Ritr_Ty rbegin() noexcept
    {
        assert(sz >= 0);
        return Ritr_Ty(myhead()->myprev());
    }

    const cRitr_Ty crbegin() const noexcept
    {
        assert(sz >= 0);
        return cRitr_Ty(myhead()->myprev());
    }

    Ritr_Ty rend() noexcept
    {
        assert(sz >= 0);
        return Ritr_Ty(myhead());
    }

    cRitr_Ty crend() const noexcept
    {
        assert(sz >= 0);
        return cRitr_Ty(myhead());
    }

    Iter_Ty find(const Ty &e)
    {
        Iter_Ty itr = begin();
        const Iter_Ty eitr = end();
        while (itr != eitr && *itr != e)
        {
            ++itr;
        }
        return itr;
    }

    void insert(Iter_Ty iter, const Ty &e)
    {
        assert(sz >= 0);
        Node_Ty *last = iter.node->myprev();
        Node_Ty *nod = _create_node(e);
        _insert_after(nod, last);
    }

    void insert(Iter_Ty iter, Ty &&e)
    {
        assert(sz >= 0);
        Node_Ty *last = iter.node->myprev();
        Node_Ty *nod = _create_node(e);
        _insert_after(nod, last);
    }

    Iter_Ty erase(Iter_Ty iter)
    {
        assert(sz > 0);
        Node_Ty *nod = iter.node;
        assert(nod && nod != myhead());
        Iter_Ty ret(nod->mynext());
        --sz;
        _destroy_node(nod);
        return ret;
    }

private:
    Node_Ty *myhead() const noexcept
    {
        return pointer_convert(&head, 0, Node_Ty*);
    }

    template<typename ...Args>
    void _construct_tuple(const Ty &first, Args...args)
    {
        push_back(first);
        _construct_tuple(args...);
    }

    template<typename ...Args>
    void _construct_tuple(Ty &&first, Args...args)
    {
        push_back(first);
        _construct_tuple(args...);
    }

    void _construct_tuple(const Ty &last)
    {
        push_back(last);
    }

    void _construct_tuple(Ty &&last)
    {
        push_back(last);
    }

    template<typename ...Args>
    void _construct_tuple_after(Node_Ty *base, const Ty &first, Args...args)
    {
        Node_Ty *nod = _create_node(first);
        _insert_after(nod, base);
        _construct_tuple_after(nod, args...);
    }

    template<typename ...Args>
    void _construct_tuple_after(Node_Ty *base, Ty &&first, Args...args)
    {
        Node_Ty *nod = _create_node(first);
        _insert_after(nod, base);
        _construct_tuple_after(nod, args...);
    }

    void _construct_tuple_after(Node_Ty *base, const Ty &last)
    {
        Node_Ty *nod = _create_node(last);
        _insert_after(nod, base);
    }

    void _construct_tuple_after(Node_Ty *base, Ty &&last)
    {
        Node_Ty *nod = _create_node(last);
        _insert_after(nod, base);
    }

    Node_Ty *_create_node(const Ty &e)
    {
        Node_Ty *nod = (Node_Ty*)allocator.get();
        assert(nod);
        new (nod) Node_Ty(e);
        return nod;
    }

    Node_Ty *_create_node(Ty &&e)
    {
        Node_Ty *nod = (Node_Ty*)allocator.get();
        assert(nod);
        new (nod) Node_Ty(e);
        return nod;
    }

    Node_Ty *_create_node(Node_Ty *prev, Node_Ty *next, const Ty &e)
    {
        Node_Ty *nod = (Node_Ty*)allocator.get();
        assert(nod);
        new (nod) Node_Ty(prev, next, e);
        return nod;
    }

    Node_Ty *_create_node(Node_Ty *prev, Node_Ty *next, Ty &&e)
    {
        Node_Ty *nod = (Node_Ty*)allocator.get();
        assert(nod);
        new (nod) Node_Ty(prev, next, e);
        return nod;
    }

    void _create_insert_head(const Ty &e) noexcept
    {
        Node_Ty *last = myhead();
        Node_Ty *next = myhead()->mynext();
        Node_Ty *node = _create_node(last, next, e);
        last->mynext() = node;
        next->myprev() = node;
    }

    void _create_insert_head(Ty &&e) noexcept
    {
        Node_Ty *last = myhead();
        Node_Ty *next = myhead()->mynext();
        Node_Ty *node = _create_node(last, next, e);
        assert(last && next && node);
        last->mynext() = node;
        next->myprev() = node;
    }

    void _create_insert_tail(const Ty &e) noexcept
    {
        Node_Ty *last = myhead()->myprev();
        Node_Ty *next = myhead();
        Node_Ty *node = _create_node(last, next, e);
        assert(last && next && node);
        last->mynext() = node;
        next->myprev() = node;
    }

    void _create_insert_tail(Ty &&e) noexcept
    {
        Node_Ty *last = myhead()->myprev();
        Node_Ty *next = myhead();
        Node_Ty *node = _create_node(last, next, e);
        assert(last && next && node);
        last->mynext() = node;
        next->myprev() = node;
    }

    void _destroy_node(Node_Ty *nod) noexcept
    {
        assert(nod && nod != myhead());
        Node_Ty *last = nod->myprev();
        Node_Ty *next = nod->mynext();
        last->mynext() = next;
        next->myprev() = last;

        nod->~Node_Ty();
        allocator.put(nod);
    }

    void _destroy_head() noexcept
    {
        _destroy_node(myhead()->mynext());
    }

    void _destroy_tail() noexcept
    {
        _destroy_node(myhead()->myprev());
    }

    void _insert_head(Node_Ty *nod) noexcept
    {
        Node_Ty *last = myhead();
        Node_Ty *next = myhead()->mynext();
        assert(last && next && nod);
        nod->myprev() = last;
        nod->mynext() = next;
        last->mynext() = nod;
        next->myprev() = nod;
    }

    void _insert_tail(Node_Ty *nod) noexcept
    {
        Node_Ty *last = myhead()->myprev();
        Node_Ty *next = myhead();
        assert(last && next && nod);
        nod->myprev() = last;
        nod->mynext() = next;
        last->mynext() = nod;
        next->myprev() = nod;
    }

    void _insert_after(Node_Ty *nod, Node_Ty *base) noexcept
    {
        Node_Ty *next = base->mynext();
        assert(base && next && nod);
        nod->myprev() = base;
        nod->mynext() = next;
        base->mynext() = nod;
        next->myprev() = nod;
    }

private:
    std_list::list_dummy_node head;
    slot_allocator<sizeof(Node_Ty)> allocator;
    s64 sz;
};

}

#endif //# __INT_LIST_HPP__ ends
