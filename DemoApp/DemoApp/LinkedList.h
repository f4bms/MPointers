
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <library.h>

class Node {
public:
    int value;
    MPointer<Node> next = nullptr;

    // Default constructor
    Node() {
        value = 0;
        next = nullptr;
    }

    // Constructor with value
    Node(int val) {
        value = val;
        next = nullptr;
    }
};

class LinkedList {
public:
    // Insert a new node at the beginning of the list
    void insert(int value) {
        MPointer<Node> newNode = MPointer<Node>::New(); // Create a new node
        newNode->value = value;
        newNode->next = head;
        head = newNode;
    }

    void append(int value) {
        std::cout << "miau " << value << std::endl;
        MPointer<Node> newNode = MPointer<Node>::New();
        newNode->value = value;
        std::cout << "Appending value: " << value << std::endl;

        if (!head) {
            head = newNode;
            std::cout << "Head node set to new node" << std::endl;
        } else {
            MPointer<Node> current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
            std::cout << "New node appended after value: " << current->value << std::endl;
        }
    }

    // Remove the first node with the specified value
    void remove(int value) {
        MPointer<Node> current = head;
        MPointer<Node> previous = nullptr;

        while (current) {
            if (current->value == value) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    head = current->next;
                }
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    // Clear the list
    void clear() {
        while (head) {
            MPointer<Node> temp = head;
            head = head->next;
        }
        head = nullptr;
    }

    // Print the list
    void print() const {
        MPointer<Node> current = head;
        while (current) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Get the value of the node at the specified index
    int get(size_t index) const {
        MPointer<Node> current = head;
        size_t currentIndex = 0;
        while (current) {
            if (currentIndex == index) {
                return current->value;
            }
            current = current->next;
            ++currentIndex;
        }
        throw std::out_of_range("Index out of range");
    }

    // Set the value of the node at the specified index
    void set(size_t index, int value) {
        MPointer<Node> current = head;
        size_t currentIndex = 0;
        while (current) {
            if (currentIndex == index) {
                current->value = value;
                return;
            }
            current = current->next;
            ++currentIndex;
        }
        throw std::out_of_range("Index out of range");
    }

private:
    MPointer<Node> head = nullptr; // Pointer to the first node
};




#endif //LINKEDLIST_H
