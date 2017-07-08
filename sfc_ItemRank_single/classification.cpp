#include"Header.h"

void classification(float data[NumofUser][NumofItem], int user_class[NumofUser], int Numofuser_in_class[Numofclass], float class_center[Numofclass][NumofItem], float class_sim[NumofUser][Numofclass])
{
	int initial_center[Numofclass] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	/*隨機起始中心*
	cout << endl;
	cout << "User as initial center is ";
	for (int i = 0; i < Numofclass; i++)
	{
		initial_center[i] = RandomNumber(0, NumofUser - 1);
		int j = i - 1;
		while (j >= 0)
		{
			if (initial_center[i] == initial_center[j])
			{
				initial_center[i] = RandomNumber(0, NumofUser - 1);
				j = i - 1;
			}
			else
				j--;
		}
		cout << initial_center[i] << "  ";
	}
	cout << endl;
	/**/

	for (int i = 0; i < NumofUser; i++)
	{
		int flag = 0;
		/**
		for (int j = 0; j < Numofclass; j++)
		{
		if (class_center[j][0] == -1)
		{
		user_class[i] = j;
		for (int k = 0; k < NumofItem; k++)
		{
		class_center[j][k] = data[i][k];
		}
		class_sim[i][j] = 1;
		Numofuser_in_class[j]++;
		flag = 1;

		if (j == Numofclass-1)
		{
		for (int l = 0; l < Numofclass; l++)
		{
		for (int m = 0; m < Numofclass; m++)
		{
		if (l != m)
		class_sim[l][m] = Similarity(data[l], class_center[m], NumofItem, 2);//Cosine similarity
		}
		}
		}

		break;
		}
		}/**/

		/**/
		if (i == 0)
		{
			for (int j = 0; j < Numofclass; j++)
			{
				user_class[initial_center[j]] = j;
				for (int k = 0; k < NumofItem; k++)
				{
					class_center[j][k] = data[initial_center[j]][k];
				}
				class_sim[initial_center[j]][j] = 1;
				Numofuser_in_class[j]++;

				if (j == Numofclass - 1)
				{
					for (int l = 0; l < Numofclass; l++)
					{
						for (int m = 0; m < Numofclass; m++)
						{
							if (l != m)
								class_sim[l][m] = Similarity(data[l], class_center[m], NumofItem, 2);//Cosine similarity
						}
					}
				}
			}
		}/**/

		for (int j = 0; j < Numofclass; j++)
		{
			if (i == initial_center[j])
			{
				flag = 1;
			}
		}

		if (flag != 1)
		{
			float most_sim = 0;
			for (int j = 0; j < Numofclass; j++)
			{
				class_sim[i][j] = Similarity(data[i], class_center[j], NumofItem, 2);//Cosine similarity
				if (class_sim[i][j] > most_sim)
				{
					most_sim = class_sim[i][j];
					user_class[i] = j;
				}
			}
			if (most_sim == 0) //跟大家都不像，隨機分到其中一個
			{
				user_class[i] = RandomNumber(0, Numofclass - 1);
			}
			for (int k = 0; k < NumofItem; k++)
			{
				class_center[user_class[i]][k] = (class_center[user_class[i]][k] * Numofuser_in_class[user_class[i]] + data[i][k]) / (Numofuser_in_class[user_class[i]] + 1);
			}
			Numofuser_in_class[user_class[i]]++;
		}
	}

	//重算相似度
	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < Numofclass; j++)
		{
			class_sim[i][j] = Similarity(data[i], class_center[j], NumofItem, 2);//Cosine similarity
		}
	}

	//觀看結果
	/**
	for (int i = 0; i < Numofclass; i++)
	{
		cout << "第" << i + 1 << "個class有" << Numofuser_in_class[i] << "人" << endl;
	}/**/

	//重新分群
	/**
	float change_ratio;
	do
	{
		change_ratio = 0;
		for (int i = 0; i < NumofUser; i++)
		{
			float most_sim = 0;
			int last_user_class = user_class[i];
			for (int j = 0; j < Numofclass; j++)
			{
				if (class_sim[i][j] > most_sim)
				{
					most_sim = class_sim[i][j];
					user_class[i] = j;
				}
			}
			if (user_class[i] == last_user_class) //所屬群不變動
			{
			}
			else        //所屬群變動
			{
				change_ratio++;
				//修正原群中心
				for (int k = 0; k < NumofItem; k++)
				{
					class_center[last_user_class][k] = (class_center[last_user_class][k] * Numofuser_in_class[last_user_class] - data[i][k]) / (Numofuser_in_class[last_user_class] - 1);
				}
				Numofuser_in_class[last_user_class]--;

				//修正新群中心
				for (int k = 0; k < NumofItem; k++)
				{
					class_center[user_class[i]][k] = (class_center[user_class[i]][k] * Numofuser_in_class[user_class[i]] + data[i][k]) / (Numofuser_in_class[user_class[i]] + 1);
				}
				Numofuser_in_class[user_class[i]]++;
			}
		}
		for (int i = 0; i < NumofUser; i++)
		{
			for (int j = 0; j < Numofclass; j++)
			{
				class_sim[i][j] = Similarity(data[i], class_center[j], NumofItem, 2);//Cosine similarity
			}
		}
		change_ratio = change_ratio / NumofUser;
	} while (change_ratio > 0.01);
	/**/
}