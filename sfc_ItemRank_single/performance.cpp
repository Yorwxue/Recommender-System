#include"Header.h"

float MAE = 0;

void macroDOA(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], float IR[NumofUser][NumofItem])
{
	float DOA[NumofUser];
	int checkOrder[NumofUser];
	int NumofNW[NumofUser], NumofTesting[NumofUser];
	int unUsedData = 0;

	for (int i = 0; i < NumofUser; i++)
	{
		DOA[i] = 0;
		checkOrder[i] = 0;
		NumofNW[i] = 0;
		NumofTesting[i]=0;

		for (int j = 0; j < NumofItem; j++)
		{
			if (testing[i][j] > 0) //belong to Testing
			{
				NumofTesting[i]++;
				for (int k = j + 1; k < NumofItem; k++)
				{

					if (data[i][k] == Unrating && testing[i][k] < 1)  //belong to NW  //==0似乎會發生0.00000000001等，無法判定的情況
					{
						if (IR[i][j] >= IR[i][k])
						{
							checkOrder[i]++;
						}
					}
				}
			}
			else  if (data[i][j] == Unrating && testing[i][j] < 1)  //belong to NW
			{
				NumofNW[i]++;
				for (int k = j + 1; k < NumofItem; k++)
				{
					if (testing[i][k] > 0)  //belong to Testing
					{
						if (IR[i][k] >= IR[i][j])
						{
							checkOrder[i]++;
						}
					}
				}
			}
		}
		//計算個別DOA
		if (NumofNW[i] != 0 && NumofTesting[i] != 0)
		{
			DOA[i] = (float)checkOrder[i] / (NumofNW[i] * NumofTesting[i]);
		}
		else
		{
			unUsedData++;
		}
	}
	float TotalDOA = 0;
	for (int i = 0; i < NumofUser; i++)
	{
		TotalDOA += DOA[i];
	}
	if (NumofUser == unUsedData)
	{
		cout << "Testing data are contain in training data." << endl;
	}
	else
	{
		TotalDOA = TotalDOA / (NumofUser - unUsedData);
		cout << "Macro DOA = " << TotalDOA * 100 << "%"<< endl;
	}
}

/**/
void sfc_macroDOA(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], float IR[NumofUser][NumofItem], int rating_predict[NumofUser][NumofItem])
{
	float DOA[NumofUser];
	int checkOrder[NumofUser];
	int NumofNW[NumofUser], NumofTesting[NumofUser];
	int unUsedData = 0;

	for (int i = 0; i < NumofUser; i++)
	{
		DOA[i] = 0;
		checkOrder[i] = 0;
		NumofNW[i] = 0;
		NumofTesting[i] = 0;

		for (int j = 0; j < NumofItem; j++)
		{
			if (testing[i][j] > 0) //belong to Testing
			{
				NumofTesting[i]++;
				for (int k = j + 1; k < NumofItem; k++)
				{

					if (rating_predict[i][k] != 1 && testing[i][k] < 1)  //belong to NW  //rating_predict[i][k] != 1 表示在training中沒有
					{
						if (data[i][j] >= data[i][k])
						//if (data[i][j] - data[i][k] >= 1)
						{
							checkOrder[i]++;
						}
						/**
						else if (data[i][j] == data[i][k] && IR[i][j] >= IR[i][k])
						{
							checkOrder[i]++;
						}
						/**/
					}
				}
			}
			else  if (rating_predict[i][j] != 1 && testing[i][j] < 1)  //belong to NW
			{
				NumofNW[i]++;
				for (int k = j + 1; k < NumofItem; k++)
				{
					if (testing[i][k] > 0)  //belong to Testing
					{
						if (data[i][k] >= data[i][j])
						//if (data[i][k] - data[i][j] >= 1)
						{
							checkOrder[i]++;
						}
						/**
						else if (data[i][k] == data[i][j] && IR[i][k] >= IR[i][j])
						{
							checkOrder[i]++;
						}
						/**/
					}
				}
			}
		}
		//計算個別DOA
		if (NumofNW[i] != 0 && NumofTesting[i] != 0)
		{
			DOA[i] = (float)checkOrder[i] / (NumofNW[i] * NumofTesting[i]);
		}
		else
		{
			unUsedData++;
		}
	}
	float TotalDOA = 0;
	for (int i = 0; i < NumofUser; i++)
	{
		TotalDOA += DOA[i];
	}
	if (NumofUser == unUsedData)
	{
		cout << "Testing data are contain in training data." << endl;
	}
	else
	{
		TotalDOA = TotalDOA / (NumofUser - unUsedData);
		cout << "Macro DOA = " << TotalDOA * 100 << "%" << endl;
	}
}
/**/
/**
void RMSE(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], float IR[NumofUser][NumofItem], int rating_predict[NumofUser][NumofItem])
{
	float sim[NumofUser][NumofUser];
	float ave[NumofUser];
	sim_table(data, IR, sim, ave);

	float RMSE[NumofUser];
	float total_RMSE = 0;

	for (int i = 0; i < NumofUser; i++)
	{
		RMSE[i] = predict_rating(data, testing, i, sim, ave, rating_predict);
		total_RMSE += RMSE[i];
	}
	total_RMSE = total_RMSE / NumofUser;
	cout << "ave RMSE = " << total_RMSE << endl;
}
/**/


