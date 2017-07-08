#include"Header.h"

/*List Class*/
template<class T>
class List
{
public:
	List<T>* Last, *Next;
	T* ObjectPointer;
	//fin_obj_pos���O���b�Ĥ@��List
	//�Bfin_obj_pos�O���̫�@�Ӫ��󪺽s��
	//�Ҧp:�u���@�Ӫ���bList�ɡAfin_obj_pos��0
	//�Y�����S������A�h�bpointer�d�߮ɴN�|���~
	int fin_obj_pos = 0;
	clock_t time;

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
		RecordLength2Header->fin_obj_pos++;
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
			RecordLength2Header->fin_obj_pos--;
		}
		else
		{
			if (Next != NULL)
			{
				Next->Last = NULL;
				Next->fin_obj_pos = fin_obj_pos - 1;
			}
		}
		//delete this->ObjectPointer;
		delete this;
	}
};

class Item
{
public:
	string ID, Name;
	int Class;
};
