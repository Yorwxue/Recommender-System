#include"Header.h"
#include "ObjectClass.cpp"

static int NumofOldTopic;

/*藉由train時，Item間相似的Topic，組成新的Topic*/
void newTopic(double** ItemToTopicTable, double** TopicToItemTable)
{
	List<TopicClass> * TopicTable = (List<TopicClass> *)GetTable(3);

	int NumofUser = Statistics(1, 0, 0, "") + 1,
		NumofItem = Statistics(2, 0, 0, "") + 1,
		NumofTopic = Statistics(3, 0, 0, "") + 1;//舊有的Topic的個數
	NumofOldTopic = NumofTopic;
	/*確認送入資料正確性*
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < NumofTopic; j++)
		{
			if (i<10)
			cout << ItemToTopicTable[i][j] << ", ";
		}
		if (i<10)
		cout << endl;
	}
	/**/
	
	int* similarItemPair = new int[NumofItem];
	double highest = 0;
	double** ItemToItemTable = (double**)new2d(NumofItem, NumofItem, sizeof(double));
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			ItemToItemTable[i][j] = 0;
			for (int k = 0; k < NumofTopic; k++)
			{
				ItemToItemTable[i][j] += ItemToTopicTable[i][k] * TopicToItemTable[k][j];
			}
			//找出變換機率最高的
			if (highest<ItemToItemTable[i][j])
			{
				similarItemPair[i] = j;
				highest = ItemToItemTable[i][j];
			}
		}
		highest = 0;
	}
	//藉由比對變化機率最高的Item間的Topic相近，組合原有的多個Topic來產生新的Topic  <--目前進度
	ItemClass * ItemA, * ItemB;
	int NumofSameTopic = 0;
	int TopicID = NumofTopic + 1;  //新的Topic要用的ID
	string TopicName;
	//List<int>* AssemblyTopicInfo;//這個Assembly Topic包含哪些舊Topic
	//int NumofAssemblyTopic = 0;
	List<TopicClass>* ItemTopicProcessingA, *ItemTopicProcessingB;
	List<TopicClass>* AssemblyTopicProcessing;
	//int NumofRepeatTopic = 0;

	for (int i = 0; i < NumofItem; i++)
	{
		ItemA = ((List<ItemClass>*)Inquiry(2, i))->ObjectPointer;
		ItemB = ((List<ItemClass>*)Inquiry(2, similarItemPair[i]))->ObjectPointer;
		TopicClass * TopicData = NULL;
		ItemTopicProcessingA = ItemA->TopicList;
		TopicName = "Assembly Topic " + (i + 1);//由第一個Item的演化所產生的新Topic
		/**
		if (AssemblyTopicInfo == NULL)       //記下這個新Topic混合了哪些舊Topic
		{
			AssemblyTopicInfo = new List<int>();
			AssemblyTopicInfo->ObjectPointer = new int[NumofTopic];
			NumofAssemblyTopic++;
		}
		else
		{
			AssemblyTopicInfo->ListNoShift(NumofAssemblyTopic - 1)->InsertElement(new List<int>());
			AssemblyTopicInfo->ListNoShift(NumofAssemblyTopic)->ObjectPointer = new int[NumofTopic];
			NumofAssemblyTopic++;
		}/**/
		int RecordTopicNo;

		while (ItemTopicProcessingA != NULL)
		{
			ItemTopicProcessingB = ItemB->TopicList;
			while (ItemTopicProcessingB != NULL)
			{
				if (ItemTopicProcessingA->ObjectPointer->ID == ItemTopicProcessingB->ObjectPointer->ID)
				{
					int TopicNo;
					stringstream(ItemTopicProcessingB->ObjectPointer->ID) >> TopicNo;  //ID to No
					TopicNo--;                                                         //ID從1開始，No從0開始
					/**/
					if (NumofSameTopic == 0)  //還未確認是否需要新建Topic，所以先保留
					{
						RecordTopicNo = TopicNo;
					}
					NumofSameTopic++;
					if (NumofSameTopic == 2)  //重複Topic達到新建Topic的門檻(2個)，可以建立新Topic
					{
						TopicData = (TopicClass*)SearchTable(3, to_string(TopicID), TopicName);
						TopicData->SubTopic = (List<TopicClass>*)Inquiry(3, RecordTopicNo);
						TopicData->SubTopic->InsertElement((List<TopicClass>*)Inquiry(3, TopicNo));
						TopicID++;//變成下一個新Topic要用的ID
						//cout << "Total Topic +1, Now the Num. of Topic is " << TopicID-1 << endl;
					}
					else if (NumofSameTopic > 2)
					{
						if (TopicData == NULL)
						{
							TopicData = (TopicClass*)SearchTable(3, to_string(TopicID-1), TopicName);
						}
						TopicData->SubTopic->ListNoShift(TopicData->SubTopic->Length)->InsertElement((List<TopicClass>*)Inquiry(3, TopicNo));
					}
					break;/**/
				}
				ItemTopicProcessingB = ItemTopicProcessingB->Next;
			}
			ItemTopicProcessingA = ItemTopicProcessingA->Next;
		}
		/*確認新產生的這個Assembly Topic是否與新前產生的Assembly Topic重複*/
		AssemblyTopicProcessing = TopicTable;
		AssemblyTopicProcessing = AssemblyTopicProcessing->ListNoShift(NumofTopic);//找到第一個Assembly Topic
		while (AssemblyTopicProcessing->Next != NULL)
		{
			if (AssemblyTopicProcessing->ObjectPointer->SubTopic->Length == NumofSameTopic - 1)//包含的subTopic數目相同，表示有可能重複
			{//檢查細項
				for (int i = 0; i < NumofSameTopic; i++)
				{
					if (AssemblyTopicProcessing->ObjectPointer->SubTopic->ListNoShift(i)->ObjectPointer->ID != TopicData->SubTopic->ListNoShift(i)->ObjectPointer->ID)
					{
						break;
					}
					else if (i == NumofSameTopic - 1)//確認這個Assemble Topic重複了
					{
						//NumofRepeatTopic++;
						delete TopicData;
						TopicData = NULL;
						TopicTable->ListNoShift(TopicTable->Length)->DeleteElement();
						TopicID--;
						//cout << "Topic repeat, del it, Now the Num. of Topic is " << TopicID-1 << endl;
					}
				}
			}
			if (TopicData == NULL)  //確認新的Assemble Topic重複，且已刪除
			{
				break;
			}
			AssemblyTopicProcessing = AssemblyTopicProcessing->Next;
		}

		NumofSameTopic = 0;
	}
	cout << "Num. of Assemble Topic : " << TopicTable->Length + 1 - NumofTopic << " .. ";
	//cout << "Num. of repeat Topic : " << NumofRepeatTopic << endl;
}
//New Topic產生後，要變更NumofTopic，與重建Item to Topic、Topic to Item等Table



