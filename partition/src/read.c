#include "read.h"

struct bornes* append(struct bornes *head, int t, int b)
{
	struct bornes *n = malloc(sizeof(struct bornes));
	n->t = t;
	n->b = b;
	n->next = NULL;
	if (head == NULL)
		return n;
	struct bornes *p = head;
	while (p->next != NULL)
		p = p->next;
	p->next = n;
	return head;
}

int main(int argc, char **argv)
{
	int width, height, nrChannels;
    unsigned char *data = stbi_load(argv[1], &width, &height, &nrChannels, 0);
	unsigned char *img = data;

	struct bornes *head = NULL;

	printf ("%d %d %d\n", width, height, nrChannels);

	if (nrChannels == 2 || nrChannels == 4)
		return -1;

	if (nrChannels == 3)
	{
		img = malloc(width*height);
		for (int i = 0; i < height; i++)
	        for (int j = 0; j < width; j++)
				img[width*i+j] = 255 * ((data[width*i*3 + j*3] * 333/1000 + data[width*i*3 + j*3 + 1] * 333/1000 + data[width*i*3 + j*3 + 2] * 333/1000) > 127.5);
	}
	
	else if (nrChannels == 1)
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				img[width*i+j] = 255 * (img[width*i+j] > 127.5);
	}
	
	int n = 0;
	int l = 255;
	int t = 0;
	int b = 0;
	for (int i = 0; i < height; i++)
	{
		int sum = 0;
		for (int j = 0; j < width; j++)
			if (img[width*i+j] == 0)
				sum += 1;
		if (sum *2 > width)
		{
			if (l == 255)
			{
				if (n == 0)
				{
					b = i;
					head = append(head, t,b);
				}
			}
			
			l = 0;
		}
		else
		{
			if (l == 0)
			{
				n += 1;
				if (n == 5)
				{
					t = i + (i - b)/1.5;
					n = 0;
				}
			}
			l = 255;
		}
	}
	head = append(head, t,height);
	
	for (int i = 0; i < height; i++)
		for (struct bornes *p = head; p != NULL; p = p->next)
			if (p->t < i && p->b > i)
				for (int j = 0; j < width; j++)	
					img[width*i+j] = 255;


	stbi_write_png("out.png", width, height, 1, img, width);
}
