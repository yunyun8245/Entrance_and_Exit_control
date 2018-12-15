// sample.cpp -*-c++-*-

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

int main(void);
int sleep(unsigned long);

int ShowMemberList();

void MemberManage();
void LogManage();

void MemberInitialize();
void MemberChange();
void ChangeOrDelete(int point);
void DeleteMem(int point);
void ChangeMem(string data, int point);

//**************
//メイン処理☆++
//**************
int main(void)
{
	int t;
	FILE *fp;
	//アクセスするファイル
	char filename[] = "../DataFiles/LogData.csv";
	char Datalist[] = "../DataFiles/MemberData.csv";
	char Namelist[] = "../DataFiles/NameSolution.csv";

	while (true)
	{
		time_t jikan = time(NULL);
		struct tm imanojikan;
		errno_t error;

		int input_flag_1 = 0;

		int code = sleep(200);                        /* 10秒停止 = 10000*/

		string in_data;

		cout << endl << "メインメニュー" <<endl<<" 1 : メンバーの管理"<<endl<<" 2 : ログデータの管理"<<endl<<" 入力 :";
		cin >> in_data;

		if (in_data == "1")
		{
			cout << endl << endl << "メンバーの管理";
			MemberManage();
		}
		else if (in_data == "2")
		{
			cout << endl << "ログデータの管理";
			LogManage();
		}
		else
		{
			cout << endl << "選択肢の数字を入力してください";
		}
		/*
			int ret = 0, f_ret = -1,lastdata = 0;
			int found = 0;
			
			//---------------------------------------------------------------
			//-ファイルをオープンする----------------------------------------
			//-Datalis(MemberData.csv)に登録されているファイルをオープンする-
			//---------------------------------------------------------------
			if (fopen_s(&fp, Datalist, "r") == EOF)
			{
				printf("\n\n\n***-- Not found MemberData.csv --***\n\n\n");
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
				//printf("%d,%u,%u,%u,%u,%u,%u,%u,%u,%d\n", ret, data[num][0], data[num][1], data[num][2], data[num][3], data[num][4], data[num][5], data[num][6], data[num][7], data[num][8]);
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
				
				printf("\n  Found your ID  ");

				//PlaySound("../wav/login.wav",NULL,SND_FILENAME);

				//--------------------------
				//-すでに入室しているか探す-
				//data[8]が１なら入室してる-
				//--------------------------
				if (data[f_ret][8] == 0)
				{
					//ログイン処理
					is_exist = 0;
					data[f_ret][8] = 0x1;
					//PlaySound("../wav/login.wav",NULL,SND_FILENAME);
				}
				else if (data[f_ret][8] == 1)
				{
					//ログアウト処理
					is_exist = 1;
					data[f_ret][8] = 0x0;
					//PlaySound("../wav/logout.wav",NULL,SND_FILENAME);
				}
				else
				{
					//エラー処理
					is_exist = 0;
					data[f_ret][8] = 0x1;
					//PlaySound("../wav/error.wav",NULL,SND_FILENAME);
				}

				//------------------------------------------
				//-入室しているかどうかでメッセージが変わる-
				//------------------------------------------
				int log_in_out = 0;
				if (is_exist == 0)
				{
					log_in_out = 1;
					printf("\n\n-------System Message-------");
					printf("\n\n       Hello !");
					printf("\n\n  **-- Login success! --**");
					printf("\n\n----------------------------");
				}
				else if(is_exist == 1)
				{
					log_in_out = 0;
					printf("\n\n-------System Message-------");
					printf("\n\n       See you agein !");
					printf("\n\n  **-- Logout success! --**");
					printf("\n\n----------------------------");
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
				printf("\n\n  **-- LogDataに出力しました --**");
				printf("\n  %d年 %d月 %d日 %d時 %d分 %d秒 \n", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);

				fprintf(fp, "%04d,%02d,%02d,%02d,%02d,%02d", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);

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
				
				if(is_exist == 0)		PlaySound("../wav/login.wav", NULL, SND_FILENAME);
				else if(is_exist == 1)	PlaySound("../wav/logout.wav", NULL, SND_FILENAME);


				printf("\nFIN");
				printf("\n-----------------------------------------------------\n");
				sleep(1500);
			}
			else
			{
				printf("\n  Not found your ID");
				PlaySound("../wav/error.wav", NULL, SND_FILENAME);
				printf("\n\nFIN");
				printf("\n-----------------------------------------------------\n");

				sleep(1500);
			}
		}
		else if (is_get == 0)
		{
			int hoge[256] = { 0x0 };
			char h_name[256] = { 0x0 };
			printf("\n-----------* Member list *---------------------------\n");

			//---------------------------------------------------------------
			//-ファイルをオープンする----------------------------------------
			//-Datalis(MemberData.csv)に登録されているファイルをオープンする-
			//---------------------------------------------------------------
			if (fopen_s(&fp, Datalist, "r") == EOF)
			{
				printf("\n\n\n***-- Not found MemberData.csv --***\n\n\n");
			}

			//------------------------------------------
			//-データの取得(全部のデータをdata[]に取得)-
			//------------------------------------------
			int lastdata=0;
			for (int num = 0; num < 256; num++)
			{
				//データの取得
				int ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%u", &data[num][0], &data[num][1], &data[num][2], &data[num][3], &data[num][4], &data[num][5], &data[num][6], &data[num][7], &data[num][8]);

				//最後までいったらlastdataに最後のときのレコード数を保存する
				if (ret == EOF)
				{
					lastdata = num;
					break;
				}
			}
			//クローズ
			fclose(fp);


			if (fopen_s(&fp, Namelist, "r") == EOF)
			{
				printf("\nERROR");
			}

			printf("\n   [ State]  Number   Name");
			//printf("\n   [  %s  ]  No. %d : %s ");
			for (int num = 0; num < lastdata; num++)
			{
				int ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%s", hoge, hoge, hoge, hoge, hoge, hoge, hoge, hoge, h_name);
				if (ret == EOF)
				{
					break;
				}
				//取得したデータの表示
				char inout[4];
				if (data[num][8]==1)
				{
					strcpy_s(inout,"○");
				}
				else
				{
					strcpy_s(inout, "×");
				}
				printf("\n   [  %s  ]  No. %3d : %s ", inout, num + 1, h_name);
			}
			fclose(fp);
			printf("\n\n-----------------------------------------------------");


		}
		*/
	}
	return 0;
}

