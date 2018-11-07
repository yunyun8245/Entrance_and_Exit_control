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
	FILE *fp, *fp_ex;
	char filename[] = "LogData.csv";
	char Datalist[] = "MemberData.csv";

	int is_get;
	int is_exist;
	while (true)
	{
		int code = sleep(200);                        /* 10秒停止 = 10000*/
		time_t jikan = time(NULL);
		struct tm imanojikan;
		errno_t error;
		is_exist = 0;

		is_get = 1;
		//ライブラリの初期化
		if (!initialize_library()) {
			system("cls");
			fprintf(stderr, "Can't initialize library.\n");
			scanf_s("%d", &t);

			return EXIT_FAILURE;
		}

		//リーダ／ライタの自動認識とオープン
		if (!open_reader_writer_auto()) {
			fprintf(stderr, "Can't open reader writer.\n");
			scanf_s("%d", &t);

			return EXIT_FAILURE;
		}

		structure_polling polling;
		unsigned char system_code[2] = { 0xff, 0xff };	//最初は0x00だった
		polling.system_code = system_code;
		polling.time_slot = 0x00;

		unsigned char number_of_cards = 0;

		structure_card_information card_information;
		unsigned char card_idm[8];
		unsigned char card_pmm[8];
		card_information.card_idm = card_idm;
		card_information.card_pmm = card_pmm;

		//ポーリングとカード情報の取得(Polling コマンド)
		if (!polling_and_get_card_information(&polling, &number_of_cards, &card_information)) {
			system("cls");
			fprintf(stderr, "Can't find FeliCa.\n");
			error_routine();
			//scanf_s("%d", &t);

			is_get = 0;
			//return EXIT_FAILURE;
		}

		if (is_get == 1)
		{
			system("cls");
			printf("\n-----------------------------------------------------\n");
			fprintf(stdout, "number of cards: %d\n", number_of_cards);

			char IDm[] = "card IDm:";
			char PMm[] = "card PMm:";

			print_vector(IDm, card_idm, sizeof(card_idm));
			print_vector(PMm, card_pmm, sizeof(card_pmm));
			printf("-----------------------------------------------------\n");
			
			if (!close_reader_writer()) {
				fprintf(stderr, "Can't close reader writer.\n");
				scanf_s("%d", &t);

				return EXIT_FAILURE;
			}

			//ライブラリの解放
			if (!dispose_library()) {
				fprintf(stderr, "Can't dispose library.\n");
				scanf_s("%d", &t);

				return EXIT_FAILURE;
			}

			//表示できてるかの確認に使った
			//fprintf(stdout, "ERRORPOINT: %02x\n",distination[6]);

			int ret = 0, f_ret = -1;
			int found = 0;
			int data[10][9] = { 0 };

			if (fopen_s(&fp, Datalist, "r") == EOF)
			{
				printf("ERROR");
			}

			//--------------
			//-データの取得-
			//--------------
			for (int num = 0; num < 10; num++)
			{
				ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%u", &data[num][0], &data[num][1], &data[num][2], &data[num][3], &data[num][4], &data[num][5], &data[num][6], &data[num][7], &data[num][8]);

				if (ret == EOF)
				{
					//data[num][0] = -1;
					printf("\n\nBREAK\n\n");
					break;
				}

				printf("%d,%u,%u,%u,%u,%u,%u,%u,%u,%d\n", ret, data[num][0], data[num][1], data[num][2], data[num][3], data[num][4], data[num][5], data[num][6], data[num][7], data[num][8]);

			}
			fclose(fp);

			//----------
			//-検索-
			//----------
			for (int i = 0 ; i < 10 ; i++)
			{
				found = 1;
				for (int j = 0 ; j < 8 ; j++)
				{
					if (data[i][j] != card_idm[j])
					{
						found = 0;
					}
				}
				if (found == 1)
				{
					f_ret = i;
					break;
				}
			}

			//IDが見つかったらfoundが1、なかったら0
			if (found == 1)
			{
				printf("\nFound your ID \n\n");

				//--------------------------
				//-すでに入室しているか探す-
				//data[8]が１なら入室してる-
				//--------------------------
				if (data[f_ret][8] == 0)
				{
					is_exist = 0;
					data[f_ret][8] = 0x1;
				}
				else if (data[f_ret][8] == 1)
				{
					is_exist = 1;
					data[f_ret][8] = 0x0;
				}
				else
				{
					is_exist = 0;
					data[f_ret][8] = 0x1;
				}
				//--ここまで--

				//is_existが0なら未入室→ログファイルへ書き出し
				if (is_exist == 0)
				{
					//--------------------------------------
					//---filenameで指定したファイルへ出力---
					//--------------------------------------
					fopen_s(&fp_ex, filename, "a");

					//ここはカードのID出力
					for (int j = 0; j < 8;j++)
					{
						fprintf(fp_ex, "%u", card_idm[j]);		//LogDataに保存
						fprintf(fp_ex, ",");					//LogDataに保存
					}
					//ここは時間の出力
					error = localtime_s(&imanojikan, &jikan);
					printf("\n現在の日付・時刻を書き出しました。\n");
					printf("\n%d年 %d月 %d日 %d時 %d分 %d秒\n", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);

					fprintf(fp_ex, "%04d%02d%02d%02d%02d%02d", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);

					fprintf(fp_ex, "\n");						//最後に改行(LogData)
					fclose(fp_ex);
					//ここまで


					if (fopen_s(&fp, Datalist, "w") == EOF)
					{
						printf("ERROR");
					}

					for (int i = 0 ; i < 10 ; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							fprintf(fp, "%d", data[i][j]);		//LogDataに保存
							fprintf(fp, ",");					//LogDataに保存
						}
						fprintf(fp, "\n");
						if (i == f_ret) break;
					}
					fclose(fp);
					
				}
				else if(is_exist == 1)
				{
					printf("\nYou are arleady in room\n");
				}

				printf("\nFIN");
				sleep(2000);
				//scanf_s("%d", &t);
			}
			else
			{
				printf("\nNot found \n\n");
				sleep(2000);
			}
		}
	}
	return EXIT_SUCCESS;
}

//*******************************************************************
//エラー系の関数
//エラー発生した後、returnの直前に書けばエラーIDが表示される
//*******************************************************************
void error_routine(void)
{
	enumernation_felica_error_type felica_error_type;
	enumernation_rw_error_type rw_error_type;
	get_last_error_types(&felica_error_type, &rw_error_type);
	printf("felica_error_type: %d\n", felica_error_type);
	printf("rw_error_type: %d\n", rw_error_type);

	close_reader_writer();
	dispose_library();
}

//***********************
//読みだした値の表示
//***********************
void print_vector(char* title, unsigned char* vector, int length)
{
	if (title != NULL) {
		fprintf(stdout, "%s ", title);
	}

	int i;
	for (i = 0; i < length - 1; i++) {
		fprintf(stdout, "%02x ", vector[i]);
	}
	fprintf(stdout, "%02x", vector[length - 1]);
	fprintf(stdout, "\n");
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