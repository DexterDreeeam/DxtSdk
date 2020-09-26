/* ********* * ********* * ********* * ********* * *********
 *
 * int_deque.hpp
 *
 * proj: proj_2000_utils
 * desc: deque container
 * autr: dexterdreeeam
 * date: 20200902
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_DEQUE_HPP__)
#define __INT_DEQUE_HPP__

#include "../proj_1000_xos/ext_xos_interface.hpp"

namespace std
{

const s64 deque_block_min_size = 1LL << 4;
const s64 deque_block_max_size = 1LL << 10;

template<typename Ty>
class deque;

namespace std_deque
{

template<typename Ctnr_Ty>
class deque_base_iter;

template<typename Ctnr_Ty>
class deque_iter;

template<typename Ctnr_Ty>
class deque_ritr;

template<typename Ctnr_Ty>
class deque_const_iter;

template<typename Ctnr_Ty>
class deque_const_ritr;

template<typename Ty>
class deque_block
{
    using Self_Ty = deque_block<Ty>;

public:
    deque_block(s64 block_cap, Self_Ty *p, Self_Ty *n, s64 h_cur, s64 t_cur) :
        prev(p),
        next(n),
        cap(block_cap),
        sz(0),
        head_cursor(h_cur),
        tail_cursor(t_cur),
        elem((Ty*)memory_alloc(sizeof(Ty) * cap))
    {
        assert(cap > 0);
        assert(h_cur >= -1);
        assert(t_cur <= cap);
        assert(h_cur + 1 == t_cur);
        assert(elem);
    }

    ~deque_block() noexcept
    {
        assert(elem);
        memory_free(elem);
    }

    Self_Ty *&myprev() noexcept
    {
        return prev;
    }

    const Self_Ty *&myprev() const noexcept
    {
        return prev;
    }

    Self_Ty *&mynext() noexcept
    {
        return next;
    }

    const Self_Ty *&mynext() const noexcept
    {
        return next;
    }

    bool empty() const noexcept
    {
        return sz == 0;
    }

    bool full() const noexcept
    {
        return sz == cap;
    }

    s64 size() const noexcept
    {
        return sz;
    }

    Ty &back() noexcept
    {
        assert(sz > 0);
        return elem[tail_cursor - 1];
    }

    const Ty &back() const noexcept
    {
        assert(sz > 0);
        return elem[tail_cursor - 1];
    }

    Ty &front() noexcept
    {
        assert(sz > 0);
        return elem[head_cursor + 1];
    }

    const Ty &front() const noexcept
    {
        assert(sz > 0);
        return elem[head_cursor + 1];
    }

    void push_back(const Ty &e) noexcept
    {
        assert(tail_cursor < cap);
        new (&elem[tail_cursor]) Ty(e);
        ++tail_cursor;
        ++sz;
    }

    void push_back(Ty &&e) noexcept
    {
        assert(tail_cursor < cap);
        new (&elem[tail_cursor]) Ty(e);
        ++tail_cursor;
        ++sz;
    }

    void push_front(const Ty &e) noexcept
    {
        assert(head_cursor >= 0);
        new (&elem[head_cursor]) Ty(e);
        --head_cursor;
        ++sz;
    }

    void push_front(Ty &&e) noexcept
    {
        assert(head_cursor >= 0);
        new (&elem[head_cursor]) Ty(e);
        --head_cursor;
        ++sz;
    }

    void pop_back() noexcept
    {
        assert(sz > 0);
        --sz;
        --tail_cursor;
        (&elem[tail_cursor])->~Ty();
    }

    void pop_front() noexcept
    {
        assert(sz > 0);
        --sz;
        ++head_cursor;
        (&elem[head_cursor])->~Ty();
    }

    Ty &at(s64 pos) noexcept
    {
        assert(pos >= 0 && pos < sz);
        return elem[head_cursor + pos + 1];
    }

    const Ty &at(s64 pos) const noexcept
    {
        assert(pos >= 0 && pos < sz);
        return elem[head_cursor + pos + 1];
    }

private:
    Self_Ty *prev;
    Self_Ty *next;
    s64 cap;
    s64 sz;
    s64 head_cursor;
    s64 tail_cursor;
    Ty *elem;
};

template<typename Ty>
class deque_base_iter<deque<Ty>>
{
    using Container_Ty = deque<Ty>;
    using Self_Ty = deque_iter<Container_Ty>;
    using Blck_Ty = deque_block<Ty>;

protected:
    deque_base_iter() :
        deq_blk(nullptr),
        block_idx(0)
    {}

    deque_base_iter(Blck_Ty *blk, s64 blk_idx) :
        deq_blk(blk),
        block_idx(blk_idx)
    {}

    deque_base_iter(const Self_Ty &rhs) :
        deq_blk(rhs.deq_blk),
        block_idx(rhs.block_idx)
    {}

    ~deque_base_iter() noexcept = default;

    void _search_next() noexcept
    {
        assert(deq_blk);
        if (++block_idx >= deq_blk->size())
        {
            deq_blk = deq_blk->mynext();
            block_idx = 0;
            if (deq_blk && deq_blk->size() == 0)
            {
                assert(deq_blk->mynext() == nullptr);
                deq_blk = nullptr;
            }
        }
    }

    void _search_prev() noexcept
    {
        assert(deq_blk);
        if (--block_idx < 0)
        {
            deq_blk = deq_blk->myprev();
            if (deq_blk && deq_blk->size() > 0)
            {
                block_idx = deq_blk->size() - 1;
            }
            else
            {
                deq_blk = nullptr;
                block_idx = 0;
            }
        }
    }

protected:
    Blck_Ty *deq_blk;
    s64 block_idx;
};

template<typename Ty>
class deque_iter<deque<Ty>> : public deque_base_iter<deque<Ty>>
{
    using Container_Ty = deque<Ty>;
    using Self_Ty = deque_iter<Container_Ty>;
    using BaseIter_Ty = deque_base_iter<Container_Ty>;
    using Blck_Ty = deque_block<Ty>;

public:
    deque_iter() :
        BaseIter_Ty()
    {}

    deque_iter(Blck_Ty *blk, s64 blk_idx) :
        BaseIter_Ty(blk, blk_idx)
    {}

    deque_iter(const Self_Ty &rhs) :
        BaseIter_Ty(rhs)
    {}

    ~deque_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        BaseIter_Ty::deq_blk = rhs.deq_blk;
        BaseIter_Ty::block_idx = rhs.block_idx;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        BaseIter_Ty::_search_next();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        BaseIter_Ty::_search_prev();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        Self_Ty ret(BaseIter_Ty::deq_blk, BaseIter_Ty::block_idx);
        BaseIter_Ty::_search_next();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        assert(Blck_Ty::deq_blk);
        Self_Ty ret(BaseIter_Ty::deq_blk, BaseIter_Ty::block_idx);
        BaseIter_Ty::_search_prev();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::deq_blk == rhs.deq_blk && BaseIter_Ty::block_idx == rhs.block_idx;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::deq_blk != rhs.deq_blk || BaseIter_Ty::block_idx != rhs.block_idx;
    }

    Ty &operator *() noexcept
    {
        assert_info(BaseIter_Ty::deq_blk, "Dereference a non-data iterator.");
        assert(BaseIter_Ty::block_idx >= 0 && BaseIter_Ty::block_idx < BaseIter_Ty::deq_blk->size());
        return BaseIter_Ty::deq_blk->at(BaseIter_Ty::block_idx);
    }

    Ty *operator ->() noexcept
    {
        assert_info(BaseIter_Ty::deq_blk, "Dereference a non-data iterator.");
        assert(BaseIter_Ty::block_idx >= 0 && BaseIter_Ty::block_idx < BaseIter_Ty::deq_blk->size());
        return &BaseIter_Ty::deq_blk->at(BaseIter_Ty::block_idx);
    }
};

template<typename Ty>
class deque_ritr<deque<Ty>> : public deque_base_iter<deque<Ty>>
{
    using Container_Ty = deque<Ty>;
    using Self_Ty = deque_ritr<Container_Ty>;
    using BaseIter_Ty = deque_base_iter<Container_Ty>;
    using Blck_Ty = deque_block<Ty>;

public:
    deque_ritr() :
        BaseIter_Ty()
    {}

    deque_ritr(Blck_Ty *blk, s64 blk_idx) :
        BaseIter_Ty(blk, blk_idx)
    {}

    deque_ritr(const Self_Ty &rhs) :
        BaseIter_Ty(rhs)
    {}

    ~deque_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        BaseIter_Ty::deq_blk = rhs.deq_blk;
        BaseIter_Ty::block_idx = rhs.block_idx;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        BaseIter_Ty::_search_prev();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        BaseIter_Ty::_search_next();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        Self_Ty ret(BaseIter_Ty::deq_blk, BaseIter_Ty::block_idx);
        BaseIter_Ty::_search_prev();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        Self_Ty ret(BaseIter_Ty::deq_blk, BaseIter_Ty::block_idx);
        BaseIter_Ty::_search_next();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::deq_blk == rhs.deq_blk && BaseIter_Ty::block_idx == rhs.block_idx;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::deq_blk != rhs.deq_blk || BaseIter_Ty::block_idx != rhs.block_idx;
    }

    Ty &operator *() noexcept
    {
        assert_info(BaseIter_Ty::deq_blk, "Dereference a non-data iterator.");
        assert(BaseIter_Ty::block_idx >= 0 && BaseIter_Ty::block_idx < BaseIter_Ty::deq_blk->size());
        return BaseIter_Ty::deq_blk->at(BaseIter_Ty::block_idx);
    }

    Ty *operator ->() noexcept
    {
        assert_info(BaseIter_Ty::deq_blk, "Dereference a non-data iterator.");
        assert(BaseIter_Ty::block_idx >= 0 && BaseIter_Ty::block_idx < BaseIter_Ty::deq_blk->size());
        return &BaseIter_Ty::deq_blk->at(BaseIter_Ty::block_idx);
    }
};

template<typename Ty>
class deque_const_iter<deque<Ty>> : public deque_base_iter<deque<Ty>>
{
    using Container_Ty = deque<Ty>;
    using Self_Ty = deque_const_iter<Container_Ty>;
    using BaseIter_Ty = deque_base_iter<Container_Ty>;
    using Blck_Ty = deque_block<Ty>;

public:
    deque_const_iter() :
        BaseIter_Ty()
    {}

    deque_const_iter(Blck_Ty *blk, s64 blk_idx) :
        BaseIter_Ty(blk, blk_idx)
    {}

    deque_const_iter(const Self_Ty &rhs) :
        BaseIter_Ty(rhs)
    {}

    ~deque_const_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        BaseIter_Ty::deq_blk = rhs.deq_blk;
        BaseIter_Ty::block_idx = rhs.block_idx;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        BaseIter_Ty::_search_next();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        BaseIter_Ty::_search_prev();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        Self_Ty ret(BaseIter_Ty::deq_blk, BaseIter_Ty::block_idx);
        BaseIter_Ty::_search_next();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        Self_Ty ret(BaseIter_Ty::deq_blk, BaseIter_Ty::block_idx);
        BaseIter_Ty::_search_prev();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::deq_blk == rhs.deq_blk && BaseIter_Ty::block_idx == rhs.block_idx;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::deq_blk != rhs.deq_blk || BaseIter_Ty::block_idx != rhs.block_idx;
    }

    const Ty &operator *() const noexcept
    {
        assert_info(BaseIter_Ty::deq_blk, "Dereference a non-data iterator.");
        assert(BaseIter_Ty::block_idx >= 0 && BaseIter_Ty::block_idx < BaseIter_Ty::deq_blk->size());
        return BaseIter_Ty::deq_blk->at(BaseIter_Ty::block_idx);
    }

    const Ty *operator ->() const noexcept
    {
        assert_info(BaseIter_Ty::deq_blk, "Dereference a non-data iterator.");
        assert(BaseIter_Ty::block_idx >= 0 && BaseIter_Ty::block_idx < BaseIter_Ty::deq_blk->size());
        return &BaseIter_Ty::deq_blk->at(BaseIter_Ty::block_idx);
    }
};

template<typename Ty>
class deque_const_ritr<deque<Ty>> : public deque_base_iter<deque<Ty>>
{
    using Container_Ty = deque<Ty>;
    using Self_Ty = deque_const_ritr<Container_Ty>;
    using BaseIter_Ty = deque_base_iter<Container_Ty>;
    using Blck_Ty = deque_block<Ty>;

public:
    deque_const_ritr() :
        BaseIter_Ty()
    {}

    deque_const_ritr(Blck_Ty *blk, s64 blk_idx) :
        BaseIter_Ty(blk, blk_idx)
    {}

    deque_const_ritr(const Self_Ty &rhs) :
        BaseIter_Ty(rhs)
    {}

    ~deque_const_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        BaseIter_Ty::deq_blk = rhs.deq_blk;
        BaseIter_Ty::block_idx = rhs.block_idx;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        BaseIter_Ty::_search_prev();
        return *this;
    }

    Self_Ty &operator --() noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        BaseIter_Ty::_search_next();
        return *this;
    }

    Self_Ty operator ++(int) noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        Self_Ty ret(BaseIter_Ty::deq_blk, BaseIter_Ty::block_idx);
        BaseIter_Ty::_search_prev();
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        assert(BaseIter_Ty::deq_blk);
        Self_Ty ret(BaseIter_Ty::deq_blk, BaseIter_Ty::block_idx);
        BaseIter_Ty::_search_next();
        return ret;
    }

    bool operator ==(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::deq_blk == rhs.deq_blk && BaseIter_Ty::block_idx == rhs.block_idx;
    }

    bool operator !=(const Self_Ty &rhs) const noexcept
    {
        return BaseIter_Ty::deq_blk != rhs.deq_blk || BaseIter_Ty::block_idx != rhs.block_idx;
    }

    const Ty &operator *() const noexcept
    {
        assert_info(BaseIter_Ty::deq_blk, "Dereference a non-data iterator.");
        assert(BaseIter_Ty::block_idx >= 0 && BaseIter_Ty::block_idx < BaseIter_Ty::deq_blk->size());
        return BaseIter_Ty::deq_blk->at(BaseIter_Ty::block_idx);
    }

    const Ty *operator ->() const noexcept
    {
        assert_info(BaseIter_Ty::deq_blk, "Dereference a non-data iterator.");
        assert(BaseIter_Ty::block_idx >= 0 && BaseIter_Ty::block_idx < BaseIter_Ty::deq_blk->size());
        return &BaseIter_Ty::deq_blk->at(BaseIter_Ty::block_idx);
    }
};

}

template<typename Ty>
class deque
{
    using Self_Ty = deque<Ty>;
    using Blck_Ty = std_deque::deque_block<Ty>;
    using Iter_Ty = std_deque::deque_iter<Self_Ty>;
    using Ritr_Ty = std_deque::deque_ritr<Self_Ty>;
    using cIter_Ty = std_deque::deque_const_iter<Self_Ty>;
    using cRitr_Ty = std_deque::deque_const_ritr<Self_Ty>;

    friend class std_deque::deque_iter<Self_Ty>;
    friend class std_deque::deque_ritr<Self_Ty>;
    friend class std_deque::deque_const_iter<Self_Ty>;
    friend class std_deque::deque_const_ritr<Self_Ty>;

public:
    deque() :
        first(new (memory_alloc(sizeof(Blck_Ty))) Blck_Ty(deque_block_min_size, nullptr, nullptr, deque_block_min_size / 2 - 1, deque_block_min_size / 2)),
        last(first),
        sz(0)
    {
        assert(first);
        assert(last);
    }

    ~deque() noexcept
    {
        Blck_Ty *blk = first;
        while (blk)
        {
            Blck_Ty *next = blk->mynext();
            first->~Blck_Ty();
            blk = next;
        }
    }

    s64 size() const noexcept
    {
        return sz;
    }

    Ty &operator [](s64 pos) noexcept
    {
        assert(pos >= 0 && pos < sz);
        if (pos <= sz / 2)
        {
            return _search_head(pos);
        }
        else
        {
            return _search_tail(pos);
        }
    }

    const Ty &operator [](s64 pos) const noexcept
    {
        assert(pos >= 0 && pos < sz);
        if (pos <= sz / 2)
        {
            return _search_head(pos);
        }
        else
        {
            return _search_tail(pos);
        }
    }

    Ty &back() noexcept
    {
        assert(sz > 0);
        if (last->empty())
        {
            Blck_Ty *next_last = last->myprev();
            last->~Blck_Ty();
            last = next_last;
            last->mynext() = nullptr;
        }
        return last->back();
    }

    Ty &front() noexcept
    {
        assert(sz > 0);
        if (first->empty())
        {
            Blck_Ty *next_first = first->mynext();
            first->~Blck_Ty();
            first = next_first;
            first->myprev() = nullptr;
        }
        return first->front();
    }

    void push_back(const Ty &e) noexcept
    {
        if (last->full())
        {
            Blck_Ty *new_blk = (Blck_Ty*)memory_alloc(sizeof(Blck_Ty));
            new (new_blk) Blck_Ty(clamp(sz, deque_block_min_size, deque_block_max_size), last, nullptr, -1, 0);
            last->mynext() = new_blk;
            last = new_blk;
        }
        last->push_back(e);
        ++sz;
    }

    void push_back(Ty &&e) noexcept
    {
        if (last->full())
        {
            Blck_Ty *new_blk = (Blck_Ty*)memory_alloc(sizeof(Blck_Ty));
            new (new_blk) Blck_Ty(clamp(sz, deque_block_min_size, deque_block_max_size), last, nullptr, -1, 0);
            last->mynext() = new_blk;
            last = new_blk;
        }
        last->push_back(e);
        ++sz;
    }

    void push_front(const Ty &e) noexcept
    {
        if (first->full())
        {
            Blck_Ty *new_blk = (Blck_Ty*)memory_alloc(sizeof(Blck_Ty));
            s64 new_cap = clamp(sz, deque_block_min_size, deque_block_max_size);
            new (new_blk) Blck_Ty(new_cap, nullptr, first, new_cap - 1, new_cap);
            first->myprev() = new_blk;
            first = new_blk;
        }
        first->push_front(e);
        ++sz;
    }

    void push_front(Ty &&e) noexcept
    {
        if (first->full())
        {
            Blck_Ty *new_blk = (Blck_Ty*)memory_alloc(sizeof(Blck_Ty));
            s64 new_cap = clamp(sz, deque_block_min_size, deque_block_max_size);
            new (new_blk) Blck_Ty(new_cap, nullptr, first, new_cap - 1, new_cap);
            first->myprev() = new_blk;
            first = new_blk;
        }
        first->push_front(e);
        ++sz;
    }

    void pop_back() noexcept
    {
        assert(sz >= 0);
        --sz;
        if (last->empty())
        {
            Blck_Ty *next_last = last->myprev();
            last->~Blck_Ty();
            last = next_last;
            last->mynext() = nullptr;
        }
        last->pop_back();
    }

    void pop_front() noexcept
    {
        assert(sz >= 0);
        --sz;
        if (first->empty())
        {
            Blck_Ty *next_first = first->mynext();
            first->~Blck_Ty();
            first = next_first;
            first->myprev() = nullptr;
        }
        first->pop_front();
    }

    Iter_Ty begin() noexcept
    {
        if (sz == 0)
        {
            return Iter_Ty(nullptr, 0);
        }
        assert(first);
        if (first->size())
        {
            return Iter_Ty(first, 0);
        }
        else
        {
            assert(first->mynext() && first->mynext()->size());
            return Iter_Ty(first->mynext(), 0);
        }
    }

    Iter_Ty end() noexcept
    {
        return Iter_Ty(nullptr, 0);
    }

    Ritr_Ty rbegin() noexcept
    {
        if (sz == 0)
        {
            return Ritr_Ty(nullptr, 0);
        }
        assert(last);
        if (last->size())
        {
            return Ritr_Ty(last, last->size() - 1);
        }
        else
        {
            assert(last->myprev() && last->myprev()->size());
            return Ritr_Ty(last->myprev(), last->myprev()->size() - 1);
        }
    }

    Ritr_Ty rend() noexcept
    {
        return Ritr_Ty(nullptr, 0);
    }

    cIter_Ty cbegin() noexcept
    {
        if (sz == 0)
        {
            return cIter_Ty(nullptr, 0);
        }
        assert(first);
        if (first->size())
        {
            return cIter_Ty(first, 0);
        }
        else
        {
            assert(first->mynext() && first->mynext()->size());
            return cIter_Ty(first->mynext(), 0);
        }
    }

    cIter_Ty cend() noexcept
    {
        return cIter_Ty(nullptr, 0);
    }

    cRitr_Ty crbegin() noexcept
    {
        if (sz == 0)
        {
            return cRitr_Ty(nullptr, 0);
        }
        assert(last);
        if (last->size())
        {
            return cRitr_Ty(last, last->size() - 1);
        }
        else
        {
            assert(last->myprev() && last->myprev()->size());
            return cRitr_Ty(last->myprev(), last->myprev()->size() - 1);
        }
    }

    cRitr_Ty crend() noexcept
    {
        return cRitr_Ty(nullptr, 0);
    }

private:
    Ty &_search_head(s64 pos) noexcept
    {
        assert(pos >= 0 && pos < sz);
        Blck_Ty *blk = first;
        while (pos >= blk->size())
        {
            pos -= blk->size();
            blk = blk->mynext();
        }
        return blk->at(pos);
    }

    const Ty &_search_head(s64 pos) const noexcept
    {
        assert(pos >= 0 && pos < sz);
        Blck_Ty *blk = first;
        while (pos >= blk->size())
        {
            pos -= blk->size();
            blk = blk->mynext();
        }
        return blk->at(pos);
    }

    Ty &_search_tail(s64 pos) noexcept
    {
        assert(pos >= 0 && pos < sz);
        Blck_Ty *blk = last;
        s64 fore_count = sz - blk->size(); //# data count in front of this block
        while (pos < fore_count)
        {
            blk = blk->myprev();
            fore_count -= blk->size();
        }
        return blk->at(pos - fore_count);
    }

    const Ty &_search_tail(s64 pos) const noexcept
    {
        assert(pos >= 0 && pos < sz);
        Blck_Ty *blk = last;
        s64 fore_count = sz - blk->size(); //# data count in front of this block
        while (pos < fore_count)
        {
            blk = blk->myprev();
            fore_count -= blk->size();
        }
        return blk->at(pos - fore_count);
    }

private:
    Blck_Ty *first;
    Blck_Ty *last;
    s64 sz;
};

}

#endif //# __INT_DEQUE_HPP__ ends
