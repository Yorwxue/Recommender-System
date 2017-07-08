#include"Header.h"
#include"object_class.cpp"

#define exp 2.718281828


//#define direct_c_cluster_0 0.5
//#define direct_G_cluster_threshold 0.2

#define c_cluster_0 0.5
#define G_cluster_threshold 0.7625

#define c_0 0.5
#define G_threshold 0.4

void* sfc(float data[NumofUser][NumofItem], int user_class[NumofUser], int* num_of_G, int num_of_class)
{
	float** sample = (float**)new2d(num_of_class, NumofItem,sizeof(float));

	List<int>* G = NULL;
	item_sample(data, user_class, sample, num_of_class);

	/*for check(若training很少，有些ITEM可能不會出現過)*
	for (int i = 0; i < NumofItem; i++)
	{
		float check = 0;
		for (int j = 0; j < Numofclass; j++)
		{
			check += sample[j][i];
		}
		if (check >= 1.00001)
		{
			cout << check << ", ";
		}
		else if (check <= 0.99999)
		{
			cout << check << ", ";
		}
	}/**/

	for (int i = 0; i < NumofItem; i++)
	{
		if (G == NULL)
		{
			G = new List<int>();
			G->ObjectPointer = new int[NumofItem];
			array_initial(G->ObjectPointer, NumofItem, 0);
			G->ObjectPointer[i] = 1;
			G_update(G->c, G->m, sample, G->ObjectPointer, G->Num_xi_in_G, i, num_of_class);
			array_initial(G->c, num_of_class, c_0);
		}
		else
		{
			//計算與現有群的歸屬度
			float* xi = new float[num_of_class];
			float xi_m_G;     //xi與現有G的歸屬度
			float most_similarity = -1;
			int xi_G = -1;  //xi分到哪個G

			for (int j = 0; j < num_of_class; j++)  //取出xi資料(某個item在各個class的資料)
			{
				xi[j] = sample[j][i];
			}

			for (int j = 0; j < (G->Length + 1); j++)
			{
				xi_m_G = membership(G->ListNoShift(j)->c, G->ListNoShift(j)->m, xi, num_of_class);
				//是否達門檻
				if (G_threshold < xi_m_G)
				{
					if (most_similarity == -1)//決定xi歸屬
					{
						most_similarity = xi_m_G;
						xi_G = j;
					}
					else if (most_similarity < xi_m_G)
					{
						most_similarity = xi_m_G;
						xi_G = j;
					}
				}
			}
			//xi歸屬運算
			if (xi_G == -1)//現有G，都與xi差異很大，建立新G
			{
				G->ListNoShift(G->Length)->InsertElement(new int[NumofItem]);
				array_initial(G->ListNoShift(G->Length)->ObjectPointer, NumofItem, 0);
				G->ListNoShift(G->Length)->ObjectPointer[i] = 1;
				G_update(G->ListNoShift(G->Length)->c, G->ListNoShift(G->Length)->m, sample, G->ListNoShift(G->Length)->ObjectPointer, G->ListNoShift(G->Length)->Num_xi_in_G, i, num_of_class);
				array_initial(G->ListNoShift(G->Length)->c, num_of_class, c_0);
			}
			else//加入現有的G
			{
				G->ListNoShift(xi_G)->ObjectPointer[i] = 1;
				G->ListNoShift(xi_G)->Num_xi_in_G++;
				G_update(G->ListNoShift(xi_G)->c, G->ListNoShift(xi_G)->m, sample, G->ListNoShift(xi_G)->ObjectPointer, G->ListNoShift(xi_G)->Num_xi_in_G, i, num_of_class);
			}
		}

	}
	cout << "Num of G is " << G->Length + 1 << endl;

	float** new_data = (float**)new2d(NumofItem,G->Length+1,sizeof(float));

	for (int i = 0; i < NumofItem; i++)
	{
		float* xi=new float[num_of_class];
		for (int j = 0; j < num_of_class; j++)  //取出xi資料(某個item在各個class的資料)
		{
			xi[j] = sample[j][i];
		}
		for (int j = 0; j < (G->Length + 1); j++)
		{
			new_data[i][j] = membership(G->ListNoShift(j)->c, G->ListNoShift(j)->m, xi, num_of_class);
		}
	}

	*num_of_G = G->Length + 1;

	/*觀看資料正確性*
	for (int i = 0; i < 10; i++)
	{
	for (int j = 0; j < 10; j++)
	{
		cout << new_data[i][j] << ", ";
	}
	}
	/**/
    //system("pause");
	return new_data;
}


