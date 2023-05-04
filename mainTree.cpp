#include <iostream>

using namespace std;
struct BINOMIALNODE
{
    int data; // the main data in this case a number
    int degree; // the degree k
    BINOMIALNODE *child; // child of the node
    BINOMIALNODE *sibling; // used for link list of similar degree trees
    BINOMIALNODE *parent; // parent of the node
};

BINOMIALNODE* newBinomialNode(int num) // creates a new binomial tree
{
    BINOMIALNODE *node = new BINOMIALNODE;
    node->data = num;
    node->degree = 0;
    node->sibling;
    node->child = nullptr;
    node->parent = nullptr;
    node->sibling = nullptr;
    return  node;
}

BINOMIALNODE* mergeBinomialTree(BINOMIALNODE *node1, BINOMIALNODE *node2) // merge two binomial trees (mainly used for merging binomial heap)
{
    if (node1->data > node2->data) // checks for smallest data
    {
        swap(node1, node2); // swap so node1 is smaller
    }

    node2->parent = node1; // setting parent of node2 to node1
    node2->sibling = node1->child; // setting the sibling of node2 to node1's child
    node1->child = node2; // setting the child of node1 to node 2
    node1->degree++; // increase the degree of node 1 since two tree of the same degree merge into a tree of k+1

    return node1; //return node1 which is the lowest number (highest priority)
}

BINOMIALNODE* mergeBinomialHeap(BINOMIALNODE *heap1, BINOMIALNODE *heap2) // merging binomial heaps
{
    BINOMIALNODE temp; // create a temp binomial node
    BINOMIALNODE* tail = &temp; // have a pointer to tail which reference to temp
    temp.sibling = NULL; // set sibling to NULL

    while (heap1 != NULL && heap2 != NULL) // loop to connect the two heaps to a linked list
    {
        if (heap1->degree <= heap2->degree)
        {
            tail->sibling = heap1;
            heap1 = heap1->sibling;
        }
        else
        {
            tail->sibling = heap2;
            heap2 = heap2->sibling;
        }
        tail = tail->sibling;
    }

    if (heap1 != NULL)
    {
        tail->sibling = heap1;
    }
    else
    {
        tail->sibling = heap2;
    }
    
    BINOMIALNODE* previousNode = &temp;
    BINOMIALNODE* currentNode = temp.sibling;
    BINOMIALNODE* nextNode;

    if (currentNode != NULL)
    {
        nextNode = currentNode->sibling; 
    }
    else
    {
        nextNode = currentNode->sibling = NULL;
    }

    while (nextNode != NULL)
    {
        if (currentNode->degree != nextNode->degree || (nextNode->sibling != NULL && nextNode->sibling->degree == currentNode->degree))
        {
            previousNode = currentNode;
            currentNode = nextNode;
        }
        else if (currentNode->data <= nextNode->data)
        {
            currentNode->sibling = nextNode->sibling;
            mergeBinomialTree(currentNode, nextNode);
        }
        else
        {
            if (previousNode == &temp)
            {
                heap1 = nextNode;
            }
            else
            {
                previousNode->sibling = nextNode;
            }
            mergeBinomialTree(nextNode, currentNode);
            currentNode = nextNode;  
        }
        nextNode = currentNode->sibling;
    }

    return temp.sibling;
}

BINOMIALNODE* insert(BINOMIALNODE* node, int val)
{
    BINOMIALNODE* temp = newBinomialNode(val);
    return mergeBinomialHeap(node, temp);
}

BINOMIALNODE* findMinNode(BINOMIALNODE* head)
{

}

