#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <library.h>

class Node {
public:
    int value;
    MPointer<Node> next = nullptr;
    MPointer<Node> prev = nullptr; // Added prev pointer

    Node() : value(0), next(nullptr), prev(nullptr) {}

    // Constructor with value
    Node(int val) : value(val), next(nullptr), prev(nullptr) {}
};

class LinkedList {
public:
    void insert(int value) {
        MPointer<Node> newNode = MPointer<Node>::New();
        newNode->value = value;
        newNode->next = head;

        if (head) {
            head->prev = newNode; // Update the previous pointer of the current head
        }
        head = newNode;
    }

    void append(int value) {
        MPointer<Node> newNode = MPointer<Node>::New();
        newNode->value = value;

        if (!head) {
            head = newNode;
        } else {
            MPointer<Node> current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current; // Set the previous pointer of the new node
        }
    }

    void remove(int value) {
        MPointer<Node> current = head;
        while (current) {
            if (current->value == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                }
                return;
            }
            current = current->next;
        }
    }

    void clear() {
        while (head) {
            MPointer<Node> temp = head;
            head = head->next;
        }
        head = nullptr;
    }

    void print() const {
        MPointer<Node> current = head;
        while (current) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

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

    MPointer<Node> getHead() const { return head; }
    void setHead(MPointer<Node> newHead) { head = newHead; }

    size_t getSize() const {
        size_t size = 0;
        MPointer<Node> current = head;
        while (current) {
            ++size;
            current = current->next;
        }
        return size;
    }

private:
    MPointer<Node> head = nullptr;
};

#endif //LINKEDLIST_H
