#include"Header.h"
#include"object_class.cpp"

List<List<Item>>* data_base;

void new_Case(List<Item>* new_case)
{
	if (data_base == NULL)
	{
		data_base = new List<List<Item>>();
		data_base->ObjectPointer = new_case;
		data_base->time = clock();
	}
	else
	{
		data_base->ListNoShift(data_base->fin_obj_pos)->InsertElement(new_case);
		data_base->ListNoShift(data_base->fin_obj_pos)->time = clock();
	}
}

void new_item(List<Item>* Case, Item* new_item)
{
	if (Case == NULL)
	{
		Case = new List<Item>();
		Case->ObjectPointer = new_item;
		Case->time = clock();
	}
	else
	{
		Case->ListNoShift(Case->fin_obj_pos)->InsertElement(new_item);
		Case->ListNoShift(Case->fin_obj_pos)->time = clock();
	}
}