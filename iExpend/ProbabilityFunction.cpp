#include"Header.h"

/*P(A)*/
//A:ID
//Parameter Status : (Parameter/Lengyh*Parameter) .. disable
double Probability(string A, int TableName, int TableNo, int ListName, double Parameter)
{
	//A所在的表單長度 : Parameter*(Statistics(TableName, TableNo, 0, ""))
	//cout << "Num. of A : " << Statistics(TableName, TableNo, ListName, A) << endl;
	//cout << "Length : " << Statistics(TableName, TableNo, ListName, "") + 1 << endl;
	//double NumofA = Statistics(TableName, TableNo, ListName, A);
	//double Length = Statistics(TableName, TableNo, ListName, "") + 1;
	//double Temp = NumofA / Length;//((Statistics(TableName, TableNo, ListName, A)) / (Statistics(TableName, TableNo, ListName, "") + 1));
	return ((double)Statistics(TableName, TableNo, ListName, A)) / ((double)Statistics(TableName, TableNo, ListName, "") + 1);
}

/*P(B|A)*
//A、B皆為ID
double ConditionProbability(string A, int TableNameA, int TableNoA, int ListNameA, string B, int TableNameB, int TableNoB, int ListNameB)
{
	return 0;
}
/**/

void BaseProbability(double** ItemToTopicTable, double** TopicToItemTable, int NumofItem, int NumofTopic)
{
	//Item to Topic
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < NumofTopic; j++)
		{
			ItemToTopicTable[i][j] = Probability(to_string(j + 1), 2, i, 1, parameter_b);
		}
	}
	//Topic to Item
	for (int i = 0; i < NumofTopic; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			TopicToItemTable[i][j] = Probability(to_string(j + 1), 3, i, 1, parameter_a);
		}
	}

}