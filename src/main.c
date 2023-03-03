#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "gwave/gwave.h"
#include "note/note.h"
#include "partition/partition.h"

int main(int argc, char **argv)
{
	//make the keyboard non-blocking
	struct termios oldTerminalConf, newTerminalConf;
	tcgetattr(STDIN_FILENO,&oldTerminalConf);
	newTerminalConf = oldTerminalConf;
	newTerminalConf.c_lflag &=(~ICANON & ~ECHO);
 	tcsetattr(STDIN_FILENO,TCSANOW,&newTerminalConf);
	unsigned long long int i = 0;
	snd_pcm_t *array_pcm[60];
	array_pcm[0] = init_audio();
	t = atoi(argv[3]);
	init_notes(argv[1]);
	init_partition(argv[2]);
    while (1)
    {
		array_pcm[(i+1)%60] = init_audio();
		if (i > 50)
			snd_pcm_close(array_pcm[(i+10)%60]);
        unsigned char keyEntered = getchar();
        snd_pcm_writei(array_pcm[i%60], notes[(int)keyEntered].note, notes[(int)keyEntered].size*SAMPLE_RATE*t/1000);
		i += 1;
		
    }

    /* restore the former settings */
	tcsetattr(STDIN_FILENO,TCSANOW,&oldTerminalConf);

    return 0;
  }
