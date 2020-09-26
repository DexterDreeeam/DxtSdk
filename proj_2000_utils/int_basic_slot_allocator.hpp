/* ********* * ********* * ********* * ********* * *********
 *
 * int_basic_slot_allocator.hpp
 *
 * proj: proj_2000_utils
 * desc: basic slot allocator struct for containers
 * autr: dexterdreeeam
 * date: 20200907
 * tips: same slot size container, non-thread-safe
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_BASIC_SLOT_ALLOCATOR_HPP__)
#define __INT_BASIC_SLOT_ALLOCATOR_HPP__

#include "../proj_1000_xos/ext_xos_interface.hpp"

namespace std
{

const s64 slot_allocator_default_cap = 4LL;

template<s64 DataSz>
class slot_allocator
{
    using Self_Ty = slot_allocator<DataSz>;

    template<s64 SlotDataSz>
    struct _slot
    {
        _slot() :
            data(),
            prev(this),
            next(this)
        {}

        u8     data[SlotDataSz];
        _slot *prev;
        _slot *next;
    };

    template<s64 BlockDataSz>
    struct _block
    {
        _block(s64 sz) :
            next(nullptr),
            slots_cnt(sz)
        {}

        _block<BlockDataSz> *next;
        s64                  slots_cnt;
        _slot<BlockDataSz>   slots[0];
    };

public:
    slot_allocator() :
        size(slot_allocator_default_cap),
        cap(slot_allocator_default_cap),
        slot_head()
    {
        block_head = pointer_convert(memory_alloc(sizeof(_block<DataSz>) + sizeof(_slot<DataSz>) * cap), 0, _block<DataSz>*);
        block_head->next = nullptr;
        block_head->slots_cnt = cap;

        for (s64 i = 0; i != cap; ++i)
        {
            _slot<DataSz> *slot = &block_head->slots[i];
            slot->prev = slot_head.prev;
            slot->next = &slot_head;
            slot->prev->next = slot;
            slot->next->prev = slot;
        }
    }

    slot_allocator(s64 cap) :
        size(cap),
        cap(cap),
        slot_head()
    {
        block_head = pointer_convert(memory_alloc(sizeof(_block<DataSz>) + sizeof(_slot<DataSz>) * cap), 0, _block<DataSz>*);
        block_head->next = nullptr;
        block_head->slots_cnt = cap;

        for (s64 i = 0; i != cap; ++i)
        {
            _slot<DataSz> *slot = &block_head->slots[i];
            slot->prev = slot_head.prev;
            slot->next = &slot_head;
            slot->prev->next = slot;
            slot->next->prev = slot;
        }
    }

    slot_allocator(Self_Ty &&rhs) noexcept :
        size(rhs.size),
        cap(rhs.cap)
    {
        slot_head.prev = rhs.slot_head.prev;
        slot_head.next = rhs.slot_head.next;
        block_head = rhs.block_head;

        rhs.size = 0;
        rhs.cap = 0;
        rhs.slot_head.prev = nullptr;
        rhs.slot_head.next = nullptr;
        rhs.block_head = nullptr;
    }

    Self_Ty &operator =(Self_Ty &&rhs) noexcept
    {
        _block<DataSz> *blk = block_head;
        while (blk)
        {
            _block<DataSz> *blk_next = blk->next;
            memory_free(pointer_convert(blk, 0, void*));
            blk = blk_next;
        }

        size = rhs.size;
        cap = rhs.cap;
        slot_head.prev = rhs.slot_head.prev;
        slot_head.next = rhs.slot_head.next;
        slot_head.prev->next = &slot_head;
        slot_head.next->prev = &slot_head;
        block_head = rhs.block_head;

        rhs.size = 0;
        rhs.cap = 0;
        rhs.slot_head.prev = nullptr;
        rhs.slot_head.next = nullptr;
        rhs.block_head = nullptr;
        return *this;
    }

    ~slot_allocator() noexcept
    {
        _block<DataSz> *blk = block_head;
        while (blk)
        {
            _block<DataSz> *blk_next = blk->next;
            memory_free(pointer_convert(blk, 0, void*));
            blk = blk_next;
        }
    }

    void *get() noexcept
    {
        if (size == 0)
        {
            append_block(cap);
        }

        --size;
        _slot<DataSz> *slot = slot_head.next;
        slot->next->prev = slot->prev;
        slot->prev->next = slot->next;
        slot->next = nullptr;
        slot->prev = nullptr;

        return pointer_convert(slot, 0, void*);
    }

    void put(void *p) noexcept
    {
        _slot<DataSz> *slot = pointer_convert(p, 0, _slot<DataSz>*);
        slot->prev = slot_head.prev;
        slot->next = &slot_head;
        slot->prev->next = slot;
        slot->next->prev = slot;

        ++size;
    }

private:
    void append_block(s64 block_sz)
    {
        _block<DataSz> *new_block = pointer_convert(memory_alloc(sizeof(_block<DataSz>) + sizeof(_slot<DataSz>) * block_sz), 0, _block<DataSz>*);
        assert(new_block);
        new_block->slots_cnt = block_sz;

        for (s64 i = 0; i != block_sz; ++i)
        {
            _slot<DataSz> *slot = &new_block->slots[i];
            slot->prev = slot_head.prev;
            slot->next = &slot_head;
            slot->prev->next = slot;
            slot->next->prev = slot;
        }

        new_block->next = block_head;
        block_head = new_block;
        cap += block_sz;
        size += block_sz;
    }

private:
    s64             size;
    s64             cap;
    _slot<DataSz>   slot_head;
    _block<DataSz> *block_head;
};

}

#endif //# __INT_BASIC_SLOT_ALLOCATOR_HPP__ ends
