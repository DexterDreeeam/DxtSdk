/* ********* * ********* * ********* * ********* * *********
 *
 * int_list.hpp
 *
 * proj: proj_2000_utils
 * desc: list container
 * autr: dexterdreeeam
 * date: 20200911
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_LIST_HPP__)
#define __INT_LIST_HPP__

namespace std
{

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

    Self_Ty *&mynext() noexcept
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
class list
{
    using Data_Ty = Ty;
    using Self_Ty = list<Ty>;
    using Node_Ty = list_node<Ty>;

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

    list(Self_Ty &rhs) :
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
    list_dummy_node head;
    slot_allocator<sizeof(Node_Ty)> allocator;
    s64 sz;
};

}

#endif //# __INT_LIST_HPP__ ends
