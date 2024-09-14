#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "LinkedList.h"

class QuickSort {
public:
    static void QuickSortList(LinkedList& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            QuickSortList(arr, low, pi - 1);
            QuickSortList(arr, pi + 1, high);
        }
    }

private:
    static int partition(LinkedList& arr, int low, int high) {
        int pivot = arr.get(high);
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr.get(j) < pivot) {
                i++;
                swap(arr, i, j); // Use the swap method
            }
        }

        swap(arr, i + 1, high); // Swap the pivot element to its correct position
        return (i + 1);
    }

    // Swap method that swaps elements at two indices in the LinkedList
    static void swap(LinkedList& arr, int i, int j) {
        int temp = arr.get(i);
        arr.set(i, arr.get(j));
        arr.set(j, temp);
    }
};

#endif //QUICKSORT_H
