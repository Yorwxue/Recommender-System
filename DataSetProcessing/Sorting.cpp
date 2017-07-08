#include"Header.h"

/*由大到小排序*/
void quickSort(int arr[NumofData][NumofEntry], int left, int right, int CareNo)
{
	int i = left, j = right;
	int tmp[NumofEntry];

	int pivot = arr[(left + right) / 2][CareNo];
	//stringstream(arr[(left + right) / 2][CareNo]) >> pivot;

	/* partition */
	while (i <= j)
	{
		while (arr[i][CareNo] < pivot)
			i++;
		while (arr[j][CareNo] > pivot)
			j--;
		if (i <= j)
		{
			for (int k = 0; k < NumofEntry; k++)
			{
				tmp[k] = arr[i][k];
				arr[i][k] = arr[j][k];
				arr[j][k] = tmp[k];
			}
			i++;
			j--;
		}
	}

	/* recursion */
	if (left < j)
		quickSort(arr, left, j, CareNo);
	if (i < right)
		quickSort(arr, i, right, CareNo);
}

void quickSort(int arr[], int left, int right)
{
	int i = left, j = right;
	int tmp;
	double pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j)
		{
			tmp = arr[i];

			arr[i] = arr[j];

			arr[j] = tmp;

			i++;
			j--;
		}
	}

	/* recursion */
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}