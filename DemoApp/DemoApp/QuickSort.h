#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "LinkedList.h"

//NO pude no cambiar los algoritmos de ordenamiento por el swap :))

class QuickSort {
public:
    static void QuickSortList(LinkedList& list) {
        size_t listSize = getListSize(list);
        QuickSortList(list, 0, listSize - 1);
    }

private:
    static void QuickSortList(LinkedList& list, int low, int high) {
        if (low < high) {
            int pi = partition(list, low, high);
            QuickSortList(list, low, pi - 1);
            QuickSortList(list, pi + 1, high);
        }
    }

    static int partition(LinkedList& list, int low, int high) {
        int pivot = list.get(high);
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (list.get(j) < pivot) {
                i++;
                swap(list, i, j);
            }
        }

        swap(list, i + 1, high);
        return (i + 1);
    }

    static void swap(LinkedList& list, int i, int j) {
        int temp = list.get(i);
        list.set(i, list.get(j));
        list.set(j, temp);
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

#endif //QUICKSORT_H