/*新產生的Assembly Topic，可以套用在哪些Item上*/
void Apply()
{
	List<ItemClass> * ItemTable = (List<ItemClass> *)GetTable(2);
	List<TopicClass> * TopicTable = (List<TopicClass> *)GetTable(3);

	int NumofUser = Statistics(1, 0, 0, "") + 1,
		NumofItem = Statistics(2, 0, 0, "") + 1,
		NumofTopic = Statistics(3, 0, 0, "") + 1;//新的Topic個數

	List<ItemClass>* Item;
	List<TopicClass>* Topic;
	List<TopicClass>* subTopic;

	int NumofApply = 0;  //分別計算各個Assembly Topic被套用到多少個Item上

	for (int j = 0; j < (NumofTopic - NumofOldTopic); j++)  //尋找到新的(未被套用過的)Assembly Topic
	{
		Topic = TopicTable->ListNoShift(NumofOldTopic + j);
		int NumofSubTopic = Topic->ObjectPointer->SubTopic->Length + 1;

		for (int i = 0; i < NumofItem; i++)      //開始套用到各個Item
		{
			Item = ItemTable->ListNoShift(i);
			int NumofTopicInItem = Item->ObjectPointer->TopicList->Length + 1;
			if (NumofTopicInItem == NumofSubTopic)  //先確認包含的subTopic個數相同
			{
				//檢查細項
				for (int k = 0; k < NumofSubTopic; k++)
				{
					subTopic = Topic->ObjectPointer->SubTopic->ListNoShift(k);
					int Find = 0;

					for (int L = 0; L < NumofTopicInItem; L++)
					{
						if (subTopic->ObjectPointer->ID == Item->ObjectPointer->TopicList->ListNoShift(L)->ObjectPointer->ID)
						{
							Find = 1;
							break;
						}
					}
					if (Find == 0)
					{
						break;
					}
					if (k == NumofSubTopic - 1)  //確認符合這個Assembly Topic，開始套用
					{
						NumofApply++;
						//在Item中新增Topic
						Item->ObjectPointer->TopicList->ListNoShift(Item->ObjectPointer->TopicList->Length)->InsertElement(new List<TopicClass>());
						Item->ObjectPointer->TopicList->ListNoShift(Item->ObjectPointer->TopicList->Length)->ObjectPointer = Topic->ObjectPointer;
						//在Topic中新增Item
						if (Topic->ObjectPointer->ItemList == NULL)
						{
							Topic->ObjectPointer->ItemList = new List<ItemClass>();
							Topic->ObjectPointer->ItemList->ObjectPointer = Item->ObjectPointer;
						}
						else
						{
							Topic->ObjectPointer->ItemList->ListNoShift(Topic->ObjectPointer->ItemList->Length)->InsertElement(new List<ItemClass>());
							Topic->ObjectPointer->ItemList->ListNoShift(Topic->ObjectPointer->ItemList->Length)->ObjectPointer = Item->ObjectPointer;
						}
					}
				}
			}
		}
		//cout << "Assemble Topic No " << j + 1 << " apply for " << NumofApply << " times" << endl;

		/*擁有這個Assembly Topic的Item太少，刪除這個Assembly Topic*
		if (NumofApply<(NumofItem*delAssemblyTopicRatio))
		{
			//cout << "Del Topic : " << Topic->ObjectPointer->ID << endl;
			//cout << "remainder : " << NumofTopic - NumofOldTopic << endl;
			delApply(Topic->ObjectPointer->ID);
			NumofTopic--;
			j--;
		}
		/*刪除完畢*/
		NumofApply = 0;
	}
	cout << "Num. of Apply Assemble Topic : " << TopicTable->Length + 1 - NumofOldTopic << " .. ";
}

