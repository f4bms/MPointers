#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "LinkedList.h"

class InsertionSort {
public:
    static void Sort(LinkedList& list) {
        if (list.getSize() <= 1) {
            return; // List is already sorted
        }

        MPointer<Node> sorted = nullptr;
        MPointer<Node> current = list.getHead();

        while (current) {
            MPointer<Node> next = current->next;
            insertSorted(sorted, current);
            current = next;
        }

        list.setHead(sorted);
    }

private:
    static void insertSorted(MPointer<Node>& sorted, MPointer<Node> newNode) {
        if (!sorted || newNode->value <= sorted->value) {
            newNode->next = sorted;
            newNode->prev = nullptr;
            if (sorted) {
                sorted->prev = newNode;
            }
            sorted = newNode;
        } else {
            MPointer<Node> current = sorted;
            while (current->next && current->next->value < newNode->value) {
                current = current->next;
            }
            newNode->next = current->next;
            if (current->next) {
                current->next->prev = newNode;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }
};

#endif // INSERTIONSORT_H
