#ifndef DTSTRING_H
#define DTSTRING_H

#include "Object.h"

namespace DTLib
{

class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    // 比对函数
    bool equal(const char* l, const char* r, int len) const;

    // KMP
    static int* make_pmt(const char* p);
    static  int kmp(const char* s, const char* p);

public:
    String();
    String(char c);
    String(const char* s);
    String(const String& s);

    int length() const;
    const char* str() const; // 与传统c语言字符串进行互操作

    // 判断是否以指定字符串开始或结束
    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;

    // 在指定位置处插入字符串
    String& insert(int i, const char* s);
    String& insert(int i, const String& s);

    // 去掉字符串两端的空白
    String& trim();

    /* 基于KMP，对字符串的操作 */

    // 查找子串s在字符串中的位置
    int indexOf(const char* s) const;
    int indexOf(const String& s) const;
    // 在字符串中将指定的子串删除
    String& remove(int i, int len);
    String& remove(const char* s);
    String& remove(const String& s);
    // 字符串中的子串替换
    String& replace(const char* t, const char* s);
    String& replace(const String& t, const char* s);
    String& replace(const char* t, const String& s);
    String& replace(const String& t, const String& s);
    // 从字符串中创建子串
    String sub(int i, int len) const;


    // 数组访问操作符重载
    char& operator [] (int i);
    char operator [] (int i) const;
    bool operator == (const String& s) const;
    bool operator == (const char* s) const;
    bool operator != (const String& s) const;
    bool operator != (const char* s) const;
    bool operator > (const String& s) const;
    bool operator > (const char* s) const;
    bool operator < (const String& s) const;
    bool operator < (const char* s) const;
    bool operator >= (const String& s) const;
    bool operator >= (const char* s) const;
    bool operator <= (const String& s) const;
    bool operator <= (const char* s) const;
    
    String operator + (const String& s) const;
    String operator + (const char* s) const;
    String& operator += (const String& s);
    String& operator += (const char* s);

     // 使用remove实现字符串间的减法操作
    String operator - (const String& s) const;
    String operator - (const char* s) const;
    String& operator -= (const String& s);
    String& operator -= (const char* s);
    
    String& operator = (const String& s);
    String& operator = (const char* s);
    String& operator = (char c);

    ~String();

};

}

#endif // DTSTRING_H
