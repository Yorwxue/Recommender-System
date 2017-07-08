#include"Header.h"
#include"ObjectClass.cpp"

/*Object List*/

//Start Pointer
UserClass * UserData;
ItemClass * ItemData;
TopicClass * TopicData;
/**/

void Read()
{
	char FileInput[500];
	fstream fr;
	string InputProcess;

	/*Topic Data*/
	int TopicID = 1;
	cout << "Topic Data .. ";
	fr.open("u.topic", ios::in);
	if (!fr)        //如果開啟檔案失敗，fin為0；成功，fin為1
		cout << "Fail to open file" << endl;
	else
	{
		while (fr.getline(FileInput, sizeof(FileInput), '|'))
		{
			TopicData = (TopicClass*)SearchTable(3, to_string(TopicID++), (string)FileInput);
			//cout << "Topic:" << TopicData->Name<< endl;
		}
	}
	fr.close();
	cout << "OK" << endl;
	//cout << endl;

	/*Item Data*/
#define NumofItemTopic 23
	string ItemDataInput[NumofItemTopic];
	cout << "Item Data .. ";
	fr.open("u.item", ios::in);
	if (!fr)        //如果開啟檔案失敗，fin為0；成功，fin為1
		cout << "Fail to open file" << endl;
	else
	{
		while (fr.getline(FileInput, sizeof(FileInput)))
		{
			InputProcess = FileInput;
			istringstream ss(InputProcess);
			string token;
			int i = 0;
			while (std::getline(ss, token, '|'))
			{
				ItemDataInput[i++] = token;
			}
			ItemData = (ItemClass*)SearchTable(2, ItemDataInput[0], ItemDataInput[1]);
			//cout << "Item:" << ItemData->Name<< endl;
			i = NumofItemTopic - 1;

			/***Test***
			while (i > 3)
			{
				if (i == 20)
				{
					if (ItemDataInput[i] == "1")
					{
						//Topic中新增Item
						TopicData = ((List<TopicClass>*)Inquiry(3, 0))->ObjectPointer;
						if (TopicData->ItemList == NULL)
						{
							TopicData->ItemList = new List<ItemClass>();
						}
						else
						{
							TopicData->ItemList->ListNoShift(TopicData->ItemList->Length)->InsertElement(new List<ItemClass>());
						}
						TopicData->ItemList->ListNoShift(TopicData->ItemList->Length)->ObjectPointer = ItemData;

						//Item中新增Topic
						if (ItemData->TopicList == NULL)
						{
							ItemData->TopicList = (List<TopicClass>*)Inquiry(3, 0);
							//cout << ItemData->TopicList->ObjectPointer->Name << endl;
						}
						else
						{
							ItemData->TopicList->ListNoShift(ItemData->TopicList->Length)->InsertElement((List<TopicClass>*)Inquiry(3, 0));
							//cout << ItemData->TopicList->ListNoShift(ItemData->TopicList->Length)->ObjectPointer->Name << endl;
						}
					}
					else
					{
						//Topic中新增Item
						TopicData = ((List<TopicClass>*)Inquiry(3, 1))->ObjectPointer;
						if (TopicData->ItemList == NULL)
						{
							TopicData->ItemList = new List<ItemClass>();
						}
						else
						{
							TopicData->ItemList->ListNoShift(TopicData->ItemList->Length)->InsertElement(new List<ItemClass>());
						}
						TopicData->ItemList->ListNoShift(TopicData->ItemList->Length)->ObjectPointer = ItemData;

						//Item中新增Topic
						if (ItemData->TopicList == NULL)
						{
							ItemData->TopicList = (List<TopicClass>*)Inquiry(3, 1);
							//cout << ItemData->TopicList->ObjectPointer->Name << endl;
						}
						else
						{
							ItemData->TopicList->ListNoShift(ItemData->TopicList->Length)->InsertElement((List<TopicClass>*)Inquiry(3, 1));
							//cout << ItemData->TopicList->ListNoShift(ItemData->TopicList->Length)->ObjectPointer->Name << endl;
						}
					}
				}
				i--;
			}
		
			/**/
			while (i > 3)
			{
				if (ItemDataInput[i] == "1")
				{
					//Topic中新增Item
					TopicData = ((List<TopicClass>*)Inquiry(3, i - 4))->ObjectPointer;
					if (TopicData->ItemList == NULL)
					{
						TopicData->ItemList = new List<ItemClass>();
					}
					else
					{
						TopicData->ItemList->ListNoShift(TopicData->ItemList->Length)->InsertElement(new List<ItemClass>());
					}
					TopicData->ItemList->ListNoShift(TopicData->ItemList->Length)->ObjectPointer = ItemData;

					//Item中新增Topic
					if (ItemData->TopicList == NULL)
					{
						ItemData->TopicList = (List<TopicClass>*)Inquiry(3, i - 4);
						//cout << ItemData->TopicList->ObjectPointer->Name << endl;
					}
					else
					{
						ItemData->TopicList->ListNoShift(ItemData->TopicList->Length)->InsertElement((List<TopicClass>*)Inquiry(3, i-4));
						//cout << ItemData->TopicList->ListNoShift(ItemData->TopicList->Length)->ObjectPointer->Name << endl;
					}
				}
				i--;
			}/**/
		}
	}
	fr.close();
	cout << "OK" << endl;
	//cout << endl;

	/*User Data*/
#define NumofUserTopic 4
	string UserDataInput[NumofUserTopic];
	cout << "User Data .. ";
	fr.open("u.train", ios::in);
	if (!fr)        //如果開啟檔案失敗，fin為0；成功，fin為1
		cout << "Fail to open file" << endl;
	else
	{
		while (fr.getline(FileInput, sizeof(FileInput)))
		{
			InputProcess = FileInput;
			istringstream ss(InputProcess);
			string token;
			int i = 0;
			while (std::getline(ss, token, '|'))
			{
				UserDataInput[i++] = token;
			}
			UserData = (UserClass*)SearchTable(1, UserDataInput[0], "ID:" + UserDataInput[0]);

			int Rating, ItemNo, RatingRecord;
			stringstream(UserDataInput[2]) >> Rating;
			RatingRecord = Rating;
			stringstream(UserDataInput[1]) >> ItemNo;

			//cout << UserData->Name << endl;
			if (UserData->ItemList == NULL)
			{
				//Item
				UserData->ItemList = (List<ItemClass>*)Inquiry(2, --ItemNo);//電腦的ItemNo從0開始
				//Rating
				UserData->ItemRating = new List<int>();
				UserData->ItemRating->ObjectPointer = new int();
				*(UserData->ItemRating->ObjectPointer) = RatingRecord;
				while (--Rating > 0)             //Rating視同購買次數
				{
					//Item
					UserData->ItemList->ListNoShift(UserData->ItemList->Length)->InsertElement(new List<ItemClass>());
					UserData->ItemList->ListNoShift(UserData->ItemList->Length)->ObjectPointer = UserData->ItemList->ObjectPointer;
					//Rating
					UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->InsertElement(new List<int>());
					UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer = new int();
					*(UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer) = RatingRecord;
				}	
				//UserData->Item2Topic = new List<TopicClass>();
				//cout << UserData->ItemList->ObjectPointer->Name << endl;
			}
			else
			{
				//Item
				UserData->ItemList->ListNoShift(UserData->ItemList->Length)->InsertElement((List<ItemClass>*)Inquiry(2, --ItemNo));
				//Rating
				UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->InsertElement(new List<int>());
				UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer = new int();
				*(UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer) = RatingRecord;
				while (--Rating > 0)             //Rating視同購買次數
				{
					//Item
					UserData->ItemList->ListNoShift(UserData->ItemList->Length)->InsertElement(new List<ItemClass>());
					UserData->ItemList->ListNoShift(UserData->ItemList->Length)->ObjectPointer = UserData->ItemList->ListNoShift((UserData->ItemList->Length) - 1)->ObjectPointer;
					//Rating
					UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->InsertElement(new List<int>());
					UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer = new int();
					*(UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer) = RatingRecord;
				}
				//UserData->Item2Topic->ListNoShift(UserData->Item2Topic->Length)->InsertElement(new List<TopicClass>());
				//cout << UserData->ItemList->ListNoShift(UserData->ItemList->Length)->ObjectPointer->Name << endl;
			}
		}
	}
	fr.close();
	cout << "OK" << endl;
	//cout << endl;
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

/*可以合併進入Read()，為了Testing才特別獨立出來，為了晚點才完成獨檔工作，以確保Learning時，不包含這部分資料*/
void ReadForTesting()
{
	Reset(1);
	char FileInput[500];
	fstream fr;
	string InputProcess;
	/*User Data*/
	string UserDataInput[NumofUserTopic];
	//cout << "User Data for Testing .. ";
	fr.open("u.test", ios::in);
	if (!fr)        //如果開啟檔案失敗，fin為0；成功，fin為1
		cout << "Fail to open file" << endl;
	else
	{
		while (fr.getline(FileInput, sizeof(FileInput)))
		{
			InputProcess = FileInput;
			istringstream ss(InputProcess);
			string token;
			int i = 0;
			while (std::getline(ss, token, '|'))
			{
				UserDataInput[i++] = token;
			}
			UserData = (UserClass*)SearchTable(1, UserDataInput[0], "ID:" + UserDataInput[0]);

			int Rating, ItemNo, RatingRecord;
			stringstream(UserDataInput[2]) >> Rating;
			RatingRecord = Rating;
			stringstream(UserDataInput[1]) >> ItemNo;
			if (UserData->ItemList == NULL)
			{
				//Item
				UserData->ItemList = (List<ItemClass>*)Inquiry(2, --ItemNo);//電腦的ItemNo從0開始
				//Rating
				UserData->ItemRating = new List<int>();
				UserData->ItemRating->ObjectPointer = new int();
				*(UserData->ItemRating->ObjectPointer) = RatingRecord;
				while (--Rating > 0)             //Rating視同購買次數
				{
					//Item
					UserData->ItemList->ListNoShift(UserData->ItemList->Length)->InsertElement(new List<ItemClass>());
					UserData->ItemList->ListNoShift(UserData->ItemList->Length)->ObjectPointer = UserData->ItemList->ObjectPointer;
					//Rating
					UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->InsertElement(new List<int>());
					UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer = new int();
					*(UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer) = RatingRecord;
				}
			}
			else
			{
				//Item
				UserData->ItemList->ListNoShift(UserData->ItemList->Length)->InsertElement((List<ItemClass>*)Inquiry(2, --ItemNo));
				//Rating
				UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->InsertElement(new List<int>());
				UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer = new int();
				*(UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer) = RatingRecord;
				while (--Rating > 0)             //Rating視同購買次數
				{
					//Item
					UserData->ItemList->ListNoShift(UserData->ItemList->Length)->InsertElement(new List<ItemClass>());
					UserData->ItemList->ListNoShift(UserData->ItemList->Length)->ObjectPointer = UserData->ItemList->ListNoShift((UserData->ItemList->Length) - 1)->ObjectPointer;
					//Rating
					UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->InsertElement(new List<int>());
					UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer = new int();
					*(UserData->ItemRating->ListNoShift(UserData->ItemRating->Length)->ObjectPointer) = RatingRecord;
				}
			}
		}
	}
	fr.close();
	//cout << "OK" << endl;
	//cout << endl;
}