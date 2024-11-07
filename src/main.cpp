/*!
    \file
    File with the main function
*/

#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "Default.h"
#include "Dump.h"
#include "ListMethods.h"

int main() {
    srand((unsigned int)time(NULL));

    List* list = ListCtor(5);

    ListInsertAfter(list, 0, 10);
    ListInsertStart(list, 777);
    ListInsertAfter(list, 0, 666);

    ListResize(list, 10);

    ListDeleteStart(list);
    ListInsertAfter(list, 2, 999);
    ListInsertEnd(list, 333);

    printf("%d\n", VeryVerySlowAlgorithmThatFindIndexOfElementByItsValuePleaseDontUseThisFunctionBecauseItsTheSlowest(list, 999));

    ListDtor(list);

    return SUCCESS;
}
