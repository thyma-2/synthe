#include "read.h"

int width, height, nrChannels;


struct bornes* append_b(struct bornes *head, int t, int b)
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

struct linked_img *find_last(struct linked_img *head)
{
	while (head->next != NULL)
		head = head->next;
	return head;
}

struct linked_img* append_i(struct linked_img *head, int h)
{
	struct linked_img *n = malloc(sizeof(struct linked_img));
	n->height = h;
	n->img = malloc(h*width);	
	n->next = NULL;
	if (head == NULL)
		return n;
	struct linked_img *p= head;
	while (p->next != NULL)
		p = p->next;
	p->next = n;
	return head;
}

int main(int argc, char **argv)
{
    unsigned char *data = stbi_load(argv[1], &width, &height, &nrChannels, 0);
	unsigned char *binary_img = data;

	struct bornes *head_b = NULL;
	struct linked_img *head_i = NULL;

	printf ("%d %d %d\n", width, height, nrChannels);

	if (nrChannels == 2 || nrChannels == 4)
		return -1;

	if (nrChannels == 3)
	{
		binary_img = malloc(width*height);
		for (unsigned int i = 0; i < height; i++)
	        for (unsigned int j = 0; j < width; j++)
				binary_img[width*i+j] = 255 * ((data[width*i*3 + j*3] * 333/1000 + data[width*i*3 + j*3 + 1] * 333/1000 + data[width*i*3 + j*3 + 2] * 333/1000) > 127.5);
	}
	
	else if (nrChannels == 1)
	{
		for (unsigned int i = 0; i < height; i++)
			for (unsigned int j = 0; j < width; j++)
				binary_img[width*i+j] = 255 * (binary_img[width*i+j] > 127.5);
	}
	
	int n = 0;
	int l = 255;
	int t = 0;
	int b = 0;
	int e = 0;
	for (unsigned int i = 0; i < height; i++)
	{
		int sum = 0;
		for (unsigned int j = 0; j < width; j++)
			if (binary_img[width*i+j] == 0)
				sum += 1;
		if (sum *2 > width)
		{
			if (l == 255)
			{
				if (n == 0)
					t = i;
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
					b = i;
					e = b-t;		
					n = 0;
					head_b = append_b(head_b, t-e/2,b+e/1.4);
				}
			}
			l = 255;
		}
	}
	
	for (struct bornes *p = head_b; p != NULL; p = p->next)
	{
		head_i = append_i(head_i, p->b-p->t);
		struct linked_img *current = find_last(head_i);
		for (int i = p->t; i < p->b; i++)
			for (int j = 0; j < width; j++)
				current->img[(i-p->t)*width+j] = binary_img[width*i+j];

	}
	
	free(binary_img);
	char x = 'a';
	char path_out[] = "outx.png";
	for (struct linked_img *p = head_i; p != NULL; p = p->next)
	{
		path_out[3] = x;
		x += 1;
		stbi_write_png(path_out, width, p->height, 1, p->img, width);
	}

}
