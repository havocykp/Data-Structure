#ifndef OBJECT_H
#define OBJECT_H

// 顶层父类
// 统一动态内存申请的行为
// 在堆中创建Object子类的对象，失败时返回NULL值
// Object类为纯虚父类，所有子类都能进行动态类型识别

namespace DTLib
{

class Object
{
public:
    void* operator new(unsigned int size) throw();
    void operator delete (void* p);
    void* operator new[] (unsigned int size) throw();
    void operator delete[] (void *p);
    bool operator == (const Object& obj);
    bool operator != (const Object& obj);
    virtual ~Object() = 0;
};

}

#endif // OBJECT_H
