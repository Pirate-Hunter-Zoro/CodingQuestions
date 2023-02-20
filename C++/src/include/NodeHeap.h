#ifndef Heap_H
#define Heap_H

#include "Node.h"

class NodeHeap {

    friend class Graph;

private:
    // field values
    int size;
    int arraySize;
    Node** array;

    // default constructor
    NodeHeap();

    // insertion
    void insert(Node *toInsert);

    // extraction
    Node* extractMin();

    // deletion
    bool remove(Node *toRemove);

    // determining if heap is empty
    bool isEmpty() { return this->size == 0; }

    // repairing heap properties
    void repair();
    int getLesserChild(int idx);
    int lastReturnedLesserChildIdx;

    // search
    int search(Node* toSearch);
    int recSearch(Node* toSearch, int idx);

public:

    // printing
    friend std::ostream &operator<<(std::ostream &os, const NodeHeap &heapToPrint);

};

// base constructor
NodeHeap::NodeHeap() : size(0) {}

/**
 * @brief insertion of a Node into the heap
 *
 * @param id
 */
void NodeHeap::insert(Node* toInsert)
{
    if (this->search(toInsert) == -1 && toInsert != nullptr) {
        // only insert if the heap does not contain this value
        this->size++;
        if (this->size > 1 && this->size > this->arraySize)
        {
            // we need a new array to store stuff - allocate some storage in the heap
            Node** newArray = new Node*[(this->size - 1) * 2]; // array of pointers
            this->arraySize = (this->size - 1) * 2;
            // copy the old values into the double sized array
            for (int i = 0; i < this->size - 1; i++)
            {
                newArray[i] = this->array[i];
            }
            // now for the new value
            newArray[this->size - 1] = toInsert;
            // delete the old array
            delete[] this->array;
            this->array = newArray;
            this->repair();
        }
        else if (this->size > 1)
        {
            // then we just get to insert into our NOT full underlying array
            this->array[this->size - 1] = toInsert;
            this->repair();
        }
        else
        {
            // this is the first value to insert
            this->arraySize = 1;
            this->array = new Node*;
            *(this->array) = toInsert;
        }
    }
}

/**
 * @brief Method to extract the minimum value in this heap
 * 
 * @return Node* 
 */
Node* NodeHeap::extractMin(){
    Node* toReturn = this->array[0];
    this->remove(toReturn);
    return toReturn;
}

/**
 * @brief deletion of a Node in the heap
 *
 * @param id
 * @return true
 * @return false
 */
bool NodeHeap::remove(Node* toRemove)
{
    if (toRemove != nullptr) {
        int relevantIndex = this->search(toRemove);
        if (relevantIndex != -1)
        {
            this->size--;
            this->array[relevantIndex] = this->array[this->size];
            // what if the value at the end is actually what we're removing?
            // that's okay - until our size increases again this index is ignored because we only care about indeces in [0, size-1]
            if (this->size < this->arraySize / 4)
            {
                // it's time to cut down the size of our underlying array
                this->arraySize = this->arraySize / 2;
                Node** newArray = new Node*[this->arraySize];
                for (int i = 0; i < this->size; i++)
                {
                    newArray[i] = this->array[i];
                }
                // now we can delete the old array
                delete[] this->array;
                this->array = newArray;
            }
            // repair heap properties
            this->repair();
            return true;
        }
    }
    // otherwise
    return false;
}

/**
 * @brief searching for a value
 *
 * @param id
 * @return int
 */
int NodeHeap::search(Node* toSearch)
{
    return this->recSearch(toSearch, 0);
}

/**
 * @brief recursive helper to search for a value in a heap
 *
 * @param id
 * @param idx
 * @return int - the index of the value that belongs here
 */
int NodeHeap::recSearch(Node* toSearch, int idx)
{
    if (toSearch == nullptr){
        // base case
        return -1;
    }

    // the children for a node at a given index i are at position 2i+1,2i+2
    if (idx >= this->size)
    {
        // base case
        return -1;
    }
    else
    {
        if (this->array[idx] == toSearch)
        {
            return idx;
        }
        else
        {
            if (toSearch->key < this->array[idx]->key)
            {
                // then this tree (or subtree) CANNOT contain the value because every child of this node has a key greater than this node's key, but we're looking for one that is less
                return -1;
            }
            else
            {
                // there is hope
                int candidate1 = this->recSearch(toSearch, 2 * idx + 1); // left child
                int candidate2 = this->recSearch(toSearch, 2 * idx + 2); // right child
                if (candidate1 != -1)
                {
                    return candidate1;
                }
                else
                {
                    return candidate2; // -1 or not, all hope is here
                }
            }
        }
    }
}

/**
 * @brief After an insertion or deletion, we must repair the heap properties
 *
 */
void NodeHeap::repair()
{
    // go through the first half of the array, pushing things DOWN only
    int start = ceil(this->size / 2);
    for (int idx = start; idx >= 0; idx--)
    {
        int currentIdx = idx;
        while (this->getLesserChild(currentIdx) != -1){
            // flip the lesser child with this node
            Node* temp = this->array[currentIdx];
            this->array[currentIdx] = this->array[this->lastReturnedLesserChildIdx];
            this->array[this->lastReturnedLesserChildIdx] = temp;
            currentIdx = this->lastReturnedLesserChildIdx;
        }
    }
}

/**
 * @brief given a node at a certain position, return whether the node has a child which is less than it
 * 
 * @param idx 
 * @return int - the index 
 */
int NodeHeap::getLesserChild(int idx)
{
    // set the default value
    this->lastReturnedLesserChildIdx = -1;

    // check the left and right children, should they exist
    if (this->size > (idx * 2 + 2) && this->array[idx * 2 + 2]->key < this->array[idx]->key && this->array[idx * 2 + 2]->key < this->array[idx * 2 + 1]->key)
    {
        this->lastReturnedLesserChildIdx = idx*2+2;
        // so we won't have to immediately call this function again just to find the index
        return this->lastReturnedLesserChildIdx;
    }
    else if (this->size > (idx * 2 + 1) && this->array[idx * 2 + 1]->key < this->array[idx]->key)
    {
        this->lastReturnedLesserChildIdx = idx*2+1;
        // so we won't have to immediately call this function again just to find the index
        return this->lastReturnedLesserChildIdx;
    }

    // otherwise, return -1 (which is what lastReturnedLesserChildIdx will be) - either there are no children or both children are larger
    return this->lastReturnedLesserChildIdx;
}

/**
 * @brief Prints out a NodeHeap
 * 
 * @param os 
 * @param heap 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const NodeHeap &heap){
    for (int i=0; i<heap.size-1; i++){
        os << *(heap.array[i]) << " || ";
    }
    // last element
    if (heap.size > 0){
        os << *(heap.array[heap.size-1]);
    }
    // now return the outstream
    return os;
}

#endif