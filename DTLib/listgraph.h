#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "graph.h"
#include "linklist.h"
#include "exception.h"
#include "dynamicarray.h"

// 邻接链表图类型

namespace DTLib
{

template <typename V, typename E>
class ListGraph : public Graph<V, E>
{
protected:
    struct Vertex : public Object
    {
        V* data;
        LinkList<Edge<E> > edge;

        Vertex()
        {
            data = NULL;
        }
    };

    LinkList<Vertex*> m_list; // 邻接链表

public:
    ListGraph(unsigned int n = 0)
    {
        for(unsigned int i = 0; i < n; i++)
        {
            addVertex();
        }
    }

    int addVertex()  // O(n)
    {
        int ret = -1;
        Vertex* v = new Vertex();

        if(v != NULL)
        {
            m_list.insert(v);

            ret = m_list.length() - 1; // 编号
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new vertex object ...");
        }

        return ret;
    }

    int addVertex(const V& value)  // O(n)
    {
        int ret = addVertex();

        if(ret >= 0)
        {
            setVertex(ret, value);
        }

        return ret;
    }

    bool setVertex(int i, const V& value)  // O(n)
    {
        int ret = ((0 <= i) && (i < vCount()));

        if(ret)
        {
            Vertex* vertex = m_list.get(i);
            V* data = vertex->data;

            if( data == NULL)
            {
                data = new V();
            }

            if(data != NULL)
            {
                *data = value;

                vertex->data = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new vertex value ...");
            }
        }

        return ret;
    }

    V getVertex(int i)
    {
        V ret;

        if(!getVertex(i, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    bool getVertex(int i, V& value)  // O(n)
    {
        int ret ((0 <= i) && (i < vCount()));

        if(ret)
        {
            Vertex* v = m_list.get(i);

            if(v->data != NULL)
            {
                value = *(v->data);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
            }
        }

        return ret;
    }

    void removeVertex()  // O(n*n)
    {
        if(m_list.length() > 0)
        {
            int index = m_list.length() - 1;
            Vertex* v = m_list.get(index);  // O(n)

            if(m_list.remove(index))
            {
//                int i = 0;

//                for(m_list.move(0); !m_list.end(); m_list.next())
                for(int i = (m_list.move(0), 0); !m_list.end(); i++, m_list.next())  // O(n)
                {
                    int pos = m_list.current()->edge.find(Edge<E>(i, index));  // O(n)

                    if(pos >= 0)
                    {
                        m_list.current()->edge.remove(pos);
                    }

               //     i++;
                }

                delete v->data;
                delete v;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No vertex in current graph ...");
        }

    }

    SharedPointer<Array<int> > getAdjacent(int i)  // O(n)
    {
        DynamicArray<int>* ret = NULL;

        if((0 <= i) && (i < vCount()))
        {
            Vertex* vertex = m_list.get(i);

            ret = new DynamicArray<int>(vertex->edge.length());

            if(ret != NULL)
            {
                for(int k = (vertex->edge.move(0), 0); !vertex->edge.end(); k++, vertex->edge.next())
                {
                    ret->set(k, vertex->edge.current().e);
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }
    }

    bool isAdjacent(int i, int j)
    {
        return (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) && (m_list.get(i)->edge.find(Edge<E>(i, j)) >= 0);
    }

    E getEdge(int i, int j)  // O(n)
    {
        E ret;

        if(!getEdge(i, j, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Edge <i, j> is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value)  // O(n)
    {
        int ret = ((0 <= i) && (i < vCount()) &&
                   (0 <= j) && (j < vCount())) ;

        if(ret)
        {
            Vertex* vertex = m_list.get(i);

            int pos = vertex->edge.find(Edge<E>(i, j));

            if(pos >= 0)
            {
                value = vertex->edge.get(pos).data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)  // O(n)
    {
        int ret = ((0 <= i) && (i < vCount()) &&
                   (0 <= j) && (j < vCount())) ;

        if(ret)
        {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i, j));

            if(pos >= 0)
            {
                ret = vertex->edge.set(pos, Edge<E>(i, j, value));
            }
            else
            {
                ret = vertex->edge.insert(0, Edge<E>(i, j, value));
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j)  // O(n)
    {
        int ret = ((0 <= i) && (i < vCount()) &&
                   (0 <= j) && (j < vCount())) ;

        if(ret)
        {
            Vertex* vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i, j));

            if(pos >= 0)
            {
                ret = vertex->edge.remove(pos);
            }
        }

        return ret;
    }

    int vCount()  // O(1)
    {
        return m_list.length();
    }

    int eCount()  // O(n)
    {
        int ret = 0;

        for(m_list.move(0); !m_list.end(); m_list.next())
        {
            ret += m_list.current()->edge.length();
        }
        return ret;
    }

    int ID(int i)  // O(n*n)
    {
        int ret = 0;

        if((0 <= i) && (i < vCount()))
        {
            for(m_list.move(0); !m_list.end(); m_list.next())
            {
                LinkList<Edge<E> >& edge = m_list.current()->edge;

                for(edge.move(0); !edge.end(); edge.next())
                {
                    if(edge.current().e == i)
                    {
                        ret++;
                        break;
                    }
                }

            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    int OD(int i)  // O(n)
    {
        int ret = 0;

        if((0 <= i) && (i < vCount()))
        {
            ret = m_list.get(i)->edge.length();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }
    }

    ~ListGraph()
    {
        Vertex* toDel = m_list.get(0);

        m_list.remove(0);

        delete toDel->data;
        delete toDel;
    }
};



}

#endif // LISTGRAPH_H
