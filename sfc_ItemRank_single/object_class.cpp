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
	//Length都記錄在第一個
	//且Length是指最後一個物件的編號
	//例如:只有一個物件在List時，Length為0
	//若完全沒有物件，則在pointer查詢時就會失誤
	int Length = 0;

	/*頁碼，方便像array一樣直接找到物件*/
	//0是自己，等同不移動，不能使用此涵式
	//小於0的移動未實作
	//實際作法是以目前物件為起點，往後移動多少個位址，所以只有在"0"物件時使用，才會類似array
	//使用時要加括號，如 "(List->ListNoShift(int))->ObjectPointer"
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

	/*插入element到下一個*/
	//需要知道新的Element的位址
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
	/*刪除自身*/
	//刪除的是開頭的話，要特別留意將第二個Element接回StartPointer
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
	//Length都記錄在第一個
	//且Length是指最後一個物件的編號
	//例如:只有一個物件在List時，Length為0
	//若完全沒有物件，則在pointer查詢時就會失誤
	int Length = 0;

	/*頁碼，方便像array一樣直接找到物件*/
	//0是自己，等同不移動，不能使用此涵式
	//小於0的移動未實作
	//實際作法是以目前物件為起點，往後移動多少個位址，所以只有在"0"物件時使用，才會類似array
	//使用時要加括號，如 "(List->ListNoShift(int))->ObjectPointer"
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

	/*插入element到下一個*/
	//需要知道新的Element的位址
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
	/*刪除自身*/
	//刪除的是開頭的話，要特別留意將第二個Element接回StartPointer
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