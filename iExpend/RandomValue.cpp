#include"Header.h"

/****************************************Random Number**********************************************
給予希望的最大值與最小值，就能產生介於這兩個值中的隨機數，這個隨機亂數也可能等於最大值，或等於最小值。
其亂數值是依照時間所產生，所以重複呼叫時，會給予不同的亂數值(整數)。
***************************************************************************************************/
int RandomNumber(int MinValue, int MaxValue)   //Both MinValue and MaxValue are included
{
	//srand((unsigned)time(NULL));//這行要放在乎叫此函式的涵式中
	int R = (rand() % (MaxValue - MinValue + 1)) + MinValue;
	return R;
}