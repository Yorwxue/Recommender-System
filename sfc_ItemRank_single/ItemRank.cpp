#include"Header.h"

void ItemRank(float IR[], float sta[][NumofItem], float dyn[], int iterations[])
{
	iterations[0]++;
	/**
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			//cout << fixed << setprecision(3) << sta[i][j] << ", ";
		}
		//cout << fixed << setprecision(3) << IR[i] << ", ";
		cout << fixed << setprecision(3) << dyn[i] << ", ";
		cout << endl;
	}
	system("pause");
	/**/
	float computing[NumofItem];
	float oldIR[NumofItem];
	for (int i = 0; i < NumofItem; i++)
	{
		oldIR[i] = IR[i];
	}

	Multi(computing, sta, IR);
	/**
	for (int i = 0; i < NumofItem; i++)
	{
		cout << fixed << setprecision(5) << computingIR[i] << ", ";
	}
	cout << endl;
	system("pause");/**/
	//multi(alpha, computing, NumofItem);//已放入ADD中，作加權加法
	Add(IR, computing, dyn, NumofItem, alpha);
	if (Similarity(oldIR, IR, NumofItem, 1) > stable)
	{
		ItemRank(IR, sta, dyn, iterations);
	}
}

void fastItemRank(float IR[], float sta[][NumofItem], float dyn[], int times)
{
	times--;
	float tempIR_start[NumofItem];
	float tempIR_finish[NumofItem];
	float temp_alpha;

	for (int i = 0; i < NumofItem; i++)
	{
		IR[i] = 0;
		IR[i] = (1 - alpha) * dyn[i];
		tempIR_start[i] = IR[i];

	}
	
	while (times > 0)
	{
		temp_alpha = pow(alpha, fastItemRankIterationTimes - times);
		Multi(tempIR_finish, sta, tempIR_start);
		for (int i = 0; i < NumofItem; i++)
		{
			tempIR_start[i] = temp_alpha * tempIR_finish[i];
			IR[i] += tempIR_start[i];

		}
		times--;
	}
}

void spec_fastItemRank(float IR[], float spec_sta[][NumofItem][NumofItem], float sim[], float dyn[], int times)
{
	times--;
	float sta[NumofItem][NumofItem];
	float tempIR_start[NumofItem];
	float tempIR_finish[NumofItem];
	float temp_alpha;

	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			sta[i][j] = 0;
			for (int k = 0; k < Numofclass; k++)
			{
				sta[i][j] += sim[k] * spec_sta[k][i][j];
			}
		}
	}

	for (int i = 0; i < NumofItem; i++)
	{
		tempIR_start[i] = (1 - alpha) * dyn[i];
		IR[i] += tempIR_start[i];
	}

	while (times > 0)
	{
		temp_alpha = pow(alpha, fastItemRankIterationTimes - times);
		Multi(tempIR_finish, sta, tempIR_start);
		for (int i = 0; i < NumofItem; i++)
		{
			tempIR_start[i] = temp_alpha * tempIR_finish[i];
			IR[i] += tempIR_start[i];

		}
		times--;
	}
}

void sfc_fastItemRank(float* IR, float** sta, float* dyn, int times, int Num_of_G)
{
	times--;
	float* tempIR_start = new float[Num_of_G];
	float* tempIR_finish = new float[Num_of_G];
	float temp_alpha;

	for (int i = 0; i < Num_of_G; i++)
	{
		IR[i] = 0;
		IR[i] = (1 - alpha) * dyn[i];
		tempIR_start[i] = IR[i];

	}

	while (times > 0)
	{
		temp_alpha = pow(alpha, fastItemRankIterationTimes - times);
		Multi(tempIR_finish, sta, tempIR_start, Num_of_G);
		for (int i = 0; i < Num_of_G; i++)
		{
			tempIR_start[i] = temp_alpha * tempIR_finish[i];
			IR[i] += tempIR_start[i];

		}
		times--;
	}
}

void CorrelationMatrix(float data[NumofUser][NumofItem], float sta[NumofItem][NumofItem])
{

	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < NumofItem - 1; j++)
		{
			for (int k = j + 1; k < NumofItem; k++)
			{
				if (data[i][j] > 0 && data[i][k] > 0)
				{
					//sta(C)為對稱矩陣
					sta[j][k]++;    
					sta[k][j]++;

					//考慮評分影響   //下面這種方法的影響在小數點以下..
					//sta[j][k] += ((data[i][j] / data[i][k])>1 ? 1 : (data[i][j] / data[i][k]));
					//sta[k][j] += ((data[i][k] / data[i][j])>1 ? 1 : (data[i][k] / data[i][j]));
				}
			}
		}
	}
	/*正規化*/
	for (int i = 0; i < NumofItem; i++)
	{
		float sum = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			sum += sta[j][i];
		}

		for (int j = 0; j < NumofItem; j++)
		{
			if (sum != 0)
			{
				sta[j][i] = sta[j][i] / sum;
			}
			else
			{
				sta[j][i] = 0;
			}
		}
	}
	/*觀看結果*
#define viewNum 50
	cout << endl;
	int view[viewNum][3];
	for (int i = 0; i < viewNum; i++)
	{
		view[i][2] = -1;
	}
	int point[3];
	cout << "item 1, item 2 , joint times" << endl;
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = i + 1; j < NumofItem; j++)
		{
			point[0] = i + 1;
			point[1] = j + 1;
			point[2] = sta[i][j];
			insert(view, point, viewNum);
			//cout << fixed << setprecision(3) << sta[i][j] << ", ";
		}
		//cout << endl;
	}
	for (int i = 0; i < viewNum; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << view[i][j] << ", ";
		}
		cout << endl;
	}
	system("pause");
	/**/
}

