#include <iostream>
#include "QuickSort.h"


//profe si corre esto mi Reference Counter empieza en 1 por cualquier cosa
//Hay un Mpointer que no sé qué está pasando que se crea de la nada :))
//el pointer que se crea de la nada es el del medio pero omitiendo eso lo demás sirve


MPointer<int> foo() {
    MPointer<int> temp2 = MPointer<int>::New();
    MPointer<int> temp = MPointer<int>::New();
    temp = 666;
    MPointerGC::getInstance()->debug();
    return temp;
}
int main()
{
    MPointer<int> mp1 = MPointer<int>::New();
    MPointer<int> mp2 = MPointer<int>::New();
    MPointer<bool> bP = MPointer<bool>::New();
    MPointer<bool> bP2 = bP;
    bP = true;
    foo();
    MPointerGC::getInstance()->debug();

    *mp1 = 100;
    mp2 = 55;
    MPointer<int> mp3 = mp2;
    MPointerGC::getInstance()->debug();

    mp3 = mp1;
    MPointerGC::getInstance()->debug();



    return 0;
}
