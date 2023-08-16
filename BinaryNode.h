//
//  BinaryNode.h
//  BST Team Project
//
//  Created by Teresa Bui on 6/9/22.
//

#ifndef BinaryNode_h
#define BinaryNode_h


template<class SmartPhone>
class BinaryNode
{
private:
    SmartPhone              item;         // Data portion
    BinaryNode<SmartPhone>* leftPtr;        // Pointer to left child
    BinaryNode<SmartPhone>* rightPtr;        // Pointer to right child

public:
    // constructors
    BinaryNode(const SmartPhone & anItem)    {item = anItem; leftPtr = 0; rightPtr = 0;}
    BinaryNode(const SmartPhone & anItem,
               BinaryNode<SmartPhone>* left,
               BinaryNode<SmartPhone>* right) {item = anItem; leftPtr = left; rightPtr = right;}
    // setters
    void setItem(const SmartPhone & anItem) {item = anItem;}
    void setLeftPtr(BinaryNode<SmartPhone>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<SmartPhone>* right) {rightPtr = right;}
    
    // getters
    SmartPhone getItem() const     {return item;}
    BinaryNode<SmartPhone>* getLeftPtr() const  {return leftPtr;}
    BinaryNode<SmartPhone>* getRightPtr() const {return rightPtr;}

    // other functions
    bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
    
};

#endif /* BinaryNode_h */
