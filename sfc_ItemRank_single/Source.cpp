#include"Header.h"

#include"rejtrix.h"

//float spec_sta[Numofclass][NumofItem][NumofItem];

void main()
{
	float executing_time = 0;
	clock_t start, process, end;
	start = clock();
	float initial = 0;        //1.0 / NumofItem;//�쫬�ϥ�1.0 / NumofItem; �ֳt���ϥ�0
	//float initialTopic = 1.0 // NumofTopic;
	float data[NumofUser][NumofItem],
		testing[NumofUser][NumofItem],
		IR[NumofUser][NumofItem],
		//sta[NumofItem][NumofItem],
		dyn[NumofUser][NumofItem];         //�ɤJ�ӧOuser�������v�T
		//spec_dyn[Numofclass][NumofItem],
		//spec_IR[Numofclass][NumofItem];
	//float class_center[Numofclass][NumofItem];
	int user_class[NumofUser];
	//float class_sim[NumofUser][Numofclass];
	//int Numofuser_in_class[Numofclass];
	int rating_predict[NumofUser][NumofItem];      //training�����ʤ֡A�A�g�ѹw���ɤW������
	//float spec_sta[Numofclass][NumofItem][NumofItem];

	//�[���
	//int iterations[NumofUser];

	/*�[�ݸ�ƥ��T��*
	for (int i = 0; i < NumofItem; i++)
	{
	for (int j = 0; j < NumofItem; j++)
	{
	//cout << fixed << setprecision(3) << sta[i][j] << ", ";
	}
	cout << fixed << setprecision(3) << IR[i] << ", ";
	cout << endl;
	}
	system("pause");
	/**/

	//Initial
	/**
	for (int i = 0; i < Numofclass; i++)
	{
		Numofuser_in_class[i] = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			class_center[i][j] = -1;
			//spec_dyn[i][j] = 0;
		}
		for (int j = 0; j < NumofUser; j++)
		{
			class_sim[j][i] = -1;
		}
	}/**/

	for (int i = 0; i < NumofUser; i++)
	{
		//iterations[i] = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			IR[i][j] = initial;
			data[i][j] = Unrating;
			testing[i][j] = 0;
		}
	}
	/**
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			//sta[i][j] = 0;
			for (int k = 0; k < Numofclass; k++)
			{
				spec_sta[k][i][j] = 0;
			}
		}
	}
	/**/
	//initial finish

	//read file
	cout << "training data .. ";
	process = clock();
	Read("train.txt", data);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;

	/**
	//*1
	cout << "item data .. ";
	process = clock();
	ReadItem("item.txt", itemData);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	/**/
	//read finish


	float normalize_data[NumofUser][NumofItem];
	/*normalize*/
	for (int i = 0; i < NumofUser; i++)
	{
		int sum = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			sum += data[i][j];
		}
		for (int j = 0; j < NumofItem; j++)
		{
			normalize_data[i][j] = data[i][j] / sum;
		}
	}
	/**/

	/*normalize2*
	for (int i = 0; i < NumofItem; i++)
	{
		int sum = 0;
		for (int j = 0; j < NumofUser; j++)
		{
			sum += data[j][i];
		}
		for (int j = 0; j < NumofUser; j++)
		{
			if (sum != 0)
			{
				normalize_data[j][i] = data[j][i] / sum;
			}
			else
			{
				normalize_data[j][i] = 0;
			}
		}
	}
	/**/

	/**/
	cout << "classfication .. ";
	process = clock();

	//classification(data, user_class, Numofuser_in_class, class_center, class_sim);  //k-means

	int num_of_class;
	float** sfc_class_sim = sfc_cluster(normalize_data, &num_of_class, user_class);

	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	executing_time += (float)((end - process) / CLOCKS_PER_SEC);
	/**/

	/**/
	cout << "sfc .. " << endl;
	process = clock();
	int num_of_G;
	float** data_trans = (float**)sfc(data, user_class, &num_of_G, num_of_class);  //h:NumofItem, w:G->Length+1, type:float
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	executing_time += (float)((end - process) / CLOCKS_PER_SEC);
	float** new_data = (float**)new2d(NumofUser, num_of_G, sizeof(float));
	/**/

	/*���եΡA�������~����*
	cout << "direct ssc for item .. " << endl;
	process = clock();
	int num_of_G;
	float** data_trans = sfc_direct_cluster(data, &num_of_G);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	executing_time += (float)((end - process) / CLOCKS_PER_SEC);
	float** new_data = (float**)new2d(NumofUser, num_of_G, sizeof(float));
	/**/

	/*�[�ݸ�ƥ��T��*
	for (int i = 0; i < 10; i++)
	{
	for (int j = 0; j < 10; j++)
	{
	cout << data_trans[i][j] << ", ";
	}
	}
	/**/

	/**/
	cout << "data trans .. ";
	process = clock();
	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < num_of_G; j++)
		{
			new_data[i][j] = 0;
			for (int k = 0; k < NumofItem; k++)
			{
				new_data[i][j] += data[i][k] * data_trans[k][j];
			}
		}
	}
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	executing_time += (float)((end - process) / CLOCKS_PER_SEC);
	/**/

	/*�[�ݸ�ƥ��T��*
	for (int i = 0; i < 10; i++)
	{
	for (int j = 0; j < 10; j++)
	{
	cout << new_data[i][j] << ", ";
	}
	}
	/**/

	cout << "correlation matrix .. ";
	process = clock();

	/*k-means ���� class label*
	float** sfc_sta = (float**)new2d(NumofUser, num_of_G, sizeof(float));
	
	float** sfc_spec_sta[Numofclass];

	for (int i = 0; i < Numofclass; i++)
	{
		sfc_spec_sta[i] = (float**)new2d(NumofUser, num_of_G, sizeof(float));
		for (int j = 0; j < NumofUser; j++)
		{
			for (int k = 0; k < num_of_G; k++)
			{
				sfc_spec_sta[i][j][k] = 0;
			}
		}
	}
	/**/

	/*sfc ���� class label��sta*/
	cout << endl;
	float** sfc_cluster_sta = (float**)new2d(num_of_G, num_of_G, sizeof(float));
	for (int j = 0; j < num_of_G; j++)
	{
		for (int k = 0; k < num_of_G; k++)
		{
			sfc_cluster_sta[j][k] = 0;
		}
	}
	/**/

	//CorrelationMatrix(data, sta);                   //�쪩ItemRank
	//sfc_CorrelationMatrix(new_data, sfc_sta, num_of_G);          //�ϥ�sfc ��֯S�x��ItemRank

	/*k-means ���� class label*
	for (int i = 0; i < Numofclass; i++)
	{
		//spec_CorrelationMatrix(data, spec_sta, user_class);       //���s�᪺�쪩ItemRank�A���F���U�s���ӥN��IR�A�~�A���ϥ�
		sfc_spec_CorrelationMatrix(new_data, sfc_spec_sta, num_of_G, user_class);          //�ϥ�sf ��֯S�x��ItemRank
	}/**/

	/*sfc ���� class label��CorrelationMatrix*/
		sfc_cluster_CorrelationMatrix(new_data, sfc_cluster_sta, num_of_G);          //�ϥ�sf ��֯S�x��ItemRank
	/**/

	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	executing_time += (float)((end - process) / CLOCKS_PER_SEC);

	cout << "Dynamic matrix .. ";
	process = clock();
	float** sfc_dyn = (float**)new2d(NumofUser, num_of_G, sizeof(float));
	for (int i = 0; i < NumofUser; i++)
	{
		//DynamicMatrix(data, dyn[i], i);
		//spec_DynamicMatrix(data, spec_dyn[user_class[i]], i);                //���s�᪺�쪩ItemRank�A���F���U�s���ӥN��IR�A�~�A���ϥ�
		sfc_DynamicMatrix(new_data, sfc_dyn[i], i, num_of_G);
	}
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	executing_time += (float)((end - process) / CLOCKS_PER_SEC);

	//���O��C��user����
	cout << "ItemRank .. " << endl;/**/
	process = clock();
	float** sfc_IR = (float**)new2d(NumofUser, num_of_G, sizeof(float));
	/**
	for (int i = 0; i < NumofUser; i++)
	{
	for (int j = 0; j < num_of_G; j++)
	{
	sfc_IR[i][j] = 0;
	}
	}
	/**/

	/*���s�᪺�쪩ItemRank�A���F���U�s���ӥN��IR�A�~�A���ϥ�*
	for (int i = 0; i < Numofclass; i++)
	{
		fastItemRank(spec_IR[i], spec_sta[i], spec_dyn[i], fastItemRankIterationTimes); //�N�s���R�A�x�}spec_sta�A�M�ΤW�|�N���A�p��C�Ӹs���N��IR
	}
	/**/

	int flag = 1;
	for (int i = 0; i < NumofUser; i++)
	{
		//ItemRank(IR[i], sta, dyn[i], &iterations[i]);
		//fastItemRank(IR[i], sta, dyn[i], fastItemRankIterationTimes);   

		//fastItemRank(IR[i], spec_sta[user_class[i]], dyn[i], fastItemRankIterationTimes); //�N�s���R�A�x�}spec_sta�A�M�ΤW�|�N��

		//spec_fastItemRank(IR[i], spec_sta, class_sim[i], dyn[i], fastItemRankIterationTimes); //�N�s���R�A�x�}spec_sta�A�M�ΤW�|�N���A�æҼ{�ۦ���(�ӮɤӤ[�A�B�ǽT�׮t�����j)

		//sfc_fastItemRank(sfc_IR[i], sfc_sta, sfc_dyn[i], fastItemRankIterationTimes, num_of_G);
		
		/*k-means ����label*
		sfc_fastItemRank(sfc_IR[i], sfc_spec_sta[user_class[i]], sfc_dyn[i], fastItemRankIterationTimes, num_of_G);
		/**/

		/*sfc����label*/
		sfc_fastItemRank(sfc_IR[i], sfc_cluster_sta, sfc_dyn[i], fastItemRankIterationTimes, num_of_G);
		/**/

		//spec_sfc_fastItemRank(sfc_IR[i], sfc_spec_sta, class_sim[i], sfc_dyn[i], fastItemRankIterationTimes, num_of_G);

		float processing = (float)i / NumofUser;
		if (processing > 0.9 && flag == 9)
		{
			cout << "90% complete, total spent " << (float)((clock() - process) / CLOCKS_PER_SEC) << " sec" << endl;
			flag++;
		}
		else if (processing > 0.8 && flag == 8)
		{
			cout << "80% complete, total spent " << (float)((clock() - process) / CLOCKS_PER_SEC) << " sec" << endl;
			flag++;
		}
		else if (processing > 0.7 && flag == 7)
		{
			cout << "70% complete, total spent " << (float)((clock() - process) / CLOCKS_PER_SEC) << " sec" << endl;
			flag++;
		}
		else if (processing > 0.6 && flag == 6)
		{
			cout << "60% complete, total spent " << (float)((clock() - process) / CLOCKS_PER_SEC) << " sec" << endl;
			flag++;
		}
		else if (processing > 0.5 && flag == 5)
		{
			cout << "50% complete, total spent " << (float)((clock() - process) / CLOCKS_PER_SEC) << " sec" << endl;
			flag++;
		}
		else if (processing > 0.4 && flag == 4)
		{
			cout << "40% complete, total spent " << (float)((clock() - process) / CLOCKS_PER_SEC) << " sec" << endl;
			flag++;
		}
		else if (processing > 0.3 && flag == 3)
		{
			cout << "30% complete, total spent " << (float)((clock() - process) / CLOCKS_PER_SEC) << " sec" << endl;
			flag++;
		}
		else if (processing > 0.2 && flag == 2)
		{
			cout << "20% complete, total spent " << (float)((clock() - process) / CLOCKS_PER_SEC) << " sec" << endl;
			flag++;
		}
		else if (processing > 0.1 && flag == 1)
		{
			cout << "10% complete, total spent " << (float)((clock() - process) / CLOCKS_PER_SEC) << " sec" << endl;
			flag++;
		}
	}
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;/**/
	executing_time += (float)((end - process) / CLOCKS_PER_SEC);

	/*iterations for all users*
	int total_iterations = 0;
	for (int i = 0; i < NumofUser; i++)
	{
	total_iterations += iterations[i];
	}
	cout << "average iterating times is " << total_iterations / NumofUser << endl;
	/**/

	//Testing
	cout << "testing data .. ";
	process = clock();
	Read("test.txt", testing);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;


	/*������^�쥻��IR�A�H�K�p��DOA   (��)*
	cout << "inv. data trans .. " << endl;
	process = clock();
	Matrix matrix_data_trans(NumofItem, num_of_G);
	for (int i = 0; i < NumofItem; i++)
	{
	for (int j = 0; j < num_of_G; j++)
	{
	matrix_data_trans[i][j] = data_trans[i][j];
	}
	}

	Matrix matrix_inv_data_trans = pseudoinverse(matrix_data_trans);
	cout << "OK" << endl << "spent " << (float)((clock() - process) / CLOCKS_PER_SEC) << " sec" << endl;

	cout << "processing .. ";
	process = clock();
	float** inv_data_trans = (float**)new2d(num_of_G, NumofItem, sizeof(float));

	for (int i = 0; i < num_of_G; i++)
	{
	for (int j = 0; j < NumofItem; j++)
	{
	inv_data_trans[i][j] = matrix_inv_data_trans[i][j];
	//inv_data_trans[i][j] = (matrix_inv_data_trans[i][j] >= 0 ? matrix_inv_data_trans[i][j] : 0);
	//if (i<50 && j<10)
	//    cout << inv_data_trans[i][j] << "  ";
	}
	//if (i<50)
	//    cout << endl;
	}

	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;

	cout << "trans_back_to_IR .. " << endl;
	process = clock();
	for (int i = 0; i < NumofUser; i++)
	{
	for (int j = 0; j < NumofItem; j++)
	{
	for (int k = 0; k < num_of_G; k++)
	{
	IR[i][j] = sfc_IR[i][k] * inv_data_trans[k][j];
	}
	}
	}
	delete inv_data_trans;
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	/**/

	/*�ǥѬۦ��צ^�D�C�ӤH��IR*
	for (int i = 0; i < NumofUser; i++)
	{
		//float sum_of_class_sim = 0;
		for (int j = 0; j < Numofclass; j++)
		{
			//sum_of_class_sim += class_sim[i][j];
			for (int k = 0; k < NumofItem; k++)
			{
				IR[i][k] += class_sim[i][j] * spec_IR[j][k];
			}
		}
	}
	/**/

	//������^IR(�G)
	/**/
	cout << "data trans .. ";
	process = clock();
	for (int i = 0; i < num_of_G; i++)
	{
		float sum = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			sum += data_trans[j][i];
		}
		for (int j = 0; j < NumofItem; j++)
		{
			if (sum != 0)
				 data_trans[j][i] = data_trans[j][i] / sum;
			else   //�q�`���|�o�͡A�ثe���o�͹L
				data_trans[j][i] = 0;
		}
	}
	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			for (int k = 0; k < num_of_G; k++)
			{
				IR[i][j] += sfc_IR[i][k] * data_trans[j][k];
			}
		}
	}
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	executing_time += (float)((end - process) / CLOCKS_PER_SEC);
	cout << "total executing time = " << executing_time << endl;
	/**/

	/**/
	cout << "Macro DOA .. " << endl;
	process = clock();
	macroDOA(data, testing, IR);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	/**/

	/**/
	cout << "RMSE .. " << endl;//�PMAE�u��ܤ@����  ->  �H�X�֤@�_�p��
	process = clock();
	//RMSE(data, testing, IR, rating_predict);
	sfc_RMSE(data, testing, sfc_IR, num_of_G, rating_predict);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	/**/
	/**
	cout << "MAE .. " << endl;
	process = clock();
	sfc_MAE(data, testing, sfc_IR, num_of_G, rating_predict);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	/**/

	/**
	cout << "Macro DOA of rating-IR ver. .. " << endl;
	process = clock();
	sfc_macroDOA(data, testing, IR, rating_predict);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	/**/

	/*�[�ݵ��G*
	for (int i = 0; i < NumofItem; i++)
	{
	cout << fixed<< setprecision(4)<< IR[0][i] << ", ";
	}
	cout << endl;/**/

	end = clock();
	cout << "spent " << (float)((end - start) / CLOCKS_PER_SEC) << " sec" << endl;
	
	delete new_data;
	delete data_trans;

	/*k-means*
	for (int i = 0; i < Numofclass; i++)
	{
		delete sfc_spec_sta[i];
		
	}
	/**/

	/*sfc*/
	delete sfc_cluster_sta;
	/**/

	delete sfc_dyn;
	delete sfc_IR;
	
	//show(data, IR);

	system("pause");
}