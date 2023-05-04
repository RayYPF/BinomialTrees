#include <iostream>

using namespace std;
struct BINOMIALNODE
{
    int data;
    int degree;
    BINOMIALNODE *child;
    BINOMIALNODE *sibling;
    BINOMIALNODE *parent;

    BINOMIALNODE* newBinomialTree(int num)
    {
        BINOMIALNODE *bnode = new BINOMIALNODE;
        bnode->data = num;
        bnode->degree = 0;
        bnode->sibling;
        bnode->child = nullptr;
        bnode->parent = nullptr;
        bnode->sibling = nullptr;
        return bnode;
    }

    BINOMIALNODE* mergeBinomialTree(BINOMIALNODE *node1, BINOMIALNODE *node2)
    {
        if(node1->data > node2->data)
        {
            swap(node1, node2);
        }

        node2->parent = node1;
        node2->sibling = node1->child;
        node1->child = node2;
        node1->degree++;

        return node1;
    }

    BINOMIALNODE* mergeBinomialHeap(BINOMIALNODE *heap1, BINOMIALNODE *heap2)
    {
        BINOMIALNODE temp;
        
    }

};
