#include <alsa/asoundlib.h>
#include <math.h>

#define SAMPLE_RATE 44100

short *generate_buff(short *sample, size_t sample_size, int t, int freq);
long load_raw(char *path, short **array);
snd_pcm_t *init_audio(void);