//メンバーリストの表示☆
//戻り値はメンバーの数
int ShowMemberList()
{
	FILE *fp;
	char Namelist[] = "../DataFiles/NameSolution.csv";

	printf("\n\n----------------Member list--------------------\n");
	int hoge[256] = { 0x0 };
	char h_name[256] = { 0x0 };
	int num = 0;
	int ret = 0;
	if (fopen_s(&fp, Namelist, "r") == EOF)
	{
		printf("\nERROR");
	}
	for (num = 0; num < 256; num++)
	{
		printf("", num);//なぜかこれがあると動く
		ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%s", hoge, hoge, hoge, hoge, hoge, hoge, hoge, hoge, h_name);
		//printf("\nret : %d",ret);
		if (ret == EOF)
		{
			fclose(fp);
			printf("\n\n-----------------------------------------------");

			return num;
		}
		//取得したデータの表示
		printf("\n No. %3d : %s", num + 1, h_name);
	}
	fclose(fp);
	printf("\n\n-----------------------------------------------");

	return num;
}

//メンバーの管理☆++
void MemberManage()
{
	system("cls");
	printf("\n*-- MemberManageを開きました");
	int flag_input_1 = 0;
	string in_data;

	while (1)
	{
		//メンバーの一覧表示
		int test = ShowMemberList();

		cout << endl << "メンバー管理メニュー" << endl << " 1 : メンバーの名前変更/削除" << endl << " 2 : メンバーの初期化" << endl << " 入力 :";
		cin >> in_data;

		if (in_data == "1")
		{
			//メンバーの名前の変更/削除
			MemberChange();
		}
		else if (in_data == "2")
		{
			//メンバーの初期化
			MemberInitialize();
		}
		else
		{
			cout << endl << "選択肢の数字を入力してください";
		}
	}

}

//ログの管理
void LogManage()
{
	system("cls");
	printf("\n*-- LogManageを開きました");
}

