/*!
    \file
    File with a description of the double linked list DUMP functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdarg.h>

#include <string.h>

#include "Default.h"
#include "Dump.h"
#include "ListMethods.h"

const char* CAT          = "Cat [shape=none, label=\"\", image=\"/home/yan/projects/Double-linked-list/DumpFiles/cutecat.jpg\", fixedsize=true, width=1, height=1];";
const char* LOG_FILE     = "/home/yan/projects/Double-linked-list/DumpFiles/log.html";
const char* DOT_FILENAME = "/home/yan/projects/Double-linked-list/DumpFiles/test1.dot";
const int   COMMAND_BUFFER_CONSTANT = 500;

/// @brief Macro for the add new line in .dot file
#define NEWDOTLINE(filename) fprintf(filename, "\n  ");

/// @brief Macro for the add new line in .html file
#define NEWHTMLLINE(filename) fputc('\n', filename);

/*!
    @brief Function that calls DUMP
    \param [out] list   - pointer on list
    \param  [in] func   - call function name
    \param  [in] line   - call function line
    \param  [in] title  - information about call function
*/
ListReturnCode ListDump(List* list, const char* func, int line, const char* title, ...) {
    ASSERT(list   != NULL, "NULL POINTER WAS PASSED!\n");
    ASSERT(func   != NULL, "NULL POINTER WAS PASSED!\n");

    FILE* dot_file = fopen(DOT_FILENAME, "w");
    if (!dot_file) {
        printf(RED("Error occured while opening input file!\n"));

        return FILE_ERROR;
    }

    CreateBase(dot_file);
    CreateNodes(list, dot_file);
    CreateEdges(list, dot_file);

    int dump_id = rand();

    char* command = (char*) calloc(COMMAND_BUFFER_CONSTANT, sizeof(char));
    if (command == NULL) {
        printf(RED("MEMORY ERROR!\n"));

        return MEMORY_ERROR;
    }
    fclose(dot_file);

    sprintf(command, "dot -Tpng %s -o /home/yan/projects/Double-linked-list/DumpFiles/dump%d.png",
                                 DOT_FILENAME,                                             dump_id);

    int system_end = system(command);
    if (system_end != 0) {
        printf(RED("Something went wrong...\n"));

        return UNKNOWN_ERROR;
    }
    free(command);

    FILE* html_file = fopen(LOG_FILE, "a");
    if (!html_file) {
        printf(RED("Error occured while opening input file!\n"));

        return FILE_ERROR;
    }

    fprintf(html_file, "<pre>\n<hr>\n    <font size=\"10\">");

    va_list args = {};
    va_start(args, title);

    vfprintf(html_file, title, args);

    va_end(args);

    fprintf(html_file, " ✅</font>\n    ");

    MakeHTMLDump(list, html_file, dump_id, func, line);
    fclose(html_file);

    return SUCCESS;
}

/*!
    @brief Function that creates base for DUMP
    \param [out] list     - pointer on list
    \param  [in] filename - filename .dot file for DUMP
*/
ListReturnCode CreateBase(FILE* filename) {
    ASSERT(filename != NULL, "NULL POINTER WAS PASSED!\n");

    fprintf(filename, "digraph list{\n  rankdir=LR\n  %s\n", CAT);
    NEWDOTLINE(filename)

    return SUCCESS;
}

/*!
    @brief Function that creates nodes for DUMP
    \param [out] list     - pointer on list
    \param  [in] filename - filename .dot file for DUMP
*/
ListReturnCode CreateNodes(List* list, FILE* filename) {
    ASSERT(list     != NULL, "NULL POINTER WAS PASSED!\n");
    ASSERT(filename != NULL, "NULL POINTER WAS PASSED!\n");

    for (size_t i = 0; i < list->capacity; i++) {
        fprintf(filename, "node%lu [shape=Mrecord,style=\"rounded, filled\",\t"
                          "label=\"index: %lu | data: %d | next: %d | prev: %d\",fillcolor=\"lightblue\"]\n  ",
                                i,         i,   DATA(i),   NEXT(i),   PREV(i));
    }
    fprintf(filename,     "node0 [shape=Mrecord,style=\"rounded, filled\",\t"
                          "label=\"index: 0 | data: %d | next: %d | prev: %d\",fillcolor=\"grey\"]\n  ",
                                              DATA(0),   NEXT(0),   PREV(0));
    NEWDOTLINE(filename)

    return SUCCESS;
}

