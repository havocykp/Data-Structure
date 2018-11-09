#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "duallinklist.h"
#include "LinuxList.h"
#include "exception.h"

// 双向循环链表

namespace DTLib
{

template <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    ////////////////////////
    Node node;
    list_head* ld =  &node.head;
    // pn1 和 pn2 是否相等？？
    Node* pn1 = reinterpret_cast<Node*>(ld);
    Node* pn2 = list_entry(ld, Node, head);
    ///////////////////////

    list_head m_header;
    list_head* m_current;

    list_head* position(int i) const
    {
        list_head* ret = const_cast<list_head*>(&m_header);

        for(int p = 0; p < i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

public:
    DualCircleList()
    {
        this->m_length = 0;
        this->m_step = 1;

        m_current = NULL;

        INIT_LIST_HEAD(&m_header);
    }

    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = true;
        Node* node = new Node();

        i = i% (this->m_length + 1);

        if(node != NULL)
        {
            node->value = e;

            list_add_tail(&node->head, position(i)->next);

            this->m_length++;
        }
        else
        {
            // 结点创建不成功，抛异常
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");

        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        ret = ((0 <= i) && (i < this->m_length));

        if(ret)
        {
            list_head* toDel = position(i)->next;

            if(m_current == toDel)
            {
                m_current = toDel->next;
            }

            list_del(toDel);

            this->m_length--;

            delete list_entry(toDel, Node, head);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = true;

        i = mod(i);

        ret = ((0 <= i) && (i < this->m_length));

        if(ret)
        {

            list_entry(position(i)->next, Node, head)->value = e;
        }

        return ret;
    }

    virtual T get(int i) const
    {
        T ret;

        if(get(i, ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter is to get element ...");
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = true;
        i = mod(i);
        ret = ((0 <= i) && (i < this->m_length));

        if(ret)
        {

            e = list_entry(position(i)->next, Node, head)->value;
        }

        return ret;
    }

    int find(const T& e) const
    {
        int ret = -1;
        int i = 0;
        list_head* slider = NULL;

        list_for_each(slider, &m_header)
        {
            if(list_entry(slider, Node, head)->value == e)
            {
                ret = i;
                break;
            }

            i++;
        }

        return ret;
    }

    int length() const
    {
        return this->m_length;
    }

    void clear()
    {
        while(this->m_length > 0)
        {
            remove(0);
        }
    }

    bool move(int i, int step = 1)
    {
        bool ret = (step > 0);

        i = mod(i);

        ret = ret && ((0 <= i) && (i < this->m_length));

        if(ret)
        {
            m_current = position(i)->next;

            this->m_step = step;
        }

        return ret;
    }

    bool end()
    {
        return (m_current == NULL) || (this->m_length == 0);
    }

    virtual T current()
    {
        //if(m_current != NULL)
        if(!end())
        {
            return list_entry(m_current, Node, head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    //  移动游标
    bool next()
    {
        int i = 0;

        while((i < this->m_step) && !end())
        {
           if(m_current != &m_header)
           {
               m_current = m_current->next;
               i++;
           }
           else
           {
               m_current = m_current->next;
           }
        }

        if(m_current == &m_header)
        {
            m_current = m_current->next;
        }

        return (i == this->m_step);
    }

    bool pre()
    {
       int i = 0;

       while((i < this->m_step) && !end())
       {
          if(m_current != &m_header)
          {
              m_current = m_current->prev;
              i++;
          }
          else
          {
              m_current = m_current->prev;
          }
       }

       if(m_current == &m_header)
       {
           m_current = m_current->prev;
       }

       return (i == this->m_step);
    }

    ~DualCircleList()
    {
        clear();
    }

};

}

#endif // DUALCIRCLELIST_H
