#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "LinkedList.h"

class BubbleSort {
public:
    static void Sort(LinkedList& list) {
        bool swapped;
        size_t listSize = getListSize(list);

        for (size_t i = 0; i < listSize - 1; ++i) {
            swapped = false;
            for (size_t j = 0; j < listSize - i - 1; ++j) {
                if (list.get(j) > list.get(j + 1)) {
                    swap(list, j, j + 1);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

private:
    static void swap(LinkedList& list, size_t index1, size_t index2) {
        if (index1 == index2) return;
        int temp = list.get(index1);
        list.set(index1, list.get(index2));
        list.set(index2, temp);
    }

    static size_t getListSize(const LinkedList& list) {
        size_t size = 0;
        try {
            while (true) {
                list.get(size); // Try to access each index
                ++size;
            }
        } catch (const std::out_of_range&) {
            // Size determined when exception is caught
        }
        return size;
    }
};

#endif // BUBBLESORT_H
