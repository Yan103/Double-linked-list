/*!
    \file
    File with a description of the methods of a doubly linked list
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Default.h"
#include "Dump.h"
#include "ListMethods.h"

/// @brief Password
const char* SECRET_PASSWORD_PLEASE_DONT_TELL_IT_TO_ANYONE = "333";

/*!
    @brief Function that creates a doubly linked list
    \param  [in] size - list size
*/
List* ListCtor(size_t size) {
    ASSERT(size > 0, "ERROR SIZE!\n");

    List* list = (List*) calloc(1, sizeof(List));
    if (list == NULL) {
        printf(RED("MEMORY ERROR!\n"));

        return NULL;
    }

    list->data = (ListElem*) calloc(size, sizeof(ListElem));
    if (list->data == NULL) {
        printf(RED("MEMORY ERROR!\n"));
        FREE(list);

        return NULL;
    }
    DATA(0) = POISON;

    list->next = (int*) calloc(size, sizeof(int));
    if (list->next == NULL) {
        printf(RED("MEMORY ERROR!\n"));
        FREE(list);
        FREE(list->data);

        return NULL;
    }
    NEXT(0) = 0;

    list->prev = (int*) calloc(size, sizeof(int));
    if (list->prev == NULL) {
        printf(RED("MEMORY ERROR!\n"));
        FREE(list);
        FREE(list->data);
        FREE(list->next);

        return NULL;
    }
    PREV(0) = 0;

    for (size_t i = 1; i < size; i++) {
        list->data[i] = POISON;
        list->next[i] = (int)i + 1;
        list->prev[i] = -1;
    }

    NEXT(size - 1) = -1;
    list->capacity = size;
    list->free     = 1;

    LIST_VERIFY(list);
    LIST_DUMP(list, "%s (%lu)", __func__, size);

    return list;
}

/*!
    @brief Function that deletes a doubly linked list
    \param [out] list - pointer on list
*/
ListReturnCode ListDtor(List* list) {
    ASSERT(list != NULL, "NULL POINTER WAS PASSED!\n");

    LIST_VERIFY(list);
    LIST_DUMP(list, "%s", __func__);

    FREE(list->data)
    FREE(list->next)
    FREE(list->prev)

    FREE(list)

    return SUCCESS;
}

/*!
    @brief Function that insert a value after specified index in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] index - element index
    \param  [in] value - insert value
*/
ListReturnCode ListInsertAfter(List* list, int index, ListElem value) {
    ASSERT(list != NULL, "NULL POINTER WAS PASSED!\n");
    ASSERT(index >= 0,   "INDEX ERROR!\n");

    LIST_VERIFY(list);
    LIST_DUMP(list, "Start: %s (%d, %d)", __func__, index, value);

    if (list->free == -1) {
        printf(RED("There is no free space in the list!\n"));

        return FREE_ERROR;
    }

    int new_index = list->free;
    int old_index = NEXT(index);

    list->free = NEXT(new_index);
    DATA(new_index) = value;

    NEXT(index) = new_index;
    NEXT(new_index) = old_index;

    PREV(new_index) = PREV(old_index);
    PREV(old_index) = new_index;

    LIST_VERIFY(list);
    LIST_DUMP(list, "End: %s (%d, %d)", __func__, index, value);

    return SUCCESS;
}

/*!
    @brief Function that insert a value before specified index in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] index - element index
    \param  [in] value - insert value
*/
ListReturnCode ListInsertBefore(List* list, int index, ListElem value) {
    ASSERT(list != NULL, "NULL POINTER WAS PASSED!\n");
    ASSERT(index >= 0,   "INDEX ERROR!\n");

    LIST_VERIFY(list);

    ListInsertAfter(list, PREV(index), value);

    return SUCCESS;
}

/*!
    @brief Function that insert a value in start (0 index) in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] value - insert value
*/
ListReturnCode ListInsertStart(List* list, ListElem value) {
    ASSERT(list != NULL, "NULL POINTER WAS PASSED!\n");

    LIST_VERIFY(list);

    ListInsertAfter(list, 0, value);

    return SUCCESS;
}

/*!
    @brief Function that insert a value in end (capacity - 1 index) in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] value - insert value
*/
ListReturnCode ListInsertEnd(List* list, ListElem value) {
    ASSERT(list != NULL, "NULL POINTER WAS PASSED!\n");
    LIST_VERIFY(list);

    ListInsertAfter(list, PREV(0), value);

    return SUCCESS;
}

/*!
    @brief Function that delete an element by his index in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] index - delete index
*/
ListReturnCode ListDeleteIndex(List* list, int index) {
    ASSERT(list != NULL, "NULL POINTER WAS PASSED!\n");
    ASSERT(index >= 0,   "INDEX ERROR!\n");

    LIST_VERIFY(list);
    LIST_DUMP(list, "Start: %s (%d)", __func__, index);

    DATA(index) = POISON;

    int next_index = NEXT(index);
    int prev_index = PREV(index);

    NEXT(prev_index) = next_index;
    PREV(next_index) = prev_index;

    NEXT(index) = list->free;
    PREV(index) = -1;
    list->free = index;

    LIST_VERIFY(list);
    LIST_DUMP(list, "End: %s (%d)", __func__, index);

    return SUCCESS;
}

/*!
    @brief Function that delete a value from start (0 index) in a doubly linked list
    \param [out] list  - pointer on list
*/
ListReturnCode ListDeleteStart(List* list) {
    ASSERT(list != NULL, "NULL POINTER WAS PASSED!\n");

    LIST_VERIFY(list);

    ListDeleteIndex(list, NEXT(0));

    return SUCCESS;
}

