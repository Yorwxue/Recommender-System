#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;


//processing
#define NumofClass 943  //�ϥΪ̼ƥ�
#define NumofData 100000  //����`����
#define NumofEntry 4  //�@����Ʀ��X�Ӳӥ�
//#define CareNo 0  //sorting�ɪ��̾ڡAClass���W�٩Ҧb

//observed
#define NumofUser 943
#define NumofItem 1682
#define NumofTopic 19
#define NumofInfo 4
void ReadItem(string fileName, double itemData[NumofItem][NumofTopic]);


void quickSort(int arr[], int left, int right);
void quickSort(int arr[NumofData][NumofEntry], int left, int right, int CareNo);
void Read(string fileName, int careNo);
void Write(string fileName, string fileName2);
void ReplaceAll(string& str, const string& from, const string& to);
int RandomNumber(int MinValue, int MaxValue);
void write_info_for_read(string fileName);
void Write5(string fileName, string fileName2, string fileName3, string fileName4, string fileName5);