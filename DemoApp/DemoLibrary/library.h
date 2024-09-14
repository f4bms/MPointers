#ifndef DEMOLIBRARY_LIBRARY_H
#define DEMOLIBRARY_LIBRARY_H
#include "MPointerGC.h"

template <typename T>
class MPointer {
public:
    static MPointer<T> New() {
        auto instance = MPointer();
        std::cout << "MPointer::New()" << std::endl;
        instance.memory = new T();
        instance.logicalAddress = MPointerGC::getInstance()->registerMemory(instance.memory);
        MPointerGC::getInstance()->incrementRefCount(instance.logicalAddress);
        std::cout << "Memory registered with ID: " << instance.logicalAddress << std::endl;
        return instance;
    }


    MPointer(const MPointer<T>& source) : memory(source.memory), logicalAddress(source.logicalAddress) {
        std::cout << "MPointer::CopyConstructor()" << std::endl;
        MPointerGC::getInstance()->incrementRefCount(this->logicalAddress);
    }

    ~MPointer() {
        std::cout << "MPointer::destructor()" << std::endl;
        if (memory != nullptr) {
            MPointerGC::getInstance()->decrementRefCount(this->logicalAddress);
        }
    }

    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            if (memory != nullptr) {
                MPointerGC::getInstance()->decrementRefCount(this->logicalAddress);
            }
            this->memory = other.memory;
            this->logicalAddress = other.logicalAddress;
            if (this->memory != nullptr) {
                MPointerGC::getInstance()->incrementRefCount(this->logicalAddress);
            }
        }
        return *this;
    }

    MPointer(const std::nullptr_t) : memory(nullptr), logicalAddress(-1) {
        std::cout << "MPointer::Constructor(nullptr)" << std::endl;
    }

    MPointer<T>& operator=(std::nullptr_t) {
        if (memory != nullptr) {
            MPointerGC::getInstance()->decrementRefCount(this->logicalAddress);
        }
        memory = nullptr;
        logicalAddress = -1;
        return *this;
    }

    MPointer<T>& operator=(const T& value) {
        if (memory != nullptr) {
            *memory = value;
        }
        return *this;
    }

    T& operator*() {
        return *memory;
    }

    T* operator->() {
        return memory;
    }

    explicit operator bool() const {
        return memory != nullptr;
    }

private:
    T* memory = nullptr;
    int logicalAddress = -1;

    MPointer() = default;
    MPointer(T* ptr) : memory(ptr), logicalAddress(MPointerGC::getInstance()->registerMemory(ptr)) {}

};

#endif //DEMOLIBRARY_LIBRARY_H
