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

void MemberInitialize();
void MemberChange();
void ChangeOrDelete(int point);
void DeleteMem(int point);
void ChangeMem(string data, int point);
void LogClear();

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

		cout << endl << "メインメニュー" <<endl<<" 1 : メンバーの管理"<<endl<<" 2 : ログデータの初期化"<<endl<<" 入力 :";
		cin >> in_data;

		if (in_data == "1")
		{
			cout << endl << endl << "メンバーの管理";
			MemberManage();
		}
		else if (in_data == "2")
		{
			cout << endl << "ログデータの初期化";
			LogClear();
		}
		else
		{
			cout << endl << "選択肢の数字を入力してください";
		}
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

//ログデータの初期化☆++
void LogClear()
{
	system("cls");
	printf("\n*-- LogClearを開きました");
	FILE *fp;
	//アクセスするファイル
	char filename[] = "../DataFiles/LogData.csv";

	string y_n;
	while (1)
	{
		cout << endl << endl << "本当に初期化してもよろしいですか？(y / n) : ";
		cin >> y_n;

		if (y_n == "y")
		{
			
			//---------------------------------------------------------------
			//-ファイルをオープンする----------------------------------------
			//-Datalis(LogData.csv)に登録されているファイルをオープンする-
			//---------------------------------------------------------------
			if (fopen_s(&fp, filename, "w") == EOF)//wは上書き
			{
				printf("\n\n\n***-- Not found LogData.csv --***\n\n\n");
			}
			fclose(fp);
			
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
	

	cout << endl << endl << "DELETE : "<< point;
}

//変更++
void ChangeMem(string data, int point)
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
	printf("\n*-- ChangeManageを開きました");
	cout <<endl<< "new_name : "<<data;

	
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
		printf("\nret : %d", ret);
		strcpy_s(n_name[num], h_name);
		if (ret == EOF)
		{
			breakpoint = num;
			fclose(fp);
			printf("\n\n-----------------------------------------------");
			break;
		}
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
	for (num = 0; num < 256; num++)
	{
		if (num == breakpoint) break;
		//printf("\n No. %3d : %s ", num + 1, n_name[num]);
		fprintf(fp, "%u,%u,%u,%u,%u,%u,%u,%u,", hoge[num][0], hoge[num][1], hoge[num][2], hoge[num][3], hoge[num][4], hoge[num][5], hoge[num][6], hoge[num][7]);

		if (num + 1 != point)
		{
			fprintf(fp, "%s\n", n_name[num]);
		}
		else 
		{
			char testes[256];
			strcpy_s(testes,data.c_str());
			fprintf(fp, "%s\n", testes);
		}
	}
	fclose(fp);

	
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