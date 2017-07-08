#include"Header.h"
#include"ObjectClass.cpp"

/*Object List*/

//Start Pointer
List<UserClass> * UserTable;
List<ItemClass> * ItemTable;
List<TopicClass> * TopicTable;

//Processing Pointre
List<UserClass> * UserProcess;
List<ItemClass> * ItemProcess;
List<TopicClass> * TopicProcess;

/*{Mark, User, Item, Topic}*/
//Mark    : 0
//User    : 1
//Item    : 2
//Topic : 3
string NameTable[27][4] = { ("a", "-1", "-1", "-1"), ("b", "-1", "-1", "-1"), ("c", "-1", "-1", "-1"), ("d", "-1", "-1", "-1"), ("e", "-1", "-1", "-1"), ("f", "-1", "-1", "-1"), ("g", "-1", "-1", "-1"), ("h", "-1", "-1", "-1"), ("i", "-1", "-1", "-1"), ("j", "-1", "-1", "-1"), ("k", "-1", "-1", "-1"), ("l", "-1", "-1", "-1"), ("m", "-1", "-1", "-1"), ("n", "-1", "-1", "-1"), ("o", "-1", "-1", "-1"), ("p", "-1", "-1", "-1"), ("q", "-1", "-1", "-1"), ("r", "-1", "-1", "-1"), ("s", "-1", "-1", "-1"), ("t", "-1", "-1", "-1"), ("u", "-1", "-1", "-1"), ("v", "-1", "-1", "-1"), ("w", "-1", "-1", "-1"), ("x", "-1", "-1", "-1"), ("y", "-1", "-1", "-1"), ("z", "-1", "-1", "-1") };

/*(取消)search結束之後,可以使用ListNoShift(TableNo)來跳到該物件*/
/*search結束之後,直接回傳該物件的位址*/
//TableName:
//1:User
//2:Item
//3:Topic
void* SearchTable(int TableName, string ID, string Name)
{
	//static int Test = 0;
	//int TableNo = 0;
	switch (TableName)
	{
		/*User*/
	case 1 :
		if (UserTable == NULL)
		{
			//cout << Name << endl;
			//cout << ++Test << endl;
			UserTable = new List<UserClass>();
			UserProcess = UserTable;
			UserProcess->ObjectPointer = new UserClass();
			UserProcess->ObjectPointer->ID = ID;
			UserProcess->ObjectPointer->Name = Name;
		}
		else
		{
			UserProcess = UserTable;
			while (UserProcess->Next != NULL)
			{
				//TableNo++;
				if (UserProcess->ObjectPointer->ID == ID)
				{
					break;
				}
				UserProcess = UserProcess->Next;
			}
			if (UserProcess->Next == NULL && UserProcess->ObjectPointer->ID != ID)
			{
				//TableNo++;
				//cout << Name << endl;
				//cout << ++Test << endl;
				UserProcess->InsertElement(new List<UserClass>());
				UserProcess = UserProcess->Next;
				UserProcess->ObjectPointer = new UserClass();
				UserProcess->ObjectPointer->ID = ID;
				UserProcess->ObjectPointer->Name = Name;
			}
		}
		/*找到/新增 使用者完成*/
		return UserProcess->ObjectPointer;
		break;

		/*Item*/
	case 2 :
		if (ItemTable == NULL)
		{
			ItemTable = new List<ItemClass>();
			ItemProcess = ItemTable;
			ItemProcess->ObjectPointer = new ItemClass();
			ItemProcess->ObjectPointer->ID = ID;
			ItemProcess->ObjectPointer->Name = Name;
		}
		else
		{
			ItemProcess = ItemTable;
			while (ItemProcess->Next != NULL)
			{
				//TableNo++;
				if (ItemProcess->ObjectPointer->ID == ID)
				{
					break;
				}
				ItemProcess = ItemProcess->Next;
			}
			if (ItemProcess->Next == NULL && ItemProcess->ObjectPointer->ID != ID)
			{
				//TableNo++;
				ItemProcess->InsertElement(new List<ItemClass>());
				ItemProcess = ItemProcess->Next;
				ItemProcess->ObjectPointer = new ItemClass();
				ItemProcess->ObjectPointer->ID = ID;
				ItemProcess->ObjectPointer->Name = Name;
			}
		}
		/*找到/新增 物品完成*/
		return ItemProcess->ObjectPointer;
		break;

		/*Topic*/
	case 3 :
		if (TopicTable == NULL)
		{
			TopicTable = new List<TopicClass>();
			TopicProcess = TopicTable;
			TopicProcess->ObjectPointer = new TopicClass();
			TopicProcess->ObjectPointer->ID = ID;
			TopicProcess->ObjectPointer->Name = Name;
		}
		else
		{
			TopicProcess = TopicTable;
			while (TopicProcess->Next != NULL)
			{
				//TableNo++;
				if (TopicProcess->ObjectPointer->ID == ID)
				{
					break;
				}
				TopicProcess = TopicProcess->Next;
			}
			if (TopicProcess->Next == NULL && TopicProcess->ObjectPointer->ID != ID)
			{
				//TableNo++;
				TopicProcess->InsertElement(new List<TopicClass>());
				TopicProcess = TopicProcess->Next;
				TopicProcess->ObjectPointer = new TopicClass();
				TopicProcess->ObjectPointer->ID = ID;
				TopicProcess->ObjectPointer->Name = Name;
			}
		}
		/*找到/新增 特徵完成*/
		return TopicProcess->ObjectPointer;
		break;
	}
	//return TableNo;
}

