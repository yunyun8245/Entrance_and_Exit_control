// sample.cpp -*-c++-*-

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <time.h>

int main(void);
int sleep(unsigned long);
int intcmp(int *a,int *b , int num);
void calcsec(struct tm t1, struct tm t2, int *data);


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
	char filename[] = "../DataFiles/LogData.csv";
	char Namelist[] = "../DataFiles/NameSolution.csv";
	char Distfile[256] = "../RecordFiles/Record_";

	int Member[8];//NameSolutionから持ってきたデータをいれる
	char Name[256];//NameSolutionからもってきた名前データ

	int data_log[8];//LogDataから持ってきたデータが入る
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

	int ret_log;
	int ret = 0;
	int in_out = 0;//ログインかログアウトかの変数受け取る


	//時間関係の変数
	int code = sleep(200);                        /* 10秒停止 = 10000*/
	time_t jikan = time(NULL);
	struct tm imanojikan;
	struct tm t_in;
	struct tm t_out;
	int ans_day[5] = { 0 };
	errno_t error;
	t_in.tm_year = 0;
	t_in.tm_mon = 0;
	t_in.tm_mday = 0;
	t_in.tm_hour = 0;
	t_in.tm_min = 0;
	t_in.tm_sec = 0;


	error = localtime_s(&imanojikan, &jikan);

	//出力ファイルの名前を生成
	//printf("\n%d年 %d月 %d日 %d時 %d分 %d秒\n", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);
	int year_b= imanojikan.tm_year + 1900, month_b= imanojikan.tm_mon + 1, day_b= imanojikan.tm_mday, hour_b= imanojikan.tm_hour, min_b= imanojikan.tm_min;
	char year_t[256];
	char month_t[256];
	char day_t[256];
	char hour_t[256];
	char min_t[256];
	char csv[] = ".csv";
	char bar[] = "-";
	//文字列に変換
	_itoa_s(year_b, year_t, sizeof(year_t), 10);
	_itoa_s(month_b, month_t, sizeof(month_t), 10);
	_itoa_s(day_b, day_t, sizeof(day_t), 10);
	_itoa_s(hour_b, hour_t, sizeof(hour_t), 10);
	_itoa_s(min_b, min_t, sizeof(min_t), 10);
	
	//名前にしていく
	strcat_s(Distfile, year_t);
	strcat_s(Distfile, bar);
	strcat_s(Distfile, month_t);
	strcat_s(Distfile, bar);
	strcat_s(Distfile, day_t);
	strcat_s(Distfile, bar);
	strcat_s(Distfile, hour_t);
	strcat_s(Distfile, bar);
	strcat_s(Distfile, min_t);

	//最後に.csvをつける
	strcat_s(Distfile, csv);


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

		//-----------------------------------------------------
		//-データの出力＜DistinationRecord.csvにデータを出力＞-
		//-----------------------------------------------------
		if (fopen_s(&fp_dist, Distfile, "a") == EOF)
		{
			printf("ERROR");
		}

		int ex = 0;

		//LogData.csvの最後まで全部読む
		while (ret_log != EOF)
		{
			ret_log = fscanf_s(fp_logdata, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%d,%d,%d,%d,%d,%d", &in_out, &data_log[0], &data_log[1], &data_log[2], &data_log[3], &data_log[4], &data_log[5], &data_log[6], &data_log[7], &year,&month, &day,&hour,&min, &sec);
			if (ret_log == EOF)
			{
				break;
			}

			//intcmpは比較して等しかったら０が返ってくる。等しくなかったら－１。
			if (intcmp(data_log,Member,8) == 0) 
			{
				ex = 1;
				printf("\nRECORDED DATA -> ID : %u,%u,%u,%u,%u,%u,%u,%u  ,DATE  :  %d %d %d %d %d %d", data_log[0], data_log[1], data_log[2], data_log[3], data_log[4], data_log[5], data_log[6], data_log[7], year, month, day, hour, min, sec);
				
				fprintf(fp_dist, "%s",Name);
				fprintf(fp_dist, ",");

				if (in_out == 0)
				{
					fprintf(fp_dist, "OUT");
					fprintf(fp_dist, ",");
					fprintf(fp_dist, "%d,%d,%d,%d,%d,%d", year, month, day, hour, min, sec);
					fprintf(fp_dist, "\n");
					//t_outにデータを入れる
					t_out.tm_year = year;
					t_out.tm_mon =month;
					t_out.tm_mday =day;
					t_out.tm_hour =hour;
					t_out.tm_min =min;
					t_out.tm_sec =sec;

					calcsec(t_in, t_out, ans_day);
					printf("\n         %d日 %d時間 %d分 %d秒",ans_day[0], ans_day[1], ans_day[2], ans_day[3]);

					fprintf(fp_dist, "滞在時間,%d日,%d時間,%d分,%d秒", ans_day[0], ans_day[1], ans_day[2], ans_day[3]);
					fprintf(fp_dist, "\n");
				}
				else if (in_out == 1)
				{
					fprintf(fp_dist, "IN");
					fprintf(fp_dist, ",");
					fprintf(fp_dist, "%d,%d,%d,%d,%d,%d", year, month, day, hour, min, sec);
					fprintf(fp_dist, "\n");
					//t_inにデータを入れる
					t_in.tm_year = year;
					t_in.tm_mon = month;
					t_in.tm_mday = day;
					t_in.tm_hour = hour;
					t_in.tm_min = min;
					t_in.tm_sec = sec;
				}

				//fprintf(fp_dist, "%d,%d,%d,%d,%d,%d", year, month, day, hour, min, sec);
				//fprintf(fp_dist, "\n");
			}
		}
		if(ex == 1)fprintf(fp_dist, "\n");
		fclose(fp_dist);
		fclose(fp_logdata);
		printf("\n\n %s 's all data was imported.",Name);
		printf("\n\n-----------------------------------------------------------------");
		sleep(500);
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


int is_leap_year(int year)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) ? 1 : 0;
}

