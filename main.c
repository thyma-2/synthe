#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "src/gwave/gwave.h"

int main(int argc, char **argv)
{
	//make the keyboard non-blocking
	struct termios oldTerminalConf, newTerminalConf;
	tcgetattr(STDIN_FILENO,&oldTerminalConf);
	newTerminalConf = oldTerminalConf;
	newTerminalConf.c_lflag &=(~ICANON & ~ECHO);
 	tcsetattr(STDIN_FILENO,TCSANOW,&newTerminalConf);
	short *sample = NULL;
	//short empty_sample[SAMPLE_RATE] = {0};
    long sample_size = load_raw(argv[1], &sample);
	short *to_send;
	unsigned long long int i = 0;
	snd_pcm_t *array_pcm[60];
	array_pcm[0] = init_audio();
    while (1)
    {
		array_pcm[(i+1)%60] = init_audio();
		if (i > 50)
			snd_pcm_close(array_pcm[(i+10)%60]);
        unsigned char keyEntered = getchar();
		if (keyEntered == 'w')
			to_send = generate_buff(sample, sample_size, SAMPLE_RATE,131);
		else if (keyEntered == 'x')
			to_send = generate_buff(sample, sample_size, SAMPLE_RATE,147);
		else if (keyEntered == 'c')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,165);
		else if (keyEntered == 'v')
			to_send = generate_buff(sample, sample_size, SAMPLE_RATE,175);
		else if (keyEntered == 'b')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,196);
		else if (keyEntered == 'n')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,220);
		else if (keyEntered == ',')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,246);
		else if (keyEntered == 'a')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,262);
        else if (keyEntered == 'z')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,294);
        else if (keyEntered == 'e')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,330);
        else if (keyEntered == 'r')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,349);
        else if (keyEntered == 't')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,392);
        else if (keyEntered == 'y')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,440);
        else if (keyEntered == 'u')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,493);
		else if (keyEntered == 'q')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,139);
        else if (keyEntered == 's')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,156);
        else if (keyEntered == 'f')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,185);
        else if (keyEntered == 'g')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,208);
        else if (keyEntered == 'h')
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,233);
		/*
        else if (keyEntered == 33)
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,262);
        else if (keyEntered == 34)
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,294);
        else if (keyEntered == 35)
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,330);
        else if (keyEntered == 36)
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,349);
        else if (keyEntered == 37)
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,392);
        else if (keyEntered == 38)
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,440);
        else if (keyEntered == 39)
            to_send = generate_buff(sample, sample_size, SAMPLE_RATE,493);*/

        snd_pcm_writei(array_pcm[i%60], to_send, SAMPLE_RATE);
        free(to_send);
		i += 1;
		
    }

    /* restore the former settings */
	tcsetattr(STDIN_FILENO,TCSANOW,&oldTerminalConf);

    return 0;
  }
