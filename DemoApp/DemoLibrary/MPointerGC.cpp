#include "MPointerGC.h"
#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>

MPointerGC* MPointerGC::instance = nullptr;

// Constructor privado
MPointerGC::MPointerGC() : disposed(false), memoryIdAutoIncrement(0) {
    memoryRegistry = new MemoryList();
}

// Destructor para limpiar los recursos
MPointerGC::~MPointerGC() {
    if (!disposed) {
        delete memoryRegistry;
        disposed = true;
    }
}

// Método estático para obtener la instancia (Singleton)
MPointerGC* MPointerGC::getInstance() {
    if (instance == nullptr) {
        instance = new MPointerGC();

        // Inicia el hilo de limpieza
        pthread_t cleanupThread;
        pthread_create(&cleanupThread, nullptr, &cleanupLoop, nullptr);
        pthread_detach(cleanupThread);
    }
    return instance;
}

int MPointerGC::registerMemory(void *memory) {
    // Check if the memory is already registered
    int existingId = memoryRegistry->getId(memory);
    if (existingId != -1) {
        // Memory already registered, return the existing ID
        std::cout << "Memory already registered with ID: " << existingId << std::endl;
        return existingId;
    }
    // Register new memory
    int id = memoryIdAutoIncrement++;
    memoryRegistry->add(memory, id);
    std::cout << "Memory registered with ID: " << id << std::endl;
    return id;
}


// Incrementar el conteo de referencias
void MPointerGC::incrementRefCount(int logical_addr) {
    memoryRegistry->incrementRefCount(logical_addr);
    std::cout << "Incrementing reference count for address: " << logical_addr << std::endl;
}

// Decrementar el conteo de referencias
void MPointerGC::decrementRefCount(int logical_addr) {
    memoryRegistry->decrementRefCount(logical_addr);
    std::cout << "Decrementing reference count for address: " << logical_addr << std::endl;
    memoryRegistry->removeIfZeroReferences(logical_addr);
}

// Función de limpieza en bucle (hilo)
void* MPointerGC::cleanupLoop(void* arg) {
    MPointerGC* gc = MPointerGC::getInstance();
    while (!gc->disposed) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::cout << "Running cleanup loop..." << std::endl;
        gc->debug();
    }
    return nullptr;
}

// Método de depuración para imprimir el estado del recolector de basura
void MPointerGC::debug() {
    std::cout << "Debugging MPointerGC..." << std::endl;
    memoryRegistry->debug();
}
