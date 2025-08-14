//
//  main.cpp
//  AnahitaVaidhya_Project2
//
//  Created by Anahita Vaidhya on 1/24/24.
//
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

//Test Constructor
void testCon()
{
    Map m;
    //Check if size of map is 0
    assert(m.size() == 0);
}

//Test Destructor
void testCopyCon()
{
    //Check size if lhs = rhs size
    Map m;
    
    KeyType key1 = "alpha";
    ValueType value1 = 1.0;
    
    KeyType key2 = "beta";
    ValueType value2 = 3.0;
    
    KeyType key3 = "delta";
    ValueType value3 = 2.0;
    
    m.insert(key1, value1);
    m.insert(key2, value2);
    m.insert(key3, value3);
    
    Map n(m);
    
    assert(n.size() == m.size());
    
    //Loop through every node and check if they are the same
    for(int i = 0; i < n.size(); i++){
        m.get(i, key1, value1);
        n.get(i, key2, value2);
        assert(key1 == key2 && value1 == value2);
    }
}

//Test Assignment Operator
void testAssignmentOp()
{
    Map m;
    Map n;
    
    KeyType key1 = "alpha";
    ValueType value1 = 1.0;
    
    KeyType key2 = "delta";
    ValueType value2 = 2.0;
    
    KeyType key3 = "beta";
    ValueType value3 = 3.0;
    
    KeyType key4 = "gamma";
    ValueType value4 = 4.0;
    
    KeyType key5 = "zeta";
    ValueType value5 = 5.0;

    m.insert(key1, value1);
    m.insert(key2, value2);
    m.insert(key3, value3);
    
    n.insert(key4, value4);
    n.insert(key5, value5);
    
    m = n;
    
    //Check if size of m is equal to n
    assert(m.size() == n.size());
    assert(m.size() == 2);
    
    //Loop through to see if m = n now
    for(int i = 0; i < m.size(); i++){
        m.get(i, key1, value1);
        n.get(i, key2, value2);
        assert(key1 == key2 && value1 == value2);
    }
}

//Test contains
void testContains() {
    Map m;
    
    KeyType key1 = "alpha";
    ValueType value1 = 1.0;
    
    KeyType key2 = "delta";
    ValueType value2 = 2.0;
    
    KeyType key3 = "beta";
    ValueType value3 = 3.0;
    
    KeyType key4 = "gamma";
    
    m.insert(key1, value1);
    m.insert(key2, value2);
    m.insert(key3, value3);
    
    //Contains
    assert(m.contains(key1));
    assert(m.contains(key2));
    assert(m.contains(key3));
    
    //Doesn't contain
    assert(!m.contains(key4));
}

//Test insert
void testInsert() {
    Map m;
    KeyType key1 = "alpha";
    ValueType value1 = 1.0;
    ValueType valuex = 2.0;
    
    KeyType key2 = "delta";
    ValueType value2 = 2.0;
    KeyType key3 = "beta";
    ValueType value3 = 3.0;
    KeyType key4 = "aaa";
    ValueType value4 = 11.0;
    
    //Same key, should not be inserting alpha more than once and should return false
    assert(m.insert(key1, value1)); //Adding to null node
    assert(!m.insert(key1, value1));
    assert(!m.insert(key1, valuex));
    
    //Should insert and return true
    assert(m.insert(key2, value2)); //Adding to tail
    assert(m.insert(key3, value3)); //Adding to middle
    assert(m.insert(key4, value4)); //Adding to head
    
    assert(m.size() == 4);
    
    //Check if list is sorted correctly
    m.get(0, key1, value1);
    assert(key1 == "aaa" && value1 == 11);
    m.get(1, key1, value1);
    assert(key1 == "alpha" && value1 == 1);
    m.get(2, key1, value1);
    assert(key1 == "beta" && value1 == 3);
    m.get(3, key1, value1);
    assert(key1 == "delta" && value1 == 2);
}

