#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int low, int high);
void quicksort(int arr[], int low, int high);
void swap(int* a, int* b);


int partition(int arr[], int low, int high)
{
    int pivot = arr[high];

    int i = low - 1;

    for(int j = low; j <= high -1; j++)
    {
	if(arr[j] < pivot)
	{
	    i++;
	    swap(&arr[i], &arr[j]);
	}
    }

    swap(&arr[i+1], &arr[high]);
    return i+1;
}

void swap(int* a, int* b) 
{
    int t = *a;
    *a = *b;
    *b = t;
}

void quicksort(int arr[], int low, int high)
{
    if(low < high)
    {
	int pi = partition(arr, low, high);
	
	quicksort(arr, low, pi-1);
	quicksort(arr, pi+1, high);
    }
}


int main(int argc, char* argv[])
{
    if(argc > 2)
    {
	int arr[argc];
	for(int i = 0; i < argc; i++)
	{
		if(i > 0)
		{
			arr[i] = strtol(argv[i], NULL, 10);
		}
	}
	int arr_length = sizeof(arr)/sizeof(arr[0]);
	quicksort(arr, 0, arr_length-1);
    	for(int i = 0; i < arr_length-1; i++)
	{
		printf("\n%d\n", arr[i]);
	}
    }
}


