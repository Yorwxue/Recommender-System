#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include <ctime>
#include<iomanip>

using namespace std;

#define parameter_a 0.001
#define parameter_b 0.08
#define chainReserve 0.3
#define stableRatio 0.01
#define delAssemblyTopicRatio 0.01

template<class T>
class List;
class UserClass;
class ItemClass;
class TopicClass;

double Probability(string A, int TableName, int TableNo, int ListName, double Parameter);
//double ConditionProbability(string A, int TableNameA, int TableNoA, int ListNameA, string B, int TableNameB, int TableNoB, int ListNameB);
void Read();
void Reset(int TableName);
void ReadForTesting();
void ReplaceAll(string& str, const string& from, const string& to);
void* SearchTable(int TableName, string ID, string Name);
void* Inquiry(int TableName, int TableNo);
int Statistics(int TableName, int TableNo, int ListName, string QueryID);
void* new2d(int h, int w, int size);
int RandomNumber(int MinValue, int MaxValue);
void quickSort(double arr[], int append[], int append2[], int left, int right);
double Similarity(double A[], double B[], int Length, int kind);
void newTopic(double** ItemToTopicTable, double** TopicToItemTable);
void BaseProbability(double** ItemToTopicTable, double** TopicToItemTable, int NumofItem, int NumofTopic);
void* GetTable(int TableName);
void Apply();
void delApply(string delID);