//Test update
void testUpdate() {
    Map m;
    KeyType key1 = "alpha";
    ValueType value1 = 1;
    ValueType valuex = 2;
    
    KeyType key2 = "beta";
    ValueType value2 = 2;
    
    m.insert(key1, value1);
    m.insert(key2, value2);
    
    assert(m.update(key1, value1));
    
    //Same key, can update
    assert(m.update(key1, value1)); //Same value
    assert(m.update(key1, valuex)); //Different Value
    
    //Different key, can't update, should return false
    assert(!m.update(key2, value2));
    
    //Check if value was updated
    m.get(0, key1, value1);
    assert(key1 == "alpha" && value1 == 2);
}

//Test insertOrUpdate
void testInsertOrUpdate() {
    Map m;
    KeyType key1 = "alpha";
    ValueType value1;
    
    m.insert(key1, 1);
    
    //Same key, can update, not insert
    assert(m.insertOrUpdate(key1, 1)); //Same value
    assert(m.insertOrUpdate(key1, 2)); //Different Value
    
    //Different key, can insert, should return true
    KeyType key2 = "beta";
    assert(m.insertOrUpdate(key2, 2));
    
    //Check if value was updated
    m.get(0, key1, value1);
    assert(key1 == "alpha" && value1 == 2);
    
    //Check if key was added
    m.get(1, key1, value1);
    assert(key1 == "beta" && value1 == 2);
}

//Test erase
void testErase(){
    Map m;
    KeyType key1 = "alpha";
    ValueType value1 = 1.0;
    
    KeyType key2 = "beta";
    ValueType value2 = 2.0;
    
    KeyType key3 = "delta";
    ValueType value3 = 3.0;

    //If empty
    //Should be false because it's empty
    assert(!m.erase(key1));
    
    //If head if equal to key
    m.insert(key1, value1);
    m.get(key1, value1);
    assert(m.erase(key1));
    assert(!m.get(key1, value1));
    assert(m.size() == 0);

    //If tail is equal to key
    m.insert(key2, value2);
    m.insert(key3, value3);
    
    assert(m.erase(key3));
    assert(!m.get(key3, value3));
    assert(m.get(key2, value2) && key2 == "beta");
    assert(m.size() == 1);
    
    //If key is in the middle
    key1 = "alpha";
    value1 = 1.0;
    
    key2 = "delta";
    value2 = 3;
    
    m.insert(key1, value1);
    m.insert(key2, value2);
    key3 = "beta";
    assert(m.erase(key3));
    assert(!m.get(key3, value1));
    assert(m.get(key1, value1) && key1 == "alpha");
    assert(m.get(key2, value1) && key2 == "delta");
    assert(m.size() == 2);
}
    
//Test get1
void testGet1(){
    Map m;
    KeyType key1 = "alpha";
    ValueType value1 = 1.0;
    
    KeyType key2 = "beta";
    ValueType value2 = 0.0;
    
    KeyType key3 = "delta";
    ValueType value3 = 0.0;
    
    KeyType key4 = "gamma";
    ValueType value4 = 0.0;
    
    m.insert(key1, value1);
    m.insert(key2, value2);
    m.insert(key3, value3);
    m.insert(key4, value4);
    
    assert(m.get(key1, value1) && key1 == "alpha");
    assert(m.get(key2, value2) && key2 == "beta");
    assert(m.get(key3, value3) && key3 == "delta");
    assert(m.get(key4, value4) && key4 == "gamma");
}

//Test get2
void testGet2(){
    Map m;
    KeyType key1 = "alpha";
    ValueType value1 = 1.0;
    
    KeyType key2 = "beta";
    ValueType value2 = 0.0;
    
    KeyType key3 = "delta";
    ValueType value3 = 0.0;
    
    KeyType key4 = "gamma";
    ValueType value4 = 0.0;
    
    m.insert(key2, value2);
    m.insert(key1, value1);
    m.insert(key4, value4);
    m.insert(key3, value3);
    
    assert(m.get(0, key1, value1) && key1 == "alpha");
    assert(m.get(1, key2, value2) && key2 == "beta");
    assert(m.get(2, key3, value3) && key3 == "delta");
    assert(m.get(3, key4, value4) && key4 == "gamma");
}

