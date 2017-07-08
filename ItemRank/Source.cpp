#include"Header.h"

void main()
{
	clock_t start, process, end;
	start = clock();
	float executing_time = 0;
	float initial = 1.0 / NumofItem;
	float data[NumofUser][NumofItem]
	/** =
	{
	{ 0.8, 0.4, 0, 0, 0 },
	{ 0, 1, 1, 1, 0 },
	{ 1, 0, 1, 0, 0 },
	{ 1, 0, 0, 1, 1 },
	{ 1, 1, 1, 1, 0 },
	{ 1, 0, 1, 0, 0 },
	{ 1, 0, 1, 1, 0 },
	{ 1, 1, 0, 1, 0 },
	{ 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1 },
	{ 0, 1, 0, 1, 0 },
	{ 0, 0, 1, 1, 0 }
	}/**/
	/** =
	{
		{ 0, 3, 3, 3, 0 },
		{ 3, 4, 3, 3, 0 },
		{ 4, 0, 2, 0, 0 },
		{ 3, 0, 4, 0, 0 },
		{ 4, 2, 0, 0, 0 },
		{ 3, 3, 0, 4, 0 },
		{ 0, 3, 0, 0, 3 },
		{ 3, 0, 0, 3, 4 },
		{ 3, 0, 0, 0, 3 },
		{ 0, 0, 3, 0, 3 }
	}/**/
	,
    	testing[NumofUser][NumofItem],
	    IR[NumofUser][NumofItem],
	    sta[NumofItem][NumofItem],
	    dyn[NumofUser][NumofItem];         //導入個別user評分的影響

	int rating_predict[NumofUser][NumofItem];

	//觀察用
	int iterations[NumofUser];

		
	/*觀看資料正確性*
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
	for (int i = 0; i < NumofUser; i++)
	{
		//iterations[i] = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			IR[i][j] = initial;
			data[i][j] = 0;
			testing[i][j] = 0;
		}
	}
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			sta[i][j] = 0;
		}
	}

	//initial finish

	//read file
	/**/
	cout << "training data .. ";
	process = clock();
	Read("train.txt", data);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	/**/

	/**
	//*1
	cout << "item data .. ";
	process = clock();
	ReadItem("item.txt", itemData);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	/**/
	//read finish

	cout << "correlation matrix .. ";
	process = clock();
	CorrelationMatrix(data, sta);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	executing_time += (float)((end - process) / CLOCKS_PER_SEC);


	cout << "Dynamic matrix .. ";
	process = clock();
	for (int i = 0; i < NumofUser; i++)
	{
		DynamicMatrix(data, dyn[i],i);
	}
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	executing_time += (float)((end - process) / CLOCKS_PER_SEC);

	//分別對每個user執行
	/**/
	cout << "ItemRank .. ";
	process = clock();
	int flag = 1;
	for (int i = 0; i < NumofUser; i++)
	{
		//ItemRank(IR[i], sta, dyn[i], &iterations[i]);
		fastItemRank(IR[i], sta, dyn[i], fastItemRankIterationTimes);
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

	cout << "Total executing time = " << executing_time << endl;

	/*iterations for all users*
	int total_iterations = 0;
	for (int i = 0; i < NumofUser; i++)
	{
		total_iterations += iterations[i];
	}
	cout << "average iterating times is " << total_iterations / NumofUser << endl;
	/**/

	/**/
	//Testing
	cout << "testing data .. ";
	process = clock();
	Read("test.txt", testing);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;

	/**/
	/**/
	cout << "Macro DOA for ItemRank .. ";
	process = clock();
	macroDOA(data, testing, IR);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	/**/

	/**/
	cout << "RMSE .. " << endl;
	process = clock();
	RMSE(data, testing, IR, rating_predict);
	end = clock();
	cout << "OK, spent " << (float)((end - process) / CLOCKS_PER_SEC) << " sec" << endl;
	/**/

	/*觀看結果*
	for (int i = 0; i < NumofItem; i++)
	{
		cout << fixed<< setprecision(4)<< IR[0][i] << ", ";
	}
	cout << endl;/**/

	end = clock();
	cout << "spent " << (float)((end - start) / CLOCKS_PER_SEC) << " sec" << endl;

	//show(data, IR);

	system("pause");
}