#include"Header.h"

void quickSort(float arr[], float append[], int append2[], int left, int right);

//這會破壞原本data中的順序，故僅供觀察，測效能時須註解掉
void show(float data[NumofUser][NumofItem], float IR[NumofUser][NumofItem])
{
	int user_no = 0;
	int item_no[NumofItem];
	for (int i = 0; i < NumofItem; i++)
	{
		item_no[i] = i + 1;
	}
	quickSort(IR[user_no], data[user_no], item_no, 0, NumofItem - 1);
	int flag = 0;
	for (int i = 0; i < NumofItem; i++)
	{
		cout << "item no. " << item_no[i] << ", IR: " << IR[user_no][i] << ", predict rating: " << data[user_no][i] << endl;

		if (++flag == 50)
		{
			flag = 0;
			system("pause");
		}
	}
}

/*由大到小排序*/
void quickSort(float arr[], float append[], int append2[], int left, int right)
{
	int i = left, j = right;
	float tmp;
	float tmpAppend;
	int tmpAppend2;
	float pivot = arr[(left + right) / 2];

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