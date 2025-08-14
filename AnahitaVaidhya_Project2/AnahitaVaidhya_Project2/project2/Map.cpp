//
//  Map.cpp
//  AnahitaVaidhya_Project2
//
//  Created by Anahita Vaidhya on 1/24/24.
//

#include "Map.h"
#include <stdio.h>

Map::Map()
{
    //Set size to 0
    m_size = 0;
    
    //Allocate head and tail with nullptr
    head = nullptr;
    tail = nullptr;
}

Map::~Map()
{
    //Check if head is a nullptr and return
    if(head == nullptr)
        return;
    
    //Clears memory
    Node* copyHead = head;
    Node* next;
    
    while(copyHead != nullptr){
        next = copyHead->nextNode;
        delete copyHead;
        copyHead = next;
    }
}

Map::Map(const Map& other){
    //Set size of current to other
    m_size = other.m_size;
    
    // If other is empty, set head and tail to nullptr and return
    if(other.m_size == 0){
        head = nullptr;
        tail = nullptr;
        return;
    } else { //If map isn't empty
        Node* copyNode = other.head;
        Node* prevNode = nullptr;
        
        //Copy it in newNode
        while(copyNode != nullptr){
            Node* newNode = new Node;
            newNode->value.m_key = copyNode->value.m_key;
            newNode->value.m_value = copyNode->value.m_value;
            //In case last element, set to nullptr
            newNode->nextNode = nullptr;
            //Insert head
            if(prevNode == nullptr){
                head = newNode;
            } else {
                prevNode->nextNode = newNode;
            }
            newNode->prevNode = prevNode;
            
            prevNode = newNode;
            copyNode = copyNode->nextNode;
        }
    }
}