/*!
    @brief Function that creates edges for DUMP
    \param [out] list     - pointer on list
    \param  [in] filename - filename .dot file for DUMP
*/
ListReturnCode CreateEdges(List* list, FILE* filename) {
    ASSERT(list     != NULL, "NULL POINTER WAS PASSED!\n");
    ASSERT(filename != NULL, "NULL POINTER WAS PASSED!\n");

    //* NEXT edges
    fprintf(filename, "edge[color=blue]\n  ");
    fprintf(filename, "node0->node%d\n  ", NEXT(0));

    for (int i = NEXT(0); i != 0; i = NEXT(i)) {
        fprintf(filename, "node%d->node%d\n  ", i, NEXT(i));
    }
    NEWDOTLINE(filename)

    //* PREV edges
    fprintf(filename, "edge[color=red]\n  ");
    fprintf(filename, "node0->node%d\n  ", PREV(0));

    for (int i = PREV(0); i != 0; i = PREV(i)) {
        fprintf(filename, "node%d->node%d\n  ", i, PREV(i));
    }
    NEWDOTLINE(filename)

    //* FREE edges
    fprintf(filename, "edge[color=green]\n  ");
    fprintf(filename, "Cat->node%d\n  ", list->free);
    fprintf(filename, "node%d [fillcolor=\"lightgreen\"]\n  ", list->free);

    int last_index = -1;
    for (int i = list->free; NEXT(i) != -1; i = NEXT(i)) {
        fprintf(filename, "node%d->node%d\n  ", i, NEXT(i));
        fprintf(filename, "node%d [fillcolor=\"lightgreen\"]\n  ", i);
        last_index = i;
    }

    if (last_index != -1) {
        fprintf(filename, "node%d [fillcolor=\"lightgreen\"]\n  ", last_index + 1);
    }

    fprintf(filename, "\n}");

    return SUCCESS;
}

/*!
    @brief Function that returns time in what function was launched
*/
static tm GetTime() {
    time_t time_now = time(NULL);

    return *localtime(&time_now);
}

/*!
    @brief Function that creates edges for DUMP
    \param [out] list      - pointer on list
    \param  [in] html_file - filename .html file for DUMP
    \param  [in] dump_id   - dump id to address the necessary DUMP
*/
ListReturnCode MakeHTMLDump(List* list, FILE* html_file, int dump_id, const char* func, int line) {
    ASSERT(list      != NULL, "NULL POINTER WAS PASSED!\n");
    ASSERT(html_file != NULL, "NULL POINTER WAS PASSED!\n");
    ASSERT(func      != NULL, "NULL POINTER WAS PASSED!\n");

    struct tm tm = GetTime();

    fprintf(html_file, "DUMPED %d-%02d-%02d %02d:%02d:%02d from function %s, %d line \n    ",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, func, line);
    fprintf(html_file, "List [%p]: size = %lu\n    ", list, list->capacity);

    fprintf(html_file, "data [%p]: ", list->data);
    for (size_t i = 0; i < list->capacity; i++) {
        if (i != list->capacity - 1) {
            fprintf(html_file, "%d, ", list->data[i]);
        } else {
            fprintf(html_file, "%d", list->data[i]);
        }
    }
    NEWHTMLLINE(html_file)

    fprintf(html_file, "    next [%p]: ", list->next);
    for (size_t i = 0; i < list->capacity; i++) {
        if (i != list->capacity - 1) {
            fprintf(html_file, "%d, ", list->next[i]);
        } else {
            fprintf(html_file, "%d", list->next[i]);
        }
    }
    NEWHTMLLINE(html_file)

    fprintf(html_file, "    prev [%p]: ", list->prev);
    for (size_t i = 0; i < list->capacity; i++) {
        if (i != list->capacity - 1) {
            fprintf(html_file, "%d, ", list->prev[i]);
        } else {
            fprintf(html_file, "%d", list->prev[i]);
        }
    }
    NEWHTMLLINE(html_file)
    NEWHTMLLINE(html_file)

    fprintf(html_file, "    <img src=dump%d.png>", dump_id);

    return SUCCESS;
}
