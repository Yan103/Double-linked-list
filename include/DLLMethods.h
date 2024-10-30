#include <stdio.h>

typedef int DLL_elem;

const int LIST_SIZE   = 10;
const DLL_elem POISON = -666;

struct DLL {
    DLL_elem* data;
    int*      next;
    int*      prev;
};

void DLLCtor(DLL* dll);
void DLLDtor(DLL* dll);
DLL* DLLInit();