void item_sample(float data[NumofUser][NumofItem], int user_class[NumofUser], float** sample, int num_of_class)
{
	int Num_of_item_appear[NumofItem];

	for (int j = 0; j < NumofItem; j++)
	{
		Num_of_item_appear[j] = 0;
		for (int i = 0; i < num_of_class; i++)
		{
			sample[i][j] = 0;
		}
	}

	for (int j = 0; j < NumofItem; j++)
	{
		for (int i = 0; i < NumofUser; i++)
		{
			sample[user_class[i]][j] += data[i][j];
			Num_of_item_appear[j] += data[i][j];
		}
		if (Num_of_item_appear[j] != 0)
		{
			for (int i = 0; i < num_of_class; i++)
			{
				sample[i][j] = sample[i][j] / Num_of_item_appear[j];
			}
		}
		else
		{
			for (int i = 0; i < num_of_class; i++)
			{
				sample[i][j] = 0;
			}
		}
	}
}

void G_update(float* c, float* m, float** x, int G[NumofItem], int Num_of_item_in_G, int new_entry,int num_of_class)
{
	/**
	mean_vector(m, x, G, Num_of_item_in_G);
	standard_deviation_vector(c, m, x, G, Num_of_item_in_G);
	/**/

	/**/
	float* new_x = new float[num_of_class];
	for (int i = 0; i < num_of_class; i++)
	{
		new_x[i] = x[i][new_entry];
	}
	mean_vector_update(new_x, m, num_of_class, Num_of_item_in_G);
	deviation_upddate(c, m, new_x, Num_of_item_in_G, num_of_class, c_0);
	/**/
}
/**
void mean_vector(float m[Numofclass], float x[Numofclass][NumofItem], int G[NumofItem], int Num_of_item_in_G)
{
	for (int i = 0; i < Numofclass; i++)
	{
		m[i] = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			if (G[j] == 1)
			{
				m[i] += x[i][j];
			}
		}
		m[i] = m[i] / Num_of_item_in_G;
	}
}

void standard_deviation_vector(float c[Numofclass], float m[Numofclass], float x[Numofclass][NumofItem], int G[NumofItem], int Num_of_item_in_G)
{
	for (int i = 0; i < Numofclass; i++)
	{
		c[i] = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			if (G[j] == 1)
			{
				c[i] += pow(x[i][j] - m[i], 2);
			}
		}
		c[i] = sqrt(c[i] / Num_of_item_in_G);
	}
}
/**/
float membership(float c[], float m[], float xi[], int num_of_class)
{
	float mem = 0;
	for (int i = 0; i < num_of_class; i++)
	{
		if (i == 0)
		{
			if (c[i] == 0)  //發生在整個G中的xi都長的一模一樣時
			{
				mem = 1;
			}
			else
			{
				mem = pow(exp, (-pow(((xi[i] - m[i]) / c[i]), 2)));
			}
		}
		else
		{
			if (c[i] != 0)
			{
				mem = mem*pow(exp, (-pow(((xi[i] - m[i]) / c[i]), 2)));
			}
		}
	}
	if (!(mem <= 1))
	{
		system("pause");
	}
	return mem;
}




//void new_G_cluster(float data[NumofUser][NumofItem], float c[NumofItem], float m[NumofItem], int G[NumofUser], int Num_of_item_in_G);
void G_cluster_update(float data[NumofUser][NumofItem], float c[NumofItem], float m[NumofItem], int G[NumofUser], int Num_of_item_in_G, int new_entry);
void cluster_mean_vector(float data[NumofUser][NumofItem], float m[NumofItem], int G[NumofUser], int Num_of_item_in_G);
void cluster_standard_deviation_vector(float data[NumofUser][NumofItem], float c[NumofItem], float m[NumofItem], int G[NumofUser], int Num_of_item_in_G);
float cluster_membership(float c[NumofItem], float m[NumofItem], float xi[NumofItem]);

//直接對item作ssc
//void G_direct_cluster_update(float data[NumofItem][NumofUser], float c[NumofUser], float m[NumofUser], int G[NumofItem], int Num_of_item_in_G, int new_entry);
//float direct_cluster_membership(float c[NumofUser], float m[NumofUser], float xi[NumofUser]);

