#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

int load_float_csv(char *path, double **array, char del)
{
	int size_sample = 0;
    FILE *fptr = fopen(path,"r");
	if (fptr == NULL)
		return -1;
    fseek(fptr, 0, SEEK_END);
    long fsize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, fptr);
    fclose(fptr);
    string[fsize] = 0;

    for (int i = 0; string[i] != 0; i++)
        if (string[i] == del)
            size_sample += 1;
    *array = malloc(sizeof(double) * size_sample + 1);
    int i = 0;
    int n = 0;
    while (n < size_sample)
    {
        (*array)[n] = atof(&string[i]);
        n += 1;
        while (string[i] != del)
            i += 1;
        i+=1;
    }
    (*array)[n] = atof(&string[i]);
    free(string);
	return size_sample;
}

int main(int argc, char **argv)
{
	double *sample = NULL;
	int size_sample = load_float_csv(argv[1], &sample, ' ');
	if (size_sample == -1)
	{
		printf ("failed to load file\n");
		return -1;
	}

	int freq = 440;
	int micro_period = 1000000/freq;
	int ratio = size_sample * freq;

	struct timeval start, stop; 
	gettimeofday(&start, NULL); 
	long long start_micro = 1000000 * start.tv_sec + start.tv_usec;
	long long t = 0;
	
	while (t < 100000)
	{
		gettimeofday(&stop, NULL);
	    t = 1000000 * stop.tv_sec + stop.tv_usec - start_micro;
		//printf ("%f %d\n",(float)t/1000000, (int)(sample[(t%micro_period)*ratio/1000000]*9999));
		putchar(sample[(t%micro_period)*ratio/1000000]*9999);
	}

/*
	for (int j = 0; j <  size_sample; j++)
		//putchar(9999 * (j  % 72 > 36));
		putchar((int)(sample[j%size_sample]));
	for (int j = 0; j < 100 * size_sample; j++)
		putchar(0);
	for (int j = 0; j < 100 * size_sample; j++)
        putchar(9999 * cos(j/400));*/
	return 0;
}

