#include "adaptarray.h"
#include <stdlib.h>
#include <stdio.h>

struct AdptArray_ {
    PElement* data;
    int size;
    int capacity;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
};

PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func) {
    PAdptArray arr = malloc(sizeof(struct AdptArray_));
    if (arr == NULL) {
        return NULL;
    }
    arr->data = malloc(sizeof(PElement) * 4);
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }
    arr->size = 0;
    arr->capacity = 4;
    arr->copy_func = copy_func;
    arr->del_func = del_func;
    arr->print_func = print_func;
    return arr;
}

void DeleteAdptArray(PAdptArray arr) {
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < arr->size; i++) {
        arr->del_func(arr->data[i]);
    }
    free(arr->data);
    free(arr);
}

Result SetAdptArrayAt(PAdptArray arr, int index, PElement element) {
    if (index < 0 || index >= arr->size) {
        return FAIL;
    }
    arr->del_func(arr->data[index]);
    arr->data[index] = arr->copy_func(element);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray arr, int index) {
    if (index < 0 || index >= arr->size) {
        return NULL;
    }
    return arr->data[index];
}

int GetAdptArraySize(PAdptArray arr) {
    return arr->size;
}

void PrintDB(PAdptArray arr) {
    for (int i = 0; i < arr->size; i++) {
        arr->print_func(arr->data[i]);
    }
}
