#include <string>
#include <iostream>
#include "SetType.h"

using namespace std;

template<class T>
SetType<T>::SetType() {
    // Create an array of forward_lists and initially set to an empty forward_list
    buckets = new forward_list<T>[DEFAULT_BUCKETS];

    // Your code here
    numBuckets = DEFAULT_BUCKETS;
    numElems = 0;
    maxLoad = DEFAULT_LOAD_FACTOR;
}

template <class T>
SetType<T>::SetType(int numBucks) {
    buckets = new forward_list<T>[numBucks];
    numBuckets = numBucks;
    numElems = 0;
    maxLoad = DEFAULT_LOAD_FACTOR;
}

template<class T>
SetType<T>::SetType(SetType &otherSet) {
    // This function is complete. No modification required.
    // This assumes the operator= is implemented.
    *this = otherSet;
}

template<class T>
SetType<T>::~SetType() {
    delete [] buckets;
}


template<class T>
SetType<T> SetType<T>::operator+(T elem) {
    // use add function and assignment operator to help with this function
    SetType<T> result;
    result = *this; // assuming you overloaded the assignment operator
    // same strategy can be used in a lot of the operator functions
    // Your code here

    // find the index that the element is supposed to go in by running the elem through the hash function
    int bucket = GetHashIndex(elem);
    // put the elem in the corresponding index
    result.buckets[bucket].push_front(elem);

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(T elem) {
    SetType<T> result;

    // Your code here
    result = *this;
    result.Remove(elem);
    return result;
}

template<class T>
SetType<T> SetType<T>::operator+(SetType & otherSet) {
    SetType<T> result;

    // Your code here
    // copy all the elements from this instance of the set to result
    result = *this;
    otherSet.ResetIterator();
    // copy all the remaining elements that you have not already copied in otherSet to the result
    // since the add function knows not to add any elements that already are in the set, the add function can be used to copy the elements
    // also use the iterator to iterate through all the elements
    for (int i = 0; i < otherSet.numElems; i++) {
        result.Add(otherSet.GetNextItem());
    }
    ResetIterator();



    return result;
}

template<class T>
SetType<T> SetType<T>::operator*(SetType & otherSet) {
    // intersection
    SetType<T> result;

    // Your code here
    T item;
    ResetIterator();
    // iterate through either of the sets to find the common elements
    for (int i = 0; i < this->numElems; i++) {
        item = this->GetNextItem();
        if (otherSet.Contains(item)) {
            result.Add(item);
        }
    }
    ResetIterator();

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(SetType& otherSet) {
    SetType<T> result;

    // Your code here
    result = *this;
    otherSet.ResetIterator();
    // iterate through otherSet
    // if there is a common element between otherSet and this set, remove
    T item;
    for (int i = 0; i < otherSet.numElems; i++) {
        item = otherSet.GetNextItem();
        if (result.Contains(item)) {
            result.Remove(item);
        }
    }
    ResetIterator();
    return result;
}

template<class T>
T SetType<T>::GetNextItem() {
    // Your code here

    // if the iterCount is greater than numElems, it means that there are no more elements to iterate over
    if (iterCount > numElems) {
        throw IteratorOutOfBounds();
    }
    // Returns the current item and then move to the next item
    T item;

    // this while statement allows you to skip over the buckets that do not contain any elements
    while (bucketIter == buckets[currBucket].end()) {
        // go the next bucket since no element exists in the current one
        ++currBucket;
        // set the bucketIter to the next bucket as well
        bucketIter = buckets[currBucket].begin();
    }
    // at this point it means that there are elements that exist in the current bucket
    item = *bucketIter;
    ++bucketIter;
    ++iterCount;


    return item;
}

template<class T>
int SetType<T>::GetHashIndex(const T& key) {
    // This is done... No touching!
    unordered_map<T,T> mapper;
    typename unordered_map<T,T>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(key) % numBuckets);
}


template<class T>
void SetType<T>::SetMaxLoad(double max) {
    // This function is done
    if (maxLoad < 0.1)
        maxLoad = 0.1;

    maxLoad = max;
}
template<class T>
SetType<T>& SetType<T>::operator=(SetType const &other) {
    // Your code here
    // delete buckets
    delete [] buckets;

    // reallocate correct number of buckets
    buckets = new forward_list<T>[other.numBuckets];

    // ensure that this instance of the set is empty
    this->MakeEmpty();
    //*this->MakeEmpty();

    this->numBuckets = other.numBuckets;
    this->numElems = other.numElems;

    auto tempBucketIt = other.buckets[0].begin();
    for (int i = 0; i < this->numBuckets; i++) {
        // at this point it means there are elements that exist in the bucket
        while (tempBucketIt != other.buckets[i].end()) {
            this->buckets[i].push_front(*tempBucketIt);
            ++tempBucketIt;
        }
        // this while statement skips over the buckets that do not have any elements
        tempBucketIt = other.buckets[i+1].begin();
    }
    ResetIterator();
    return *this;
}


template<class T>
void SetType<T>::Rehash(int newNumBuckets) {
    SetType<T> rehashedSet(newNumBuckets);

    // Your code here

    // loop through everything in this and add it to the rehashed set
    T item;
    for (int i = 0; i < this->numBuckets; i++) {
        item = this->GetNextItem();
        rehashedSet.Add(item);
    }
    ResetIterator();

    *this = rehashedSet;
}

template<class T>
void SetType<T>::Add(T elem) {
    // if the element already exist in the set, the set should not change
    if (this->Contains(elem)) {
        return;
    }

    // if the load factor is above the maxLoad, then the number of buckets need to be doubled and Rehash should be called
//    if (this->LoadFactor() > maxLoad) {
//        Rehash(numBuckets*2);
//        numBuckets = numBuckets * 2;
//    }

    // find the index that the function is supposed to go in using the GetHashIndex function
    int bucket = GetHashIndex(elem);
    // put the element in the corresponding index
    buckets[bucket].push_front(elem);
    ++numElems;
}

template<class T>
void SetType<T>::Remove(T elem) {
    // find the bucket that the elem exists at
    int bucket = GetHashIndex(elem);
    // iterate through the linked list
    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); it++) {
        if (*it == elem) {
            buckets[bucket].remove(elem);
            --numElems;
            return;
        }
    }
}

template<class T>
bool SetType<T>::Contains(T elem) {
    // find the bucket that the elem exists at
    int bucket = GetHashIndex(elem);
    // iterate through the linked list to see if it exists
    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); it++) {
        if (*it == elem) {
            return true;
        }
    }
    return false;
}

template<class T>
void SetType<T>::MakeEmpty() {
    // iterate through the bucket and clear all the buckets
    for (int i = 0; i < numBuckets; i++) {
        buckets[i].clear();
    }
    numElems = 0;

}

template<class T>
double SetType<T>::LoadFactor() const {
    return (numElems/numBuckets);
}

template<class T>
void SetType<T>::ResetIterator() {
    currBucket = 0;
    iterCount = 0;
    bucketIter = buckets[0].begin();
}


