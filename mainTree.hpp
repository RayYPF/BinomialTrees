#ifndef BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_HPP


BINOMIALNODE* newBinomialNode(int num);
BINOMIALNODE* mergeBinomialTree(BINOMIALNODE* node1, BINOMIALNODE* node2);
BINOMIALNODE* mergeBinomialHeap(BINOMIALNODE* node1, BINOMIALNODE* node2);
BINOMIALNODE* findNum(BINOMIALNODE* node, int num);
BINOMIALNODE* insert(BINOMIALNODE* node, int num);
BINOMIALNODE* findMinNode(BINOMIALNODE* node);

#endif
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
    BINOMIALNODE* node = new BINOMIALNODE;
    node->data = num;
    node->degree = 0;
    node->parent = nullptr;
    node->child = nullptr;
    node->sibling = nullptr;
    return node;
}

BINOMIALNODE* mergeBinomialTree(BINOMIALNODE* node1, BINOMIALNODE* node2) // merge two binomial trees (mainly used for merging binomial heap)
{
    if (node1->data > node2->data) // checks for smallest data
    {
        swap(node1, node2); // swap so node1 is smaller
    }

    node2->parent = node1; // setting parent of node2 to node1
    node2->sibling = node1->child; // setting the sibling of node2 to node1's child
    node1->child = node2; // setting the child of node1 to node 2
    node1->degree++; // increase the degree of node 1 since two tree of the same degree merge into a tree of k+1
    
    return node1; //return node1 which is the lowest number (highest priority) of the tree
}

BINOMIALNODE* mergeBinomialHeap(BINOMIALNODE* node1, BINOMIALNODE* node2) // merging binomial heaps
{
    if (node1 == nullptr) // check if either the node is null
    {
        return node2;
    }
    if (node2 == nullptr)
    {
        return node1;
    }
    BINOMIALNODE* temp1 = node1; // create a temp binomial node for each node
    BINOMIALNODE* temp2 = node2;
    BINOMIALNODE* head = nullptr;
    BINOMIALNODE* tail = nullptr; // have a pointer to tail which reference to temp

    while (temp1 != nullptr && temp2 != nullptr) // loop to connect the two heaps to a linked list
    {
        if (temp1->degree <= temp2->degree)
        {
            if (head == nullptr)
            {
                head = temp1;
            }
            else 
            {
                tail->sibling = temp1;
            }
            tail = temp1;
            temp1 = temp1->sibling;
        }
        else
        {
            if (head == nullptr)
            {
                head = temp2;
            }
            else 
            {
                tail->sibling = temp2;
            }
            tail = temp2;
            temp2 = temp2->sibling;
        }
    }

    if (temp1 != nullptr) //check if heap1 is NULL 
    {
        tail->sibling = temp1; // if yes set the sibling of tail to heap1
    }
    else
    {
        tail->sibling = temp2; // if no set the sibling of tail to heap2
    }
    
    BINOMIALNODE* previousNode = nullptr; // creates 3 temp pointer to keep track of node
    BINOMIALNODE* currentNode = head;
    BINOMIALNODE* nextNode = head->sibling;

    while (nextNode != nullptr)
    {
        if (currentNode->degree != nextNode->degree || (nextNode->sibling != nullptr && nextNode->sibling->degree == currentNode->degree))
        {
            previousNode = currentNode;
            currentNode = nextNode;
        }
        else if (currentNode->data <= nextNode->data)
        {
            currentNode->sibling = nextNode->sibling;
            currentNode = mergeBinomialTree(currentNode, nextNode); // merge the tree
        }
        else
        {
            if (previousNode == nullptr)
            {
                head = nextNode;
            }
            else
            {
                previousNode->sibling = nextNode;
            }
            currentNode = mergeBinomialTree(nextNode, currentNode); // merge the tree
            currentNode = nextNode;  
        }
        nextNode = currentNode->sibling;
    }
    return head;
}

BINOMIALNODE* findNum(BINOMIALNODE* node, int num) // find a specific number in the heap
{
    BINOMIALNODE* temp = node;
    if (temp == nullptr)
    {
        return nullptr;
    }

    if (temp->data == num)
    {
        return temp;
    }
    
    if (temp->data < num)
    {
        BINOMIALNODE* treeSearch = findNum(temp->child, num);
        if (treeSearch != nullptr)
        {
            return treeSearch;
        }
    }
    

    return findNum(temp->sibling, num);
}

BINOMIALNODE* insert(BINOMIALNODE* node, int num) // insert a new num into the heap
{
    if (findNum(node, num) != nullptr)
    {
        return node;
    }
    BINOMIALNODE* temp = newBinomialNode(num);
    return mergeBinomialHeap(node, temp);
}

BINOMIALNODE* findMinNode(BINOMIALNODE* node) // find the smallest number in the link list of trees
{
    BINOMIALNODE* minNode = nullptr;
    BINOMIALNODE* temp = node; // set a pointer to the head
    while (temp != nullptr) // goes through the linked list to find smallest
    {
        if (minNode == nullptr || temp->data < minNode->data) 
        {
            minNode = temp;
        }
        temp = temp->sibling;
    }
    return minNode; // return smallest
}
BINOMIALNODE* deleteMinNode(BINOMIALNODE* node) // delete the smallest root of the heap (doesn't work)
{
    BINOMIALNODE* temp = findMinNode(node); // set temp to smallest node
    if (temp == node)
    {

        node = node->sibling;
        
    }
    else
    {
        BINOMIALNODE* previousNode = node; // makes a pointer to previous node
        while (previousNode->sibling != temp)
        {
            previousNode = previousNode->sibling;
        }
        previousNode->sibling = temp->sibling;
        BINOMIALNODE* child = temp->child;
        if (temp->sibling != nullptr)
        {
            temp->sibling->parent = child;
        }
    }
    BINOMIALNODE* child = temp->child;
    BINOMIALNODE* newNode = nullptr;
    while (child != nullptr)
    {
        BINOMIALNODE* next = child->sibling;
        child->parent = nullptr;
        child->sibling = newNode;
        newNode = child;
        child = next;
    }
    node = mergeBinomialHeap(node, newNode);
    delete temp;
    return node;

}