Map& Map::operator=(const Map& rhs) {
    //Check if lhs and rhs are equal and if not, perform swap
    if(this != &rhs){
        //Create a temp Map since rhs is a const
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}

bool Map::contains(const KeyType& key) const
{
    Node* traverse = head;
    //check this
    //Traverse through
    while(traverse != nullptr){
        //Check if contains key
        if(traverse->value.m_key == key){
            return true;
        }
        //Increment
        traverse = traverse->nextNode;
    }
    //Doesn't contain key
    return false;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    //Check if key is in the linked list already
    if(contains(key)){
        return false;
    }
    
    Node* traverse = head;
    
    Node* newNode = new Node;
    
    newNode->value.m_key = key;
    newNode->value.m_value = value;

    //Nullptr case
    if(traverse == nullptr){
        head = newNode;
        tail = newNode;
        
        head->nextNode = nullptr;
        tail->nextNode = nullptr;
        
        head->prevNode = nullptr;
        tail->prevNode = nullptr;
        
        m_size++;
        
        return true;
    }
    
    //Add to head case
    if(key < traverse->value.m_key){
        head = newNode;
        
        head->nextNode = traverse;
        head->prevNode = nullptr;
        
        traverse->prevNode = head;
        
        m_size++;
        
        return true;
    }
    
    //Add in tail or middle case
    while(key >= traverse->value.m_key && traverse->nextNode != nullptr){
        traverse = traverse->nextNode;
    }
    //Add to tail
    if(traverse->nextNode == nullptr && key > traverse->value.m_key){
        tail = newNode;
        
        tail->prevNode = traverse;
        tail->nextNode = nullptr;
        
        traverse->nextNode = tail;
        
        m_size++;
        
        return true;
        
    //Add to middle
    } else {
        traverse = traverse->prevNode;
        
        newNode->nextNode = traverse->nextNode;
        traverse->nextNode = newNode;
        
        newNode->nextNode->prevNode = newNode;
        newNode->prevNode = traverse;
        
        m_size++;
        
        return true;
    }
}

bool Map::update(const KeyType& key, const ValueType& value)
{
    Node* traverse = head;
    if(traverse != nullptr){
        
        while(traverse->nextNode != nullptr){
            //Check if any repeats of key
            if(key == traverse->value.m_key){
                traverse->value.m_value = value;
                return true;
            }
            traverse = traverse->nextNode;
        }
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    Node* traverse = head;
    
    while(traverse != nullptr){
        //Check if any repeats of key
        if(key == traverse->value.m_key){
            traverse->value.m_value = value;
        }
        traverse = traverse->nextNode;
    }
    
    insert(key, value);
    
    return true;
}

bool Map::erase(const KeyType& key)
{
    // Shift pairs left to replace the one erased
    //If empty, return false
    if(head == nullptr){
        return false;
    //If head is equal to key
    } else if(head->value.m_key == key){
        Node* temp = head;
        head = temp->nextNode;
        if (head != nullptr) {  // Check if head is not nullptr before accessing prevNode
            head->prevNode = nullptr;
        }
        m_size--;
        delete temp;
        return true;
    //If tail is equal to key
    } else if(tail->value.m_key == key){
        Node* temp = tail;
        tail = temp->prevNode;
        if (tail != nullptr) {  // Check if tail is not nullptr before accessing nextNode
            tail->nextNode = nullptr;
        }
        m_size--;
        delete temp;
        return true;
    }
    
    Node* temp = head;
    while(temp->nextNode != nullptr){
        temp = temp->nextNode;
        if(temp->value.m_key == key){
            Node* prev = temp->prevNode;
            Node* next = temp->nextNode;
            
            prev->nextNode = next;
            if (next != nullptr) {  // Check if next is not nullptr before accessing prevNode
                next->prevNode = prev;
            }
            m_size--;
            delete temp;
            return true;
        }
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    Node* traverse = head;
    
    while(traverse != nullptr && traverse->value.m_key <= key){
        if(traverse->value.m_key == key){
            value = traverse->value.m_value;
            return true;
        }
        traverse = traverse->nextNode;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0  ||  i >= m_size)
        return false;
    
    Node* traverse = head;
    
    for(int k = 0; k < i; k++){
        if(traverse->nextNode == nullptr)
            return false;
        traverse = traverse->nextNode;
    }
    
    key = traverse->value.m_key;
    value = traverse->value.m_value;
    
    return true;
}

void Map::swap(Map& other)
{
    //Swap sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
    
    //Swap head pointers
    Node* tempHead = this->head;
    this->head = other.head;
    other.head = tempHead;
    
    //Swap tail pointers
    Node* tempTail = this->tail;
    this->tail = other.tail;
    other.tail = tempTail;
}

bool merge(const Map& m1, const Map& m2, Map& result){
    KeyType key1;
    ValueType value1;
    
    KeyType key2;
    ValueType value2;
    
    ValueType valueR;
    
    bool returnVar = true;
    
    //Check if result has values and erase
    while(result.empty() != true){
        result.get(0, key1, value1);
        result.erase(key1);
    }
    
    //Add m1 into result
    for(int i = 0; i < m1.size(); i++){
        m1.get(i, key1, value1);
        result.insert(key1, value1);
    }
    
    //Add m2 and different cases into result
    for(int i = 0; i < m2.size(); i++){
        m2.get(i, key2, value2);
            if(result.contains(key2)){
                result.get(key2, valueR);
                        if(value2 != valueR){
                            result.erase(key2);
                            returnVar = false;
                        }
            } else {
                result.insert(key2, value2);
            }
    }
    return returnVar;
}

void reassign(const Map& m, Map& result){
    ValueType prevVal; //assume this is already value of previous node
    ValueType tempVal;
    KeyType key0;
    
    KeyType key;
    ValueType value;
    
    //Check if result has values and erase
    while(result.empty() != true){
        result.get(0, key, value);
        result.erase(key);
    }
    
    //Regular case
    m.get(0, key0, prevVal);
    
    for(int i = 1; i < m.size(); i++){
        m.get(i, key, tempVal);
        
        result.insert(key, prevVal);
        prevVal = tempVal;
    }
    
    //First Node
    //After looping through all the nodes, tempVal and prevVal both have the value of the last node
    result.insert(key0, prevVal);
}
