#include "MPointerGC.h"
#include <iostream>
#include <chrono>
#include <mutex>


MemoryList::MemoryList() : head(nullptr) {}

MemoryList::~MemoryList() {
    MemoryNode* current = head;
    while (current != nullptr) {
        MemoryNode* next = current->next;
        delete current;
        current = next;
    }
}

void MemoryList::add(void* memory, int logicalAddress) {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    if (memory == nullptr) {
        std::cerr << "Cannot add nullptr memory to MemoryList!" << std::endl;
        return;
    }
    head = new MemoryNode(memory, 1, logicalAddress, head);
}

void MemoryList::remove(int logicalAddress) {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    MemoryNode** current = &head;
    while (*current != nullptr) {
        if ((*current)->logicalAddress == logicalAddress) {
            MemoryNode* toDelete = *current;
            *current = (*current)->next;
            delete toDelete;
            return;
        }
        current = &(*current)->next;
    }
    std::cerr << "Memory with logical address " << logicalAddress << " not found in the list!" << std::endl;
}
bool MemoryList::contains(int logicalAddress) const {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    MemoryNode* current = head;
    while (current != nullptr) {
        if (current->logicalAddress == logicalAddress) {
            return true;
        }
        current = current->next;
    }
    return false;
}
bool MemoryList::contains(void* memory) const {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    MemoryNode* current = head;
    while (current != nullptr) {
        if (current->memory == memory) {
            return true;
        }
        current = current->next;
    }
    return false;
}


void MemoryList::incrementRefCount(int logicalAddress) {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    MemoryNode* current = head;
    while (current != nullptr) {
        if (current->logicalAddress == logicalAddress) {
            current->referenceCount++;
            return;
        }
        current = current->next;
    }
    std::cerr << "Memory with logical address " << logicalAddress << " not found!" << std::endl;
}

void MemoryList::decrementRefCount(int logicalAddress) {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    MemoryNode* current = head;
    while (current != nullptr) {
        if (current->logicalAddress == logicalAddress) {
            current->referenceCount--;
            return;
        }
        current = current->next;
    }
    std::cerr << "Memory with logical address " << logicalAddress << " not found!" << std::endl;
}

int MemoryList::getReferenceCount(int logicalAddress) const {
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

int MemoryList::getId(void* memory) const {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    MemoryNode* current = head;
    while (current != nullptr) {
        if (current->memory == memory) {
            return current->logicalAddress;
        }
        current = current->next;
    }
    return -1;
}

void MemoryList::removeIfZeroReferences(int logicalAddress) {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    MemoryNode** current = &head;
    while (*current != nullptr) {
        if ((*current)->logicalAddress == logicalAddress) {
            if ((*current)->referenceCount == 0) {
                MemoryNode* toDelete = *current;
                *current = (*current)->next;

                delete static_cast<char*>(toDelete->memory);

                delete toDelete;
                std::cout << "Memory with logical address " << logicalAddress << " has been freed." << std::endl;
                return;
            }
        }
        current = &(*current)->next;
    }
}

void MemoryList::debug() const {
    std::lock_guard<std::mutex> lock(memoryListMutex);
    MemoryNode* current = head;
    while (current != nullptr) {
        std::cout << "Memory address: " << current->memory
                  << ", Logical Address: " << current->logicalAddress
                  << ", RefCount: " << current->referenceCount << std::endl;
        current = current->next;
    }
}