#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

int file_length_seeker(FILE *stream)
{
	int count = 0;
	int temp;

	while (fscanf(stream, "%d", &temp) == 1) {
		count++;
	}

	rewind(stream);
	return count;
}

int argv_to_int(char* argv)
{
	char* final;
	long guess = strtol(argv, &final, 0);

	if(final == argv)
	{
		return -1;
	}

	return (int)guess;
}



int binary_search(int* data, int data_length, int target)
{

	int inicio = 0;
	int fim = data_length;
	
	float loops = 0;
	loops++;
	if(target == data_length)
	{
		printf("quantidade de iteracoes: %2.f\n", loops);
		return target;
	}

	while(inicio <= fim)
	{
		int meio = inicio+((fim-inicio)/2); 	
		int aux = data[meio-1];
		loops++;	


		if(aux < target)
		{
			inicio = meio+1;
		}
		else if(aux > target)
		{
			fim = meio-1;
		}
		else
		{
			printf("quantidade de iteracoes: %2.f\n", loops);
			return meio;
		}

	}
	
	printf("Numero nao esta na lista\n");
	return -1;

	return -2;
}

int* load_file_to_memory(FILE *file, long length)
{
    if (!file) return NULL;

    int* memory = malloc(sizeof(int) * length);
    if (!memory) return NULL;

    for (long i = 0; i < length-1; i++)
    {
	    int temp;
	    int result = fscanf(file, "%i", &temp);

	    if (result != 1) {
		printf("Erro na leitura na posição %ld\n", i);
		break;
	    }

	    memory[i] = temp;    
    }

    return memory;
}

int main(int argc, char** argv)
{

	if(argc != 2)
	{
		printf("Uso: binarie_search [NUMERO]\n");
		return 1;
	}
	
	int guess = argv_to_int(argv[1]);
	if(guess == -1)
	{
		goto error;
	}

	FILE* number_file = fopen("numeros.txt", "r");
	if(number_file == NULL)
	{
		printf("Erro ao abrir o arquivo\n %d\n", errno);
		goto error;
	}	

	int end_of_file = file_length_seeker(number_file);
	if(end_of_file == -1)
	{
		printf("Erro ao calcular o tamanho do arquivo\n");
		goto error;
	}


	int* number_list = load_file_to_memory(number_file, end_of_file);
	if(number_list == NULL)
	{
		printf("Erro ao carregar o arquivo para memoria\n");
		goto error_number_list;
	}

	printf("Valor maximo de iteracoes: %F\n", log2(end_of_file));
	printf("resposta final: %i\n", binary_search(number_list, end_of_file, guess));

	fclose(number_file);
	free(number_list);

	return 0;

	error:
		fclose(number_file);
		return 1;

	error_number_list:
		free(number_list);
		fclose(number_file);
		return 1;

}
