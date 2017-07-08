#include"Header.h"
#include"object_class.cpp"

float sim_item(Item* item_A, Item* item_B);

float sim_cast(List<Item>* case_A, List<Item>* case_B)
{
	int Len_A = (case_A->fin_obj_pos) + 1,
		Len_B = (case_B->fin_obj_pos) + 1;
	float total_sim = 0;
	for (int i = 0; i < Len_A; i++)
	{
		float sim = 0;
		for (int j = 0; j < Len_B; j++)
		{
			float check_item_sim = sim_item(case_A->ListNoShift(i)->ObjectPointer, case_B->ListNoShift(j)->ObjectPointer);
			if (check_item_sim > sim)
			{
				sim = check_item_sim;
			}
		}
		total_sim += sim;
	}
	total_sim = total_sim / Len_A;
	return total_sim;
}

float sim_item(Item* item_A, Item* item_B)
{
	float sim = 0;
	if (item_A->Class == item_B->Class)
	{
		sim++;
	}
	return sim;
}