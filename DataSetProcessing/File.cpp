#include"Header.h"

extern double itemData[NumofItem][NumofTopic];
extern int DataSet[NumofData][NumofEntry];
extern int DataLength;
extern int NumofDataInClass[NumofClass];
extern string itemInfo[NumofItem][NumofInfo];

double ChoosedRatio = 0.9;   //for train

//CareNo是計數依據
void Read(string fileName, int CareNo)
{
	int NowDataProcessing = -1;
	int counter;

	DataLength = 0;

	char FileInput[500];
	fstream fr;
	string InputProcess;

	/*Feature Data*/
	int FeatureID = 1;
	cout << "Data Reading .. ";
	fr.open(fileName, ios::in);
	if (!fr)        //如果開啟檔案失敗，fin為0；成功，fin為1
		cout << "Fail to open file" << endl;
	else
	{
		int i = 0;
		counter = 0;
		while (fr.getline(FileInput, sizeof(FileInput)))
		{
			InputProcess = FileInput;
			istringstream ss(InputProcess);
			string token;
			int j = 0;
			while (std::getline(ss, token, '|'))
			{
				stringstream(token) >> DataSet[i][j++];
			}
			/**/
			if (NowDataProcessing != DataSet[i][CareNo])
			{
				if (NowDataProcessing != -1)
				{
					NumofDataInClass[NowDataProcessing - 1] = counter;
				}
				NowDataProcessing = DataSet[i][CareNo];
				counter = 0;
			}
			counter++;
			/**/
			i++;
		}
		NumofDataInClass[NowDataProcessing - 1] = counter;
		DataLength = i;
	}
	fr.close();
	cout << "OK" << endl;
}

void Write(string fileName, string fileName2)
{
	cout << "Data Writing .. ";

	int No = 0;

	fstream fw, fw2;
	fw.open(fileName, ios::out);//開啟檔案
	fw2.open(fileName2, ios::out);

	int NumofTrain = 0, NumofTest = 0;

	/*Chance 1 -選擇要寫入file 1的data*/
	int StartPoint = 0;//寫入資料的每個class的起點
	int EndPoint = 0;
	while (No < NumofClass)
	{
		int  Places;
		if ((NumofDataInClass[No] * ChoosedRatio) - (int)(NumofDataInClass[No] * ChoosedRatio) >= 0.5)
		{
			Places = (int)(NumofDataInClass[No] * ChoosedRatio) + 1;
		}
		else
		{
			Places = (int)(NumofDataInClass[No] * ChoosedRatio);
		}
		//
		int* DataInClass = new int[Places];
		int PlacesProcessing = 0;

		while (PlacesProcessing < Places)
		{
			int checkRepeat, checkProcessing = 0;
			checkRepeat = RandomNumber(0, NumofDataInClass[No] - 1);

			/*確認是否重複*/
			while (checkProcessing < PlacesProcessing)
			{
				if (checkRepeat == DataInClass[checkProcessing])
				{
					checkRepeat = RandomNumber(0, NumofDataInClass[No] - 1);
					checkProcessing = -1;
				}
				checkProcessing++;
			}/**/
			DataInClass[PlacesProcessing] = checkRepeat;
			PlacesProcessing++;
		}
		quickSort(DataInClass, 0, Places - 1);
		/**
		if (No == NumofClass - 1)
		{
		cout << Places << "/";
		cout << NumofDataInClass[No] << endl;
		cout << DataInClass[Places - 5] << endl;
		cout << DataInClass[Places - 4] << endl;
		cout << DataInClass[Places - 3] << endl;
		cout << DataInClass[Places - 2] << endl;
		cout << DataInClass[Places - 1] << endl;
		}
		/*開始寫入資料*/

		/*for (PlacesProcessing = 0; PlacesProcessing < Places; PlacesProcessing++)
		{
			for (int j = 0; j < NumofEntry; j++)
			{
				fw << DataSet[StartPoint + DataInClass[PlacesProcessing]][j];
				if (j < NumofEntry - 1)
				{
					fw << ",";
				}
			}
			fw << endl;
		}
		/**/
		EndPoint = NumofDataInClass[No];//實際個數
		PlacesProcessing = 0;

		for (int i = 0; i < EndPoint; i++)
		{
			if (i == DataInClass[PlacesProcessing])
			{
				PlacesProcessing++;
				NumofTrain++;
				for (int j = 0; j < NumofEntry; j++)
				{
					fw << DataSet[StartPoint + i][j];
					if (j < NumofEntry - 1)
					{
						fw << ",";
					}
				}
				fw << endl;
			}
			else
			{
				NumofTest++;
				for (int j = 0; j < NumofEntry; j++)
				{
					fw2 << DataSet[StartPoint + i][j];
					if (j < NumofEntry - 1)
					{
						fw2 << ",";
					}
				}
				fw2 << endl;
			}
		}
		StartPoint += NumofDataInClass[No];

		No++;
		delete DataInClass;
	}
	/**
	int test = 99998;
	while (test < NumofData)
	{
	for (int j = 0; j < NumofEntry; j++)
	{
	cout << DataSet[test][j];
	if (j < NumofEntry - 1)
	{
	cout << "|";
	}
	}
	test++;
	cout << endl;
	}/**/
	/*Chance 2*
	for (int i = 0; i < DataLength; i++)
	{
	for (int j = 0; j < NumofEntry; j++)
	{
	fw << DataSet[i][j];
	if (j<NumofEntry - 1)
	{
	fw << "|";
	}
	}

	fw << endl;
	}
	/**/

	fw.close();
	fw2.close();
	cout << "train/test=" << NumofTrain << "/" << NumofTest << " .. ";
	cout << "OK" << endl;
}

