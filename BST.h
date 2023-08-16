//
//  BSTree.h
//  BST Team Project
//
//  Created by Teresa Bui on 6/9/22.
//

#ifndef BSTree_h
#define BSTree_h

#include "BinaryNode.h"
#include "BinaryTree.h"

template<class SmartPhone>
class BinarySearchTree : public BinaryTree<SmartPhone>
{
public:
    // insert a node at the correct location
    bool insert(const SmartPhone &item);
    // remove a node if found
    bool remove(const SmartPhone &item);
    // find a target node
    bool search(const SmartPhone &target, SmartPhone &returnedItem) const;
   
    
private:
     // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<SmartPhone>* _insert(BinaryNode<SmartPhone>* nodePtr, BinaryNode<SmartPhone>* newNode);
   
     // search for target node
    BinaryNode<SmartPhone>* _search(BinaryNode<SmartPhone>* treePtr, const SmartPhone &target) const;
    
     // find the largest node
    BinaryNode<SmartPhone>* _findLargest(BinaryNode<SmartPhone>* nodePtr, SmartPhone &smallest) const;
   
     // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<SmartPhone>* _remove(BinaryNode<SmartPhone>* nodePtr, const SmartPhone target, bool &success);
    
     //delete target node from tree, called by internal remove node
    BinaryNode<SmartPhone>* _removeNode(BinaryNode<SmartPhone>* targetNodePtr);
    
};


///////////////////////// public function definitions ///////////////////////////
//Wrapper for _insert - Inserting items within a tree
template<class SmartPhone>
bool BinarySearchTree<SmartPhone>::insert(const SmartPhone & newEntry)
{
    BinaryNode<SmartPhone>* newNodePtr = new BinaryNode<SmartPhone>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    return true;
}

// Wrapper for _remove
template<class SmartPhone>
bool BinarySearchTree<SmartPhone>::remove(const SmartPhone &target)
{
    bool success = false; //assume false
    BinaryNode<SmartPhone>* removedNodePtr = nullptr;
    removedNodePtr = _remove(this->rootPtr, target, success);
    if (success) {
        return true;
    }
    return false;
    
}


//Wrapper for _search
// - it calls the private _search function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller
//   via the output parameter, and returns true, otherwise it returns false.
template<class SmartPhone>
bool BinarySearchTree<SmartPhone>::search(const SmartPhone& target, SmartPhone& returnedItem) const
{
    BinaryNode<SmartPhone>* temp = nullptr;
   
    temp = _search(this->rootPtr, target);
    if (temp)
    {
        returnedItem = temp->getItem();
        return true;
    }
    return false;
}

//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
template<class SmartPhone>
BinaryNode<SmartPhone>* BinarySearchTree<SmartPhone>::_insert(BinaryNode<SmartPhone>* nodePtr,
                                                          BinaryNode<SmartPhone>* newNodePtr)
{
    //Recursive
    BinaryNode<SmartPhone>* pWalk = nodePtr;
    
    if( !nodePtr) // == NULL
       {
           nodePtr = newNodePtr;
           return nodePtr;
       }
      else if (pWalk->getItem() > newNodePtr->getItem()) // if the node is less than, point left
      {
            nodePtr->setLeftPtr(_insert(pWalk->getLeftPtr(), newNodePtr));
      }
      else
      {
          nodePtr->setRightPtr(_insert(pWalk->getRightPtr(), newNodePtr)); // if the node is greater than, point right
      }

    return nodePtr;
}

//Implementation for the search operation
// - return NULL if target not found, otherwise
// - returns a pointer to the node that matched the target
template<class SmartPhone>
BinaryNode<SmartPhone>* BinarySearchTree<SmartPhone>::_search(BinaryNode<SmartPhone>* nodePtr,
                                                           const SmartPhone &target) const
{
    BinaryNode<SmartPhone>* found = nullptr;
    
    if (nodePtr) // != NULL
    {
        if (nodePtr->getItem() == target)                   // locating the target node, return if found
        {
            found = nodePtr;
            return found;
        }
       else if (nodePtr->getItem() > target)                // point left if target is less than the node's key
        {
            return _search(nodePtr->getLeftPtr(), target);
        }
        else                                                // point right if target is greater than the node's key
         {
            return _search(nodePtr->getRightPtr(), target);
         }
    }
    
    return found;
}

// find the largest node
template <class SmartPhone>
BinaryNode<SmartPhone>* BinarySearchTree<SmartPhone>::_findLargest(BinaryNode<SmartPhone>* nodePtr, SmartPhone& largest) const {
    BinaryNode<SmartPhone>* biggest;

    if (nodePtr->getRightPtr() == nullptr) {
        largest = nodePtr->getItem();
        biggest = nodePtr;
        return biggest;
    }
    else {
        biggest = _findLargest(nodePtr->getRightPtr(), largest);
    }

    return biggest;
}

// internal remove node: locate and delete target node under nodePtr subtree
template <class SmartPhone>
BinaryNode<SmartPhone>* BinarySearchTree<SmartPhone>::_remove(BinaryNode<SmartPhone>* nodePtr, const SmartPhone target, bool& success) {
    BinaryNode<SmartPhone>* found = nullptr;

    if (nodePtr) {
        if (nodePtr->getItem() == target) {
            if (nodePtr == this->rootPtr) {             // if the root is the target, remove the node
                success = true;
                this->rootPtr = _removeNode(nodePtr);
            }
            else {
                success = true;
                found = _removeNode(nodePtr);
                return found;
            }
        }
        else if (nodePtr->getItem() > target) {         // if target is less than the node's key, point left
            nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
        }
        else {                                          // if target is less than the node's key, point right
            nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
        }
    }

    return nodePtr;
}

//delete target node from tree, called by internal remove node
template <class SmartPhone>
BinaryNode<SmartPhone>* BinarySearchTree<SmartPhone>::_removeNode(BinaryNode<SmartPhone>* targetNodePtr) {
    BinaryNode<SmartPhone>* successor = nullptr;
    bool success = false;
    SmartPhone replacement;

    if (targetNodePtr->isLeaf()) {                      // target is a leaf node (no children)
        delete targetNodePtr;
        return nullptr;
    }
    
    // node with one child
    else if (targetNodePtr->getLeftPtr() == nullptr) {  // is in the left child
        // finding the successor
        successor = targetNodePtr->getRightPtr();
        delete targetNodePtr;
        return successor;
    }
    else if (targetNodePtr->getRightPtr() == nullptr) { // is in the right child
        // finding the successor
        successor = targetNodePtr->getLeftPtr();
        delete targetNodePtr;
        return successor;
    }
    else {
        // node with two children, point to the largest one of the two
        // finding the successor, largest child of the tree
        successor = _findLargest(targetNodePtr->getLeftPtr(), replacement);
        targetNodePtr->setItem(replacement);
        targetNodePtr->setLeftPtr(_remove(targetNodePtr->getLeftPtr(), replacement, success));
        return targetNodePtr;
    }
}


#endif /* BSTree_h */
