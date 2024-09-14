#ifndef MEMORYLIST_H
#define MEMORYLIST_H
#include <iostream>
#include <mutex>

class MemoryNode {
public:
    void* memory;
    int referenceCount;
    int logicalAddress;
    MemoryNode* next;

    MemoryNode(void* mem, int refCount, int logAddr, MemoryNode* nxt = nullptr)
        : memory(mem), referenceCount(refCount), logicalAddress(logAddr), next(nxt) {}
};

class MemoryList {
public:
    MemoryList();
    ~MemoryList();

    void add(void* memory, int logicalAddress);
    void remove(int logicalAddress);

    bool contains(int logicalAddress) const;

    bool contains(void *memory) const;

    void incrementRefCount(int logicalAddress);
    void decrementRefCount(int logicalAddress);
    int getReferenceCount(int logicalAddress) const;
    int getId(void* memory) const;
    void removeIfZeroReferences(int logicalAddress);
    void debug() const;

    int getRefCount(int logicalAddress) const;

    void freeMemory(int logicalAddress);

private:
    MemoryNode* head;
    mutable std::mutex memoryListMutex;
};
#endif // MEMORYLIST_H
