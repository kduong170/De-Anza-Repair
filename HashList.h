//  HashList.h
//  Created by Kimberly Duong

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"

class HashList
{
private:
    HashNode* hashAry;
    int hashSize;
    int count;
    int totalCollisions;
    int longestCollision;
    
public:
    HashList() { count = 0; hashSize = 40; totalCollisions = 0; longestCollision = 0; hashAry = new HashNode[hashSize]; }
    HashList(int n)    { count = 0; hashSize = n; totalCollisions = 0; longestCollision = 0; hashAry = new HashNode[hashSize]; }
    ~HashList(){ delete [] hashAry; }

    int getCount() const    { return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const {return 100.0 * ((count * 1.0) / hashSize); }
    int getTotalCollisions() const {return totalCollisions; }
    int getLongestCollision() const {return longestCollision; }
    bool isEmpty() const    { return count == 0; }
    bool isFull()  const    { return count == hashSize; }
    
    bool insert( const SmartPhone &itemIn );
    bool remove( SmartPhone &itemOut, const SmartPhone &key );
    bool  search( SmartPhone &itemOut, const SmartPhone &key );
    
    int _hash( string key );
    HashList* rehash (int newSize);

};

/*~*~*~*
   Insert an item into the hash table
   It rejects duplicates
*~**/
bool HashList::insert( const SmartPhone &itemIn )
{
    if ( count == hashSize)
        return false;
    
    int index = _hash(itemIn.getSerial());
    int collisions = 0;
   
    while (hashAry[index].getOccupied() > 0) {
        if (hashAry[index].getItem() == itemIn) 
            return false;
        index = (index + 1) % hashSize;
        collisions++;
    }
   
    hashAry[index].setItem(itemIn);
    hashAry[index].setOccupied(1);
    hashAry[index].setNoCollisions(collisions);
    count++;
    totalCollisions =  totalCollisions + collisions;
    if (collisions > longestCollision)
        longestCollision = collisions;
   
    return true;
}

/*~*~*~*
   Removes the item with the matching key from the hash table
     - copies data in the hash node to itemOut
     - replaces data in the hash node with an empty record
*~**/
bool HashList::remove( SmartPhone &itemOut, const SmartPhone &key )
{
    int index = _hash(key.getSerial());
    int collisions = 0;

    while (hashAry[index].getOccupied() != 0 && collisions < hashSize){
         
        if (hashAry[index].getItem() == key) {
            itemOut = hashAry[index].getItem();
            SmartPhone emptyPhone;
            hashAry[index].setItem(emptyPhone);
            hashAry[index].setOccupied(-1);
            count--;
            totalCollisions = totalCollisions - collisions;
            return true;
        }
      
        index = (index + 1) % hashSize;
        collisions++;
    }
    
    return false;
}

/*~*~*~*
   hash search - linear probe
   if found:
      - copy data to itemOut
      - returns true
   if not found, returns false
*~**/
bool HashList::search( SmartPhone &itemOut, const SmartPhone &key )
{
   int index = _hash(key.getSerial());
   int collisions = 0;

   while (hashAry[index].getOccupied() != 0 && collisions < hashSize){
      if (hashAry[index].getItem() == key) {
         itemOut = hashAry[index].getItem();
         return true;
      }
      
      index = (index + 1) % hashSize;
      collisions++;
   }
     
    return false;
}
/*~*~*~*
   Creates new HashList and inserts elements into it
*~**/
HashList* HashList::rehash(int newSize)
{
    HashList* newHash = new HashList(newSize);
    
    for (int i = 0; i <= hashSize; i++)
        if (hashAry[i].getOccupied() == 1)
        {
            newHash->insert(hashAry[i].getItem());
        }
    return newHash;
}

/*~*~*~*
   Returns a hash value for key
*~**/
int HashList::_hash( string key )
{
    int sum = 0;
    for (int i = 0; key[i]; ++i)
        sum += key[i];
    return sum % hashSize;
}

#endif // HASHTABLE_H_

