#include "MemoryList.h"
#include <iostream>
#include <mutex>


// Constructor
MemoryList::MemoryList() : head(nullptr) {}

MemoryList::~MemoryList() {
    Node* current = head;

    while (current != nullptr) {
        Node* next = current->next;

        // Free the dynamically allocated memory associated with the node
        if (current->memory != nullptr) {
            delete static_cast<char*>(current->memory);  // Adjust the cast based on actual memory type
            current->memory = nullptr;  // Optional: set pointer to nullptr after deletion
        }

        // Delete the node itself
        delete current;
        current = next;
    }

    head = nullptr;  // Ensure the list is fully cleared
}

std::mutex memoryListMutex;

void MemoryList::add(void* memory, int logicalAddress) {
    std::lock_guard<std::mutex> lock(memoryListMutex);

    // Check if the memory pointer is nullptr
    if (memory == nullptr) {
        std::cerr << "Cannot add nullptr memory to MemoryList!" << std::endl;
        return;
    }

    // Proceed with adding the valid memory pointer
    Node* newNode = new Node{memory, 1, logicalAddress, head};
    head = newNode;
}


// Eliminar un nodo por el ID lógico
void MemoryList::remove(int logicalAddress) {
    Node** current = &head;
    while (*current != nullptr) {
        if ((*current)->logicalAddress == logicalAddress) {
            Node* toDelete = *current;
            *current = (*current)->next;
            delete toDelete;
            return;
        }
        current = &(*current)->next;
    }
    std::cerr << "Memory with logical address " << logicalAddress << " not found in the list!" << std::endl;
}

void MemoryList::incrementRefCount(int logicalAddress) {
    Node* current = head;
    while (current != nullptr) {
        if (current->logicalAddress == logicalAddress) {
            std::cout << "Before Increment: Ref count = " << current->referenceCount << std::endl;
            current->referenceCount++;
            std::cout << "After Increment: Ref count = " << current->referenceCount << std::endl;
            return;
        }
        current = current->next;
    }
    std::cerr << "Memory with logical address " << logicalAddress << " not found!" << std::endl;
}

void MemoryList::decrementRefCount(int logicalAddress) {
    Node* current = head;
    while (current != nullptr) {
        if (current->logicalAddress == logicalAddress) {
            std::cout << "Before Decrement: Ref count = " << current->referenceCount << std::endl;
            current->referenceCount--;
            std::cout << "After Decrement: Ref count = " << current->referenceCount << std::endl;
            return;
        }
        current = current->next;
    }
    std::cerr << "Memory with logical address " << logicalAddress << " not found!" << std::endl;
}
// Method to get the reference count of a registered memory
int MemoryList::getReferenceCount(int logicalAddress) const {
    std::lock_guard<std::mutex> lock(memoryListMutex);

    Node* current = head;
    while (current != nullptr) {
        if (current->logicalAddress == logicalAddress) {
            return current->referenceCount;
        }
        current = current->next;
    }
    std::cerr << "Memory with logical address " << logicalAddress << " not found!" << std::endl;
    return -1; // Indicate that the logical address was not found
}
// Method to get the ID of a registered memory
int MemoryList::getId(void* memory) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->memory == memory) {
            return current->logicalAddress;
        }
        current = current->next;
    }
    return -1; // Indicate that the memory address is not found
}




void MemoryList::removeIfZeroReferences(int logicalAddress) {
    Node** current = &head;
    while (*current != nullptr) {
        if ((*current)->logicalAddress == logicalAddress) {
            if ((*current)->referenceCount == 0) {
                Node* toDelete = *current;
                *current = (*current)->next;

                // Delete the memory pointed to by 'memory'
                delete static_cast<char*>(toDelete->memory); // Type may need adjustment

                delete toDelete;
                std::cout << "Memory with logical address " << logicalAddress << " has been freed." << std::endl;
                return;
            }
        }
        current = &(*current)->next;
    }
}

// Método de depuración para imprimir todas las direcciones de memoria y sus conteos de referencias
void MemoryList::debug() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << "Memory address: " << current->memory
                  << ", Logical Address: " << current->logicalAddress
                  << ", RefCount: " << current->referenceCount << std::endl;
        current = current->next;
    }
}