float** sfc_cluster(float data[NumofUser][NumofItem], int* num_of_G, int user_class[NumofUser])
{
	List_G_cluster<int>* G = NULL;
	for (int i = 0; i < NumofUser; i++)
	{
		if (G == NULL)
		{
			G = new List_G_cluster<int>();
			G->ObjectPointer = new int[NumofUser];
			array_initial(G->ObjectPointer, NumofUser, 0);
			G->ObjectPointer[i] = 1;
			//new_G_cluster(data, G->c, G->m, G->ObjectPointer, G->Num_xi_in_G);
			G_cluster_update(data, G->c, G->m, G->ObjectPointer, G->Num_xi_in_G, i);
			array_initial(G->c, NumofItem, c_cluster_0);
			user_class[i] = 0;
		}
		else
		{
			//計算與現有群的歸屬度
			float xi_m_G;     //xi與現有G的歸屬度
			float most_similarity = -1;
			int xi_G = -1;  //xi分到哪個G

			for (int j = 0; j < (G->Length + 1); j++)
			{
				xi_m_G = cluster_membership(G->ListNoShift(j)->c, G->ListNoShift(j)->m, data[i]);
				//是否達門檻
				if (G_cluster_threshold < xi_m_G)
				{
					if (most_similarity == -1)//決定xi歸屬
					{
						most_similarity = xi_m_G;
						xi_G = j;
					}
					else if (most_similarity < xi_m_G)
					{
						most_similarity = xi_m_G;
						xi_G = j;
					}
				}
			}
			
			user_class[i] = xi_G;

			//xi歸屬運算
			if (xi_G == -1)//現有G，都與xi差異很大，建立新G
			{
				user_class[i] = G->Length + 1;

				G->ListNoShift(G->Length)->InsertElement(new int[NumofUser]);
				array_initial(G->ListNoShift(G->Length)->ObjectPointer, NumofUser, 0);
				G->ListNoShift(G->Length)->ObjectPointer[i] = 1;
				//new_G_cluster(data, G->ListNoShift(G->Length)->c, G->ListNoShift(G->Length)->m, G->ListNoShift(G->Length)->ObjectPointer, G->ListNoShift(G->Length)->Num_xi_in_G);
				G_cluster_update(data, G->ListNoShift(G->Length)->c, G->ListNoShift(G->Length)->m, G->ListNoShift(G->Length)->ObjectPointer, G->ListNoShift(G->Length)->Num_xi_in_G,i);
				array_initial(G->ListNoShift(G->Length)->c, NumofItem, c_cluster_0);
			}
			else//加入現有的G
			{
				G->ListNoShift(xi_G)->ObjectPointer[i] = 1;
				G->ListNoShift(xi_G)->Num_xi_in_G++;
				G_cluster_update(data, G->ListNoShift(xi_G)->c, G->ListNoShift(xi_G)->m, G->ListNoShift(xi_G)->ObjectPointer, G->ListNoShift(xi_G)->Num_xi_in_G, i);
			}
		}

	}
	cout << "Num of class is " << G->Length + 1 << endl;

	*num_of_G = G->Length + 1;
	/**/
	float** sfc_class_sim = (float**)new2d(NumofUser, *num_of_G, sizeof(float));
	/**
	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < *num_of_G; j++)
		{
			sfc_class_sim[i][j] = cluster_membership(G->ListNoShift(j)->c, G->ListNoShift(j)->m, data[i]);
		}
	}
	/**/
	/*觀看資料正確性*
	for (int i = 0; i < 10; i++)
	{
	for (int j = 0; j < 10; j++)
	{
	cout << new_data[i][j] << ", ";
	}
	}
	/**/
	//system("pause");
	return sfc_class_sim;
}

/**
void new_G_cluster(float data[NumofUser][NumofItem], float c[NumofItem], float m[NumofItem], int G[NumofUser], int Num_of_item_in_G)
{
	cluster_mean_vector(data, m, G, Num_of_item_in_G);
	cluster_standard_deviation_vector(data, c, m, G, Num_of_item_in_G);
}
/**/