/**
void spec_CorrelationMatrix(float data[NumofUser][NumofItem], float sta[Numofclass][NumofItem][NumofItem], int user_class[NumofUser])
{

	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < NumofItem - 1; j++)
		{
			for (int k = j + 1; k < NumofItem; k++)
			{
				if (data[i][j] > 0 && data[i][k] > 0)
				{
					//sta(C)為對稱矩陣
					sta[user_class[i]][j][k]++;
					sta[user_class[i]][k][j]++;

					//考慮評分影響   //下面這種方法的影響在小數點以下..
					//sta[j][k] += ((data[i][j] / data[i][k])>1 ? 1 : (data[i][j] / data[i][k]));
					//sta[k][j] += ((data[i][k] / data[i][j])>1 ? 1 : (data[i][k] / data[i][j]));
				}
			}
		}
	}
	//正規化
	for (int k = 0; k < Numofclass; k++)
	{
		for (int i = 0; i < NumofItem; i++)
		{
			float sum = 0;
			for (int j = 0; j < NumofItem; j++)
			{
				sum += sta[k][j][i];
			}

			for (int j = 0; j < NumofItem; j++)
			{
				if (sum != 0)
				{
					sta[k][j][i] = sta[k][j][i] / sum;
				}
				else
				{
					sta[k][j][i] = 0;
				}
			}
		}
	}
	//觀看結果
	#define viewNum 50
	cout << endl;
	int view[viewNum][3];
	for (int i = 0; i < viewNum; i++)
	{
	view[i][2] = -1;
	}
	int point[3];
	cout << "item 1, item 2 , joint times" << endl;
	for (int i = 0; i < NumofItem; i++)
	{
	for (int j = i + 1; j < NumofItem; j++)
	{
	point[0] = i + 1;
	point[1] = j + 1;
	point[2] = sta[i][j];
	insert(view, point, viewNum);
	//cout << fixed << setprecision(3) << sta[i][j] << ", ";
	}
	//cout << endl;
	}
	for (int i = 0; i < viewNum; i++)
	{
	for (int j = 0; j < 3; j++)
	{
	cout << view[i][j] << ", ";
	}
	cout << endl;
	}
	system("pause");
}
/**/

void sfc_CorrelationMatrix(float** data, float** sta, int Num_of_G)
{

	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < Num_of_G - 1; j++)
		{
			for (int k = j + 1; k < Num_of_G; k++)
			{
				if (data[i][j] > 0 && data[i][k] > 0)
				{
					//sta(C)為對稱矩陣
					sta[j][k]++;
					sta[k][j]++;
				}
			}
		}
	}
	/*正規化*/
	for (int i = 0; i < Num_of_G; i++)
	{
		float sum = 0;
		for (int j = 0; j < Num_of_G; j++)
		{
			sum += sta[j][i];
		}

		for (int j = 0; j < Num_of_G; j++)
		{
			if (sum != 0)
			{
				sta[j][i] = sta[j][i] / sum;
			}
			else
			{
				sta[j][i] = 0;
			}
		}
	}

}

/**
void sfc_spec_CorrelationMatrix(float** data, float** sta[Numofclass], int Num_of_G, int user_class[NumofUser])
{

	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < Num_of_G - 1; j++)
		{
			for (int k = j + 1; k < Num_of_G; k++)
			{
				if (data[i][j] > 0 && data[i][k] > 0)
				{
					//sta(C)為對稱矩陣
					//sta[user_class[i]][j][k]++;
					//sta[user_class[i]][k][j]++;

					//考慮評分影響
					sta[user_class[i]][j][k] += ((data[i][j] / data[i][k]) > 1 ? 1 : (data[i][j] / data[i][k]));
					sta[user_class[i]][k][j] += ((data[i][k] / data[i][j]) > 1 ? 1 : (data[i][k] / data[i][j]));
					//cout << data[i][j] / data[i][k] << ", " << data[i][k] / data[i][j] << endl;
				}
			}
		}
	}
	//正規化
	for (int k = 0; k < Numofclass; k++)
	{
		for (int i = 0; i < Num_of_G; i++)
		{
			float sum = 0;
			for (int j = 0; j < Num_of_G; j++)
			{
				sum += sta[k][j][i];
			}

			for (int j = 0; j < Num_of_G; j++)
			{
				if (sum != 0)
				{
					sta[k][j][i] = sta[k][j][i] / sum;
				}
				else
				{
					sta[k][j][i] = 0;
				}
			}
		}
	}
}
/**/

