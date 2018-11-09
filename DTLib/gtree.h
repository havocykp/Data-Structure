#ifndef GTREE_H
#define GTREE_H

#include "tree.h"
#include "gtreenode.h"
#include "exception.h"
#include "linkqueue.h"


namespace DTLib
{

template <typename T>
class GTree : public Tree<T>
{
protected:
    LinkQueue<GTreeNode<T>*> m_queue;


    // 基于数据元素值的查找：判断值是否存在于树中
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                // 遍历当前结点的每一颗子树
                for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
                {
                    // 在子树中查找目标元素的值value
                   ret = find(node->child.current(), value);
                }
            }
        }

        return ret;
    }

    // 基于结点的查找：判断是否存在指定结点
    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;

        if(node == obj)
        {
            return node;
        }
        else
        {
            if(node != NULL)
            {
                for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
                {
                    // 在子树中查找目标结点
                    find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }

    void free(GTreeNode<T>* node)
    {
        if(node != NULL)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                free(node->child.current());
            }

            if(node->flag())
            {
                delete node;
            }
        }
    }

    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
       ret = new GTree<T>();

       if(ret == NULL)
       {
           THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
       }
       else
       {
           if(root() == node)
           {
               this->m_root = NULL;
           }
           else
           {
               LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;

               child.remove(child.find(node));

               node->parent = NULL;
           }
           ret->m_root = node;
       }
    }

    int count(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = 1;

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int h = height(node->child.current());

                if(ret < h)
                {
                    ret = h;
                }
            }

            ret = ret + 1;
        }

        return ret;
    }
    
    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;
        
        if(node != NULL)
        {
            ret = node->child.length();
            
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int d = degree(node->child.current());
                
                if(ret < d)
                {
                    ret = d;
                }
            }
        }
        
        return ret;
    }

public:
    GTree()
    {

    }

    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        if(node != NULL)
        {
            if(this->m_root == NULL)
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T>* np = find(node->parent);

                if(np != NULL)
                {
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);

                    if(np->child.find(n) < 0)
                    {
                        np->child.insert(n);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidOperationException, "Invalid parent tree node ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be NULL ...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;
        GTreeNode<T>* node = GTreeNode<T>::NewNode();

        if(node != NULL)
        {
            node->value = value;
            node->parent = parent;

            insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node ...");
        }

        return ret;
    }

    SharedPointer<Tree<T> > remove(const T& value)
    {
        GTree<T>* ret = NULL;
        GTreeNode<T>* node = find(value);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value ...");
        }
        else
        {
            remove(node, ret);
            m_queue.clear();
        }

        return ret;
    }

    SharedPointer<Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;

        node = find(node);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        }
        else
        {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret);
            m_queue.clear();
        }

        return ret;
    }

    GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());

        this->m_root = NULL;

        m_queue.clear();
    }
    /* 树的层序遍历 */
    // 遍历初始化函数
    bool begin()
    {
        bool ret = (root() != NULL);
        if(ret)
        {
            m_queue.clear();
            m_queue.add(root());
        }

        return ret;
    }

    bool end()
    {
        return(m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = (m_queue.length() > 0);

        if(ret)
        {
            GTreeNode<T>* node = m_queue.front();

            m_queue.remove();

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                m_queue.add(node->child.current());
            }
        }

        return ret;
    }

    T current()
    {
        if(!end())
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H