//將已套用的Topic刪除
void delApply(string delID)
{
	int NumofItem = Statistics(2, 0, 0, "") + 1,
		NumofTopic = Statistics(3, 0, 0, "") + 1;//新的Topic個數
	List<ItemClass> * ItemTable = (List<ItemClass> *)GetTable(2);
	List<ItemClass> * ItemProcessing = ItemTable;
	List<TopicClass> * TopicTable = (List<TopicClass> *)GetTable(3);
	List<TopicClass> * TopicProcessing = TopicTable;

	for (int i = 0; i < NumofItem; i++)
	{
		ItemProcessing = ItemTable->ListNoShift(i);
		int NumofTopicInItem = ItemProcessing->ObjectPointer->TopicList->Length + 1;
		for (int j = 0; j < NumofTopicInItem; j++)
		{
			if (ItemProcessing->ObjectPointer->TopicList->ListNoShift(j)->ObjectPointer->ID == delID)
			{
				ItemTable->ListNoShift(i)->ObjectPointer->TopicList->ListNoShift(j)->DeleteElement();
				j = NumofTopicInItem;
				break;
			}
		}
	}

	while (TopicProcessing != NULL)
	{
		if (TopicProcessing->ObjectPointer->ID == delID)
		{
			delete TopicProcessing->ObjectPointer;
			TopicProcessing->DeleteElement();
			break;
		}
		TopicProcessing = TopicProcessing->Next;
	}
}