#include <alsa/asoundlib.h>
#include <math.h>

float PI = 3.14159265359;
int SAMPLE_RATE = 44100;



short *generate_buff(short *sample, size_t sample_size, int t, int freq)
{
	float ratio = (float)sample_size*(float)freq / (float)SAMPLE_RATE;
	short *to_ret = malloc(sizeof(short) * t);
	for (int i = 0; i < t; i++)
	{
		to_ret[i] = sample[((int)(i*ratio))%sample_size];
//		printf ("%d\n", to_ret[i]);
	}
	return to_ret;
}

long gen_square(short **array)
{
	*array = malloc(360);
	for (int i = 0; i < 180; i++)
		(*array)[i] = 10000;
	for (int i = 180; i<360;i++)
		(*array)[i] = -10000; 
	return 360;
}

long load_raw(char *path, short **array)
{
	FILE *fptr = fopen(path, "r");
	if (fptr == NULL)
		return -1;
	fseek(fptr, 0, SEEK_END);
    long fsize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    *array = calloc(fsize, sizeof(short));
    fread(*array, fsize, 1, fptr);
	fclose(fptr);
	return fsize/2;
}

int main(int argc, char **argv)
{
	snd_pcm_t *pcm;
	snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0);
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_hw_params_alloca(&hw_params);

	snd_pcm_hw_params_any(pcm, hw_params);
	snd_pcm_hw_params_set_access(pcm, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format(pcm, hw_params, SND_PCM_FORMAT_S16_LE);
	snd_pcm_hw_params_set_channels(pcm, hw_params, 1);
	snd_pcm_hw_params_set_rate(pcm, hw_params, SAMPLE_RATE, 0);
	snd_pcm_hw_params_set_periods(pcm, hw_params, 10, 0);
	snd_pcm_hw_params_set_period_time(pcm, hw_params, 100000, 0); // 0.1 seconds

	snd_pcm_hw_params(pcm, hw_params);
	

	short *sample = NULL;
    long sample_size = load_raw(argv[1], &sample);
	//snd_pcm_writei(pcm, sample, sample_size);
	short *to_send = generate_buff(sample, sample_size, SAMPLE_RATE,131);
	snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
	free(to_send);
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 139);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);	
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 147);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 156);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 165);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 175);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 185);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 196);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
    to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 207);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 220);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 233);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 247);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, SAMPLE_RATE, 262);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	
//	snd_pcm_writei(pcm, sample, sample_size);

	snd_pcm_drain(pcm);
	snd_pcm_close(pcm);
}
