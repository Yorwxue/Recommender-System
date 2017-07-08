#include"Header.h"

/*List Class*/
template<class T>
class List
{
public:
	List<T>* Last, *Next;

	float c[Numofclass], m[Numofclass];
	int Num_xi_in_G = 1;

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
	void InsertElement(T* new_data)
	{
		List<T>* NewElement = new List<T>();
		NewElement->ObjectPointer = new_data;

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


/*List Class*/
template<class T>
class List_G_cluster
{
public:
	List_G_cluster<T>* Last, *Next;

	float c[NumofItem], m[NumofItem];
	int Num_xi_in_G = 1;

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
	List_G_cluster<T>* ListNoShift(int ShiftValue)
	{
		List_G_cluster<T>* Target = this;
		while (ShiftValue > 0)
		{
			Target = Target->Next;
			ShiftValue--;
		}
		return Target;
	}

	/*���Jelement��U�@��*/
	//�ݭn���D�s��Element����}
	void InsertElement(T* new_data)
	{
		List_G_cluster<T>* NewElement = new List_G_cluster<T>();
		NewElement->ObjectPointer = new_data;

		NewElement->Last = this;
		if (Next != NULL)
		{
			Next->Last = NewElement;
			NewElement->Next = Next;
		}
		Next = NewElement;

		List_G_cluster<T>* RecordLength2Header = this;
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

			List_G_cluster<T>* RecordLength2Header = this;
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