void sim_table(float data[NumofUser][NumofItem], float IR[NumofUser][NumofItem], float sim[NumofUser][NumofUser], float ave[NumofUser])
{
	for (int i = 0; i < NumofUser; i++)
	{
		ave[i] = ave_rating(data, i);
		for (int j = i; j < NumofUser; j++)
		{
			if (i != j)
			{
				sim[i][j] = Similarity(IR[i], IR[j], NumofItem, 2);
				sim[j][i] = sim[i][j];
			}
			else
			{
				sim[i][j] = 1;
			}
		}
	}
}

float predict_rating(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], int UserNo, float sim[NumofUser][NumofUser], float ave[NumofUser], int rating_predict[NumofUser][NumofItem])
{
	float pre_rating = 0;
	float sum_sim = 0;

	int NumofTesting = 0;
	float RMSE = 0;
	MAE = 0;

	for (int i = 0; i < NumofItem; i++)
	{
		if (data[UserNo][i] == Unrating)
		{
			rating_predict[UserNo][i] = 1;
			for (int j = 0; j < NumofUser; j++)
			{
				if (UserNo != j && data[j][i] >= 1)  //可能會出現0.00000001之類的情況，所以避免使用>0
				{
					sum_sim += sim[UserNo][j];
					pre_rating += sim[UserNo][j] * (data[j][i]-ave[j]);
				}
			}
			pre_rating = ave[UserNo] + (pre_rating / sum_sim);
			//4捨5入
			if (pre_rating >= 1 && pre_rating <= 5)
			{
				/**/
				if ((pre_rating - (int)pre_rating) >= 0.5)
				{
					data[UserNo][i] = ((int)pre_rating) + 1;
				}
				else
				{
					data[UserNo][i] = (int)pre_rating;
				}
				/**/
			}
			else if (pre_rating > 5)
			{
				data[UserNo][i] = 5;
			}
			else
			{
				data[UserNo][i] = 1;
			}

			if (testing[UserNo][i] >= 1)
			{
				NumofTesting++;
				RMSE += pow(data[UserNo][i] - testing[UserNo][i], 2);
				int temp = data[UserNo][i] - testing[UserNo][i];
				if (temp >= 0)
					MAE += temp;
				else
					MAE -= temp;
			}
			sum_sim = 0;
			pre_rating = 0;
		}
	}
	if (NumofTesting != 0)
	{
		MAE = MAE / NumofTesting;
		return sqrt(RMSE / NumofTesting);
	}
	else//除非testing被training所包含，否則不會發生
	{
		system("pause");
		return 0;
	}
}

