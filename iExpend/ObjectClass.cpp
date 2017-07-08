#include"Header.h"

/*List Class*/
template<class T>
class List
{
public:
	List<T>* Last, * Next;
	T* ObjectPointer;
	//Length���O���b�Ĥ@��
	//�BLength�O���̫�@�Ӫ��󪺽s��
	//�Ҧp:�u���@�Ӫ���bList�ɡALength��0
	//�Y�����S������A�h�bpointer�d�߮ɴN�|���~
	int Length = 0;

	/*���X�A��K��array�@�˪�����쪫��*/
	//0�O�ۤv�A���P�����ʡA����ϥΦ��[��
	//�p��0�����ʥ���@
	//��ڧ@�k�O�H�ثe���󬰰_�I�A���Ჾ�ʦh�֭Ӧ�}�A�ҥH�u���b"0"����ɨϥΡA�~�|����array
	//�ϥήɭn�[�A���A�p "(List->ListNoShift(int))->ObjectPointer"
	List<T>* ListNoShift(int ShiftValue)
	{
		List<T>* Target = this;
		while (ShiftValue > 0)
		{
			Target = Target->Next;
			ShiftValue--;
		}
		return Target;
	}

	/*���Jelement��U�@��*/
	//�ݭn���D�s��Element����}
	void InsertElement(List<T>* NewElement)
	{
		NewElement->Last = this;
		if (Next != NULL)
		{
			Next->Last = NewElement;
			NewElement->Next = Next;
		}
		Next = NewElement;

		List<T>* RecordLength2Header = this;
		while (RecordLength2Header->Last != NULL)
		{
			RecordLength2Header = RecordLength2Header->Last;
		}
		RecordLength2Header->Length++;
	}
	/*�R���ۨ�*/
	//�R�����O�}�Y���ܡA�n�S�O�d�N�N�ĤG��Element���^StartPointer
	void DeleteElement()
	{
		if (Last != NULL)
		{
			if (Next != NULL)
			{
				Next->Last = Last;
				Last->Next = Next;
			}
			else
			{
				Last->Next = NULL;
			}

			List<T>* RecordLength2Header = this;
			while (RecordLength2Header->Last != NULL)
			{
				RecordLength2Header = RecordLength2Header->Last;
			}
			RecordLength2Header->Length--;
		}
		else
		{
			if (Next != NULL)
			{
				Next->Last = NULL;
				Next->Length = Length - 1;
			}
		}
		//delete this->ObjectPointer;
		delete this;
	}
};

/*User Class*/
//ItemList : 1
//Item2Topic : 2
class UserClass
{
public:
	string ID, Name;
	List<ItemClass>* ItemList;
	List<TopicClass>* Item2Topic;
	List<int>* ItemRating;
};

/*Item Class*/
//TopicList : 1
//TopicValueList : 2
class ItemClass
{
public:
	string ID, Name;
	List<TopicClass>* TopicList;
	List<float>* TopicValueList;
};

/*Topic Class*/
class TopicClass
{
public:
	string ID, Name;
	int AssemblyTopic = 0;
	List<TopicClass>* SubTopic;
	List<ItemClass>* ItemList;
};

