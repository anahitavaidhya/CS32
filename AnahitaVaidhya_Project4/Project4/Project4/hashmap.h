//
//  HashMap.h
//  Project4
//
//  Created by Anahita Vaidhya on 3/8/24.
//

#ifndef hashmap_h
#define hashmap_h

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cassert>
#include <list>

using namespace std;

template <typename T>
class HashMap {
public:
    // Constructor
    HashMap(double max_load = 0.75) : numBuckets(10), numAssociations(0), maxLoadFactor(max_load) {
        if (max_load <= 0) {
            maxLoadFactor = 0.75;
        } else {
            maxLoadFactor = max_load;
        }
        buckets = new list<Pair>[numBuckets];
    }

    
    // Destructor; deletes all of the items in the hashmap
    ~HashMap(){
        delete[] buckets;
    }

    // Return the number of associations in the hashmap
    int size() const{
        return numAssociations;
    }
    
    size_t numOfBuckets() const {
        return numBuckets;
    }
    
// The insert method associates one item (key) with another (value).
// If no association currently exists with that key, this method inserts
// a new association into the hashmap with that key/value pair. If there is
// already an association with that key in the hashmap, then the item
// associated with that key is replaced by the second parameter (value).
// Thus, the hashmap must contain no duplicate keys.
    void insert(const string& key, const T& value){
        size_t index = doHash(key);

        for (auto& pair : buckets[index]) {
            if (pair.key == key) {
                // Replace value if key already exists
                pair.value = value;
                return;
            }
        }

        // Key not found, insert new key-value pair
        buckets[index].push_back({key, value});
        numAssociations++;

        double loadFactor = static_cast<double>(numAssociations) / numBuckets;
        if (loadFactor > maxLoadFactor) {
            expand();
        }
    }
    

// If no association exists with the given key, return nullptr; otherwise,
// return a pointer to the value associated with that key. This pointer can be
// used to examine that value within the map.
    const T* find(const string& key) const{
        size_t index = doHash(key);

        for (const auto& pair : buckets[index]) {
            if (pair.key == key) {
                return &pair.value;
            }
        }
        return nullptr;
    }
    
// If no association exists with the given key, return nullptr; otherwise,
// return a pointer to the value associated with that key. This pointer can be
// used to examine that value or modify it directly within the map.
    T* find(const string& key) {
        const auto& hm = *this;
        return const_cast<T*>(hm.find(key));
    }
    
// Defines the bracket operator for HashMap, so you can use your map like this:
// your_map["david"] = 2.99;
// If the key does not exist in the hashmap, this will create a new entry in
// the hashmap and map it to the default value of type T (0 for builtin types).
// It returns a reference to the newly created value in the map.
    T& operator[](const string& key) {
        T* something = find(key);
        
        if (something != nullptr){
            return *something;
        } else {
            insert(key, T());
            return buckets[doHash(key)].back().value;
        }
    }
        
private:
    struct Pair {
        string key;
        T value;
    };

    list<Pair>* buckets;
    size_t numBuckets;
    size_t numAssociations;
    double maxLoadFactor;

    size_t doHash(const string& key) const {
        return hash<string>()(key) % numBuckets;
    }

    void expand() {
        size_t oldNumBuckets = numBuckets;
        numBuckets = numBuckets * 2;
        list<Pair>* newBuckets = new list<Pair>[numBuckets]();

        for (size_t i = 0; i < oldNumBuckets; i++) {
            for (const auto& pair : buckets[i]) {
                size_t index = doHash(pair.key);
                newBuckets[index].push_back({pair.key,pair.value});
            }
        }
        
        delete[] buckets;
        buckets = newBuckets;
    }
};


#endif /* hashmap_h */
