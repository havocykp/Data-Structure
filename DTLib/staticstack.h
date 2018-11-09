#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "stack.h"
#include "exception.h"

// 顺序栈

/*
   缺陷：
    当存储的元素为类类型时，对象在创建时，
    会多次调用元素类型的构造函数，影响效率
*/

namespace DTLib
{

template <typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_top;
    int m_size;

public:
    StaticStack()  // O(1)
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity() const  // O(1)
    {
        return N;
    }

    void push(const T& e) // O(1)
    {
        if(m_size < N)
        {
            // 压栈
            m_space[m_top + 1] = e;
            m_top++;
            m_size++;
        }
        else
        {
           THROW_EXCEPTION(InvalidOperationException, "No space in current stack ...");
        }
    }

    void pop()  // O(1)
    {
        if(m_size > 0) // 判断栈中有无数据元素
        {
            m_top--;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const  // O(1)
    {
        if(m_size > 0) // 判断栈中有无数据元素
        {
           return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

     void clear()  // O(1)
     {
         m_top = -1;
         m_size = 0;
     }

     int size() const  // O(1)
     {
         return m_size;
     }
};

}

#endif // STATICSTACK_H
