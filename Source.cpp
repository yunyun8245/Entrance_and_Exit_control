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
		int data[256][9] = { 0 };

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


		//----------------------
		//-カード関係の変数宣言-
		//----------------------
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
			printf("\n-----------------------------------------------------\n");
			fprintf(stderr, "Can't find FeliCa.");
			error_routine();
			printf("\n-----------------------------------------------------\n");
			is_get = 0;
			//return EXIT_FAILURE;
		}

		if (is_get == 1)
		{
			system("cls");
			//----------------------
			//-カード関係の変数宣言-
			//----------------------
			char IDm[] = "card IDm:";
			char PMm[] = "card PMm:";

			printf("\n-----------------------------------------------------\n");
			fprintf(stdout, "number of cards: %d\n", number_of_cards);
			print_vector(IDm, card_idm, sizeof(card_idm));
			print_vector(PMm, card_pmm, sizeof(card_pmm));
			printf("-----------------------------------------------------\n");
			
			//クローズする
			if (!close_reader_writer()) {
				fprintf(stderr, "Can't close reader writer.\n");
				return EXIT_FAILURE;
			}

			//ライブラリの解放
			if (!dispose_library()) {
				fprintf(stderr, "Can't dispose library.\n");
				return EXIT_FAILURE;
			}

			//表示できてるかの確認に使った
			//fprintf(stdout, "ERRORPOINT: %02x\n",distination[6]);

			int ret = 0, f_ret = -1,lastdata = 0;
			int found = 0;
			
			//---------------------------------------------------------------
			//-ファイルをオープンする----------------------------------------
			//-Datalis(MemberData.csv)に登録されているファイルをオープンする-
			//---------------------------------------------------------------
			if (fopen_s(&fp, Datalist, "r") == EOF)
			{
				printf("ERROR");
			}

			//------------------------------------------
			//-データの取得(全部のデータをdata[]に取得)-
			//------------------------------------------
			for (int num = 0; num < 256; num++)
			{
				//データの取得
				ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%u", &data[num][0], &data[num][1], &data[num][2], &data[num][3], &data[num][4], &data[num][5], &data[num][6], &data[num][7], &data[num][8]);

				//最後までいったらlastdataに最後のときのレコード数を保存する
				if (ret == EOF)
				{
					lastdata = num;
					break;
				}
				//データの表示
				printf("%d,%u,%u,%u,%u,%u,%u,%u,%u,%d\n", ret, data[num][0], data[num][1], data[num][2], data[num][3], data[num][4], data[num][5], data[num][6], data[num][7], data[num][8]);
			}
			//クローズ
			fclose(fp);

			//----------------------------------------------------------------
			//-データの検索(data[]の一覧から、取得してきたcard_idm[]をさがす)-
			//----------------------------------------------------------------
			for (int i = 0 ; i < 256 ; i++)
			{
				//最初にfoundを1にしておく。data[]と比較して違ったら0をいれる。
				found = 1;
				for (int j = 0 ; j < 8 ; j++)
				{
					if (data[i][j] != card_idm[j])
					{
						found = 0;
					}
				}

				//全ての配列のデータが一致したらfoundは1のままなのでBreakする。
				//f_retには一致したdata[]の添え字を保存しておく。
				if (found == 1)
				{
					f_ret = i;
					break;
				}
			}

			//---------------------------------------
			//-IDが見つかったらfoundが1、なかったら0-
			//---------------------------------------
			if (found == 1)
			{
				printf("\nFound your ID");

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

				//------------------------------------------
				//-入室しているかどうかでメッセージが変わる-
				//------------------------------------------
				int log_in_out = 0;
				if (is_exist == 0)
				{
					log_in_out = 1;
					printf("\n\n------System Message------");
					printf("\n\nHello !");
					printf("\nRecord your Login data");
					printf("\n\n--------------------------");
				}
				else if(is_exist == 1)
				{
					log_in_out = 0;
					printf("\n\n------System Message------");
					printf("\n\nSee you agein !");
					printf("\nRecord your Logout data");
					printf("\n\n--------------------------");
				}

				//-----------------------------------------------
				//-filenameで指定したファイル(LogData.csv)へ出力-
				//-----------------------------------------------
				fopen_s(&fp, filename, "a");

				//LoginかLogoutかのデータを出力
				fprintf(fp, "%u", log_in_out);			//LogDataに保存
				fprintf(fp, ",");						//LogDataに保存

				//カードのID出力
				for (int j = 0; j < 8;j++)
				{
					fprintf(fp, "%u", card_idm[j]);			//LogDataに保存
					fprintf(fp, ",");						//LogDataに保存
				}

				//ここは時間の出力
				error = localtime_s(&imanojikan, &jikan);
				printf("\n\nLogDataに出力しました。");
				printf("\n%d年 %d月 %d日 %d時 %d分 %d秒\n", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);

				fprintf(fp, "%04d,%02d%02d,%02d%02d%02d", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);

				fprintf(fp, "\n");							//最後に改行(LogData)
				fclose(fp);

				//--------------------------------------------------
				//-Datalistで指定したファイル(MemberData.csv)へ出力-
				//--------------------------------------------------
				if (fopen_s(&fp, Datalist, "w") == EOF)
				{
					printf("\nERROR");
				}

				//lastdataまでdata[]の中に入っているデータを書き出す
				for (int i = 0; i < lastdata; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						unsigned char distination = data[i][j];
						fprintf(fp, "%u", distination);		//MemberDataに保存
						fprintf(fp, ",");					//MemberDataに保存
					}

					//ここで入室しているかどうかのデータdata[][8]を書き込む
					fprintf(fp, "%u", data[i][8]);
					fprintf(fp, "\n");
				}
				fprintf(fp, "\n");							//最後に改行(MemberData.csv)
				fclose(fp);

				printf("\nFIN");
				printf("\n-----------------------------------------------------\n");
				sleep(2000);
			}
			else
			{
				printf("\nNot found");
				printf("\nFIN");
				printf("\n-----------------------------------------------------\n");

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