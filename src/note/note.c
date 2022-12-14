#include "note.h"
#include "../gwave/gwave.h"

struct note notes[256] = {0};

void init_notes(char *path)
{
	printf ("%d\n", SAMPLE_RATE);
	FILE *fp = fopen(path, "r");
	
	if (fp == NULL)
	{
		printf ("the file %s do not exist\n", path);
		exit(0);
	}
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
	char key;
	char path_note[100];
	int freq;
	int size;
	while ((read = getline(&line, &len, fp)) != -1)
	{
		sscanf(line, "%c %s %d %d\n", &key, path_note, &size, &freq);
		short *sample = NULL;
		long sample_size = load_raw(path_note, &sample);
		notes[(int)key].note = generate_buff(sample, sample_size, SAMPLE_RATE*size, freq);
		notes[(int)key].freq =  freq;
		notes[(int)key].size = size;
		free(sample);
	}

	
	
}
