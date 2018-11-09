#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "array.h"
#include "exception.h"

namespace DTLib
{
// 动态申请空间，使得数组长度动态可变

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    // 重复代码逻辑抽象(公有成员函数的实现依赖于保护成员函数的创建)
    T* copy(T* array, int len, int newLen) // O(min(len,newLen)) => O(n)
    {
        T* ret = new T[newLen];

        if(ret != NULL)
        {
            int size = (len < newLen) ? len : newLen;

            for(int i = 0; i < size; i++)
            {
                ret[i] = array[i];
            }
        }

        return ret;
    }

    void update(T* array, int length) // O(1)
    {
        if(array != NULL)
        {
            T* temp = this->m_array;

            this->m_array = array;
            this->m_length = length;

            delete[] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamicArray object ...");
        }
    }

    void init(T* array, int length) // O(1)
    {
        if(array != NULL)
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memroy to create DynamicArray object ...");
        }
    }

public:
    // 构造函数
    DynamicArray(int length = 0) // O(1)
    {
        init(new T[length], length);
//        ////////////////////////////////
//        this->m_array = new T[length];

//        if(this->m_array != NULL)
//        {
//            this->m_length = length;
//        }
//        else
//        {
//            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object ...");
//        }
    }

    // 拷贝构造
    DynamicArray(const DynamicArray<T>& obj) // O(n)
    {
        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
//        //////////////////////////////////////////
//        T* array = copy(obj.m_array, obj.m_length, obj.m_length);

//        init(array, obj.m_length);
//        //////////////////////////////////////////
//        this->m_array = new T[obj.m_length];

//        if(this->m_array != NULL)
//        {
//            this->m_length = obj.m_length;

//            for(int i = 0; i < obj.m_length; i++)
//            {
//                this->m_array[i] = obj.m_array[i];
//            }
//        }
//        else
//        {
//            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DyanmicArray object ...");
//        }
    }

    // 赋值操作符
    DynamicArray<T>& operator= (const DynamicArray<T>& obj) // O(n)
    {

        if(this != &obj)
        {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
//            ///////////////////////////////////////////////////////////////////
//            T* array = copy(obj.m_array, obj.m_length, obj.m_length);

//            update(array, obj.m_length);
//            //////////////////////////////////////////////////////////////////
//             T* array = new T[obj.m_length];
//             if(array != NULL)
//             {
//                 for(int i = 0; i < obj.m_length; i++)
//                 {
//                     array[i] = obj.m_array[i];
//                 }

//                 T* temp = this->m_array;

//                 this->m_array = array;
//                 this->m_length = obj.m_length;

//                 delete[] temp;
//             }
//             else
//             {
//                 THROW_EXCEPTION(NoEnoughMemoryException, "No memory to copy object ...");
//             }
         }

        return *this;
    }

    int length() const // O(1)
    {
        return m_length;
    }

    void resize(int length) // 动态重置数组的长度 O(n)
    {
        if(length != m_length)
        {
            update(copy(this->m_array, m_length, length), length);
//            ////////////////////////////////////////////////////
//            T* array = copy(this->m_array, m_length, length);

//            update(array, length);
//            ////////////////////////////////////////////////////
//            T* array = new T[length];

//            if(array != NULL)
//            {
//                int size = (length < m_length) ? length : m_length;

//                for(int i = 0; i < size; i++)
//                {
//                    array[i] = this->m_array[i];
//                }

//                T* temp = this->m_array;

//                this->m_array = array;
//                this->m_length = length;

//                delete[] temp;
//            }
//            else
//            {
//                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize object ...");
//            }
        }
    }

    ~DynamicArray() // O(1)
    {
        delete[] this->m_array;
    }
};

}

#endif // DYNAMICARRAY_H