//メンバーの初期化++
void MemberInitialize()
{
	system("cls");
	printf("\n*-- MemberInitializeを開きました");
	FILE *fp;
	//アクセスするファイル
	char Datalist[] = "../DataFiles/MemberData.csv";
	char Namelist[] = "../DataFiles/NameSolution.csv";

	string y_n;
	while (1)
	{
		cout << endl << endl << "本当に初期化してもよろしいですか？(y / n) : ";
		cin >>y_n;

		if (y_n == "y")
		{
			/*
			//---------------------------------------------------------------
			//-ファイルをオープンする----------------------------------------
			//-Datalis(MemberData.csv)に登録されているファイルをオープンする-
			//---------------------------------------------------------------
			if (fopen_s(&fp, Datalist, "w") == EOF)//wは上書き
			{
			printf("\n\n\n***-- Not found MemberData.csv --***\n\n\n");
			}
			fclose(fp);

			//------------------------------------------------------------------
			//-ファイルをオープンする-------------------------------------------
			//-Namelist(NameSolution.csv)に登録されているファイルをオープンする-
			//------------------------------------------------------------------
			if (fopen_s(&fp, Namelist, "w") == EOF)
			{
			printf("\n\n\n***-- Not found NameSolution.csv --***\n\n\n");
			}
			fclose(fp);
			*/
			cout << endl << "初期化しました";
			break;
		}
		else if (y_n == "n")
		{
			cout << endl << "キャンセルしました";
			break;
		}
		else
		{
			cout << endl << "選択肢にある数字を入力してください";
		}
	}
}

//メンバーの名前変更/削除☆++
void MemberChange()
{
	system("cls");
	printf("\n*-- MemberChangeを開きました");
	FILE *fp;
	char filename[] = "../DataFiles/LogData.csv";
	char Datalist[] = "../DataFiles/MemberData.csv";
	char Namelist[] = "../DataFiles/NameSolution.csv";

	string in_data;

	while (1)
	{

		//メンバーの一覧表示
		int num_list = ShowMemberList();

		cout << endl << endl << "変更/削除したいメンバーのNumberを入力してください(0 : キャンセル)"<<endl<<"入力 : ";
		cin >> in_data;

		int num_input = stoi(in_data);
		if (in_data == "0")
		{
			cout << endl << "キャンセルしました";
			break;
		}

		if ((num_input > num_list) || (0>num_input))
		{
			cout << endl << "存在しないメンバーです";
			//printf("%d",num_list);
		}
		else
		{
			//探索を開始
			int hoge[256] = { 0x0 };
			int is_exist = 1;
			char h_name[256] = { 0x0 };
			if (fopen_s(&fp, Namelist, "r") == EOF)
			{
				cout << endl << "Not found file \"Namelist\"";
			}

			for (int num = 0; num < 256; num++)
			{
				int ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%s", hoge, hoge, hoge, hoge, hoge, hoge, hoge, hoge, h_name);
				if (num+1 == num_input)
				{
					break;
				}

				if (ret == EOF)
				{
					printf("\n\nError！！\n\n");
					is_exist = 0;
					break;
				}
			}
			std::fclose(fp);

			if (is_exist == 0)
			{
				//ほぼあり得ないエラー
				break;
			}
			else
			{
				//名前の変更/削除
				cout << endl << h_name << "さんの名前を変更/削除します";
				sleep(1000);
				ChangeOrDelete(num_input);
				break;
			}
		}
	}
}

//削除か変更か☆++
void ChangeOrDelete(int point)
{
	system("cls");
	printf("\n*-- ChangeOrDeleteを開きました");
	while (1)
	{
		string new_name;
		cout << endl << "新しい名前を入力してください(0だと削除)"<<endl<<"入力 : ";
		cin >> new_name;

		if (new_name=="0")
		{
			DeleteMem(point);
		}
		else
		{
			ChangeMem(new_name,point);
		}
		break;
	}
}

