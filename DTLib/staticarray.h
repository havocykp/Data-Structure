#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "array.h"

// 静态数组类，通过封装原生数组方式实现
namespace DTLib
{

template <typename T, int N>
class StaticArray : public Array<T>
{
protected:
    T m_space[N];
public:
    // 无参构造
    StaticArray() // O(1)
    {
        this->m_array = m_space;
    }

    // 拷贝构造和赋值操作
    StaticArray(const StaticArray<T, N>& obj) // O(n)
    {
        this->m_array = m_space;

        for(int i = 0; i < N; i++)
        {
            m_space[i] = obj.m_space[i];
        }
    }

    StaticArray<T, N>& operator= (const StaticArray<T, N>& obj) // O(n)
    {
        if(this != &obj) // 防止自赋值
        {
            for(int i = 0; i < N; i++)
            {
                m_space[i] = obj.m_space[i];
            }

            return *this;
        }
    }

    int length() const // O(1)
    {
        return N;
    }
};

}

#endif // STATICARRAY_H