void write_info_for_read(string fileName)
{
	cout << "Data Writing .. ";

	int No = 0;

	fstream fw;
	fw.open(fileName, ios::out);//開啟檔案
	
	for (int i = 0; i < DataLength; i++)
	{
		for (int j = 0; j < NumofEntry; j++)
		{
			if (j == 0)
			{
				fw << setw(3) << DataSet[i][j];
				//cout << setw(3) << DataSet[i][j];
			}
			else if (j == 1)
			{
				fw << setw(4) << DataSet[i][j];
				//cout << setw(4) << DataSet[i][j];
			}
			else
			{
				fw << DataSet[i][j];
				//cout << DataSet[i][j];
			}
			fw << ", ";
			//cout << ", ";
		}
		for (int k = 2; k < NumofInfo-1; k++)
		{
			fw << itemInfo[DataSet[i][1]][k] << ", ";
		}
		for (int k = 0; k < NumofTopic; k++)
		{
			fw << itemData[DataSet[i][1]][k] << ", ";
		}
		fw << endl;
	}
	/**/

	fw.close();
	cout << "OK" << endl;
}

/*replace(string, "A", "B")*/
//Replace all of A in the string with B 
void ReplaceAll(string& str, const string& from, const string& to)
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}




void ReadItem(string fileName, double itemData[NumofItem][NumofTopic])
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
				if (j <= 3)
				{
					//stringstream(token) >> itemInfo[No][j++];
					itemInfo[No][j++] = token;
				}
				else if (j++ > 3)
				{
					stringstream(token) >> itemData[No][j - 5];
					/**
					if (No<10)
						cout << itemData[No][j - 5] << ", ";
					if (itemData[No][j - 5] != 0 && itemData[No][j - 5] != 1)
					{
						cout << endl << No + 1 << ":" << j - 5 << ", " << itemData[No][j - 5] << endl;
						system("pause");
					}/**/
				}
			}
			/**
			if (No<10)
				cout << endl;/**/
			No++;
		}
		//system("pause");
	}
	fr.close();
}


void Write5(string fileName, string fileName2, string fileName3, string fileName4, string fileName5)
{
	cout << "Data Writing .. ";

	int No = 0;

	fstream fw, fw2, fw3, fw4, fw5;
	fw.open(fileName, ios::out);//開啟檔案
	fw2.open(fileName2, ios::out);
	fw3.open(fileName3, ios::out);
	fw4.open(fileName4, ios::out);
	fw5.open(fileName5, ios::out);
	int NumofTrain = 0, NumofTest = 0;

	
		/*開始寫入資料*/
	int Numofsplit[5];
	Numofsplit[0] = 0;
	Numofsplit[1] = 0;
	Numofsplit[2] = 0;
	Numofsplit[3] = 0;
	Numofsplit[4] = 0;

	for (int i = 0; i < NumofData; i++)
	{
		switch (i % 5){

		case 0:
			Numofsplit[0]++;
			for (int j = 0; j < NumofEntry; j++)
			{
				fw << DataSet[i][j];
				if (j < NumofEntry - 1)
				{
					fw << ",";
				}
			}
			fw << endl;
			break;

		case 1:
			Numofsplit[1]++;
			for (int j = 0; j < NumofEntry; j++)
			{
				fw2 << DataSet[i][j];
				if (j < NumofEntry - 1)
				{
					fw2 << ",";
				}
			}
			fw2 << endl;
			break;
		case 2:
			Numofsplit[2]++;
			for (int j = 0; j < NumofEntry; j++)
			{
				fw3 << DataSet[i][j];
				if (j < NumofEntry - 1)
				{
					fw3 << ",";
				}
			}
			fw3 << endl;
			break;
		case 3:
			Numofsplit[3]++;
			for (int j = 0; j < NumofEntry; j++)
			{
				fw4 << DataSet[i][j];
				if (j < NumofEntry - 1)
				{
					fw4 << ",";
				}
			}
			fw4 << endl;
			break;
		case 4:
			Numofsplit[4]++;
			for (int j = 0; j < NumofEntry; j++)
			{
				fw5 << DataSet[i][j];
				if (j < NumofEntry - 1)
				{
					fw5 << ",";
				}
			}
			fw5 << endl;
			break;
		default:
			cout << "error" << endl;
			system("pause");
		}
	}
		/**/

	fw.close();
	fw2.close();
	fw3.close();
	fw4.close();
	fw5.close();
	for (int i = 1; i <= 5; i++)
	{
		cout << "split " << i << "=" << Numofsplit[i - 1] << endl;
	}
	cout << "OK" << endl;
}