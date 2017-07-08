#include"Header.h"
/*由大到小排序*/
void quickSort(double arr[], int append[], int append2[], int left, int right)
{
	int i = left, j = right;
	double tmp;
	int tmpAppend, tmpAppend2;
	double pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j)
	{
		while (arr[i] > pivot)
			i++;
		while (arr[j] < pivot)
			j--;
		if (i <= j)
		{
			tmp = arr[i];
			tmpAppend = append[i];
			tmpAppend2 = append2[i];

			arr[i] = arr[j];
			append[i] = append[j];
			append2[i] = append2[j];

			arr[j] = tmp;
			append[j] = tmpAppend;
			append2[j] = tmpAppend2;
			i++;
			j--;
		}
	}

	/* recursion */
	if (left < j)
		quickSort(arr, append, append2, left, j);
	if (i < right)
		quickSort(arr, append, append2, i, right);
}