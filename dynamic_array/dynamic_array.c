#include <stdlib.h>
#include <stdio.h>

typedef struct dynamic_array
{
    int *data;
    size_t size;
    size_t used;
} dynamic_array;


void initialize_array(dynamic_array *da, size_t initialSize)
{
    da->data = calloc(initialSize, sizeof(int));
    da->size = initialSize;
    da->used = 0;
}

void insert_array(dynamic_array *da, int value)
{
    if(da->used*sizeof(value) == da->size)
    {
        da->size *= 2;
        da->data = realloc(da->data, da->size * sizeof(value));
    }

    da->data[da->used] = value;
    da->used += 1;
    
}

void free_array(dynamic_array *da)
{
    free(da->data);
    da->data = NULL;
    da->used = da->size = 0;
}

int main()
{
    int tamanho = 20;
    dynamic_array x;
    initialize_array(&x, tamanho);

    for(int i = 0; i < tamanho+20; i++)
    {
        insert_array(&x, i+1);
    }

    for(int i = 0; i < x.used; i++)
    {
        printf("%i\n", x.data[i]);
    }

}
