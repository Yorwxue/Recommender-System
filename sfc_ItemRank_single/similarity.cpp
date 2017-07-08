#include"Header.h"

float Similarity(float A[], float B[], int Length, int kind)
{
	//for case 1
	float variation = 0, innerProduct = 0;
	//for case 2
	float NormA = 0;
	float NormB = 0;
	float AB = 0;
	float Similarity;
	//
	switch (kind)
	{
	case 1:
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
		if (Similarity > 1)
		{
			Similarity = 1;
			//system("pause"); 
		}
		break;
	default:
		Similarity = 0;
	}
	//cout <<"variation:"<< fixed << setprecision(5) << Similarity << ", ";
	return Similarity;
}

float sfc_Similarity(float* A, float* B, int Length)
{
	float NormA = 0;
	float NormB = 0;
	float AB = 0;
	float Similarity;

	for (int i = 0; i < Length; i++)
	{
		AB += A[i] * B[i];
		NormA += pow(A[i], 2);
		NormB += pow(B[i], 2);
	}
	Similarity = AB / (sqrt(NormA)*sqrt(NormB));
	if (Similarity > 1)
	{ 
		Similarity = 1;
		//system("pause"); 
	}

	return Similarity;
}