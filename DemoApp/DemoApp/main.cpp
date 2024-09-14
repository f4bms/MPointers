#include <iostream>
#include "QuickSort.h"

MPointer<int> foo() {
    MPointer<int> temp2 = MPointer<int>::New();
    MPointer<int> temp = MPointer<int>::New();
    temp = 666;
    MPointerGC::getInstance()->debug();
    return temp;
}
int main()
{

    return 0;
}


