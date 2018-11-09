#ifndef POINTER_H
#define POINTER_H

#include <iostream>
#include "Object.h"

// 智能指针抽象类
namespace DTLib
{

template <typename T>
class Pointer : public Object
{
protected:
    T* m_pointer;

public:
    Pointer(T* p = NULL)
    {
        m_pointer = p;
    }

    T* operator-> ()
    {
        return m_pointer;
    }

    T& operator* ()
    {
        return *m_pointer;
    }

    // const 重载
    const T* operator-> () const
    {
        return m_pointer;
    }

    const T& operator* () const
    {
        return *m_pointer;
    }

    bool isNull() const
    {
        return (m_pointer == NULL);
    }

    T* get() const
    {
        return m_pointer;
    }

};

}

#endif // POINTER_H
