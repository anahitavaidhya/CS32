//
//  Map.h
//  AnahitaVaidhya_Project2
//
//  Created by Anahita Vaidhya on 1/24/24.
//

// Map.h

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
  public:
    Map();         // Create an empty map (i.e., one whose size() is 0).
    
    ~Map();
    
    Map(const Map& other);
    
    Map& operator=(const Map& rhs);

    bool empty() const;  // Return true if the map is empty, otherwise false.

    int size() const;    // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
      // If key is not equal to any key currently in the map and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that either the key is already in the map, or the map has a fixed
      // capacity and is full).

    bool update(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value that it currently maps to, but instead map to
      // the value of the second parameter; in this case, return true.
      // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
      // If key is equal to a key currently in the map, then make that key no
      // longer map to the value that it currently maps to, but instead map to
      // the value of the second parameter; in this case, return true.
      // If key is not equal to any key currently in the map, and if the
      // key/value pair can be added to the map, then do so and return true.
      // Otherwise, make no change to the map and return false (indicating
      // that the key is not already in the map and the map has a fixed
      // capacity and is full).

    bool erase(const KeyType& key);
      // If key is equal to a key currently in the map, remove the key/value
      // pair with that key from the map and return true.  Otherwise, make
      // no change to the map and return false.
     
    bool contains(const KeyType& key) const;
      // Return true if key is equal to a key currently in the map, otherwise
      // false.
     
    bool get(const KeyType& key, ValueType& value) const;
      // If key is equal to a key currently in the map, set value to the
      // value in the map which the key maps to, and return true.  Otherwise,
      // make no change to the value parameter of this function and return
      // false.
     
    bool get(int i, KeyType& key, ValueType& value) const;
      // If 0 <= i < size(), copy into the key and value parameters the
      // key and value of the key/value pair in the map whose key is strictly
      // greater than exactly i keys in the map and return true.  Otherwise,
      // leave the key and value parameters unchanged and return false.

    void swap(Map& other);
      // Exchange the contents of this map with the other one.

  private:
    struct Pair
    {
        KeyType   m_key;
        ValueType m_value;
    };
    
    struct Node
    {
        Pair value;
        Node* prevNode;
        Node* nextNode;
    };
    
    int  m_size;                     // number of pairs in the map
    Node* head;
    Node* tail;
    
    // At any time, the elements of m_data indexed from 0 to m_size-1
    // are in use and are stored in ascending order of the keys.
    Node* findFirstAtLeast(const KeyType& key) const;
      // Return the index of the pair in m_data whose key is the least one
      // that is >= key, or m_size if there is no such pair.

    bool doInsertOrUpdate(const KeyType& key, const ValueType& value,
                          bool mayInsert, bool mayUpdate);
      // If the key is not present in the map and if mayInsert is true, insert
      // the pair if there is room.  If the key is present and mayUpdate is
      // true, update the pair with the given key.
};

//Non-member functions
bool merge(const Map& m1, const Map& m2, Map& result);

void reassign(const Map& m, Map& result);

// Inline implementations
inline
int Map::size() const
{
    return m_size;
}

inline
bool Map::empty() const
{
    return size() == 0;
}

#endif // MAP_INCLUDED
//===================================================================
