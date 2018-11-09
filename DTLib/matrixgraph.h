#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "graph.h"
#include "exception.h"
#include "dynamicarray.h"

// 邻接矩阵图类型

namespace DTLib
{

template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E>
{
protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_eCount;

public:
    MatrixGraph()
    {
        for(int i = 0; i < vCount(); i++)
        {
            m_vertexes[i] = NULL;

            for(int j = 0; j < vCount(); j++)
            {
                m_edges[i][j] = NULL;
            }
        }

        m_eCount = 0;
    }

    V getVertex(int i)
    {
        V ret;

        if(!getVertex(i, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "No value assigned to this vertex ...");
        }

        return ret;
    }

    bool getVertex(int i, V& value)  // O(1)
    {
        bool ret = ((0 <= i) && (i < vCount()));

        if(ret)
        {
            if(m_vertexes[i] != NULL)
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
            }
        }

        return ret;
    }

    bool setVertex(int i, const V& value)  // O(1)
    {
        bool ret = ((0 <= i) && (i < vCount()));

        if(ret)
        {
            V* data = m_vertexes[i];

            if(data == NULL)
            {
               data = new V();
            }

            if(data != NULL)
            {
                *data = value;

                m_vertexes[i] = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new vertex value ...");
            }

        }

        return ret;
    }

    // 获取邻接顶点的编号
    SharedPointer< Array<int> > getAdjacent(int i)  // O(n)
    {
        DynamicArray<int>* ret = NULL;

        if((0 <= i) && (i < vCount()))
        {
            int n = 0;

            for(int j = 0; j < vCount(); j++)
            {
                if(m_edges[i][j] != NULL)
                {
                    n++;
                }
            }

            ret = new DynamicArray<int>(n);

            if(ret != NULL)
            {
                for(int j = 0, k = 0; j < vCount(); j++)
                {
                    if(m_edges[i][j] != NULL)
                    {
                        ret->set(k++, j);
                    }
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

        return ret;
    }

    bool isAdjacent(int i, int j)
    {
        return (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) && (m_edges[i][j] != NULL);
    }

    E getEdge(int i, int j)
    {
        E ret;

        if(!getEdge(i, j, ret))
        {
            THROW_EXCEPTION(InvalidParameterException, "Index<i, j> is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value)  //O(1)
    {
        bool ret = ((0 <= i) && (i < vCount()) &&
                (0 <= j) && (j < vCount()));
        if(ret)
        {
            if(m_edges[i][j] != NULL)
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)  //O(1)
    {
        bool ret = ((0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()));
        if(ret)
        {
            E* ne = m_edges[i][j];

            if(ne == NULL)
            {
                ne = new E();

                if( ne != NULL)
                {
                    *ne = value;

                    m_edges[i][j] = ne;

                    m_eCount++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new edge value ...");
                }
            }
            else
            {
                *ne = value;
            }
        }

        return ret;
    }

    bool removeEdge(int i, int j)  // O(1)
    {
        bool ret = ((0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()));
        if(ret)
        {
            E* toDel = m_edges[i][j];

            m_edges[i][j] = NULL;

            if(toDel != NULL)
            {
                m_eCount--;

                delete toDel;
            }

            m_edges[i][j] = NULL;
        }

        return ret;
    }
    int vCount()  // O(1)
    {
        return N;
    }

    // 顶点出度
    int eCount()  // O(1)
    {
        return m_eCount;
    }

    int OD(int i)  // O(n)
    {
        int ret = 0;

        if((0 <= i) && (i < vCount()))
        {
            for(int j = 0; j < vCount(); j++)
            {
                if(m_edges[i][j] != NULL)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    // 顶点入度
    int ID(int i)  // O(n)
    {
        int ret = 0;

        if((0 <= i) && (i < vCount()))
        {
            for(int j = 0; j < vCount(); j++)
            {
                if(m_edges[j][i] != NULL)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for(int i = 0; i < vCount(); i++)
        {

            for(int j = 0; j < vCount(); j++)
            {
                delete m_edges[i][j];
            }

            delete m_vertexes[i];
        }

    }
};

}

#endif // MATRIXGRAPH_H