float MAE_predict_rating(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], int UserNo, float sim[NumofUser][NumofUser], float ave[NumofUser], int rating_predict[NumofUser][NumofItem])
{
	float pre_rating = 0;
	float sum_sim = 0;

	int NumofTesting = 0;
	float MAE = 0;

	for (int i = 0; i < NumofItem; i++)
	{
		if (data[UserNo][i] == 0)
		{
			rating_predict[UserNo][i] = 1;
			for (int j = 0; j < NumofUser; j++)
			{
				if (UserNo != j && data[j][i] >= 1)  //可能會出現0.00000001之類的情況，所以避免使用>0
				{
					sum_sim += sim[UserNo][j];
					pre_rating += sim[UserNo][j] * (data[j][i] - ave[j]);
				}
			}
			pre_rating = ave[UserNo] + (pre_rating / sum_sim);
			//4捨5入
			if (pre_rating >= 1 && pre_rating <= 5)
			{
				/**/
				if ((pre_rating - (int)pre_rating) >= 0.5)
				{
					data[UserNo][i] = ((int)pre_rating) + 1;
				}
				else
				{
					data[UserNo][i] = (int)pre_rating;
				}
				/**/
			}
			else if (pre_rating > 5)
			{
				data[UserNo][i] = 5;
			}
			else
			{
				data[UserNo][i] = 1;
			}

			if (testing[UserNo][i] >= 1)
			{
				NumofTesting++;
				int temp = data[UserNo][i] - testing[UserNo][i];
				if (temp >= 0)
					MAE += temp;
				else
					MAE -= temp;
			}
			sum_sim = 0;
			pre_rating = 0;
		}
	}
	if (NumofTesting != 0)
	{
		return MAE / NumofTesting;
	}
	else//除非testing被training所包含，否則不會發生
	{
		system("pause");
		return 0;
	}
}

float ave_rating(float data[NumofUser][NumofItem], int UserNo)
{
	float ave = 0;
	int Numof_rating = 0;
	for (int i = 0; i < NumofItem; i++)
	{
		if (data[UserNo][i] != 0)
		{
			Numof_rating++;
			ave += data[UserNo][i];
		}
	}
	return ave / Numof_rating;
}


void sfc_RMSE(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], float** IR, int Num_of_G, int rating_predict[NumofUser][NumofItem])
{
	float sim[NumofUser][NumofUser];
	float ave[NumofUser];
	sfc_sim_table(data, IR, sim, ave, Num_of_G);

	float RMSE[NumofUser];
	float union_MAE[NumofUser];
	float total_RMSE = 0;
	float total_MAE = 0;

	for (int i = 0; i < NumofUser; i++)
	{
		RMSE[i] = predict_rating(data, testing, i, sim, ave, rating_predict);
		union_MAE[i] = MAE;
		total_RMSE += RMSE[i];
		total_MAE += union_MAE[i];
	}
	total_RMSE = total_RMSE / NumofUser;
	total_MAE = total_MAE / NumofUser;
	cout << "ave RMSE = " << total_RMSE << endl;
	cout << "ave MAE = " << total_MAE << endl;
}

void sfc_MAE(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], float** IR, int Num_of_G, int rating_predict[NumofUser][NumofItem])
{
	float sim[NumofUser][NumofUser];
	float ave[NumofUser];
	sfc_sim_table(data, IR, sim, ave, Num_of_G);

	float MAE[NumofUser];
	float total_MAE = 0;

	for (int i = 0; i < NumofUser; i++)
	{
		MAE[i] = MAE_predict_rating(data, testing, i, sim, ave, rating_predict);
		total_MAE += MAE[i];
	}
	total_MAE = total_MAE / NumofUser;
	cout << "ave MAE = " << total_MAE << endl;
}

void sfc_sim_table(float data[NumofUser][NumofItem], float** IR, float sim[NumofUser][NumofUser], float ave[NumofUser], int Num_of_G)
{
	for (int i = 0; i < NumofUser; i++)
	{
		ave[i] = ave_rating(data, i);
		for (int j = i; j < NumofUser; j++)
		{
			if (i != j)
			{
				sim[i][j] = sfc_Similarity(IR[i], IR[j], Num_of_G);
				sim[j][i] = sim[i][j];
			}
			else
			{
				sim[i][j] = 1;
			}
		}
	}
}

/**
//*1
void TRtoIR(float itemData[][NumofTopic], float TR[][NumofTopic], float IR[][NumofItem])
{
	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			int NumofTopicofItem = 0;
			for (int k = 0; k < NumofTopic; k++)
			{
				if (itemData[j][k] != 0)
				{
					NumofTopicofItem++;
					IR[i][j] += TR[i][k];
				}
			}
			if (NumofTopicofItem != 0)
			{
				IR[i][j] = IR[i][j] / NumofTopicofItem;
			}
			else
			{
				cout << endl << "item " << j + 1 << " doesn't have any topic." << endl;
				system("pause");
			}
		}
	}
}/**/
