#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    PElement* elements;
    int size;
    int capacity;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func)
{
    PAdptArray arr = (PAdptArray)malloc(sizeof(AdptArray));
    if (arr == NULL) return NULL;
    arr->size = 0;
    arr->capacity = 10;
    arr->elements = (PElement*)calloc(arr->capacity, sizeof(PElement));
    if (arr->elements == NULL)
    {
        free(arr);
        return NULL;
    }
    arr->copy_func = copy_func;
    arr->del_func = del_func;
    arr->print_func = print_func;
    return arr;
}

void DeleteAdptArray(PAdptArray arr)
{
    if (arr == NULL) return;
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->elements[i] != NULL)
        {
            arr->del_func(arr->elements[i]);
        }
    }
    free(arr->elements);
    free(arr);
}

Result SetAdptArrayAt(PAdptArray arr, int index, PElement element)
{
    if (arr == NULL || index < 0 || index >= arr->capacity)
    {
        return FAIL;
    }
    if (index >= arr->size)
    {
        for (int i = arr->size; i <= index; i++)
        {
            arr->elements[i] = NULL;
        }
        arr->size = index + 1;
    }
    if (arr->elements[index] != NULL)
    {
        arr->del_func(arr->elements[index]);
    }
    arr->elements[index] = arr->copy_func(element);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray arr, int index)
{
    if (arr == NULL || index < 0 || index >= arr->size)
    {
        return NULL;
    }
    return arr->elements[index];
}

int GetAdptArraySize(PAdptArray arr)
{
    if (arr == NULL)
    {
        return -1;
    }
    return arr->size;
}

void PrintDB(PAdptArray arr)
{
    if (arr == NULL || arr->print_func == NULL) return;
    for (int i = 0; i < arr->size; i++)
    {
        printf("Element %d: ", i);
        if (arr->elements[i] != NULL)
        {
            arr->print_func(arr->elements[i]);
        }
        printf("\n");
    }
}

