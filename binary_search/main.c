#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

long file_length_seeker(FILE *stream)
{
	if(fseek(stream, 0, SEEK_END) == -1)
	{
		goto error;
	}

	long end_of_file = ftell(stream);
	
	if((end_of_file < 0))
	{
		goto error;
	}

	if(fseek(stream, 0, SEEK_SET) == -1)
	{
		goto error;
	}
	
	return end_of_file;

	error:
		return -1;
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

int binary_search(FILE *A, int n, int T)
{
	int l = 0;
	int r = n-1; 
	
	float loops = 0;

	loops++;
	fseek(A, 0, SEEK_END);
	if(T == ftell(A))
	{
		printf("quantidade de iteracoes: %2.f\n", loops);
		return T;
	}

	while(l <= r)
	{
		long m = l+((r-l)/2); 	
		printf("%ld\n", m);
		fseek(A, m, SEEK_SET);
		int aux = ftell(A);
		loops++;

		if(aux < T)
		{
			l = m+1;
		}
		else if(aux > T)
		{
			r = m-1;
		}
		else
		{
			printf("quantidade de iteracoes: %2.f\n", loops);
			return m;
		}
	}
	
	printf("Numero nao esta na lista\n");
	return -1;

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
	printf("Guess: %i\n", guess);

	FILE* number_list = fopen("numeros.txt", "r");
	if(number_list == NULL)
	{
		printf("erro ao abrir o arquivo\n %d\n", errno);
		goto error;
	}
	
	long end_of_file = file_length_seeker(number_list);
	if(end_of_file == -1)
	{
		printf("%ld\n", end_of_file);
		goto error;
	}

	printf("%ld\n", end_of_file);

	printf("Valor maximo de iteracoes: %F\n", log2(end_of_file));

	printf("resposta final: %i\n", binary_search(number_list, end_of_file, guess));

	fclose(number_list);
	return 0;

	error:
		fclose(number_list);
		return 1;
}
