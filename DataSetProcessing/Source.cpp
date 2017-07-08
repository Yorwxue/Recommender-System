#include"Header.h"

int DataSet[NumofData][NumofEntry];
int DataLength;
int NumofDataInClass[NumofClass];
double itemData[NumofItem][NumofTopic];
string itemInfo[NumofItem][NumofInfo];

void main()
{
	/**
	int item1No, item2No, cont = 1;
	ReadItem("item.txt", itemData);
	/**
	while (cont == 1)
	{
		cout << "item 1: ";
		cin >> item1No;
		cout << "item 2: ";
		cin >> item2No;
		cout << "item " << setw(3) << item1No << ": ";
		for (int i = 0; i < NumofTopic; i++)
		{
			cout << itemData[item1No][i] << ", ";
		}
		cout << endl << "item " << setw(3) << item2No << ": ";
		for (int i = 0; i < NumofTopic; i++)
		{
			cout << itemData[item2No][i] << ", ";
		}
		cout << endl;
		//system("pause");
		cout << "continue? (0/1)";
		cin >> cont;
	}/**/

	//-----¤À¹j½u-----
	Read("u.sort",0);
	/*Sorting*
	cout << "Sorting .. ";
	//quickSort(DataSet, 0, DataLength - 1, 0);
	/**
	int start_point = 0;
	for (int i = 0; i < NumofClass; i++)
	{
		quickSort(DataSet, start_point, start_point + NumofDataInClass[i] - 1, 2);
		start_point += NumofDataInClass[i];
	}
	/**
	cout << "OK" << endl;
	/**/
	/**
	cout << "data length : " << DataLength << endl;
	for (int i = 0; i < DataLength; i++)
	{
		for (int j = 0; j < NumofEntry; j++)
		{
			cout << DataSet[i][j] << "|";
		}
		cout << endl;
	}
	/**/

	//Write("train.txt", "test.txt");
	Write5("split_1.txt", "split_2.txt", "split_3.txt", "split_4.txt", "split_5.txt");
	//write_info_for_read("data_for_observed.txt");

	system("pause");
}