#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "exception.h"

// 顺序表

namespace DTLib
{
template <typename T>
class SeqList : public List<T>
{
protected:
    T* m_array;   // 顺序存储空间
    int m_length; // 当前线性表长度
public:
    bool insert(int i, const T& e)
    {
        // 目标位置合法性判断
        bool ret = ((0 <= i) && (i <= m_length));

        ret = ret && (m_length < capacity());

        if(ret)
        {
            for(int p = m_length-1; p >= i; p--) // O(n)
            {
                m_array[p + 1] = m_array[p]; // 向后移动
            }
            m_array[i] = e;  // 插入
            m_length++;      // 长度加1
        }

        return ret;
    }

    bool insert(const T& e)
    {
        return insert(m_length, e);
    }

    bool remove(int i)
    {
        bool ret = ((0 <= i) && (i < m_length));

        if(ret)
        {
            for(int p = i; p < m_length-1; p++)
            {
                m_array[p] = m_array[p+1];
            }
            m_length--;
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
         bool ret = ((0 <= i) && (i < m_length));

         if(ret)
         {
             m_array[i] = 0;
         }

         return ret;
    }

    bool get(int i, T& e) const
    {
         bool ret = ((0 <= i) && (i < m_length));

         if(ret)
         {
             e = m_array[i];
         }

         return ret;
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        m_length = 0;
    }

    int find(const T& e) const // O(n)
    {
        int ret = -1;

        for(int i = 0; i < m_length; i++)
        {
            if(m_array[i] == e)
            {
                ret = i;
                break;
            }
        }

        return ret;
    }

    // 顺序存储线性表的数组访问方式
    T& operator[] (int i)
    {
        if((0 <= i) && (i < m_length))
        {
            return m_array[i];
        }
        else
        {
            // 不合法抛异常
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }

    T operator[] (int i) const
    {
        // const_cast<SeqList<T>&>(*this) 剔除const属性后，
        // 就可以使用非const模板
        return (const_cast<SeqList<T>&>(*this))[i];
    }

    // 顺序存储空间的容量
    virtual int capacity() const = 0;
};

}


#endif // SEQLIST_H
