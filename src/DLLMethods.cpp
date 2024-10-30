#include <assert.h>
#include <stdio.h>

#include <stdlib.h>

#include "Default.h"
#include "DLLMethods.h"

DLL* DLLInit() {
    DLL* dll = (DLL*) calloc(1, sizeof(DLL));
    if (dll == NULL) {
        printf(RED("MEMORY ERROR!\n"));
    }

    return dll;
}

void DLLCtor(DLL* dll) {
    assert(dll != NULL);

    dll->data = (DLL_elem*) calloc(LIST_SIZE, sizeof(DLL_elem));
    if (dll->data == NULL) {
        printf(RED("MEMORY ERROR!\n"));
    }
    dll->data[0] = POISON;
    

    dll->next = (int*) calloc(LIST_SIZE, sizeof(int));
    if (dll->next == NULL) {
        printf(RED("MEMORY ERROR!\n"));
    }

    dll->prev = (int*) calloc(LIST_SIZE, sizeof(int));
    if (dll->prev == NULL) {
        printf(RED("MEMORY ERROR!\n"));
    }
}

void DLLDtor(DLL* dll) {
    assert(dll != NULL);

    FREE(dll->data)
    FREE(dll->next)
    FREE(dll->prev)

    FREE(dll)
}