void G_cluster_update(float data[NumofUser][NumofItem], float c[NumofItem], float m[NumofItem], int G[NumofUser], int Num_of_item_in_G, int new_entry)
{
	//cluster_mean_vector(data, m, G, Num_of_item_in_G);
	//cluster_standard_deviation_vector(data, c, m, G, Num_of_item_in_G);

	mean_vector_update(data[new_entry], m, NumofItem, Num_of_item_in_G);
	deviation_upddate(c, m, data[new_entry], Num_of_item_in_G, NumofItem,c_cluster_0);
}

/**
void cluster_mean_vector(float data[NumofUser][NumofItem], float m[NumofItem], int G[NumofUser], int Num_of_item_in_G)
{
	for (int i = 0; i < NumofItem; i++)
	{
		m[i] = 0;
		for (int j = 0; j < NumofUser; j++)
		{
			if (G[j] == 1)
			{
				m[i] += data[j][i];
			}
		}
		m[i] = m[i] / Num_of_item_in_G;
	}
}
/**/
/**
void cluster_standard_deviation_vector(float data[NumofUser][NumofItem], float c[NumofItem], float m[NumofItem], int G[NumofUser], int Num_of_item_in_G)
{
	for (int i = 0; i < NumofItem; i++)
	{
		c[i] = 0;
		for (int j = 0; j < NumofUser; j++)
		{
			if (G[j] == 1)
			{
				c[i] += pow(data[j][i] - m[i], 2);
			}
		}
		c[i] = sqrt(c[i] / Num_of_item_in_G);
	}
}
/**/
float cluster_membership(float c[NumofItem], float m[NumofItem], float xi[NumofItem])
{
	float mem = 0;
	//float test;
	//float test2;
	for (int i = 0; i < NumofItem; i++)
	{
		if (i == 0)
		{
			if (c[i] == 0)  //發生在整個G中的xi都長的一模一樣時
			{
				mem = 1;
			}
			else
			{
				//mem = pow(exp, (-pow(((xi[i] - m[i]) / c[i]), 2)));
				mem = -pow(((xi[i] - m[i]) / c[i]), 2);
			}
		}
		else
		{
			if (c[i] != 0)
			{
				//float test = pow(exp, (-pow(((xi[i] - m[i]) / c[i]), 2)));
				//mem = mem*pow(exp, (-pow(((xi[i] - m[i]) / c[i]), 2)));
				//test = mem;
				//test2 = pow(((xi[i] - m[i]) / c[i]), 2);
				mem = mem - pow(((xi[i] - m[i]) / c[i]), 2);
			}
		}
		if (!(mem <= 1))
		{
			system("pause");
		}
	}
	if (!(mem <= 1))
	{
		system("pause");
	}

	mem = pow(exp, mem);

	return mem;
}

void mean_vector_update(float x[], float m[], int size, int Num_of_Entry_in_G)
{
	//float test;
	for (int i = 0; i < size; i++)
	{
		//test = m[i];
		m[i] = (Num_of_Entry_in_G*m[i] + x[i]) / (Num_of_Entry_in_G + 1);

		/*檢查是否為數字*
		if (!(m[i] <= 1 || m[i] > 1)) 
		{
			system("pause");
		}
		/**/
	}
}

void deviation_upddate(float c[], float m[], float x[], int Num_of_Entry_in_G, int size, float C)
{
	for (int i = 0; i < size; i++)
	{
		float A = ((Num_of_Entry_in_G - 1)*pow((c[i] - C), 2) + Num_of_Entry_in_G*pow(m[i], 2) + pow(x[i], 2)) / Num_of_Entry_in_G;
		float B = ((Num_of_Entry_in_G + 1) / Num_of_Entry_in_G)*pow(((Num_of_Entry_in_G*m[i] + x[i]) / (Num_of_Entry_in_G + 1)), 2);
		c[i] = sqrt(A - B) + C;
	}
}