/*!
    @brief Function that delete a value from end (capacity - 1 index) in a doubly linked list
    \param [out] list  - pointer on list
*/
ListReturnCode ListDeleteEnd(List* list) {
    ASSERT(list != NULL, "NULL POINTER WAS PASSED!\n");

    LIST_VERIFY(list);

    ListDeleteIndex(list, PREV(0));

    return SUCCESS;
}

/*!
    @brief Function that find an element by his value in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] value - delete value
    @return Returns the index of the first occurrence of the element or -1 if it is not found
*/
int VeryVerySlowAlgorithmThatFindIndexOfElementByItsValuePleaseDontUseThisFunctionBecauseItsTheSlowest(List* list, ListElem value) {
    ASSERT(list != NULL, "NULL POINTER WAS PASSED!\n");

    LIST_VERIFY(list);
    LIST_DUMP(list, "Start: %s (%d)", __func__, value);

    char password_buffer[PASSWORD_LENGTH] = {};
    printf(YELLOW("IF YOU ARE SURE THAT YOU REALLY WANT TO USE THIS FUNCTION, then\nPlease, enter a password:\n"));
    scanf("%s", password_buffer);

    if (strcmp(password_buffer, SECRET_PASSWORD_PLEASE_DONT_TELL_IT_TO_ANYONE) != 0) {
        fprintf(stderr, RED("You are not worthy to use this list! Bye, loser...\n"));
        abort();
    }

    int index = -1;

    for (int i = NEXT(0); i != 0; i = NEXT(i)) {
        if (DATA(i) == value) {
            index = i;

            break;
        }
    }

    LIST_VERIFY(list);
    LIST_DUMP(list, "End: %s (%d)", __func__, value);

    return index;
}

/*!
    @brief Function that delete an element by his value in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] value - delete value
*/
ListReturnCode ListDeleteValue(List* list, ListElem value) {
    ASSERT(list != NULL, "NULL POINTER WAS PASSED!\n");

    LIST_VERIFY(list);
    LIST_DUMP(list, "Start: %s (%d)", __func__, value);

    int delete_index = VeryVerySlowAlgorithmThatFindIndexOfElementByItsValuePleaseDontUseThisFunctionBecauseItsTheSlowest(list, value);

    if (delete_index != -1) {
        ListDeleteIndex(list, delete_index);
    } else {
        printf(RED("THERE IS NO SUCH VALUE IN LIST!\n"));

        return INDEX_ERROR;
    }

    LIST_VERIFY(list);
    LIST_DUMP(list, "End: %s (%d)", __func__, value);

    return SUCCESS;
}

/*!
    @brief Function that checks a doubly linked list for correctness
    \param [out] list  - pointer on list
*/
ListReturnCode ListVerificator(List* list) {
    if (list == NULL || list->data == NULL || list->next == NULL || list->prev == NULL) {
        return BAD_POINTER;
    }

    if (list->capacity <= 0) {
        return SIZE_ERROR;
    }

    if (NEXT(0) < 0 || PREV(0) > (int)list->capacity || list->free <= 0 || list->free > (int)list->capacity){
        return SIZE_ERROR;
    }

    for (int i = NEXT(list->free), count = 0; i != -1; i = NEXT(i), count++) {
        if ((size_t)count > list->capacity || (size_t)i >= list->capacity) {
            return SIZE_ERROR;
        }

        if (PREV(i) != -1) {
            return INDEX_ERROR;
        }
    }

    return SUCCESS;
}

/*!
    @brief Function  that will change (increase) the size of a doubly linked list
    \param [out] list     - pointer on list
    \param  [in] new_size - new list size
*/
ListReturnCode ListResize(List* list, size_t new_size) {
    ASSERT(list != 0, "NULL POINTER WAS PASSED!\n");
    ASSERT(new_size > 0, "NEW SIZE ERROR VALUE!\n");

    LIST_VERIFY(list);
    LIST_DUMP(list, "Start: %s (%lu)", __func__, new_size);

    if (new_size <= list->capacity) {
        printf(RED("NEW SIZE ERROR VALUE!\n"));

        return REALLOC_ERROR;
    }

    list->data = (ListElem*) realloc(list->data, new_size * sizeof(ListElem));
    if (list->data == NULL) {
        printf(RED("MEMORY ERROR!\n"));

        return REALLOC_ERROR;
    }

    list->next = (int*) realloc(list->next, new_size * sizeof(int));
    if (list->next == NULL) {
        printf(RED("MEMORY ERROR!\n"));

        return REALLOC_ERROR;
    }

    list->prev = (int*) realloc(list->prev, new_size * sizeof(int));
    if (list->prev == NULL) {
        printf(RED("MEMORY ERROR!\n"));

        return REALLOC_ERROR;
    }

    int free_index = list->free;
    while (NEXT(free_index) != -1) {
        free_index = NEXT(free_index);
    }

    for (size_t i = (size_t)free_index; i < new_size; i++) {
        DATA(i) = POISON;
        NEXT(i) = (int)i + 1;
        PREV(i) = -1;
    }

    list->capacity = new_size;
    NEXT(new_size - 1) = -1;

    LIST_VERIFY(list);
    LIST_DUMP(list, "End: %s (%lu)", __func__, new_size);

    return SUCCESS;
}