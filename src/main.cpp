#include <assert.h>
#include <stdio.h>

#include <stdlib.h>

#include "Default.h"
#include "DLLMethods.h"

int main() {
    DLL* dll = DLLInit();

    DLLCtor(dll);

    printf("!\n");

    DLLDtor(dll);

    return 0;
}