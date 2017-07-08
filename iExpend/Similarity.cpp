#include"Header.h"

/*回傳數值越小越穩定*/
//A : before
//B : After

double Similarity(double A[], double B[],int Length, int kind)
{
	//for case 1
	double variation = 0, innerProduct = 0;
	//for case 2
	double NormA = 0;
	double NormB = 0;
	double AB = 0;
	double Similarity;
	//
	switch (kind)
	{
	case 1 :
		/*Euclidean distance*/
		for (int i = 0; i < Length; i++)
		{
			innerProduct += pow(A[i], 2);
			variation += pow(A[i] - B[i], 2);
		}
		Similarity = sqrt(variation) / sqrt(innerProduct);
		break;

	case 2:
		/*Cosine similarity*/
		//for (int i = 0; i < Length; i++)
		//{
		//	cout << fixed << setprecision(5) << A[i] << ", ";
		//}
		//cout << endl;
		//for (int i = 0; i < Length; i++)
		//{
		//	cout << fixed << setprecision(5) << B[i] << ", ";
		//}
		//cout << endl;

		for (int i = 0; i < Length; i++)
		{
			AB += A[i] * B[i];
			NormA += pow(A[i], 2);
			NormB += pow(B[i], 2);
		}
		Similarity = AB / (sqrt(NormA)*sqrt(NormB));
		if (Similarity > 1){ system("pause"); }
		break;
	default:
		Similarity = 0;
	}
	//cout <<"variation:"<< fixed << setprecision(5) << Similarity << ", ";
	return Similarity;
}
