#include"Header.h"

/*動態產生2為array*/
//ex : int** Array = (int**)new2d(Height, Width, sizeof(int));
void* new2d(int h, int w, int size)
{
	register int i;
	void **p;

	p = (void**)new char[h*sizeof(void*) + h*w*size];
	for (i = 0; i < h; i++)
	{
		p[i] = ((char *)(p + h)) + i*w*size;
	}

	return p;
}