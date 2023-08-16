//  HashNode.h
//  Created by Kimberly Duong

#ifndef HashNode_h

#define HashNode_h
#include "SmartPhone.h"

using std::string;

class HashNode
{
private:
    SmartPhone phone;
    int occupied;    // 1 -> occupied, 0 -> empty from start, -1 -> empty after removal
    int noCollisions;

public:
    // constructors
    HashNode() {occupied = 0; noCollisions = 0;}
    HashNode(SmartPhone aPhone) {phone = aPhone; occupied = 1; noCollisions = 0;}
    HashNode(SmartPhone aPhone, int ocp, int nCol)
             {phone = aPhone; occupied = ocp; noCollisions = nCol;}
    // setters
    void setItem(const SmartPhone & aPhone) {phone = aPhone;}
    void setOccupied(int ocp) {occupied = ocp;}
    void setNoCollisions(int nCol) {noCollisions = nCol;}
    
    // getters
    SmartPhone getItem() const {return phone;}
    int getOccupied() const {return occupied;}
    int getNoCollisions() const {return noCollisions;}
};

#endif /* HashNode_h */
