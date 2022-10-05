#include <alsa/asoundlib.h>
#include <math.h>

float PI = 3.14159265359;
int SAMPLE_RATE = 44100;

int *generate_buff(double *sample, size_t sample_size, int t, int freq)
{
	int period = SAMPLE_RATE / freq;
	int ratio = sample_size / period;
	int *to_ret = malloc(sizeof(int) * t*SAMPLE_RATE/1000);
	for (int i = 0; i < t*SAMPLE_RATE/1000; i++)
		to_ret[i] = sample[(i*ratio)%sample_size] * 99999;
	return to_ret;
}


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
    return size_sample+1;
}


int *to_int(double *array, int size)
{
	int *ret = malloc(sizeof(int)*size);
	for (int i = 0; i < size; i++)
		ret[i] = (int)(array[i]*100000);
	return ret;
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
	

	double *sample = NULL;
    int sample_size = load_float_csv(argv[1], &sample, ' ');
	
	int *to_send = generate_buff(sample, sample_size, 1000, 55);
	snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
	free(to_send);
	to_send = generate_buff(sample, sample_size, 1000, 110);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, 1000, 220);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
    free(to_send);
	to_send = generate_buff(sample, sample_size, 1000, 440);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
/*	for (int i = 0; i < 203; i++)
        printf ("%d\n", to_send[i]);*/
    free(to_send);
	to_send = generate_buff(sample, sample_size, 1000, 880);
    snd_pcm_writei(pcm, to_send, SAMPLE_RATE);
	free(to_send);
	int *to_play = to_int(sample,sample_size);
	snd_pcm_writei(pcm, to_play, sample_size/3);
	snd_pcm_writei(pcm, to_play, sample_size/3);
	printf ("%d\n", sample_size);
	snd_pcm_drain(pcm);
	snd_pcm_close(pcm);
}