//削除++
void DeleteMem(int point)
{
	FILE *fp;
	char Datalist[] = "../DataFiles/MemberData.csv";
	char Namelist[] = "../DataFiles/NameSolution.csv";

	int hoge[256][8] = { 0x0 };
	char h_name[256] = { 0x0 };
	char n_name[256][256] = { 0x0 };
	int num, ret;
	int breakpoint = 0;

	system("cls");
	printf("\n*-- DeleteMemを開きました");

	/*
	//------------------------------------------------------------------
	//-ファイルをオープンする-------------------------------------------
	//-Namelist(NameSolution.csv)に登録されているファイルをオープンする-
	//------------------------------------------------------------------
	if (fopen_s(&fp, Namelist, "r") == EOF)
	{
		printf("\n\n\n***-- Not found NameSolution.csv --***\n\n\n");
	}	
	for (num = 0; num < 256; num++)
	{
		printf("", num);//なぜかこれがあると動く
		ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%s", &hoge[num][0], &hoge[num][1], &hoge[num][2], &hoge[num][3], &hoge[num][4], &hoge[num][5], &hoge[num][6], &hoge[num][7], h_name);
		printf("\nret : %d",ret);
		strcpy_s(n_name[num], h_name);
		if (ret == EOF)
		{
			breakpoint = num;
			fclose(fp);
			printf("\n\n-----------------------------------------------");
			break;
		}
		//取得したデータの表示
	}
	fclose(fp);

	//------------------------------------------------------------------
	//-ファイルをオープンする-------------------------------------------
	//-Namelist(NameSolution.csv)に登録されているファイルをオープンする-
	//------------------------------------------------------------------
	if (fopen_s(&fp, Namelist, "w") == EOF)
	{
		printf("\n\n\n***-- Not found NameSolution.csv --***\n\n\n");
	}
	for (num = 0 ; num < 256 ; num++)
	{
		if (num == breakpoint) break;
		if (num+1 != point)
		{
			//printf("\n No. %3d : %s ", num + 1, n_name[num]);
			fprintf(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%s\n", hoge[num][0], hoge[num][1], hoge[num][2], hoge[num][3], hoge[num][4], hoge[num][5], hoge[num][6], hoge[num][7], n_name[num]);

		}
	}
	fclose(fp);

	//*ここで一つ目のファイル書き換え終了*

	int next_hoge[256][9] = { 0x0 };

	//---------------------------------------------------------------
	//-ファイルをオープンする----------------------------------------
	//-Datalis(MemberData.csv)に登録されているファイルをオープンする-
	//---------------------------------------------------------------
	if (fopen_s(&fp, Datalist, "r") == EOF)//wは上書き
	{
		printf("\n\n\n***-- Not found MemberData.csv --***\n\n\n");
	}
	for (num = 0; num < 256; num++)
	{
		printf("", num);//なぜかこれがあると動く
		ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%u", &next_hoge[num][0], &next_hoge[num][1], &next_hoge[num][2], &next_hoge[num][3], &next_hoge[num][4], &next_hoge[num][5], &next_hoge[num][6], &next_hoge[num][7], &next_hoge[num][8]);
		printf("\nret : %d", ret);
		if (ret == EOF)
		{
			breakpoint = num;
			fclose(fp);
			printf("\n\n-----------------------------------------------");
			break;
		}
		//取得したデータの表示
	}
	fclose(fp);

	//---------------------------------------------------------------
	//-ファイルをオープンする----------------------------------------
	//-Datalis(MemberData.csv)に登録されているファイルをオープンする-
	//---------------------------------------------------------------
	if (fopen_s(&fp, Datalist, "w") == EOF)//wは上書き
	{
		printf("\n\n\n***-- Not found MemberData.csv --***\n\n\n");
	}
	for (num = 0; num < 256; num++)
	{
		if (num == breakpoint) break;
		if (num + 1 != point)
		{
			fprintf(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%u\n", next_hoge[num][0], next_hoge[num][1], next_hoge[num][2], next_hoge[num][3], next_hoge[num][4], next_hoge[num][5], next_hoge[num][6], next_hoge[num][7], next_hoge[num][8]);
		}
	}
	fclose(fp);

	//*ここで２つめのファイルの変更終了*
	*/

	cout << endl << endl << "DELETE : "<< point;
}

//変更++
void ChangeMem(string data, int point)
{
	system("cls");
	printf("\n*-- ChangeManageを開きました");
	cout <<endl<< "new_name : "<<data;


	cout << endl << endl << "CHANGE : " << point;
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