//Test swap
void testSwap(){
    Map m;
    KeyType key1 = "alpha";
    ValueType value1 = 1.0;
    
    KeyType key2 = "beta";
    ValueType value2 = 0.0;
    
    KeyType key3 = "delta";
    ValueType value3 = 0.0;
    
    KeyType key4 = "gamma";
    ValueType value4 = 0.0;
    
    m.insert(key2, value2);
    m.insert(key1, value1);
    m.insert(key4, value4);
    m.insert(key3, value3);
    
    Map n;
    KeyType key5 = "chi";
    ValueType value5 = 1.0;
    
    KeyType key6 = "omega";
    ValueType value6 = 0.0;
    
    KeyType key7 = "zeta";
    ValueType value7 = 0.0;
    
    KeyType key8 = "theta";
    ValueType value8 = 0.0;
    
    n.insert(key6, value6);
    n.insert(key5, value5);
    n.insert(key8, value8);
    n.insert(key7, value7);
    
    m.swap(n);
    
    assert(m.get(0, key1, value1) && key1 == "chi");
    assert(m.get(1, key2, value2) && key2 == "omega");
    assert(m.get(2, key3, value3) && key3 == "theta");
    assert(m.get(3, key4, value4) && key4 == "zeta");
    
    assert(n.get(0, key5, value5) && key5 == "alpha");
    assert(n.get(1, key6, value6) && key6 == "beta");
    assert(n.get(2, key7, value7) && key7 == "delta");
    assert(n.get(3, key8, value8) && key8 == "gamma");
}

//Test merge
void testMerge(){
    Map m1, m2, m3, m4, m5, m6, result;
    KeyType key = "Lucy";
    KeyType key1 = "Fred";
    KeyType key2 = "Ethel";
    KeyType key3 = "Ricky";
    
    ValueType value = 789;
    ValueType value1 = 123;
    ValueType value2 = 456;
    ValueType value3 = 321;
    
    //Empty Case
    assert(merge(m1, m2, result));
    
    // Case 1: No common keys
    m1.insert(key1, value1);
    m1.insert(key2, value2);

    m2.insert(key, value);
    m2.insert(key3, value3);
    
    assert(merge(m1, m2, result));
    assert(result.size() == 4);

    // Case 2: Common keys with the same values
    m3.insert(key, value1);
    m3.insert(key2, value2);

    m4.insert(key, value1);
    m4.insert(key3, value3);
    assert(merge(m3, m4, result));
    assert(result.contains(key));
    assert(result.size() == 3);
    
    // Case 3: Common keys with different values
    m5.insert(key, value);
    m5.insert(key2, value2);

    m6.insert(key, value1);
    m6.insert(key3, value3);
    assert(!merge(m5, m6, result));
    assert(!result.contains(key));
    assert(result.size() == 2);
}

// Test for reassign function
void testReassign() {
    Map m, result;

    // Case 1: Empty map
    reassign(m, result);
    //assert(result.size() == 0);

    // Case 2: Single pair in the map
    m.insert("Fred", 123);
    reassign(m, result);
    assert(result.size() == 1);
    assert(mapsEqual(result, m));  // result should be equal to m

    // Case 3: Multiple pairs in the map
    m.insert("Ethel", 456);
    m.insert("Lucy", 789);
    m.insert("Ricky", 321);

    reassign(m, result);
    assert(result.size() == 4);
    // result should contain pairs from m, with values reassigned
    // make sure each value in result corresponds to a different key in m
    for (int i = 0; i < result.size(); ++i) {
        KeyType key1, key2;
        ValueType value1, value2;

        m.get(i, key1, value1);
        result.get(i, key2, value2);

        assert(value1 != value2);
    }

    // Add more test cases as needed
}
void test()
{
    Map m;
    assert(m.insert("Fred", 123));
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);
    ValueType v = 42;
    assert(!m.get("Lucy", v)  &&  v == 42);
    assert(m.get("Fred", v)  &&  v == 123);
    v = 42;
    KeyType x = "Lucy";
    assert(m.get(0, x, v)  &&  x == "Ethel"  &&  v == 456);
    KeyType x2 = "Ricky";
    assert(m.get(1, x2, v)  &&  x2 == "Fred"  &&  v == 123);
}

int main() {
    // Run test functions
    testCon();
    testCopyCon();
    testAssignmentOp();
    testContains();
    testInsert();
    testUpdate();
    testInsertOrUpdate();
    testErase();
    testGet1();
    testGet2();
    testSwap();
    testMerge();
    testReassign();
    test();

    // If everything passes, print success
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
