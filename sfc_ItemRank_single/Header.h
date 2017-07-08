#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<sstream>
#include<time.h>

using namespace std;

#define NumofUser 943
#define NumofItem 1682
//#define NumofEntry 23
#define alpha 0.85
#define stable 0.0001

#define Unrating 0

#define Numofclass 1682  //list所能容忍的最大矩陣size

float** sfc_cluster(float data[NumofUser][NumofItem], int* num_of_G, int user_class[NumofUser]);
void classification(float data[NumofUser][NumofItem], int user_class[NumofUser], int Numofuser_in_class[Numofclass], float class_center[Numofclass][NumofItem], float class_sim[NumofUser][Numofclass]);

float** sfc_direct_cluster(float data[NumofUser][NumofItem], int* num_of_G);

//void spec_CorrelationMatrix(float data[NumofUser][NumofItem], float sta[Numofclass][NumofItem][NumofItem], int user_class[NumofUser]);
//void spec_fastItemRank(float IR[], float sta[][NumofItem][NumofItem], float sim[], float dyn[], int times);
//void spec_DynamicMatrix(float data[NumofUser][NumofItem], float dyn[NumofItem], int userNo);
int RandomNumber(int MinValue, int MaxValue); 
void* new2d(int h, int w, int size);

void* sfc(float data[NumofUser][NumofItem], int user_class[NumofUser], int* num_of_G, int num_of_class);
void item_sample(float data[NumofUser][NumofItem], int user_class[NumofUser], float** sample, int num_of_class);
void G_update(float c[Numofclass], float m[Numofclass], float** x, int G[NumofItem], int Num_of_item_in_G, int new_entry, int num_of_class);
void mean_vector(float m[Numofclass], float x[Numofclass][NumofItem], int G[NumofItem], int Num_of_item_in_G);
void standard_deviation_vector(float c[Numofclass], float m[Numofclass], float x[Numofclass][NumofItem], int G[NumofItem], int Num_of_item_in_G);
float membership(float c[Numofclass], float m[Numofclass], float xi[Numofclass], int num_of_class);
void sfc_spec_CorrelationMatrix(float** data, float** sta[Numofclass], int Num_of_G, int user_class[NumofUser]);
void Multi(float* c, float** a, float* b, int length);
void deviation_upddate(float c[], float m[], float x[], int Num_of_Entry_in_G, int size, float C);
void mean_vector_update(float x[], float m[], int size, int Num_of_Entry_in_G);
void sfc_cluster_CorrelationMatrix(float** data, float** sta, int Num_of_G);


void sfc_fastItemRank(float* IR, float** sta, float* dyn, int times, int Num_of_G);
void sfc_DynamicMatrix(float** data, float* dyn, int userNo, int Num_of_G);
void sfc_RMSE(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], float** IR, int Num_of_G, int rating_predict[NumofUser][NumofItem]);
void sfc_sim_table(float data[NumofUser][NumofItem], float** IR, float sim[NumofUser][NumofUser], float ave[NumofUser], int Num_of_G);
float sfc_Similarity(float* A, float* B, int Length);
void sfc_macroDOA(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], float IR[NumofUser][NumofItem], int rating_predict[NumofUser][NumofItem]);

void sfc_MAE(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], float** IR, int Num_of_G, int rating_predict[NumofUser][NumofItem]);

void sfc_CorrelationMatrix(float** data, float** sta, int Num_of_G);

void spec_sfc_fastItemRank(float* IR, float** spec_sta[Numofclass], float sim[], float dyn[], int times, int Num_of_G);
//*1
//#define NumofTopic 19

void array_initial(int A[], int length, float value);
void array_initial(float A[], int length, float value);

float norm(float vec[], int length);
void multi(float c, float a[], int length);
void Multi(float c[NumofItem], float a[NumofItem][NumofItem], float b[NumofItem]);
void Add(float c[], float a[], float b[], int length, float parameter);
//void inverse(int m, float** A, float** B);
//void trans(float** b, float** a, int h, int w);
//void matrix_multi(float** c, float** a, float** b, int h, int w, int a_b_i);
//void pse_inv(float** b, float** a, int a_h, int a_w);


void ItemRank(float IR[], float sta[][NumofItem], float dyn[], int iterations[]);
float Similarity(float A[], float B[], int Length, int kind);
void CorrelationMatrix(float data[NumofUser][NumofItem], float sta[NumofItem][NumofItem]);
void DynamicMatrix(float data[NumofUser][NumofItem], float dyn[NumofItem], int userNo);
void Read(string fileName, float data[NumofUser][NumofItem]);
void macroDOA(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], float IR[NumofUser][NumofItem]);

float ave_rating(float data[NumofUser][NumofItem], int UserNo);
void sim_table(float data[NumofUser][NumofItem], float IR[NumofUser][NumofItem], float sim[NumofUser][NumofUser], float ave[NumofUser]);
float predict_rating(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], int UserNo, float sim[NumofUser][NumofUser], float ave[NumofUser], int rating_predict[NumofUser][NumofItem]);
float MAE_predict_rating(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], int UserNo, float sim[NumofUser][NumofUser], float ave[NumofUser], int rating_predict[NumofUser][NumofItem]);
//void RMSE(float data[NumofUser][NumofItem], float testing[NumofUser][NumofItem], float IR[NumofUser][NumofItem], int rating_predict[NumofUser][NumofItem]);


#define fastItemRankIterationTimes 20
void fastItemRank(float IR[], float sta[][NumofItem], float dyn[], int times);
//void MatrixMulti(float c[NumofItem][NumofItem], float a[NumofItem][NumofItem], float b[NumofItem][NumofItem]);
//void selfMulti(float b[NumofItem][NumofItem], float a[NumofItem][NumofItem], int times);

/**
//*1:嘗試將Topic引入ItemRank
void ReadItem(string fileName, float itemData[NumofItem][NumofTopic]);
void TopicCorrelationMatrix(float data[NumofUser][NumofItem], float itemData[NumofItem][NumofTopic], float sta[NumofTopic][NumofTopic]);
void TopicDynamicMatrix(float data[NumofUser][NumofItem], float itemData[NumofItem][NumofTopic], float dynTopic[NumofUser][NumofTopic]);
void TopicRank(float IR[], float sta[][NumofTopic], float dyn[]);
void TopicMulti(float c[], float a[][NumofTopic], float b[]);
void TRtoIR(float itemData[NumofItem][NumofTopic], float TR[][NumofTopic], float IR[][NumofItem]);
void insert(int a[][3], int b[3], int length);
/**/

void show(float data[NumofUser][NumofItem], float IR[NumofUser][NumofItem]);