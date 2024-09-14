#include "MPointerGC.h"
#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <mutex>

MPointerGC* MPointerGC::instance = nullptr;
std::mutex gcMutex;

MPointerGC::MPointerGC() : disposed(false), memoryIdAutoIncrement(0) {
    memoryRegistry = new MemoryList();
}

MPointerGC::~MPointerGC() {
    if (!disposed) {
        delete memoryRegistry;
        disposed = true;
    }
}

MPointerGC* MPointerGC::getInstance() {
    if (instance == nullptr) {
        instance = new MPointerGC();

        pthread_t cleanupThread;
        if (pthread_create(&cleanupThread, nullptr, &cleanupLoop, nullptr) != 0) {
            throw std::runtime_error("Failed to create cleanup thread.");
        }
        pthread_detach(cleanupThread);
    }
    return instance;
}

int MPointerGC::registerMemory(void* memory) {
    if (memoryRegistry->contains(memory)) {
        std::cerr << "Memory is already registered!" << std::endl;
        return memoryRegistry->getId(memory);
    }

    int logicalAddress = memoryIdAutoIncrement++;
    memoryRegistry->add(memory, logicalAddress);
    return logicalAddress;
}



void MPointerGC::incrementRefCount(int logical_addr) {
    std::cout << "Incrementing ref count for Logical Address: " << logical_addr << std::endl;
    memoryRegistry->incrementRefCount(logical_addr);
}

void MPointerGC::decrementRefCount(int logical_addr) {
    std::cout << "Decrementing ref count for Logical Address: " << logical_addr << std::endl;
    memoryRegistry->decrementRefCount(logical_addr);

    if (memoryRegistry->getRefCount(logical_addr) == 0) {
        std::cout << "Memory at Logical Address " << logical_addr << " is being freed." << std::endl;
        memoryRegistry->freeMemory(logical_addr);
    }
}
int MemoryList::getRefCount(int logicalAddress) const {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    MemoryNode* current = head;
    while (current != nullptr) {
        if (current->logicalAddress == logicalAddress) {
            return current->referenceCount;
        }
        current = current->next;
    }
    std::cerr << "Memory with logical address " << logicalAddress << " not found!" << std::endl;
    return -1;
}
void MemoryList::freeMemory(int logicalAddress) {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    MemoryNode** current = &head;
    while (*current != nullptr) {
        if ((*current)->logicalAddress == logicalAddress) {
            MemoryNode* toDelete = *current;
            *current = (*current)->next;

            delete static_cast<char*>(toDelete->memory);

            delete toDelete;
            std::cout << "Memory with logical address " << logicalAddress << " has been freed." << std::endl;
            return;
        }
        current = &(*current)->next;
    }
    std::cerr << "Memory with logical address " << logicalAddress << " not found!" << std::endl;
}



void* MPointerGC::cleanupLoop(void* arg) {
    MPointerGC* gc = MPointerGC::getInstance();
    while (!gc->disposed) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::cout << "Running cleanup loop..." << std::endl;
        gc->debug();
    }
    return nullptr;
}

void MPointerGC::debug() {
    std::lock_guard<std::mutex> lock(gcMutex); // Lock para protección de datos
    std::cout << "Debugging MPointerGC..." << std::endl;
    try {
        memoryRegistry->debug();
    } catch (...) {
        std::cerr << "Failed to debug MPointerGC." << std::endl;
    }
}
