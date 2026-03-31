#include <stdio.h>

void print_array(int array[], int length);
void bubblesort(int array[], int length);

int main()
{
	int quantidade = 10;

	int teste[] = {4,3,2,1,6,4,2,3,10};
	print_array(teste, quantidade);
	bubblesort(teste, quantidade);
	printf("0-0");
	print_array(teste,quantidade);
	return 0;
}

void print_array(int array[], int length)
{
	for(int i = 0; i< length; i++)
	{
		printf("\n%i\n", array[i]);
	}
}

void bubblesort(int array[], int length)
{
	int swap = 1;
	while(swap == 1)
	{
		swap = 0;
		for(int i = 0; i < length; i++)
		{
			if(i > 0)
			{
				if(array[i-1] > array[i]) 
				{
					int temp = array[i-1];
					array[i-1] = array[i];
					array[i] = temp;
					swap = 1;
				}	
			}
		}
	}
}
