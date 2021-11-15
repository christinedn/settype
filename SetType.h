#ifndef SET_TYPE
#define SET_TYPE

#include<string>
#include<iostream>
#include<forward_list>
#include<unordered_map>
using namespace std;

class IteratorOutOfBounds {
public:
    string Msg() {
        return "Iterator is out of bounds.  Nothing left to iterate over.";
    }
};

const int DEFAULT_BUCKETS = 10;
const double DEFAULT_LOAD_FACTOR = 1.0;

template<class T>
class SetType
{
public:
    // Constructors
    /*
     * Function: Creates a SetType object
     * Precondition: None
     * Postcondition: A SetType object will be created
     */
    SetType();
    /*
     * Function: Creates a SetType object with a certain number of buckets
     * Precondition: None
     * Postcondition: A SetType object will be created
     */
    explicit SetType(int numBucks);
    /*
     * Function: A copy constructor that copies all the data from other set to this set
     * Precondition: None
     * Postcondition: A SetType object will be created with the same data as the set in the parameters
     */
    SetType(SetType& other);
    /*
     * Function: A destructor that destroys everything in the set
     * Precondition: None
     * Postcondition: Everything in the set will be deleted
     */
    ~SetType();
    /*
     * Function: Adds an element into the set
     * Precondition: None
     * Postcondition: An element will be added to the set
     */
    void Add(T elem);
    /*
     * Function: Removes an element from the set
     * Precondition: None
     * Postcondition: The element will be removed from the set
     */
    void Remove(T elem);
    /*
     * Function: Checks if an element exists in the set
     * Precondition: None
     * Postcondition: A boolean value will be returned depending on whether or not the element exists in the set
     */
    bool Contains(T elem);
    /*
     * Function: Clears all the data in the set
     * Precondition: None
     * Postcondition: The set will be cleared
     */
    void MakeEmpty();
    /*
     * Function: Returns the number of elements in the set
     * Precondition: None
     * Postcondition: The number of elements will be returned
     */
    int Size() const {
        return numElems;
    }
    /*
     * Function: Returns the load factor of the set
     * Precondition: None
     * Postcondition: The load factor of the set will be returned
     */
    double LoadFactor() const;
    /*
     * Function: Sets the max load of the set
     * Precondition: None
     * Postcondition: The max load of the set will be changed to the variable in the parameters
     */
    void SetMaxLoad(double max);
    /*
     * Function: Rehashes the set to a new number of buckets
     * Precondition: None
     * Postcondition: The set will be rehashed to a new number of buckets
     */
    void Rehash(int newNumBuckets);
    /*
     * Function: Adds an element to the set
     * Precondition: None
     * Postcondition: An element will be added to the set
     */
    SetType operator+(T elem);				      // Add
    /*
     * Function: Removes an element from the set
     * Precondition: None
     * Postcondition: An element will be remooved from the set
     */
    SetType operator-(T elem);				      // Remove
    /*
     * Function: Finds the union of two sets
     * Precondition: None
     * Postcondition: Returns the union of two sets
     */
    SetType operator+(SetType& otherSet);         // Union
    /*
     * Function: Finds the difference of two sets
     * Precondition: None
     * Postcondition: Returns the difference of two sets
     */
    SetType operator-(SetType& otherSet);         // Difference
    /*
     * Function: Finds the intersection of two sets
     * Precondition: None
     * Postcondition: Returns the intersection of two sets
     */
    SetType operator*(SetType& otherSet);         // Intersection
    /*
     * Function: Copies all the elements from otherSet to this set
     * Precondition: None
     * Postcondition: All the elements from otherSet will be copied to this set
     */
    SetType& operator=(SetType const& otherSet);  // Assignment (does deep copy)
    /*
     * Function: Resets the iterator
     * Precondition: None
     * Postcondition: The iterator will be reset
     */
    void ResetIterator();	// Reset iterator
    /*
     * Function: Finds the next item
     * Precondition: None
     * Postcondition: The next item will be returned
     */
    T GetNextItem();

private:
    forward_list<T>* buckets;	// An array of forward_list's
                                // (each index is a forward_list)

    int numBuckets;     // total number of buckets

    int GetHashIndex(const T& key);    // Gets the hash index given the elem

    int numElems;       // total number of elements

    double maxLoad;     // load factor of the Set

    // Iterator variables
    int currBucket;											// What bucket is the iterator on?
    int iterCount;                                          // What element are we on?
    mutable typename forward_list<T>::iterator bucketIter;	// The iterator of the current bucket

    // Any other private functions and variables you want/need
};

#include "SetType.cpp"

#endif