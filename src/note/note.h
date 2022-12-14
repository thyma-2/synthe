#include <stdlib.h>
#include <stdio.h>

struct note
{
	short *note;
	int freq;
	int size;
};

extern struct note notes[256];
void init_notes(char *path);
