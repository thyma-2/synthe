#include "partition.h"

int t;
int partition[10000][50];

void *play_partition(void *varpg)
{
	clock_t start, end;
	
    start = clock();
	char to_print[51];
	
    // Insérez ici le code que vous voulez mesurer
	for (unsigned int j = 0; j >= 0; j++)
	{
		if (j % 100000000 == 0)
		{
		end = clock();
		int from =(int)(((double)(end - start)) / CLOCKS_PER_SEC * 1000/t);
		to_print[50] = 0;
		printf("\033[H\033[J");
		for (int i = 0; i < 49; i++)
			to_print[i] = partition[i+from][0];
		printf ("%s\n", to_print);
		for (int i = 0; i < 49; i++)
            to_print[i] = partition[i+from][1];
        printf ("%s\n", to_print);
		for (int i = 0; i < 49; i++)
            to_print[i] = partition[i+from][2];
        printf ("%s\n", to_print);
		for (int i = 0; i < 49; i++)
            to_print[i] = partition[i+from][3];
        printf ("%s\n", to_print);
		for (int i = 0; i < 49; i++)
            to_print[i] = partition[i+from][4];
        printf ("%s\n", to_print);
		for (int i = 0; i < 49; i++)
            to_print[i] = partition[i+from][5];
        printf ("%s\n", to_print);
		for (int i = 0; i < 49; i++)
            to_print[i] = partition[i+from][6];
        printf ("%s\n", to_print);
		for (int i = 0; i < 49; i++)
            to_print[i] = partition[i+from][7];
        printf ("%s\n", to_print);
		for (int i = 0; i < 49; i++)
            to_print[i] = partition[i+from][8];
        printf ("%s\n", to_print);
		 for (int i = 0; i < 49; i++)
            to_print[i] = partition[i+from][9];
        printf ("%s\n", to_print);
		printf ("---------------------------------\n");
		}
			
	}

	return NULL;
	
}

char find_key(char *path, int freq, int size)
{
	for (int i = 0; i < 256; i++)
		if (notes[(int)i].freq == freq && notes[(int)i].size == size && strcmp(notes[(int)i].path, path) == 0)
			return i;
	return -1;
}

void init_partition(char *path)
{
    FILE *fp = fopen(path, "r");
	for (int w = 0; w < 1000; w++)
		for (int x = 0; x < 50; x++)
			partition[w][x] = ' ';
    if (fp == NULL)
    {
        printf ("the file %s do not exist\n", path);
        exit(0);
    }
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char path_note[100];
    int freq;
    int size;
	int i = 0;
	int j = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
		if (line[0] == ',')
		{
			int k = 0;
			j = 0;
			while(line[k] == ',')
			{
				k++;
				i++;
			}
		}
		else
		{
        	sscanf(line, "%s %d %d\n", path_note, &size, &freq);
			char key = find_key(path_note, freq,size);
			if (key == -1)
			{
				printf ("the note %s %d %d is not configured by a key", path_note, freq, size);
				exit(2);
			}
			else
			{
				partition[i][j] = key;
				j += 1;
			}
		}
    }
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, play_partition, NULL);
}

