#include "Object.h"
#include <iostream>
#include <cstdlib>

using namespace std;

namespace DTLib
{

void *Object::operator new(unsigned int size) throw()
{
   // cout << "Object::operator new:" << size << endl;
    return malloc(size);
}

void Object::operator delete(void *p)
{
   // cout << "Object::operator delete:" << p << endl;
    free(p);
}

void *Object::operator new[](unsigned int size) throw()
{
    return malloc(size);
}

void Object::operator delete[](void *p)
{
    free(p);
}

bool Object::operator ==(const Object &obj)
{
    return (this == &obj);
}

bool Object::operator !=(const Object &obj)
{
    return (this != &obj);
}

Object::~Object()
{

}

}


