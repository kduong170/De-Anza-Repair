//
//  BinaryTree.h
//  BST Team Project
//
//  Created by Teresa Bui on 6/10/22.
//

#ifndef BinaryTree_h
#define BinaryTree_h

#include "BinaryNode.h"
#include "HashList.h"

template<class SmartPhone>
class BinaryTree
{
protected:
    BinaryNode<SmartPhone>* rootPtr;        // ptr to root node
    int count;                            // number of nodes in tree

public:
    // "admin" functions
    BinaryTree() {rootPtr = 0; count = 0;}
    BinaryTree(const BinaryTree<SmartPhone> & tree){ }
    virtual ~BinaryTree() { destroyTree(rootPtr); }
   
    // common functions for all binary trees
    bool isEmpty() const   {return count == 0;}
    int getCount() const    {return count;}
    void clear()            {destroyTree(rootPtr); rootPtr = 0; count = 0;}
  
    void inOrder(void visit(SmartPhone&, HashList&), HashList& hash) const  {_inorder(visit, rootPtr, hash);}
    void printTree(void visit(SmartPhone&, int)) const{_printTree(visit, rootPtr, 1);}


    // abstract functions to be implemented by derived class
    virtual bool insert(const SmartPhone &newData) = 0;
    //virtual bool remove(const ItemType &data) = 0;
    virtual bool search(const SmartPhone &target, SmartPhone & returnedItem) const = 0;

private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<SmartPhone>* nodePtr);

    // internal traverse
    void _inorder(void visit(SmartPhone&, HashList&), BinaryNode<SmartPhone>* nodePtr, HashList& hash) const;
    void _printTree(void visit(SmartPhone&, int), BinaryNode<SmartPhone>* nodePtr, int level) const;
 
};

//Destroy the entire tree
template<class SmartPhone>
void BinaryTree<SmartPhone>::destroyTree(BinaryNode<SmartPhone>* nodePtr)
{
    if(nodePtr) // != NULL
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        delete nodePtr;
    }
}


//Inorder Traversal
template<class SmartPhone>
void BinaryTree<SmartPhone>::_inorder(void visit(SmartPhone &, HashList&), BinaryNode<SmartPhone>* nodePtr, HashList& hash) const
{
    if (nodePtr) // != NULL
    {
        SmartPhone item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr(), hash);
        visit(item, hash);
        _inorder(visit, nodePtr->getRightPtr(), hash);
    }
}

//Prints tree as an indented list
template<class SmartPhone>
void BinaryTree<SmartPhone>::_printTree(void visit(SmartPhone &, int), BinaryNode<SmartPhone>* nodePtr, int level) const
{

    if (nodePtr) // != NULL
         {
             SmartPhone item = nodePtr->getItem();          
             visit(item, level);
             _printTree(visit, nodePtr->getRightPtr(), level+1);
             _printTree(visit, nodePtr->getLeftPtr(), level+1);
         }
}


#endif /* BinaryTree_h */
