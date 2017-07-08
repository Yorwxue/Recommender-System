#include"Header.h"
#include "ObjectClass.cpp"

static int NumofOldTopic;

/*�ǥ�train�ɡAItem���ۦ���Topic�A�զ��s��Topic*/
void newTopic(double** ItemToTopicTable, double** TopicToItemTable)
{
	List<TopicClass> * TopicTable = (List<TopicClass> *)GetTable(3);

	int NumofUser = Statistics(1, 0, 0, "") + 1,
		NumofItem = Statistics(2, 0, 0, "") + 1,
		NumofTopic = Statistics(3, 0, 0, "") + 1;//�¦���Topic���Ӽ�
	NumofOldTopic = NumofTopic;
	/*�T�{�e�J��ƥ��T��*
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
			//��X�ܴ����v�̰���
			if (highest<ItemToItemTable[i][j])
			{
				similarItemPair[i] = j;
				highest = ItemToItemTable[i][j];
			}
		}
		highest = 0;
	}
	//�ǥѤ���ܤƾ��v�̰���Item����Topic�۪�A�զX�즳���h��Topic�Ӳ��ͷs��Topic  <--�ثe�i��
	ItemClass * ItemA, * ItemB;
	int NumofSameTopic = 0;
	int TopicID = NumofTopic + 1;  //�s��Topic�n�Ϊ�ID
	string TopicName;
	//List<int>* AssemblyTopicInfo;//�o��Assembly Topic�]�t������Topic
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
		TopicName = "Assembly Topic " + (i + 1);//�ѲĤ@��Item���t�ƩҲ��ͪ��sTopic
		/**
		if (AssemblyTopicInfo == NULL)       //�O�U�o�ӷsTopic�V�X�F������Topic
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
					TopicNo--;                                                         //ID�q1�}�l�ANo�q0�}�l
					/**/
					if (NumofSameTopic == 0)  //�٥��T�{�O�_�ݭn�s��Topic�A�ҥH���O�d
					{
						RecordTopicNo = TopicNo;
					}
					NumofSameTopic++;
					if (NumofSameTopic == 2)  //����Topic�F��s��Topic�����e(2��)�A�i�H�إ߷sTopic
					{
						TopicData = (TopicClass*)SearchTable(3, to_string(TopicID), TopicName);
						TopicData->SubTopic = (List<TopicClass>*)Inquiry(3, RecordTopicNo);
						TopicData->SubTopic->InsertElement((List<TopicClass>*)Inquiry(3, TopicNo));
						TopicID++;//�ܦ��U�@�ӷsTopic�n�Ϊ�ID
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
		/*�T�{�s���ͪ��o��Assembly Topic�O�_�P�s�e���ͪ�Assembly Topic����*/
		AssemblyTopicProcessing = TopicTable;
		AssemblyTopicProcessing = AssemblyTopicProcessing->ListNoShift(NumofTopic);//���Ĥ@��Assembly Topic
		while (AssemblyTopicProcessing->Next != NULL)
		{
			if (AssemblyTopicProcessing->ObjectPointer->SubTopic->Length == NumofSameTopic - 1)//�]�t��subTopic�ƥجۦP�A��ܦ��i�୫��
			{//�ˬd�Ӷ�
				for (int i = 0; i < NumofSameTopic; i++)
				{
					if (AssemblyTopicProcessing->ObjectPointer->SubTopic->ListNoShift(i)->ObjectPointer->ID != TopicData->SubTopic->ListNoShift(i)->ObjectPointer->ID)
					{
						break;
					}
					else if (i == NumofSameTopic - 1)//�T�{�o��Assemble Topic���ƤF
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
			if (TopicData == NULL)  //�T�{�s��Assemble Topic���ơA�B�w�R��
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
//New Topic���ͫ�A�n�ܧ�NumofTopic�A�P����Item to Topic�BTopic to Item��Table



/*�s���ͪ�Assembly Topic�A�i�H�M�Φb����Item�W*/
void Apply()
{
	List<ItemClass> * ItemTable = (List<ItemClass> *)GetTable(2);
	List<TopicClass> * TopicTable = (List<TopicClass> *)GetTable(3);

	int NumofUser = Statistics(1, 0, 0, "") + 1,
		NumofItem = Statistics(2, 0, 0, "") + 1,
		NumofTopic = Statistics(3, 0, 0, "") + 1;//�s��Topic�Ӽ�

	List<ItemClass>* Item;
	List<TopicClass>* Topic;
	List<TopicClass>* subTopic;

	int NumofApply = 0;  //���O�p��U��Assembly Topic�Q�M�Ψ�h�֭�Item�W

	for (int j = 0; j < (NumofTopic - NumofOldTopic); j++)  //�M���s��(���Q�M�ιL��)Assembly Topic
	{
		Topic = TopicTable->ListNoShift(NumofOldTopic + j);
		int NumofSubTopic = Topic->ObjectPointer->SubTopic->Length + 1;

		for (int i = 0; i < NumofItem; i++)      //�}�l�M�Ψ�U��Item
		{
			Item = ItemTable->ListNoShift(i);
			int NumofTopicInItem = Item->ObjectPointer->TopicList->Length + 1;
			if (NumofTopicInItem == NumofSubTopic)  //���T�{�]�t��subTopic�ӼƬۦP
			{
				//�ˬd�Ӷ�
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
					if (k == NumofSubTopic - 1)  //�T�{�ŦX�o��Assembly Topic�A�}�l�M��
					{
						NumofApply++;
						//�bItem���s�WTopic
						Item->ObjectPointer->TopicList->ListNoShift(Item->ObjectPointer->TopicList->Length)->InsertElement(new List<TopicClass>());
						Item->ObjectPointer->TopicList->ListNoShift(Item->ObjectPointer->TopicList->Length)->ObjectPointer = Topic->ObjectPointer;
						//�bTopic���s�WItem
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

		/*�֦��o��Assembly Topic��Item�Ӥ֡A�R���o��Assembly Topic*
		if (NumofApply<(NumofItem*delAssemblyTopicRatio))
		{
			//cout << "Del Topic : " << Topic->ObjectPointer->ID << endl;
			//cout << "remainder : " << NumofTopic - NumofOldTopic << endl;
			delApply(Topic->ObjectPointer->ID);
			NumofTopic--;
			j--;
		}
		/*�R������*/
		NumofApply = 0;
	}
	cout << "Num. of Apply Assemble Topic : " << TopicTable->Length + 1 - NumofOldTopic << " .. ";
}

//�N�w�M�Ϊ�Topic�R��
void delApply(string delID)
{
	int NumofItem = Statistics(2, 0, 0, "") + 1,
		NumofTopic = Statistics(3, 0, 0, "") + 1;//�s��Topic�Ӽ�
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