#ifndef MEMORYLIST_H
#define MEMORYLIST_H

#include <iostream>

class MemoryList {
public:
    MemoryList();
    ~MemoryList();

    void add(void* memory, int logicalAddress);
    void remove(int logicalAddress);
    void incrementRefCount(int logicalAddress);
    void decrementRefCount(int logicalAddress);

    int getReferenceCount(int logicalAddress) const;

    int getId(void *memory) const;

    void removeIfZeroReferences(int logicalAddress);
    void debug() const;
private:
    struct Node {
        void* memory;
        int referenceCount = 0;
        int logicalAddress;
        Node* next;
    };

    Node* head;
};

#endif // MEMORYLIST_H
