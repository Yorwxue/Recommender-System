#include "Header.h"

void Read(string fileName, float data[NumofUser][NumofItem])
{
	char FileInput[500];
	fstream fr;
	string InputProcess;
	int tuple[4];

	//cout << "Data Reading .. ";
	fr.open(fileName, ios::in);
	if (!fr)        //如果開啟檔案失敗，fin為0；成功，fin為1
		cout << "Fail to open file : " << fileName << endl;
	else
	{
		while (fr.getline(FileInput, sizeof(FileInput)))
		{
			int j = 0;
			InputProcess = FileInput;
			istringstream ss(InputProcess);
			string token;
			while (std::getline(ss, token, ','))
			{
				stringstream(token) >> tuple[j++];
			}
			data[tuple[0] - 1][tuple[1] - 1] = tuple[2];   //array從0開始，物品編號從1開始
		}
	}
	fr.close();

	/*觀看資料正確性*
	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			cout << data[i][j] << ", ";
		}
		cout << endl;
	}
	system("pause");/**/
	//cout << "OK" << endl;
}

/**
//*1
void ReadItem(string fileName, float itemData[NumofItem][NumofTopic])
{
	char FileInput[500];
	fstream fr;
	string InputProcess;
	int No = 0;

	//cout << "Data Reading .. ";
	fr.open(fileName, ios::in);
	if (!fr)        //如果開啟檔案失敗，fin為0；成功，fin為1
		cout << "Fail to open file : " << fileName << endl;
	else
	{
		while (fr.getline(FileInput, sizeof(FileInput)))
		{
			int j = 0;
			InputProcess = FileInput;
			istringstream ss(InputProcess);
			string token;
			while (std::getline(ss, token, '|'))
			{
				if (j++ > 3)
				{
					stringstream(token) >> itemData[No][j - 5];
					/**
					if (No<10)
					cout << itemData[No][j - 5] << ", ";
					if (itemData[No][j - 5] != 0 && itemData[No][j - 5] != 1)
					{
						cout << endl << No + 1 << ":" << j - 5 << ", " << itemData[No][j - 5] << endl;
						system("pause");
					}/**
				}
			}
			/**
			if (No<10)
				cout << endl;/**
			No++;
		}
		//system("pause");
	}
	fr.close();
}/**/
