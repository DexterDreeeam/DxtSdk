/* ********* * ********* * ********* * ********* * *********
 *
 * int_array.hpp
 *
 * proj: proj_2000_utils
 * desc: array container
 * autr: dexterdreeeam
 * date: 20200909
 * tips: same to STL
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_ARRAY_HPP__)
#define __INT_ARRAY_HPP__

START_NS(std)

template<typename Ty, s64 Sz>
class array;

template<typename Ctnr_Ty>
class array_iter;

template<typename Ctnr_Ty>
class array_ritr;

template<typename Ctnr_Ty>
class array_const_iter;

template<typename Ctnr_Ty>
class array_const_ritr;


template<typename Ty, s64 Sz>
class array_iter<array<Ty, Sz>>
{
    friend class array<Ty, Sz>;

    using Container_Ty = array<Ty, Sz>;
    using Self_Ty = array_iter<Container_Ty>;
    using Data_Ty = Ty;

public:
    array_iter() :
        data(nullptr)
    {}

    array_iter(const Self_Ty &rhs) :
        data(rhs.data)
    {}

    ~array_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        data = rhs.data;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        data = pointer_convert(data, sizeof(Data_Ty), Data_Ty*);
    }

    Self_Ty &operator --() noexcept
    {
        data = pointer_convert(data, -(s64)sizeof(Data_Ty), Data_Ty*);
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, sizeof(Data_Ty), Data_Ty*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, -(s64)sizeof(Data_Ty), Data_Ty*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs)
    {
        return data == rhs.data;
    }

    bool operator !=(const Self_Ty &rhs)
    {
        return data != rhs.data;
    }

    Data_Ty *operator ->()
    {
        return data;
    }

    Data_Ty &operator *()
    {
        return *data;
    }

private:
    array_iter(Data_Ty *ptr) :
        data(ptr)
    {}

    Data_Ty *data;
};

template<typename Ty, s64 Sz>
class array_ritr<array<Ty, Sz>>
{
    friend class array<Ty, Sz>;

    using Container_Ty = array<Ty, Sz>;
    using Self_Ty = array_ritr<Container_Ty>;
    using Data_Ty = Ty;

public:
    array_ritr() :
        data(nullptr)
    {}

    array_ritr(const Self_Ty &rhs) :
        data(rhs.data)
    {}

    ~array_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        data = rhs.data;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        data = pointer_convert(data, -(s64)sizeof(Data_Ty), Data_Ty*);
    }

    Self_Ty &operator --() noexcept
    {
        data = pointer_convert(data, sizeof(Data_Ty), Data_Ty*);
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, -(s64)sizeof(Data_Ty), Data_Ty*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, sizeof(Data_Ty), Data_Ty*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs)
    {
        return data == rhs.data;
    }

    bool operator !=(const Self_Ty &rhs)
    {
        return data != rhs.data;
    }

    Data_Ty *operator ->()
    {
        return data;
    }

    Data_Ty &operator *()
    {
        return *data;
    }

private:
    array_ritr(Data_Ty *ptr) :
        data(ptr)
    {}

    Data_Ty *data;
};

template<typename Ty, s64 Sz>
class array_const_iter<array<Ty, Sz>>
{
    friend class array<Ty, Sz>;

    using Container_Ty = array<Ty, Sz>;
    using Self_Ty = array_const_iter<Container_Ty>;
    using Data_Ty = Ty;

public:
    array_const_iter() :
        data(nullptr)
    {}

    array_const_iter(const Self_Ty &rhs) :
        data(rhs.data)
    {}

    ~array_const_iter() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        data = rhs.data;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        data = pointer_convert(data, sizeof(Data_Ty), Data_Ty*);
    }

    Self_Ty &operator --() noexcept
    {
        data = pointer_convert(data, -(s64)sizeof(Data_Ty), Data_Ty*);
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, sizeof(Data_Ty), Data_Ty*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, -(s64)sizeof(Data_Ty), Data_Ty*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs)
    {
        return data == rhs.data;
    }

    bool operator !=(const Self_Ty &rhs)
    {
        return data != rhs.data;
    }

    const Data_Ty *operator ->()
    {
        return data;
    }

    const Data_Ty &operator *()
    {
        return *data;
    }

private:
    array_const_iter(const Data_Ty *ptr) :
        data(ptr)
    {}

    const Data_Ty *data;
};

template<typename Ty, s64 Sz>
class array_const_ritr<array<Ty, Sz>>
{
    friend class array<Ty, Sz>;

    using Container_Ty = array<Ty, Sz>;
    using Self_Ty = array_const_ritr<Container_Ty>;
    using Data_Ty = Ty;

public:
    array_const_ritr() :
        data(nullptr)
    {}

    array_const_ritr(const Self_Ty &rhs) :
        data(rhs.data)
    {}

    ~array_const_ritr() noexcept = default;

    Self_Ty &operator =(const Self_Ty &rhs) noexcept
    {
        data = rhs.data;
        return *this;
    }

    Self_Ty &operator ++() noexcept
    {
        data = pointer_convert(data, -(s64)sizeof(Data_Ty), Data_Ty*);
    }

    Self_Ty &operator --() noexcept
    {
        data = pointer_convert(data, sizeof(Data_Ty), Data_Ty*);
    }

    Self_Ty operator ++(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, -(s64)sizeof(Data_Ty), Data_Ty*);
        return ret;
    }

    Self_Ty operator --(int) noexcept
    {
        Self_Ty ret(data);
        data = pointer_convert(data, sizeof(Data_Ty), Data_Ty*);
        return ret;
    }

    bool operator ==(const Self_Ty &rhs)
    {
        return data == rhs.data;
    }

    bool operator !=(const Self_Ty &rhs)
    {
        return data != rhs.data;
    }

    const Data_Ty *operator ->()
    {
        return data;
    }

    const Data_Ty &operator *()
    {
        return *data;
    }

private:
    array_const_ritr(const Data_Ty *ptr) :
        data(ptr)
    {}

    const Data_Ty *data;
};


template<typename Ty, s64 Sz>
class array
{
    using Self_Ty = array<Ty, Sz>;
    using Data_Ty = Ty;
    using Iter_Ty = array_iter<Self_Ty>;
    using Ritr_Ty = array_ritr<Self_Ty>;
    using cIter_Ty = array_const_iter<Self_Ty>;
    using cRitr_Ty = array_const_ritr<Self_Ty>;

    friend class array_iter<Self_Ty>;
    friend class array_ritr<Self_Ty>;
    friend class array_const_iter<Self_Ty>;
    friend class array_const_ritr<Self_Ty>;

public:
    Ty &operator [](s64 pos) noexcept
    {
        assert(Sz > 0);
        assert(pos >= 0 && pos < Sz);
        return elem[pos];
    }

    const Ty &operator [](s64 pos) const noexcept
    {
        assert(Sz > 0);
        assert(pos >= 0 && pos < Sz);
        return elem[pos];
    }

    Ty &front() noexcept
    {
        assert(Sz > 0);
        return elem[0];
    }

    const Ty &front() const noexcept
    {
        assert(Sz > 0);
        return elem[0];
    }

    Ty &back() noexcept
    {
        assert(Sz > 0);
        return elem[Sz - 1];
    }

    const Ty &back() const noexcept
    {
        assert(Sz > 0);
        return elem[Sz - 1];
    }

    Iter_Ty begin() noexcept
    {
        assert(Sz >= 0);
        return Iter_Ty(data());
    }

    cIter_Ty cbegin() const noexcept
    {
        assert(Sz >= 0);
        return cIter_Ty(data());
    }

    Iter_Ty end() noexcept
    {
        assert(Sz >= 0);
        return Iter_Ty(data() + Sz);
    }

    cIter_Ty cend() const noexcept
    {
        assert(Sz >= 0);
        return cIter_Ty(data() + Sz);
    }

    Ritr_Ty rbegin() noexcept
    {
        assert(Sz >= 0);
        return Ritr_Ty(data() + Sz - 1);
    }

    cRitr_Ty crbegin() const noexcept
    {
        assert(Sz >= 0);
        return cRitr_Ty(data() + Sz - 1);
    }

    Ritr_Ty rend() noexcept
    {
        assert(Sz >= 0);
        return Ritr_Ty(data() - 1);
    }

    cRitr_Ty crend() const noexcept
    {
        assert(Sz >= 0);
        return cRitr_Ty(data() - 1);
    }

    Ty *data() noexcept
    {
        assert(Sz > 0);
        return &elem[0];
    }

    const Ty *data() const noexcept
    {
        assert(Sz > 0);
        return &elem[0];
    }

    const s64 size() const noexcept
    {
        return Sz;
    }

public:
    Ty elem[Sz];
};

END_NS(std)

#endif //# __INT_ARRAY_HPP__ ends
