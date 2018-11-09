#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include "Object.h"

// 异常类

namespace DTLib
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

// 顶层异常类
class Exception : public Object
{
protected:
    char* m_message;
    char* m_location;

    // 辅助函数完成初始化
    void init(const char* message, const char* file, int line);

public:
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator= (const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception() = 0; // 纯虚函数
};

//  计算异常
class ArithmeticException : public Exception
{
public:
    // 无参构造
    ArithmeticException() : Exception(NULL){}
    // 带一个参数的构造
    ArithmeticException(const char* message) : Exception(message){}
    // 带两个参数的构造
    ArithmeticException(const char* file, int line ) : Exception(file, line){}
    // 带三个参数的构造
    ArithmeticException(const char* message, const char* file, int line) : Exception(message, file, line){}

    // 拷贝构造
    ArithmeticException(const ArithmeticException& e) : Exception(e){}
    // 赋值操作符重载
    ArithmeticException& operator= (const ArithmeticException& e)
    {
        Exception::operator=(e);

        return *this;
    }

};

// 空指针异常
class NullPointerException : public Exception
{
 public:
    // 无参构造
    NullPointerException() : Exception(NULL){}
    // 带一个参数构造
    NullPointerException(const char* message) : Exception(message){}
    // 带两个参数构造
    NullPointerException(const char* file, int line) : Exception(file, line){}
    // 带三个参数构造
    NullPointerException(const char* message, const char* file, int line) : Exception(message, file, line){}

    // 拷贝构造
    NullPointerException(const NullPointerException& e) : Exception(e){}
    // 赋值操作符重载
    NullPointerException& operator= (const NullPointerException& e)
    {
        Exception::operator=(e);

        return *this;
    }

};

// 越界异常
class IndexOutOfBoundsException : public Exception
{
public:
    // 无参构造
    IndexOutOfBoundsException() : Exception(NULL){}
    // 带一个参数构造
    IndexOutOfBoundsException(const char* message) : Exception(message){}
    // 带两个参数构造
    IndexOutOfBoundsException(const char* file, int line) : Exception(file, line){}
    // 带三个参数构造
    IndexOutOfBoundsException(const char* message, const char* file, int line) : Exception(message, file, line){}

    // 拷贝构造
    IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e){}
    // 赋值操作符重载
    IndexOutOfBoundsException& operator= (const IndexOutOfBoundsException& e)
    {
        Exception::operator=(e);
        return *this;
    }

};

// 内存不足异常
class NoEnoughMemoryException : public Exception
{
public:
    // 无参构造
    NoEnoughMemoryException() : Exception(NULL){}
    // 带一个参数构造
    NoEnoughMemoryException(const char* message) : Exception(message){}
    // 带两个参数构造
    NoEnoughMemoryException(const char* file, int line) : Exception(file, line){}
    // 带三个参数构造
    NoEnoughMemoryException(const char* message, const char* file, int line) : Exception(message, file, line){}

    // 拷贝构造
    NoEnoughMemoryException(const NoEnoughMemoryException& e) : Exception(e){}
    // 赋值操作符重载
    NoEnoughMemoryException& operator= (const NoEnoughMemoryException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

// 参数错误异常
class InvalidParameterException : public Exception
{
public:
    // 无参构造
    InvalidParameterException() : Exception(NULL){}
    // 带一个参数构造
    InvalidParameterException(const char* message) : Exception(message){}
    // 带两个参数构造
    InvalidParameterException(const char* file, int line) : Exception(file, line){}
    // 带三个参数构造
    InvalidParameterException(const char* message, const char* file, int line) : Exception(message, file, line){}
    
    // 拷贝构造
    InvalidParameterException(const InvalidParameterException& e) : Exception(e){}
    // 赋值操作符重载
    InvalidParameterException& operator= (const InvalidParameterException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};


class InvalidOperationException : public Exception
{
public:
    // 无参构造
    InvalidOperationException() : Exception(NULL){}
    // 带一个参数构造
    InvalidOperationException(const char* message) : Exception(message){}
    // 带两个参数构造
    InvalidOperationException(const char* file, int line) : Exception(file, line){}
    // 带三个参数构造
    InvalidOperationException(const char* message, const char* file, int line) : Exception(message, file, line){}

    // 拷贝构造
    InvalidOperationException(const InvalidOperationException& e) : Exception(e){}
    // 赋值操作符重载
    InvalidOperationException& operator= (const InvalidOperationException& e)
    {
        Exception::operator=(e);
        return *this;
    }
};

}
#endif // EXCEPTION_H
