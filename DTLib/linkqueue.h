#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "queue.h"
#include "linklist.h"
#include "exception.h"

// 链式队列

namespace DTLib
{

template <typename T>
class LinkQueue : public Queue<T>
{
protected:
    LinkList<T> m_list;

public:
    LinkQueue()
    {

    }

    // 入队
    void add(const T& e)  // O(n)
    {
        m_list.insert(e);
    }

    void remove()  // O(1)
    {
        // 每次删除下标为0的元素
       if(m_list.length() > 0)
       {
           m_list.remove(0);
       }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const  // O(1)
    {
        if(m_list.length() > 0)
        {
           return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void clear()  // O(n)
    {
       m_list.clear();
    }

    int length() const  // O(1)
    {
        return m_list.length();
    }
};

}

#endif // LINKQUEUE_H
