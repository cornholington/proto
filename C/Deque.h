/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *  @file
 *    basic double-ended queue, intended to be embedded as a member
 *     of an object
 */

#ifndef CHIP_DEQUE_H
#define CHIP_DEQUE_H

#include <stddef.h>

namespace chip {

/**
 *  @class Deque
 *
 *  embed-able double-ended queue item with a recovery pointer
 *
 */
template <class T>
class Deque
{

public:
    Deque(T * me) : me(me) { mNext = mPrev = this; };
    ~Deque() { Remove(); };

    Deque * Next() { return mNext; }
    Deque * Prev() { return mPrev; }
    T * Me() { return me; }

    void Remove()
    {
        mNext->mPrev = mPrev;
        mPrev->mNext = mNext;
        mNext = mPrev = this;
    }

    /**
     * @brief iterate over the list, starting from
     *     this item, until fn() returns true.  Returns
     *     item->me of the match or NULL if no match.
     *  Mutation of the list during fn() should be avoided
     */
    template <typename Functor>
    T * Find(Functor fn) const
    {
        Deque * next = nullptr;
        for (Deque * item = this; next != this; item = next)
        {
            next = item->mNext;

            // skip any "head" node we encounter
            if (item->me != nullptr)
            {
                if (fn(item))
                {
                    return item->me;
                }
            }
            item = next;
        }
        return nullptr;
    }

    /**
     * @brief iterate over the list, starting from
     *     this item, until fn() returns true.  Returns
     *     item->me of the match or NULL if no match.
     *  Mutation of the list during fn() should be avoided
     */
    template <typename Functor>
    T * FindR(Functor fn) const
    {
        Deque * prev = nullptr;
        for (Deque * item = mPrev; prev != mPrev; item = prev)
        {
            prev = item->mPrev;
            // skip any "head" node we encounter
            if (item->me != nullptr)
            {
                if (fn(item->me))
                {
                    return item;
                }
            }
            item = prev;
        }
    }

    /**
     * @brief iterate over items in the list, starting from
     *     this item.
     *  Mutation of the list during fn() should be avoided
     */
    template <typename Functor>
    void Foreach(Functor fn)
    {
        Deque * next = nullptr;
        for (Deque * item = this; next != this; item = next)
        {
            next = item->mNext;
            if (item->me != nullptr)
            {
                fn(item->me);
            }
            item = next;
        }
    }

    /**
     * @brief iterate over items in the list, starting from
     *    the last item
     *  Mutation of the list during fn() should be avoided
     */
    template <typename Functor>
    void ForeachR(Functor fn)
    {
        Deque * prev = nullptr;
        for (Deque * item = mPrev; prev != mPrev; item = prev)
        {
            prev = item->mPrev;
            if (item->me != nullptr)
            {
                fn(item->me);
            }
            item = prev;
        }
    }

    /**
     * @brief insert item (might be a list) as this node's
     *   previous pointer. This is logically equivalent to
     *   Append() or PushBack() when the subject Deque is
     *   the head of the list.
     *
     * if item is a head pointer, skip the head pointer
     */
    void Insert(Deque * item)
    {
        if (item->me == nullptr)
        {
            if (item->mNext == item)
            {
                // empty list
                return;
            }

            // pull the items off old head
            Deque * head = item;

            item = item->mNext;
            head->Remove();
        }
        Deque * prev = mPrev; // save off my prev

        prev->mNext  = item;        // last node's next gets item
        mPrev        = item->mPrev; // back pointer gets end of new list
        item->mPrev  = prev;        // item's prev gets my last node
        mPrev->mNext = this;        // fix tail node
    }

private:
    Deque * mNext;
    Deque * mPrev;
    T * me; // when null, is treated as a "head" node
};

} // namespace chip

#endif /* CHIP_DEQUE */