void insert(int a[][3], int b[3], int length)
{
	for (int i = length - 1; i >= 0; i--)
	{
		if (a[i][2] != -1)
		{
			if (b[2] > a[i][2])
			{
				if (i == length - 1)
				{
					for (int j = 0; j < 3; j++)
					{
						a[i][j] = b[j];
					}
				}
				else
				{
					for (int j = 0; j < 3; j++)
					{
						a[i + 1][j] = a[i][j];
						a[i][j] = b[j];
					}
				}
			}
			else
			{
				if (i < length - 1)
				{
					for (int j = 0; j < 3; j++)
					{
						a[i + 1][j] = b[j];
					}
				}
				break;
			}
		}
		else if (i == 0)
		{
			for (int j = 0; j < 3; j++)
			{
				a[i][j] = b[j];
			}
		}
	}
}

void DynamicMatrix(float data[NumofUser][NumofItem], float dyn[NumofItem], int userNo)
{
	float sum = 0;
	for (int j = 0; j < NumofItem; j++)
	{
		sum += data[userNo][j];
	}

	for (int j = 0; j < NumofItem; j++)
	{
		if (sum != 0)
		{
			dyn[j] = data[userNo][j] / sum;
		}
		else
		{
			dyn[j] = 0;
		}
		//cout << data[i][j] << ", ";
	}
	//cout << endl;
}

void spec_DynamicMatrix(float data[NumofUser][NumofItem], float dyn[NumofItem], int userNo)
{
	float sum = 0;
	for (int j = 0; j < NumofItem; j++)
	{
		sum += data[userNo][j];
	}

	for (int j = 0; j < NumofItem; j++)
	{
		if (sum != 0)
		{
			dyn[j] += data[userNo][j] / sum;
		}
		else
		{
			dyn[j] += 0;
		}
		//cout << data[i][j] << ", ";
	}
	//cout << endl;
}

void sfc_DynamicMatrix(float** data, float* dyn, int userNo, int Num_of_G)
{
	float sum = 0;
	for (int j = 0; j < Num_of_G; j++)
	{
		sum += data[userNo][j];
	}

	for (int j = 0; j < Num_of_G; j++)
	{
		if (sum != 0)
		{
			dyn[j] = data[userNo][j] / sum;
		}
		else
		{
			dyn[j] = 0;
		}
		//cout << data[i][j] << ", ";
	}
	//cout << endl;
}

/**
void spec_sfc_fastItemRank(float* IR, float** spec_sta[Numofclass], float sim[], float dyn[], int times, int Num_of_G)
{
	times--;
	float* tempIR_start = new float[Num_of_G];
	float* tempIR_finish = new float[Num_of_G];
	float temp_alpha;


	float** sta = (float**)new2d(Num_of_G, Num_of_G, sizeof(float));

	for (int i = 0; i < Num_of_G; i++)
	{
		for (int j = 0; j < Num_of_G; j++)
		{
			sta[i][j] = 0;
			for (int k = 0; k < Numofclass; k++)
			{
				sta[i][j] += sim[k] * spec_sta[k][i][j];
			}
		}
	}

	for (int i = 0; i < Num_of_G; i++)
	{
		IR[i] = 0;
		IR[i] = (1 - alpha) * dyn[i];
		tempIR_start[i] = IR[i];

	}

	while (times > 0)
	{
		temp_alpha = pow(alpha, fastItemRankIterationTimes - times);
		Multi(tempIR_finish, sta, tempIR_start, Num_of_G);
		for (int i = 0; i < Num_of_G; i++)
		{
			tempIR_start[i] = temp_alpha * tempIR_finish[i];
			IR[i] += tempIR_start[i];

		}
		times--;
	}
}
/**/

void sfc_cluster_CorrelationMatrix(float** data, float** sta, int Num_of_G)
{

	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < Num_of_G - 1; j++)
		{
			for (int k = j + 1; k < Num_of_G; k++)
			{
				if (data[i][j] > 0 && data[i][k] > 0)
				{
					//sta(C)為對稱矩陣
					//sta[j][k]++;
					//sta[k][j]++;

					//考慮評分影響
					sta[j][k] += ((data[i][j] / data[i][k]) > 1 ? 1 : (data[i][j] / data[i][k]));
					sta[k][j] += ((data[i][k] / data[i][j]) > 1 ? 1 : (data[i][k] / data[i][j]));
				}
			}
		}
	}
	/*正規化*/
	for (int i = 0; i < Num_of_G; i++)
	{
		float sum = 0;
		for (int j = 0; j < Num_of_G; j++)
		{
			sum += sta[j][i];
		}

		for (int j = 0; j < Num_of_G; j++)
		{
			if (sum != 0)
			{
				sta[j][i] = sta[j][i] / sum;
			}
			else
			{
				sta[j][i] = 0;
			}
		}
	}

}
