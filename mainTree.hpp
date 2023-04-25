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

    BINOMIALNODE swap(BINOMIALNODE *node1, BINOMIALNODE *node2)
    {
        BINOMIALNODE *temp = new BINOMIALNODE;
        temp = node1;
        node1 = node2;
        node2 = temp;
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

};
