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

/**
//*1
static float ITsta[NumofItem][NumofTopic][NumofTopic];
void TopicCorrelationMatrix(float data[NumofUser][NumofItem], float itemData[NumofItem][NumofTopic], float sta[NumofTopic][NumofTopic])
{
	//item-topic，先建表，以節省後面的計算次數
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < NumofTopic - 1; j++)
		{
			for (int k = j + 1; k < NumofTopic; k++)
			{
				if (itemData[i][j] > 0 && itemData[i][k] > 0)
				{
					ITsta[i][j][k] = 1;    //ITsta(C-Topic)為對稱矩陣
					ITsta[i][k][j] = 1;
				}
				else
				{
					ITsta[i][j][k] = 0;    //ITsta(C-Topic)為對稱矩陣
					ITsta[i][k][j] = 0;
				}
			}
		}
	}
	//join user
	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			for (int l = j + 1; l < NumofItem; l++)
			{
				if (data[i][j] > 0 && data[i][l] > 0)  //user有選到這個物品，考慮放入評分影響?
				{
					//建立Correlation Matrix
					for (int k = 0; k < NumofTopic; k++)
					{
						for (int m = 0; m < NumofTopic; m++)
						{
							sta[k][m] += ITsta[j][k][m] * ITsta[l][k][m];
							sta[m][k] = sta[k][m];  //sta為對稱
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < NumofTopic; i++)
	{
		float sum = 0;
		for (int j = 0; j < NumofTopic; j++)
		{
			sum += sta[j][i];
		}

		for (int j = 0; j < NumofTopic; j++)
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
	for (int i = 0; i < NumofTopic; i++)
	{
	for (int j = 0; j < NumofTopic; j++)
	{
	cout << fixed << setprecision(3) << sta[i][j] << ", ";
	}
	cout << endl;
	}
	system("pause");
	/**
}

void TopicDynamicMatrix(float data[NumofUser][NumofItem], float itemData[NumofItem][NumofTopic], float dynTopic[NumofUser][NumofTopic])
{
	float dyn[NumofUser][NumofItem];
	for (int i = 0; i < NumofUser; i++)
	{
		float sum = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			sum += data[i][j];
		}

		for (int j = 0; j < NumofItem; j++)
		{
			dyn[i][j] = data[i][j] / sum;
			for (int k = 0; k < NumofTopic; k++)
			{
				if (itemData[j][k] != 0)
				{
					dynTopic[i][k] += dyn[i][j] * itemData[j][k];
				}
			}
		}
	}
}

void TopicRank(float IR[], float sta[][NumofTopic], float dyn[])
{
	/**
	for (int i = 0; i < NumofTopic; i++)
	{
	for (int j = 0; j < NumofTopic; j++)
	{
	//cout << fixed << setprecision(3) << sta[i][j] << ", ";
	}
	//cout << fixed << setprecision(3) << IR[i] << ", ";
	cout << fixed << setprecision(3) << dyn[i] << ", ";
	cout << endl;
	}
	system("pause");
	/**
	float computing[NumofTopic];
	float oldIR[NumofTopic];
	for (int i = 0; i < NumofTopic; i++)
	{
		oldIR[i] = IR[i];
	}

	TopicMulti(computing, sta, IR);
	/**
	for (int i = 0; i < NumofItem; i++)
	{
	cout << fixed << setprecision(5) << computingIR[i] << ", ";
	}
	cout << endl;
	system("pause");/**
	//multi(alpha, computing, NumofItem);//已放入ADD中，作加權加法
	Add(IR, computing, dyn, NumofTopic, alpha);
	if (Similarity(oldIR, IR, NumofItem, 1) > stable)
	{
		TopicRank(IR, sta, dyn);
	}
}/**/
