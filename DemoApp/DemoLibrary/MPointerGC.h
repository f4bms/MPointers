
#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include "MemoryList.h"

class MPointerGC {
public:
    static MPointerGC* getInstance();

    bool disposed;


    ~MPointerGC();
    int registerMemory(void *memory);
    void incrementRefCount(int logical_addr);
    void decrementRefCount(int logical_addr);
    void debug();

private:
    static MPointerGC* instance;
    static void *cleanupLoop(void *arg);

    int memoryIdAutoIncrement = 0;

    MemoryList* memoryRegistry = new MemoryList;

    MPointerGC();

};

#endif //MPOINTERGC_H
