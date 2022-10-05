#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

struct bornes{
	unsigned int t;
	unsigned int b;
	struct bornes *next;
};

struct linked_img{
	unsigned int height;
	struct linked_img *next;
	char *img;
};
