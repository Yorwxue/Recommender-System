#include"Header.h"
#include"ObjectClass.cpp"

int main()
{
	srand((unsigned)time(NULL));
	clock_t startTime, finishTime, RelayStationTime;
	startTime = clock();
	/*Test List*/
	/*Test the function of ListClass*
	List<int>* TestListStart, *Pointer, *DelFirst;
	TestListStart = new List<int>();
	int Value = 3, Value2 = 4, Value3 = 5;

	TestListStart->ObjectPointer = &Value;

	Pointer = new List<int>();
	Pointer->ObjectPointer = &Value2;
	TestListStart->InsertElement(Pointer);

	(TestListStart->ListNoShift(1))->InsertElement(new List<int>());
	(TestListStart->ListNoShift(1))->Next->ObjectPointer = &Value3;
	(TestListStart->ListNoShift(2))->InsertElement(new List<int>());
	(TestListStart->ListNoShift(2))->Next->ObjectPointer = &Value;

	DelFirst = TestListStart;
	TestListStart = TestListStart->Next;
	DelFirst->DeleteElement();

	cout << *(TestListStart->ObjectPointer) << endl;
	cout << *((TestListStart->ListNoShift(1))->ObjectPointer) << endl;
	cout << *((TestListStart->ListNoShift(2))->ObjectPointer) << endl;
	/*End of test the function of ListClass*/

	Read();
	/*Test Table*/
	//cout << ((List<ItemClass>*)Inquiry(2, 1681))->ObjectPointer->Name << endl;
	//int test = 0;
	//cout << ((List<ItemClass>*)Inquiry(2, 2))->ObjectPointer->TopicList->ListNoShift(test)->ObjectPointer->ID << endl;
	//while (((List<ItemClass>*)Inquiry(2, 2))->ObjectPointer->TopicList->ListNoShift(test++)->Next != NULL)
	//{
	//	cout << ((List<ItemClass>*)Inquiry(2, 2))->ObjectPointer->TopicList->ListNoShift(test)->ObjectPointer->ID << endl;
	//}
	//cout << ((List<TopicClass>*)Inquiry(3, 15))->ObjectPointer->Name << ", ";
	//cout << ((List<TopicClass>*)Inquiry(3, 15))->ObjectPointer->ID << endl;
	//cout << ((List<TopicClass>*)Inquiry(3, 15))->ObjectPointer->ItemList->ListNoShift(1)->ObjectPointer->Name << ", ";
	//cout << ((List<TopicClass>*)Inquiry(3, 15))->ObjectPointer->ItemList->ListNoShift(1)->ObjectPointer->ID << endl;
	//cout << ((List<UserClass>*)Inquiry(1, 0))->ObjectPointer->Name << endl;
	//for (int i = 0; i < (((List<UserClass>*)Inquiry(1, 0))->ObjectPointer->ItemList->Length); i++)
	//{
	//	cout << ((List<UserClass>*)Inquiry(1, 0))->ObjectPointer->ItemList->ListNoShift(i)->ObjectPointer->Name << endl;
	//}
	//cout << ((List<UserClass>*)Inquiry(1, 0))->ObjectPointer->ID << endl;
	//cout << "Rating for Item " << ((List<UserClass>*)Inquiry(1, 0))->ObjectPointer->ItemList->ObjectPointer->ID << " : " << *(((List<UserClass>*)Inquiry(1, 0))->ObjectPointer->ItemRating->ObjectPointer) << endl;
	//cout << ((List<UserClass>*)Inquiry(1, 1))->ObjectPointer->ItemList->ObjectPointer->Name << endl;
	//cout << "P(T4 | I1) : " << Probability("4", 2, 0, 1) << endl;  //"ID", Name of Item Table is 2, Item 1 No. is 0, Name of Topic List in Item Table is 1
	//system("pause");

	cout << "Base Probability Table .. ";
	RelayStationTime = clock();

	int NumofUser = Statistics(1, 0, 0, "") + 1,
		NumofItem = Statistics(2, 0, 0, "") + 1,
		NumofTopic = Statistics(3, 0, 0, "") + 1;

	/*產生Item與Topic對應機率的Array*/
	double** ItemToTopicTable = (double**)new2d(NumofItem, NumofTopic, sizeof(double));
	/*移至Base Probability*
	for (int i = 0; i < NumofItem; i++)
	{
	for (int j = 0; j < NumofTopic; j++)
	{
	ItemToTopicTable[i][j] = Probability(to_string(j + 1), 2, i, 1, parameter_b);
	//if (i<10)
	//    cout << ItemToTopicTable[i][j] << ", ";
	}
	//if (i<10)
	//    cout << endl;
	}
	//cout << endl;
	/*Topic to Item*/
	double** TopicToItemTable = (double**)new2d(NumofTopic, NumofItem, sizeof(double));
	/*移至Base Probability*
	for (int i = 0; i < NumofTopic; i++)
	{
	for (int j = 0; j < NumofItem; j++)
	{
	//double temp = Probability(to_string(j + 1), 3, i, 1, parameter_a); //for detect point(F9) check
	TopicToItemTable[i][j] = Probability(to_string(j + 1), 3, i, 1, parameter_a);
	//if (TopicToItemTable[i][j] == 0 && j < 10)
	//{
	//	cout << "Topic : " << ((List<TopicClass>*)Inquiry(3, i))->ObjectPointer->Name << ", "
	//		<< "won't become to Item : " << ((List<ItemClass>*)Inquiry(2, j + 1))->ObjectPointer->Name
	//		<< endl;
	//}
	//if (j < 10)
	//	cout << TopicToItemTable[i][j] << ", ";
	}
	//cout << endl;
	}
	finishTime = clock();
	cout << "OK" << ", spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;


	/*產生新的Topic*/

	BaseProbability(ItemToTopicTable, TopicToItemTable, NumofItem, NumofTopic);

	//上面註解部分的Item to Topic與Topic to Item Table的建立移到BaseProbabiliy()中執行以便重複呼叫，縮減程式碼
	finishTime = clock();
	cout << "OK" << ", spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;


	/*產生新的Topic*
	cout << "New Topic .. ";
	RelayStationTime = clock();
	newTopic(ItemToTopicTable, TopicToItemTable);
	//刪除舊的Base Probability Table
	delete ItemToTopicTable;
	delete TopicToItemTable;
	finishTime = clock();
	cout << "OK" << ", spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;

	cout << "Apply Topic .. ";
	RelayStationTime = clock();
	Apply();
	finishTime = clock();
	cout << "OK" << ", spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;

	cout << "Reconstruct Base Probability Table .. ";
	RelayStationTime = clock();
	//依造新的Topic重建新的Base Probability Table
	NumofTopic = Statistics(3, 0, 0, "") + 1;
	ItemToTopicTable = (double**)new2d(NumofItem, NumofTopic, sizeof(double));
	TopicToItemTable = (double**)new2d(NumofTopic, NumofItem, sizeof(double));
	BaseProbability(ItemToTopicTable, TopicToItemTable, NumofItem, NumofTopic);

	finishTime = clock();
	cout << "OK" << ", spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;


	/*產生使用者的物件隨機對應到Topic機率的Array(即User to Item to (Topic to Topic)*)*/
	cout << "User to Topic Table .. ";
	RelayStationTime = clock();
	double RandomValue;
	double** UserToTopicTable = (double**)new2d(NumofUser, NumofTopic, sizeof(double));
	UserClass * User;
	int ItemNo, TopicNo;
	int NumofItemInUser;
	double CheckSum = 0;
	for (int i = 0; i < NumofUser; i++)
	{
		CheckSum = 0;
		for (int k = 0; k < NumofTopic; k++)
		{
			UserToTopicTable[i][k] = 0;
			User = ((List<UserClass>*)Inquiry(1, i))->ObjectPointer;
			NumofItemInUser = User->ItemList->Length + 1;
			for (int j = 0; j < NumofItemInUser; j++)//User to Item to Topic
			{
				stringstream(User->ItemList->ListNoShift(j)->ObjectPointer->ID) >> ItemNo;  //ID(string)轉No.(int)
				ItemNo--;   //Table從0開始，但No從1開始編號
				UserToTopicTable[i][k] += ItemToTopicTable[ItemNo][k] / (User->ItemList->Length + 1);
			}
			CheckSum += UserToTopicTable[i][k];
			//if (i < 10)
			//{
			//	cout << UserToTopicTable[i][k] << ", ";
			//}
		}
		//if (i < 10)
		//{
		//	cout << CheckSum;
		//	cout << endl;
		//}
	}

	/*total probability of Topic beyond all users*/
	double* AllUserToTopicTable = new double[NumofTopic];
	//double CheckSum = 0;
	for (int i = 0; i < NumofTopic; i++)
	{
		AllUserToTopicTable[i] = 0;
		for (int j = 0; j < NumofUser; j++)
		{
			AllUserToTopicTable[i] += UserToTopicTable[j][i];
		}
		AllUserToTopicTable[i] = AllUserToTopicTable[i] / NumofUser;
		//cout << AllUserToTopicTable[i] << ", ";
		//CheckSum += AllUserToTopicTable[i];
	}
	//cout << endl;
	//cout << CheckSum << endl;

	//Item to Topic Table ver.2
	for (int i = 0; i < NumofItem; i++)
	{
		for (int j = 0; j < NumofTopic; j++)
		{
			double Denominator = 0;
			for (int k = 0; k < NumofTopic; k++)
			{
				Denominator += AllUserToTopicTable[k] * TopicToItemTable[k][i];
			}
			if (Denominator != 0)
				ItemToTopicTable[i][j] = AllUserToTopicTable[j] * TopicToItemTable[j][i] / Denominator;
			else
				ItemToTopicTable[i][j] = 0;
			//if (i<10)
			//    cout << ItemToTopicTable[i][j] << ", ";
		}
		//if (i<10)
		//    cout << endl;
	}
	/**/
	//system("pause");
	/*Topic to Topic(using Item-to-Topic Table ver.2)*/
	double** TopicToTopicTable = (double**)new2d(NumofTopic, NumofTopic, sizeof(double));
	for (int i = 0; i < NumofTopic; i++)
	{
		//CheckSum = 0;
		for (int j = 0; j < NumofTopic; j++)
		{
			TopicToTopicTable[i][j] = 0;
			for (int k = 0; k < NumofItem; k++)
			{
				//double a = TopicToItemTable[i][k], b = ItemToTopicTable[k][i];
				TopicToTopicTable[i][j] += TopicToItemTable[i][k] * ItemToTopicTable[k][j];
			}
			//CheckSum += TopicToTopicTable[i][j];
			//cout << fixed << setprecision(2) << TopicToTopicTable[i][j] << ", ";
		}
		//cout << CheckSum << endl;
		//cout << endl << endl;
	}

	finishTime = clock();
	cout << "OK" << ", spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;

	cout << "Chain .. ";
	RelayStationTime = clock();
	int* chainLength = new int[NumofUser];
	for (int i = 0; i < NumofUser; i++)
	{
		/*  Chain : (Topic to Topic)*  */

		double* TopicChainStart = new double[NumofTopic];
		double* TopicChainFinish = new double[NumofTopic];

		bool chainStart = true;
		chainLength[i] = 0;
		/*Chain Start*/
		do
		{
			if (chainStart == true)      //Initial step
			{
				chainStart = false;
				CheckSum = 0;
				for (int j = 0; j < NumofTopic; j++)
				{
					//cout << fixed << setprecision(5) << UserToTopicTable[i][j] << endl;
					TopicChainStart[j] = UserToTopicTable[i][j];
					CheckSum += TopicChainStart[j];
					//cout << fixed << setprecision(5) << TopicChainStart[j] << ", ";
					TopicChainFinish[j] = 0;
				}
				//cout << CheckSum << endl;
				//cout << endl << endl;
			}
			else
			{
				CheckSum = 0;
				for (int j = 0; j < NumofTopic; j++)
				{
					TopicChainStart[j] = TopicChainFinish[j];
					TopicChainFinish[j] = 0;
					CheckSum += TopicChainStart[j];
					//cout << fixed << setprecision(5) << TopicChainStart[j] << ", ";
				}
				//cout << CheckSum << endl;
				//cout << endl << endl;
			}
			chainLength[i]++;
			CheckSum = 0;
			for (int j = 0; j < NumofTopic; j++)
			{
				for (int k = 0; k < NumofTopic; k++)
				{
					//cout << fixed << setprecision(5) << TopicToTopicTable[k][j] << endl;
					TopicChainFinish[j] += TopicChainStart[k] * TopicToTopicTable[k][j];
				}
				CheckSum += TopicChainFinish[j];
				TopicChainFinish[j] = TopicChainFinish[j] * (1 - 0.3) + UserToTopicTable[i][j] * 0.3;
				//cout << fixed << setprecision(5) << TopicChainFinish[j] << ", ";
				//CheckSum += TopicChainFinish[j];
			}
			//cout << CheckSum << endl;
			//cout << endl << endl;
		} while (Similarity(TopicChainStart, TopicChainFinish, NumofTopic, 1) > stableRatio);
		/*Chain End*/
		CheckSum = 0;
		for (int j = 0; j < NumofTopic; j++)
		{
			//cout << fixed << setprecision(5) << TopicChainFinish[j]<<endl;
			UserToTopicTable[i][j] = TopicChainFinish[j];
			CheckSum += UserToTopicTable[i][j];
		}
		//cout << endl << CheckSum << endl;
		/*  Chain : (Topic to Topic)*  Finish*/
	}
	/*(User to Item to (Topic to Topic)*)的測試流程*
	while (i < NumofUser)
	{
	User = ((List<UserClass>*)Inquiry(1, i))->ObjectPointer;
	NumofItemInUser = User->ItemList->Length + 1;
	//cout << NumofItemInUser << endl;
	j = 0;
	while (j < NumofItemInUser)
	{
	stringstream(User->ItemList->ListNoShift(j)->ObjectPointer->ID) >> ItemNo;  //ID(string)轉No.(int)
	ItemNo--;   //Table從0開始，但No從1開始編號

	//Item to Topic
	RandomValue = (double)RandomNumber(1, 99) / 100;   //Note:0.33 + 0.33 + 0.33 < 1 !!
	for (int k = 0; k < NumofTopic; k++)
	{
	RandomValue = RandomValue - ItemToTopicTable[ItemNo][k];
	if (RandomValue <= 0)
	{
	TopicNo = k;
	//User->Item2Topic->ListNoShift(j - 1)->ObjectPointer = ((List<TopicClass>*)Inquiry(3, k))->ObjectPointer;
	if (User->Item2Topic == NULL)
	{
	User->Item2Topic = new List<TopicClass>();
	User->Item2Topic->ObjectPointer = ((List<TopicClass>*)Inquiry(3, k))->ObjectPointer;
	}
	else
	{
	User->Item2Topic->ListNoShift(j - 1)->InsertElement((List<TopicClass>*)Inquiry(3, k));
	}
	break;
	}
	}
	//Topic to Topic
	while (0 < LoopLimit--)
	{
	//Topic to Item
	RandomValue = (double)RandomNumber(1, 100) / 100;
	for (int L = 0; L < NumofItem; L++)  //Topic to Item
	{
	RandomValue = RandomValue - TopicToItemTable[TopicNo][L];
	if (RandomValue <= 0)
	{
	ItemNo = L;
	RandomValue = (double)RandomNumber(1, 100) / 100;
	for (int k = 0; k < NumofTopic; k++)  //Item to Topic
	{
	RandomValue = RandomValue - ItemToTopicTable[ItemNo][k];
	if (RandomValue <= 0)
	{
	TopicNo = k;
	User->Item2Topic->ListNoShift(j)->ObjectPointer = ((List<TopicClass>*)Inquiry(3, k))->ObjectPointer;
	break;
	}
	}
	break;
	}
	}
	}//Topic to Topic over
	j++;
	}
	i++;
	}
	/**
	cout << "Num of User : " << NumofUser << endl
	<< "Num of Item in User : " << NumofItemInUser << endl;
	for (i = 0; i < NumofUser; i++)
	{
	j = 0;
	User = ((List<UserClass>*)Inquiry(1, i))->ObjectPointer;
	NumofItemInUser = User->ItemList->Length + 1;
	while (NumofItemInUser > j)
	{
	if (i==0 && j< 10)
	cout << "User Name : " << User->Name << ", "
	<< "Item Name : " << User->ItemList->ListNoShift(j)->ObjectPointer->Name << ", "
	<<	"Choosed Topic : "<< User->Item2Topic->ListNoShift(j)->ObjectPointer->Name << endl;
	j++;
	}
	}
	/**/

	finishTime = clock();
	cout << "OK, " << ", spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;


	cout << "User Data for Testing .. ";
	RelayStationTime = clock();

	//確認training時有評過分的項目，設定為0，並計數
	//int* NumofRatingInTraining = new int[NumofUser];
	int** ItemRatingRanking = (int**)new2d(NumofUser, NumofItem, sizeof(int));
	int** RecordofItemRating = (int**)new2d(NumofUser, NumofItem, sizeof(int));
	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			ItemRatingRanking[i][j] = -1;
			RecordofItemRating[i][j] = -1;
		}
	}
	for (int i = 0; i < NumofUser; i++)
	{
		User = ((List<UserClass>*)Inquiry(1, i))->ObjectPointer;
		NumofItemInUser = User->ItemList->Length + 1;
		List<ItemClass>* UserItemProcess = User->ItemList;

		int ItemNoInUser;
		int m = 0;
		//NumofRatingInTraining[i] = 0;
		while (UserItemProcess != NULL)
		{
			//NumofRatingInTraining[i]++;
			stringstream(UserItemProcess->ObjectPointer->ID) >> ItemNoInUser;
			ItemNoInUser--;                                                      //ID從1開始，No從0開始
			ItemRatingRanking[i][ItemNoInUser] = 0;
			RecordofItemRating[i][ItemNoInUser] = *(User->ItemRating->ListNoShift(m)->ObjectPointer);
			UserItemProcess = UserItemProcess->Next;
			m++;
		}
	}

	ReadForTesting();

	finishTime = clock();
	cout << "OK, " << "spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;

	cout << "Item Correspondence .. ";
	RelayStationTime = clock();

	/*設計實驗*/
	/*User to Item*/
	//User to Topic已於前面完成，此處僅依照機率對應物品
	double** UserToItemTable = (double**)new2d(NumofUser, NumofItem, sizeof(double));
	double ProbabilityofItem;

	double** ItemProbabilityRanking = (double**)new2d(NumofUser, NumofItem, sizeof(double));
	int** ItemNoRanking = (int**)new2d(NumofUser, NumofItem, sizeof(int));

	int* NumofUnRatingItem = new int[NumofUser];  //未評分的物品總數
	int* NumofRatingInTesting = new int[NumofUser];  //在training時未評分，testing時才評分的物品數總數

	for (int i = 0; i < NumofUser; i++)
	{
		NumofUnRatingItem[i] = 0;
		NumofRatingInTesting[i] = 0;

		User = ((List<UserClass>*)Inquiry(1, i))->ObjectPointer;
		NumofItemInUser = User->ItemList->Length + 1;
		for (int j = 0; j < NumofItem; j++)
		{
			ProbabilityofItem = 0;
			for (int k = 0; k < NumofTopic; k++)
			{
				//cout << UserToTopicTable[i][k] << "," << TopicToItemTable[k][j] << endl;
				ProbabilityofItem += UserToTopicTable[i][k] * TopicToItemTable[k][j];
			}
			UserToItemTable[i][j] = ProbabilityofItem;
			ItemProbabilityRanking[i][j] = ProbabilityofItem;
			ItemNoRanking[i][j] = j;
		}
		{
			List<ItemClass>* UserItemProcess = User->ItemList;
			//int Rating = -1;   //-1表示使用者從未對這物品評分，0表示training時有評過分
			int ItemNoInUser;
			int checkRepeatItemNo = -1;  //User擁有多個同樣的Item，因為同樣Item的評分會相同，所以不用重複登記分數，這是在同樣Item在User表單中的位置排在一起時才能用
			for (int m = 0; UserItemProcess != NULL; m++)
			{
				stringstream(UserItemProcess->ObjectPointer->ID) >> ItemNoInUser;
				if (checkRepeatItemNo != ItemNoInUser)
				{
					ItemRatingRanking[i][ItemNoInUser - 1] = *(User->ItemRating->ListNoShift(m)->ObjectPointer);
					checkRepeatItemNo = ItemNoInUser;
					NumofRatingInTesting[i]++;
				}
				UserItemProcess = UserItemProcess->Next;
			}
			for (int j = 0; j < NumofItem; j++)
			{
				if (ItemRatingRanking[i][j] == -1)  //-1表示使用者從未對這物品評分，0表示training時有評過分
				{
					NumofUnRatingItem[i]++;
				}
			}
		}
	}
	finishTime = clock();
	cout << "OK, " << "spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;

	/*Rating RMSE*/
	cout << "Computing Similarity .. ";
	RelayStationTime = clock();
	//建立各個User的評分基準，並計算相似度
	double* StandardOfUserRating = new double[NumofUser];
	double** Similartiy = (double**)new2d(NumofUser, NumofUser, sizeof(double));

	for (int i = 0; i < NumofUser; i++)
	{
		//建立標準
		StandardOfUserRating[i] = 0;
		int NumofRating = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			if (ItemRatingRanking[i][j] > 0)
			{
				NumofRating++;
				StandardOfUserRating[i] += ItemRatingRanking[i][j];
			}
		}
		StandardOfUserRating[i] = StandardOfUserRating[i] / NumofRating;
		//if (StandardOfUserRating[i]>5 || StandardOfUserRating[i]<0)
		//{
		//	cout << StandardOfUserRating[i] << endl;
		//}
		
		
		//計算相似度
		for (int j = 0; j < NumofUser; j++)
		{
			if (j != i)
			{
				Similartiy[i][j] = Similarity(UserToTopicTable[i], UserToTopicTable[j], NumofTopic, 2);
			}
		}
	}
	finishTime = clock();
	cout << "OK, " << "spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;

	//補足未評分項目，並評斷RMSE
	cout << "Computing RMSE .. ";
	RelayStationTime = clock();
	double RMSE = 0;
	double LastRMSE = 0;
	int totalRatingInTraining = 0;
	double** PredictItemRating = (double**)new2d(NumofUser, NumofItem, sizeof(double));
	for (int i = 0; i<NumofUser; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			if (ItemRatingRanking[i][j] > 0)   //0表示只在training時評分，-1表示從未評分，這邊是testing有評分的
			{
				PredictItemRating[i][j] = ItemRatingRanking[i][j];
			}
			else   //testing時沒評分的
			{
				PredictItemRating[i][j] = 0;
				int NumofRating = 0;
				for (int k = 0; k < NumofUser; k++)
				{
					if (ItemRatingRanking[k][j] > 0 && i != k)
					{
						if (Similartiy[i][k] != 0)
						{
							NumofRating++;
							if (ItemRatingRanking[k][j] - StandardOfUserRating[k] > 0)     //PredictItemRating出現莫名的數字<--目前進度  v下方是可能出問題的段落v
							{
								PredictItemRating[i][j] += StandardOfUserRating[i] + Similartiy[i][k] * (ItemRatingRanking[k][j] - StandardOfUserRating[k]) * ((5 - StandardOfUserRating[i]) / (5 - StandardOfUserRating[k]));
							}
							else
							{
								PredictItemRating[i][j] += StandardOfUserRating[i] + Similartiy[i][k] * (ItemRatingRanking[k][j] - StandardOfUserRating[k]) * ((StandardOfUserRating[i] - 1) / (StandardOfUserRating[k] - 1));
							}
						}
					}
				}
				PredictItemRating[i][j] = PredictItemRating[i][j] / NumofRating;
				if (PredictItemRating[i][j] > 5 || PredictItemRating[i][j] < 0)
				{
					cout << "4捨5入前" << PredictItemRating[i][j] << endl;
				}
				//四捨五入
				double DoublePart = PredictItemRating[i][j];
				int IntPart = PredictItemRating[i][j];
				if (PredictItemRating[i][j] - IntPart >= 0.5)
				{
					PredictItemRating[i][j] = IntPart + 1;
					if (PredictItemRating[i][j] > 5 || PredictItemRating[i][j] < 0)
					{
						cout << "4捨5入後" << PredictItemRating[i][j] << endl;
					}
				}
				else
				{
					PredictItemRating[i][j] = IntPart;
					if (PredictItemRating[i][j] > 5 || PredictItemRating[i][j] < 0)
					{
						cout << "4捨5入後" << PredictItemRating[i][j] << endl;
					}
				}
			}
			if (ItemRatingRanking[i][j] == 0)   //training時有評分，testing時沒評分的
			{
				//if (RecordofItemRating[i][j]>5 || RecordofItemRating[i][j]<1)
				//{
				//	cout << RecordofItemRating[i][j] << endl;
				//}
				totalRatingInTraining++;
				LastRMSE = RMSE;
				RMSE += pow(PredictItemRating[i][j] - RecordofItemRating[i][j], 2);
				if (RMSE - LastRMSE > 25)
				{
					cout << "RMSE : " << RMSE << ", Last RMSE : " << LastRMSE << endl;
					cout << PredictItemRating[i][j] << ", " << RecordofItemRating[i][j] << endl;
				}
			}
		}
	}
	RMSE = sqrt(RMSE / totalRatingInTraining);

	finishTime = clock();
	cout << "OK, " << "spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec, ";
	cout << "RMSE : " << fixed << setprecision(5) << RMSE << endl;

	/*Quick Sort*/
	cout << "Sorting .. ";
	RelayStationTime = clock();

	for (int i = 0; i < NumofUser; i++)
	{
		/**
		for (int j = 0; j < NumofItem; j++)
		{
		cout << "No : " << j << "Probability : " << fixed << setprecision(5) << ItemProbabilityRanking[i][j] << endl;
		}/**/
		quickSort(ItemProbabilityRanking[i], ItemNoRanking[i], ItemRatingRanking[i], 0, NumofItem - 1);
	}
	finishTime = clock();
	cout << "OK, " << "spent " << double(finishTime - RelayStationTime) / CLOCKS_PER_SEC << " sec" << endl;

	/*觀看結果*/
	/**
	double TotalProbability = 0;
	for (int i = 0; i < NumofUser; i++)
	{
		for (int j = 0; j < NumofItem; j++)
		{
			TotalProbability += ItemProbabilityRanking[i][j];
			if (i == 0 && j < 20 && ItemRatingRanking[i][j]>0)
				cout //<< "Item No. : " << ItemNoRanking[i][j] << ", "
				<< "Item Name : " << ((List<ItemClass>*)Inquiry(2, ItemNoRanking[i][j]))->ObjectPointer->Name << ", "
				//<< "Topic : " << ((List<ItemClass>*)Inquiry(2, ItemNoRanking[i][j]))->ObjectPointer->TopicList->ObjectPointer->Name << ", "
				<< "Rating : " << ItemRatingRanking[i][j] //<< ", "
				//<< "Probability : " << fixed << setprecision(5) << ItemProbabilityRanking[i][j]
				<< endl;
		}
	}
	cout << "Total Probability : " << TotalProbability << endl;
	/**/
	double* DOA = new double[NumofUser];
	double TotalDOA = 0;
	double* Mistake = new double[NumofUser];
	for (int i = 0; i < NumofUser; i++)
	{
		DOA[i] = 0;
		Mistake[i] = 0;
		for (int j = 0; j < NumofItem; j++)
		{
			for (int k = j + 1; k < NumofItem; k++)
			{/**/
				if (ItemRatingRanking[i][j] != -1 && ItemRatingRanking[i][j] != 0 && ItemRatingRanking[i][k] == -1)
				{
					DOA[i]++;
				}/**/
				/***Test***
				if (ItemRatingRanking[i][j] != -1 && ItemRatingRanking[i][k] != -1)
				{
				if (ItemRatingRanking[i][j] >= ItemRatingRanking[i][k])
				{
				DOA[i]++;
				}
				else
				{
				Mistake[i]++;
				}
				}
				/******/
			}
		}
	}

	for (int i = 0; i < NumofUser; i++)
	{
		DOA[i] = DOA[i] / (NumofRatingInTesting[i] * NumofUnRatingItem[i]);
		//DOA[i] = DOA[i] / (DOA[i] + Mistake[i]);//for Test
		TotalDOA += DOA[i];
	}

	finishTime = clock();
	cout << "DOA : " << fixed << setprecision(5) << TotalDOA / NumofUser << endl;
	cout << "Finish" << endl;
	cout << "Spent " << double(finishTime - startTime) / CLOCKS_PER_SEC << " sec" << endl;
	system("pause");
	return 0;
}
