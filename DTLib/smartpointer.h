#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <iostream>
#include "Pointer.h"

// 智能指针
// 指针生命周期结束时主动释放堆空间
// 一片堆空间最多只能由一个指针标识
// 杜绝指针运算和比较

namespace DTLib
{
template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p)
    {

    }

    // 拷贝构造
    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer; // 两个指针指向同一个地方
        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
    }

    // 赋值操作符
    SmartPointer<T>& operator= (const SmartPointer<T>& obj)
    {
         if(this != &obj) // 判断是否自赋值
         {
             T* p = this->m_pointer;

             this->m_pointer = obj.m_pointer;

             const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

             delete p;
         }

         return *this; // 返回自身，支持连续赋值
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};

}


#endif // SMARTPOINTER_H
