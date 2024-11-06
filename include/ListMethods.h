/*!
    \file
    File with a description of the methods of a doubly linked list
*/

#ifndef LISTMETHODS_H
#define LISTMETHODS_H

#include <stdio.h>

/// @brief Macro for accessing the value by index
#define DATA(index) list->data[(index)]

/// @brief Macro for getting the next element by index
#define NEXT(index) list->next[(index)]

/// @brief Macro for getting the previous element by index
#define PREV(index) list->prev[(index)]

/// @brief Macro for launch the list verificator function
#ifdef DEBUG
    #define LIST_VERIFY(list) {                                                              \
        int check_result = ListVerificator(list);                                            \
        if (check_result != 0) {                                                             \
            fprintf(stderr, RED("Something went wrong... Error code: %d\n"), check_result);  \
            abort();                                                                         \
        }                                                                                    \
    }
#else
    #define LIST_VERIFY(list) {}
#endif

/// @brief Type of items in a doubly linked list
typedef int ListElem;

/// @brief Constant for empty cells in a doubly linked list
const ListElem POISON = -666;

/// @brief Constant for password buffer
const size_t PASSWORD_LENGTH = 100;

/// @brief Structure doubly linked list
struct List {
    ListElem*     data;
    int*          next;
    int*          prev;
    size_t    capacity;
    int           free;
};

/// @brief Enum with return functions codes
enum ListReturnCode {
    SUCCESS       =  0,
    UNKNOWN_ERROR = -1,
    MEMORY_ERROR  = -2,
    FREE_ERROR    = -3,
    INDEX_ERROR   = -4,
    BAD_POINTER   = -5,
    SIZE_ERROR    = -6,
    FILE_ERROR    = -7,
    REALLOC_ERROR = -8,
};

/*!
    @brief Function that creates a doubly linked list
    \param  [in] size - list size
*/
List* ListCtor(size_t size);

/*!
    @brief Function that deletes a doubly linked list
    \param [out] list - pointer on list
*/
ListReturnCode ListDtor(List* list);

/*!
    @brief Function that insert a value after specified index in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] index - element index
    \param  [in] value - insert value
*/
ListReturnCode ListInsertAfter(List* list, int index, ListElem value);

/*!
    @brief Function that insert a value before specified index in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] index - element index
    \param  [in] value - insert value
*/
ListReturnCode ListInsertBefore(List* list, int index, ListElem value);

/*!
    @brief Function that insert a value in start (0 index) in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] value - insert value
*/
ListReturnCode ListInsertStart(List* list, ListElem value);

/*!
    @brief Function that insert a value in end (capacity - 1 index) in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] value - insert value
*/
ListReturnCode ListInsertEnd(List* list, ListElem value);

/*!
    @brief Function that delete a value from start (0 index) in a doubly linked list
    \param [out] list  - pointer on list
*/
ListReturnCode ListDeleteStart(List* list);

/*!
    @brief Function that delete a value from end (capacity - 1 index) in a doubly linked list
    \param [out] list  - pointer on list
*/
ListReturnCode ListDeleteEnd(List* list);

/*!
    @brief Function that delete an element by his index in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] index - delete index
*/
ListReturnCode ListDeleteIndex(List* list, int index);

/*!
    @brief Function that delete an element by his value in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] value - delete value
*/
ListReturnCode ListDeleteValue(List* list, ListElem value);

/*!
    @brief Function that find an element by his value in a doubly linked list
    \param [out] list  - pointer on list
    \param  [in] value - delete value
    @return Returns the index of the first occurrence of the element or -1 if it is not found
*/
int VeryVerySlowAlgorithmThatFindIndexOfElementByItsValuePleaseDontUseThisFunctionBecauseItsTheSlowest(List* list, ListElem value);

/*!
    @brief Function that checks a doubly linked list for correctness
    \param [out] list  - pointer on list
*/
ListReturnCode ListVerificator(List* list);

/*!
    @brief Function  that will change (increase) the size of a doubly linked list
    \param [out] list     - pointer on list
    \param  [in] new_size - new list size
*/
ListReturnCode ListResize(List* list, size_t new_size);

#endif // LISTMETHODS_H