#include "gwave.h"

float PI = 3.14159265359;



short *generate_buff(short *sample, size_t sample_size, int t, int freq)
{
	float ratio = (float)sample_size*(float)freq / (float)SAMPLE_RATE;
	short *to_ret = malloc(sizeof(short) * t);
	for (int i = 0; i < t; i++)
		to_ret[i] =(int)((float)(sample[((int)(i*ratio))%sample_size])*(float)(t-i)/(float)t);
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

snd_pcm_t *init_audio(void)
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
	return pcm;
}