void calcsec(struct tm t1,struct tm t2, int *data)
{
	int days_of_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int yy_1 = t1.tm_year, mm_1 = t1.tm_mon, dd_1 = t1.tm_mday, hh_1 = t1.tm_hour, mn_1 = t1.tm_min, ss_1 = t1.tm_sec;
	int yy_2 = t2.tm_year, mm_2 = t2.tm_mon, dd_2 = t2.tm_mday, hh_2 = t2.tm_hour, mn_2 = t2.tm_min, ss_2 = t2.tm_sec;
	int leap_years = 0;
	int days = 0;
	int hour_ans = 0;
	int min_ans = 0;
	int sec_ans = 0;
	int i;

	/* うるう年の数 */
	for (i = yy_1 + 1; i < yy_2; i++)
	{
		if (is_leap_year(i)) leap_years++;
	}

	/* yy_1-yy_2間の日数（yy_1, yy_2の年は含まない） */
	if (yy_2 - yy_1 > 1)
	{
		days += (yy_2 - yy_1 - 1) * 365 + leap_years;
	}

	/* yy_1, yy_2の年の日数 */
	/* 同じ年かどうかで振り分け */
	if (yy_1 == yy_2)
	{
		/* 同じ月かどうかで振り分け */
		if (mm_1 == mm_2)
		{
			days += dd_2 - dd_1;
		}
		else
		{
			if (is_leap_year(yy_1)) if ((mm_1 == 1 || mm_1 == 2) && mm_2 > 2) days++;
			for (i = mm_1 + 1; i <= mm_2 - 1; i++) days += days_of_month[i];
			days += days_of_month[mm_1] - dd_1;
			days += dd_2;
		}
	}
	/* if ( yy_1 != yy_2 ) */
	else
	{
		if (is_leap_year(yy_1)) if (mm_1 == 1 || mm_1 == 2) days++;
		if (is_leap_year(yy_2)) if (mm_2 > 2) days++;
		for (i = mm_1 + 1; i <= 12; i++) days += days_of_month[i];
		for (i = 1; i <= mm_2 - 1; i++) days += days_of_month[i];
		days += days_of_month[mm_1] - dd_1;
		days += dd_2;
	}

	if(hh_2-hh_1>0)
	{
		hour_ans += (hh_2 - hh_1);
	}
	else if (hh_2-hh_1<0)
	{
		days -= 1;
		hour_ans += ((hh_2+24) - hh_1);
	}

	if (mn_2- mn_1>0)
	{
		min_ans += (mn_2 - mn_1);
	}
	else if (mn_2-mn_1<0)
	{
		hour_ans -= 1;
		min_ans += ((mn_2 + 60) - mn_1);
	}

	if (ss_2 - ss_1>0)
	{
		sec_ans += (ss_2 - ss_1);
	}
	else if (ss_2 - ss_1<0)
	{
		min_ans -= 1;
		sec_ans += ((ss_2 + 60) - ss_1);
	}

	//printf("\n\n\n\n%d 日\n", days);
	//printf("\n%d 時間\n", hour_ans);
	//printf("\n%d 分\n", min_ans);
	//printf("\n%d 秒\n", sec_ans);

	data[0] = days;
	data[1] = hour_ans;
	data[2] = min_ans;
	data[3] = sec_ans;

}

