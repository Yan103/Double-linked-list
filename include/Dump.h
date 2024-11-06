/*!
    \file
    File with a description of the double linked list DUMP functions
*/

#ifndef DUMP_H
#define DUMP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Default.h"
#include "Dump.h"
#include "ListMethods.h"

#ifdef DEBUG
    #define LIST_DUMP(list, args_count, ...) { ListDump(list, __func__, __LINE__, args_count, __VA_ARGS__); }
#else
    #define LIST_DUMP(list, args_count, ...) {}
#endif

/*!
    @brief Function that calls DUMP
    \param [out] list   - pointer on list
    \param  [in] func   - call function name
    \param  [in] line   - call function line
    \param  [in] method - call function method and args
*/
ListReturnCode ListDump(List* list, const char* func, int line, int args_count, ...);

/*!
    @brief Function that creates base for DUMP
    \param [out] list     - pointer on list
*/
ListReturnCode CreateBase(FILE* filename);

/*!
    @brief Function that creates nodes for DUMP
    \param [out] list     - pointer on list
    \param  [in] filename - filename .dot file for DUMP
*/
ListReturnCode CreateNodes(List* list, FILE* filename);

/*!
    @brief Function that creates edges for DUMP
    \param [out] list     - pointer on list
    \param  [in] filename - filename .dot file for DUMP
*/
ListReturnCode CreateEdges(List* list, FILE* filename);

/*!
    @brief Function that creates edges for DUMP
    \param [out] list      - pointer on list
    \param  [in] html_file - filename .html file for DUMP
    \param  [in] dump_id   - dump id to address the necessary DUMP
    \param  [in] func      - call function name
    \param  [in] line      - call function line
    \param  [in] method    - call function method and args
*/
ListReturnCode MakeHTMLDump(List* list, FILE* html_file, int dump_id, const char* func, int line);

#endif // DUMP_H