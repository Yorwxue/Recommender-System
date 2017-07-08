#include"Header.h"

float norm(float vec[],int length)
{
	float norm = 0;
	for (int i = 0; i < length; i++)
	{
		norm += pow(vec[i],2);
	}
	norm = sqrt(norm);
	return norm;
}

void multi(float c, float a[], int length)
{
	for (int i = 0; i < length; i++)
	{
		//cout << a[i]<<", ";
		a[i] = a[i] * c;
		//cout << a[i] << endl;
	}
}

void Add(float c[], float a[], float b[], int length, float parameter)
{
	for (int i = 0; i < length; i++)
	{
		c[i] = parameter*a[i] + (1 - parameter)*b[i];
	}
}

//c = ab
//dimension
//c : m*1
//a : m*m
//b : m*1
void Multi(float c[NumofItem], float a[NumofItem][NumofItem], float b[NumofItem])
{
	for (int i = 0; i < NumofItem; i++)
	{
		c[i] = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			//cout << a[i][j] << ", " << b[j] << endl;
			c[i] += a[i][j] * b[j];
		}
		//cout << c[i] << endl;
	}
}

void Multi(float* c, float** a, float* b, int length)
{
	for (int i = 0; i < length; i++)
	{
		c[i] = 0;
		for (int j = 0; j < length; j++)
		{
			//cout << a[i][j] << ", " << b[j] << endl;
			c[i] += a[i][j] * b[j];
		}
		//cout << c[i] << endl;
	}
}

void MatrixMulti(float c[NumofItem][NumofItem], float a[NumofItem][NumofItem], float b[NumofItem][NumofItem])
{
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < NumofItem; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void array_initial(int A[], int length, float value)
{
	for (int i = 0; i < length; i++)
	{
		A[i] = value;
	}
}

void array_initial(float A[], int length, float value)
{
	for (int i = 0; i < length; i++)
	{
		A[i] = value;
	}
}

/**
void selfMulti(float b[NumofItem][NumofItem], float a[NumofItem][NumofItem], int times)
{
	if (times > 0)
	{
		for (int t = 0; t < times; t++)
		{
			if (t == 0)
			{
				for (int i = 0; i < NumofItem; i++)
				{
					for (int j = 0; j < NumofItem; j++)
					{
						b[i][j] = a[i][j];
					}
				}
			}
			else
			{
				for (int i = 0; i < NumofItem; i++)
				{
					for (int j = 0; j < NumofItem; j++)
					{
						for (int k = 0; k < NumofItem; k++)
						{
							b[i][j] += b[i][k] * a[k][j];
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < NumofItem; i++)
		{
			for (int j = 0; j < NumofItem; j++)
			{
				b[i][j] = 1;
			}
		}
	}
}
/**/
/**
//*1
void TopicMulti(float c[], float a[][NumofTopic], float b[])
{
	for (int i = 0; i < NumofTopic; i++)
	{
		c[i] = 0;
		for (int j = 0; j < NumofTopic; j++)
		{
			//cout << a[i][j] << ", " << b[j] << endl;
			c[i] += a[i][j] * b[j];
		}
		//cout << c[i] << endl;
	}
}/**/