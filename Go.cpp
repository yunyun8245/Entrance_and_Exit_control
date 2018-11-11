// sample.cpp -*-c++-*-

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <time.h>

int main(void);
int sleep(unsigned long);
int intcmp(int *a,int *b , int num);

//---------------------------------------------------------------------------------------
//***************************************************************************************
//****************<NameSolutionに登録されているメンバーのレコードを抽出>*****************
//***************************************************************************************
//---------------------------------------------------------------------------------------

//**************
//メイン処理
//**************
int main(void)
{
	FILE *fp, *fp_logdata, *fp_dist;
	//アクセスするファイル
	char filename[] = "../LogData.csv";
	char Namelist[] = "../NameSolution.csv";
	char Distfile[] = "../DistinationRecord.csv";

	int Member[8];//NameSolutionから持ってきたデータをいれる
	char Name[256];//NameSolutionからもってきた名前データ

	int data_log[8];//LogDataから持ってきたデータが入る
	int year;
	int day;
	int date;

	int ret_log;
	int ret = 0;
	int in_out = 0;//ログインかログアウトかの変数受け取る

	//--------------------------------------------------------
	//-データの取得＜NameSolution.csvから全員のデータを取得＞-
	//--------------------------------------------------------
	if (fopen_s(&fp, Namelist, "r") == EOF)
	{
		printf("ERROR");
	}

	//NameSolutionの最後の行まで繰り返す
	while (true)
	{
		printf("\n--------------------------System message-------------------------\n");
		ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%s", &Member[0], &Member[1], &Member[2], &Member[3], &Member[4], &Member[5], &Member[6], &Member[7], Name);
		if (ret == EOF)
		{
			break;
		}
		//取得データの表示
		printf("\nSort data -> ID : [  %u,%u,%u,%u,%u,%u,%u,%u  ] ,NAME : [  %s  ]\n", Member[0], Member[1], Member[2], Member[3], Member[4], Member[5], Member[6], Member[7], Name);
		//***Member[]にNameSolutionのカードIDが入っている/Nameに名前が入っている***

		//---------------------------------------------
		//-データの取得＜LogData.csvからデータを取得＞-
		//---------------------------------------------
		if (fopen_s(&fp_logdata, filename, "r") == EOF)
		{
			printf("ERROR");
		}
		ret_log = 0;
		//LogData.csvの最後まで全部読む
		while (ret_log != EOF)
		{
			ret_log = fscanf_s(fp_logdata, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%d,%d,%d", &in_out, &data_log[0], &data_log[1], &data_log[2], &data_log[3], &data_log[4], &data_log[5], &data_log[6], &data_log[7], &year, &day, &date);
			if (ret_log == EOF)
			{
				break;
			}

			//-----------------------------------------------------
			//-データの出力＜DistinationRecord.csvにデータを出力＞-
			//-----------------------------------------------------
			if (fopen_s(&fp_dist, Distfile, "a") == EOF)
			{
				printf("ERROR");
			}

			//intcmpは比較して等しかったら０が返ってくる。等しくなかったら－１。
			if (intcmp(data_log,Member,8) == 0) 
			{
				printf("\nRECORDED DATA -> ID : %u,%u,%u,%u,%u,%u,%u,%u  ,DATE  :  %d %d %d", data_log[0], data_log[1], data_log[2], data_log[3], data_log[4], data_log[5], data_log[6], data_log[7], year, day, date);
				
				fprintf(fp_dist, "%s",Name);
				fprintf(fp_dist, ",");

				if (in_out == 0)
				{
					fprintf(fp_dist, "OUT");
					fprintf(fp_dist, ",");
				}
				else if (in_out == 1)
				{
					fprintf(fp_dist, "IN");
					fprintf(fp_dist, ",");
				}

				fprintf(fp_dist, "%d,%d,%d", year, day, date);
				fprintf(fp_dist, "\n");
			}
			fclose(fp_dist);
		}
		fclose(fp_logdata);
		printf("\n\n %s 's all data was imported.",Name);
		printf("\n\n-----------------------------------------------------------------");
		sleep(1500);
		system("cls");//コンソールクリア
	}

	fclose(fp);
	printf("\nFIN");
	printf("\n\n-----------------------------------------------------------------");
	sleep(4000);
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


//numは先頭から比較する数
int intcmp(int *a, int *b, int num)
{
	int ans = 0;
	for (int i = 0; i < num; i++)
	{
		if (a[i]!=b[i])
		{
			ans = -1;
		}
	}
	return ans;
}