void* Inquiry(int TableName, int TableNo)
{
	switch (TableName)
	{
	case 1 : 
		UserProcess = new List<UserClass>();
		UserProcess->ObjectPointer = (UserTable->ListNoShift(TableNo))->ObjectPointer;
		return UserProcess;
		break;
	case 2 :
		ItemProcess = new List<ItemClass>();
		ItemProcess->ObjectPointer = (ItemTable->ListNoShift(TableNo))->ObjectPointer;
		return ItemProcess;
		break;
	case 3 :
		TopicProcess = new List<TopicClass>();
		TopicProcess->ObjectPointer = (TopicTable->ListNoShift(TableNo))->ObjectPointer;
		return TopicProcess;
		break;
	}
}

/*(User/Item/Topic, alphabet, Number)*
//ex. (1, a, 0)
//未完成
void AddNewMark(int TableName, string NewMarkName, int NewMarkNumber)
{
	for (int i = 0; i < 27; i++)
	{
		if (NameTable[i][0] == NewMarkName)
		{
			NameTable[i][TableName] = NewMarkNumber;
		}
		
	}
}
/**/

/*計算出現次數*/
//QueryID欲統計出現次數的ID
//(取消)A、B不同時，表示要同時出現才採計
//設0進入Default
//若存在List為NULL的情況，則會出現error
//當ListName為0時，TableNo就不會用到
int Statistics(int TableName, int TableNo, int ListName, string QueryID)
{
	int TotalNumble = 0;
	if (QueryID != "")
	{
		switch (TableName)
		{
		case 1://User Table
			switch (ListName)
			{
			case 1://Item List
				ItemProcess = UserTable->ListNoShift(TableNo)->ObjectPointer->ItemList;
				if (ItemProcess == NULL)
				{
					break;
				}
				if (ItemProcess->ObjectPointer->ID == QueryID)
				{
					TotalNumble++;
				}
				while (ItemProcess->Next != NULL)
				{
					ItemProcess = ItemProcess->Next;
					if (ItemProcess->ObjectPointer->ID == QueryID)
					{
						TotalNumble++;
					}
				}
				break;
			case 2://Item to Topic List
				TopicProcess = UserTable->ListNoShift(TableNo)->ObjectPointer->Item2Topic;
				if (TopicProcess == NULL)
				{
					break;
				}
				if (TopicProcess->ObjectPointer->ID == QueryID)
				{
					TotalNumble++;
				}
				while (TopicProcess->Next != NULL)
				{
					TopicProcess = TopicProcess->Next;
					if (TopicProcess->ObjectPointer->ID == QueryID)
					{
						TotalNumble++;
					}
				}
				break;
			default://User List
				UserProcess = UserTable;
				if (UserProcess == NULL)
				{
					break;
				}
				if (UserProcess->ObjectPointer->ID == QueryID)
				{
					TotalNumble++;
				}
				while (UserProcess->Next != NULL)
				{
					UserProcess = UserProcess->Next;
					if (UserProcess->ObjectPointer->ID == QueryID)
					{
						TotalNumble++;
					}
				}
				break;
			}
			break;
		case 2://Item Table
			switch (ListName)
			{
			case 1://Topic List
				TopicProcess = ItemTable->ListNoShift(TableNo)->ObjectPointer->TopicList;
				if (TopicProcess == NULL)
				{
					break;
				}
				if (TopicProcess->ObjectPointer->ID == QueryID)
				{
					TotalNumble++;
				}
				while (TopicProcess->Next != NULL)
				{
					TopicProcess = TopicProcess->Next;
					if (TopicProcess->ObjectPointer->ID == QueryID)
					{
						TotalNumble++;
					}
				}
				break;
			default://Item List
				ItemProcess = ItemTable;
				if (ItemProcess == NULL)
				{
					break;
				}
				if (ItemProcess->ObjectPointer->ID == QueryID)
				{
					TotalNumble++;
				}
				while (ItemProcess->Next != NULL)
				{
					ItemProcess = ItemProcess->Next;
					if (ItemProcess->ObjectPointer->ID == QueryID)
					{
						TotalNumble++;
					}
				}
				break;
			}
			break;
		case 3://Topic Table
			switch (ListName)
			{
			case 1://Item List
				ItemProcess = TopicTable->ListNoShift(TableNo)->ObjectPointer->ItemList;
				if (ItemProcess == NULL)
				{
					break;
				}
				if (ItemProcess->ObjectPointer->ID == QueryID)
				{
					TotalNumble++;
				}
				while (ItemProcess->Next != NULL)
				{
					ItemProcess = ItemProcess->Next;
					if (ItemProcess->ObjectPointer->ID == QueryID)
					{
						TotalNumble++;
					}
				}
				break;
			default://Topic List
				TopicProcess = TopicTable;
				if (TopicProcess == NULL)
				{
					break;
				}
				if (TopicProcess->ObjectPointer->ID == QueryID)
				{
					TotalNumble++;
				}
				while (TopicProcess->Next != NULL)
				{
					TopicProcess = TopicProcess->Next;
					if (TopicProcess->ObjectPointer->ID == QueryID)
					{
						TotalNumble++;
					}
				}
				break;
			}
			break;
		}
	}
	else
	{
		switch (TableName)
		{
		case 1 :   //User Table
			switch (ListName)
			{
			case 1 :   //Item List
				return UserTable->ListNoShift(TableNo)->ObjectPointer->ItemList->Length;
				break;
			case 2:   //Item to Topic
				return UserTable->ListNoShift(TableNo)->ObjectPointer->Item2Topic->Length;
				break;
			default:   //User List
				return UserTable->Length;
				break;
			}
			break;
		case 2 :   //Item Table
			switch (ListName)
			{
			case 1:   //Topic List
				return ItemTable->ListNoShift(TableNo)->ObjectPointer->TopicList->Length;
				break;
			case 2:   //Topic Value List
				return ItemTable->ListNoShift(TableNo)->ObjectPointer->TopicValueList->Length;
				break;
			default:   //Itrm List
				return ItemTable->Length;
				break;
			}
			break;
		case 3 :   //Topic Table
			switch (ListName)
			{
			case 1:   //Item List
				return TopicTable->ListNoShift(TableNo)->ObjectPointer->ItemList->Length;
				break;
			default:   //Topic List
				return TopicTable->Length;
				break;
			}
			break;
		}
	}
	return TotalNumble;
}

void Reset(int TableName)
{
	switch (TableName)
	{
	case 1 :
		UserTable = NULL;
		break;
	case 2:
		ItemTable = NULL;
		break;
	case 3:
		TopicTable = NULL;
		break;
	default:
		break;
	}
}

void* GetTable(int TableName)
{
	switch (TableName)
	{
	case 1:
		return UserTable;
		break;
	case 2:
		return ItemTable;
		break;
	case 3:
		return TopicTable;
		break;
	default:
		break;
	}
}