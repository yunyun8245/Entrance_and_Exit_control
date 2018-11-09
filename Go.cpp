// sample.cpp -*-c++-*-

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <time.h>
#include "felica.h"

int main(void);
void error_routine(void);
void print_vector(char* title, unsigned char* vector, int length);
int sleep(unsigned long);

//**************
//メイン処理
//**************
int main(void)
{
	int t;
	FILE *fp;
	//アクセスするファイル
	char filename[] = "../LogData.csv";
	char Datalist[] = "../MemberData.csv";

	int data[256][9];
	int Memberlist[256][9];

	int ret;

	//
	if (fopen_s(&fp, Datalist, "r") == EOF)
	{
		printf("ERROR");
	}

	//--------------
	//-データの取得-
	//--------------
	for (int num = 0; num < 256; num++)
	{
		ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%u", &data[num][0], &data[num][1], &data[num][2], &data[num][3], &data[num][4], &data[num][5], &data[num][6], &data[num][7], &data[num][8]);

		if (ret == EOF)
		{
			data[num][0] = -1;
			break;
		}

		printf("%d,%u,%u,%u,%u,%u,%u,%u,%u,%u\n", ret, data[num][0], data[num][1], data[num][2], data[num][3], data[num][4], data[num][5], data[num][6], data[num][7], data[num][8]);

	}
	fclose(fp);




}

/*********************************/
/*--- xミリ秒経過するのを待つ ---*/
/*--------sleep関数の定義--------*/
/*********************************/
int sleep(unsigned long x)
{
	clock_t  s = clock();
	clock_t  c;

	do {
		if ((c = clock()) == (clock_t)-1)       /* エラー */
			return (0);
	} while (1000UL * (c - s) / CLOCKS_PER_SEC <= x);
	return (1);
}