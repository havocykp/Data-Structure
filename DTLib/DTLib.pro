TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    Exception.cpp \
    Object.cpp \
    DtString.cpp

HEADERS += \
    SmartPointer.h \
    Exception.h \
    List.h \
    Object.h \
    Seqlist.h \
    StaticList.h \
    DynamicList.h \
    Array.h \
    StaticArray.h \
    DynamicArray.h \
    LinkList.h \
    StaticLinkList.h \
    Pointer.h \
    SharedPointer.h \
    CircleList.h \
    DualLinkList.h \
    LinuxList.h \
    DualCircleList.h \
    Stack.h \
    StaticStack.h \
    LinkStack.h \
    Queue.h \
    StaticQueue.h \
    LinkQueue.h \
    DtString.h \
    Sort.h \
    TreeNode.h \
    Tree.h \
    GTreeNode.h \
    GTree.h \
    BTree.h \
    BTreeNode.h \
    Graph.h \
    MatrixGraph.h \
    ListGraph.h
