#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "exception.h"

namespace DTLib
{
// 数组抽象类
template <typename T>
class Array : public Object
{
protected:
    T* m_array;
public:
    virtual bool set(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i < length()));

        if(ret)
        {
            m_array[i] = e;
        }

        return ret;
    }

    virtual bool get(int i, T& e) const
    {
        bool ret = ((0 <= i) && (i < length()));

        if(ret)
        {
            e = m_array[i];
        }

        return ret;
    }

    // 数组访问操作符重载
    T& operator[] (int i)
    {
        if((0 <= i) && (i < length()))
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
        }
    }

    T operator[] (int i) const
    {
       return (const_cast<Array<T>&>(*this)[i]);
    }

    T* array() const
    {
        return m_array;
    }

    virtual int length() const = 0;
};

}

#endif // ARRAY_H