//for direct
/**
float** sfc_direct_cluster(float data[NumofUser][NumofItem], int* num_of_G)
{
	List_G_cluster<int>* G = NULL;

	//item是column，非row
	float ItemData[NumofItem][NumofUser];
	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j<NumofItem; j++)
		{
			ItemData[j][i]=data[i][j];
		}
	}

	for (int i = 0; i < NumofItem; i++)
	{
		if (G == NULL)
		{
			G = new List_G_cluster<int>();
			G->ObjectPointer = new int[NumofItem];
			array_initial(G->ObjectPointer, NumofItem, 0);
			G->ObjectPointer[i] = 1;
			G_direct_cluster_update(ItemData, G->c, G->m, G->ObjectPointer, G->Num_xi_in_G, i);
			array_initial(G->c, NumofUser, direct_c_cluster_0);
		}
		else
		{
			//計算與現有群的歸屬度
			float xi_m_G;     //xi與現有G的歸屬度
			float most_similarity = -1;
			int xi_G = -1;  //xi分到哪個G

			for (int j = 0; j < (G->Length + 1); j++)
			{
				xi_m_G = direct_cluster_membership(G->ListNoShift(j)->c, G->ListNoShift(j)->m, ItemData[i]);
				//是否達門檻
				if (direct_G_cluster_threshold < xi_m_G)
				{
					if (most_similarity == -1)//決定x_i歸屬
					{
						most_similarity = xi_m_G;
						xi_G = j;
					}
					else if (most_similarity < xi_m_G)
					{
						most_similarity = xi_m_G;
						xi_G = j;
					}
				}
			}


			//xi歸屬運算
			if (xi_G == -1)//現有G，都與xi差異很大，建立新G
			{
				G->ListNoShift(G->Length)->InsertElement(new int[NumofItem]);
				array_initial(G->ListNoShift(G->Length)->ObjectPointer, NumofItem, 0);
				G->ListNoShift(G->Length)->ObjectPointer[i] = 1;
				G_direct_cluster_update(ItemData, G->ListNoShift(G->Length)->c, G->ListNoShift(G->Length)->m, G->ListNoShift(G->Length)->ObjectPointer, G->ListNoShift(G->Length)->Num_xi_in_G, i);
				array_initial(G->ListNoShift(G->Length)->c, NumofUser, c_cluster_0);
			}
			else//加入現有的G
			{
				G->ListNoShift(xi_G)->ObjectPointer[i] = 1;
				G->ListNoShift(xi_G)->Num_xi_in_G++;
				G_direct_cluster_update(ItemData, G->ListNoShift(xi_G)->c, G->ListNoShift(xi_G)->m, G->ListNoShift(xi_G)->ObjectPointer, G->ListNoShift(xi_G)->Num_xi_in_G, i);
			}
		}

	}
	cout << "Num of direct class is " << G->Length + 1 << endl;

	*num_of_G = G->Length + 1;

	float** sfc_class_sim = (float**)new2d(NumofItem, *num_of_G, sizeof(float));
	
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < *num_of_G; j++)
		{
			sfc_class_sim[i][j] = direct_cluster_membership(G->ListNoShift(j)->c, G->ListNoShift(j)->m, ItemData[i]);
		}
	}
	
	return sfc_class_sim;
}
void G_direct_cluster_update(float data[NumofItem][NumofUser], float c[NumofUser], float m[NumofUser], int G[NumofItem], int Num_of_item_in_G, int new_entry)
{
	mean_vector_update(data[new_entry], m, NumofUser, Num_of_item_in_G);
	deviation_upddate(c, m, data[new_entry], Num_of_item_in_G, NumofUser, c_cluster_0);
}
float direct_cluster_membership(float c[NumofUser], float m[NumofUser], float xi[NumofUser])
{
	float mem = 0;
	//float test;
	//float test2;
	for (int i = 0; i < NumofUser; i++)
	{
		if (i == 0)
		{
			if (c[i] == 0)  //發生在整個G中的xi都長的一模一樣時
			{
				mem = 1;
			}
			else
			{
				//mem = pow(exp, (-pow(((xi[i] - m[i]) / c[i]), 2)));
				mem = -pow(((xi[i] - m[i]) / c[i]), 2);
			}
		}
		else
		{
			if (c[i] != 0)
			{
				//float test = pow(exp, (-pow(((xi[i] - m[i]) / c[i]), 2)));
				//mem = mem*pow(exp, (-pow(((xi[i] - m[i]) / c[i]), 2)));
				//test = mem;
				//test2 = pow(((xi[i] - m[i]) / c[i]), 2);
				mem = mem - pow(((xi[i] - m[i]) / c[i]), 2);
			}
		}
		if (!(mem <= 1))
		{
			system("pause");
		}
	}
	if (!(mem <= 1))
	{
		system("pause");
	}

	mem = pow(exp, mem);

	return mem;
}
/**/