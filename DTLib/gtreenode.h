#ifndef GTREENODE_H
#define GTREENODE_H

#include "Tree.h"
#include "linklist.h"

namespace DTLib
{

template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

    // 工厂模式
    // 用于定制堆空间中的结点
    // 只有销毁定制结点的时候需要进行释放
    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }
};

}

#endif // GTREENODE_H
