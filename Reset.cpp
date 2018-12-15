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
//���C��������++
//**************
int main(void)
{
	int t;
	FILE *fp;
	//�A�N�Z�X����t�@�C��
	char filename[] = "../DataFiles/LogData.csv";
	char Datalist[] = "../DataFiles/MemberData.csv";
	char Namelist[] = "../DataFiles/NameSolution.csv";

	while (true)
	{
		time_t jikan = time(NULL);
		struct tm imanojikan;
		errno_t error;

		int input_flag_1 = 0;

		int code = sleep(200);                        /* 10�b��~ = 10000*/

		string in_data;

		cout << endl << "���C�����j���[" <<endl<<" 1 : �����o�[�̊Ǘ�"<<endl<<" 2 : ���O�f�[�^�̏�����"<<endl<<" ���� :";
		cin >> in_data;

		if (in_data == "1")
		{
			cout << endl << endl << "�����o�[�̊Ǘ�";
			MemberManage();
		}
		else if (in_data == "2")
		{
			cout << endl << "���O�f�[�^�̏�����";
			LogClear();
		}
		else
		{
			cout << endl << "�I�����̐�������͂��Ă�������";
		}
	}
	return 0;
}

//�����o�[���X�g�̕\����
//�߂�l�̓����o�[�̐�
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
		printf("", num);//�Ȃ������ꂪ����Ɠ���
		ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%s", hoge, hoge, hoge, hoge, hoge, hoge, hoge, hoge, h_name);
		//printf("\nret : %d",ret);
		if (ret == EOF)
		{
			fclose(fp);
			printf("\n\n-----------------------------------------------");

			return num;
		}
		//�擾�����f�[�^�̕\��
		printf("\n No. %3d : %s", num + 1, h_name);
	}
	fclose(fp);
	printf("\n\n-----------------------------------------------");

	return num;
}

//�����o�[�̊Ǘ���++
void MemberManage()
{
	system("cls");
	printf("\n*-- MemberManage���J���܂���");
	int flag_input_1 = 0;
	string in_data;

	while (1)
	{
		//�����o�[�̈ꗗ�\��
		int test = ShowMemberList();

		cout << endl << "�����o�[�Ǘ����j���[" << endl << " 1 : �����o�[�̖��O�ύX/�폜" << endl << " 2 : �����o�[�̏�����" << endl << " ���� :";
		cin >> in_data;

		if (in_data == "1")
		{
			//�����o�[�̖��O�̕ύX/�폜
			MemberChange();
		}
		else if (in_data == "2")
		{
			//�����o�[�̏�����
			MemberInitialize();
		}
		else
		{
			cout << endl << "�I�����̐�������͂��Ă�������";
		}
	}

}

//���O�f�[�^�̏�������++
void LogClear()
{
	system("cls");
	printf("\n*-- LogClear���J���܂���");
	FILE *fp;
	//�A�N�Z�X����t�@�C��
	char filename[] = "../DataFiles/LogData.csv";

	string y_n;
	while (1)
	{
		cout << endl << endl << "�{���ɏ��������Ă���낵���ł����H(y / n) : ";
		cin >> y_n;

		if (y_n == "y")
		{
			
			//---------------------------------------------------------------
			//-�t�@�C�����I�[�v������----------------------------------------
			//-Datalis(LogData.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
			//---------------------------------------------------------------
			if (fopen_s(&fp, filename, "w") == EOF)//w�͏㏑��
			{
				printf("\n\n\n***-- Not found LogData.csv --***\n\n\n");
			}
			fclose(fp);
			
			cout << endl << "���������܂���";
			break;
		}
		else if (y_n == "n")
		{
			cout << endl << "�L�����Z�����܂���";
			break;
		}
		else
		{
			cout << endl << "�I�����ɂ��鐔������͂��Ă�������";
		}
	}

}


//�����o�[�̏�����++
void MemberInitialize()
{
	system("cls");
	printf("\n*-- MemberInitialize���J���܂���");
	FILE *fp;
	//�A�N�Z�X����t�@�C��
	char Datalist[] = "../DataFiles/MemberData.csv";
	char Namelist[] = "../DataFiles/NameSolution.csv";

	string y_n;
	while (1)
	{
		cout << endl << endl << "�{���ɏ��������Ă���낵���ł����H(y / n) : ";
		cin >>y_n;

		if (y_n == "y")
		{
			
			//---------------------------------------------------------------
			//-�t�@�C�����I�[�v������----------------------------------------
			//-Datalis(MemberData.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
			//---------------------------------------------------------------
			if (fopen_s(&fp, Datalist, "w") == EOF)//w�͏㏑��
			{
			printf("\n\n\n***-- Not found MemberData.csv --***\n\n\n");
			}
			fclose(fp);

			//------------------------------------------------------------------
			//-�t�@�C�����I�[�v������-------------------------------------------
			//-Namelist(NameSolution.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
			//------------------------------------------------------------------
			if (fopen_s(&fp, Namelist, "w") == EOF)
			{
			printf("\n\n\n***-- Not found NameSolution.csv --***\n\n\n");
			}
			fclose(fp);
			
			cout << endl << "���������܂���";
			break;
		}
		else if (y_n == "n")
		{
			cout << endl << "�L�����Z�����܂���";
			break;
		}
		else
		{
			cout << endl << "�I�����ɂ��鐔������͂��Ă�������";
		}
	}
}

//�����o�[�̖��O�ύX/�폜��++
void MemberChange()
{
	system("cls");
	printf("\n*-- MemberChange���J���܂���");
	FILE *fp;
	char filename[] = "../DataFiles/LogData.csv";
	char Datalist[] = "../DataFiles/MemberData.csv";
	char Namelist[] = "../DataFiles/NameSolution.csv";

	string in_data;

	while (1)
	{

		//�����o�[�̈ꗗ�\��
		int num_list = ShowMemberList();

		cout << endl << endl << "�ύX/�폜�����������o�[��Number����͂��Ă�������(0 : �L�����Z��)"<<endl<<"���� : ";
		cin >> in_data;

		int num_input = stoi(in_data);
		if (in_data == "0")
		{
			cout << endl << "�L�����Z�����܂���";
			break;
		}

		if ((num_input > num_list) || (0>num_input))
		{
			cout << endl << "���݂��Ȃ������o�[�ł�";
			//printf("%d",num_list);
		}
		else
		{
			//�T�����J�n
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
					printf("\n\nError�I�I\n\n");
					is_exist = 0;
					break;
				}
			}
			std::fclose(fp);

			if (is_exist == 0)
			{
				//�قڂ��蓾�Ȃ��G���[
				break;
			}
			else
			{
				//���O�̕ύX/�폜
				cout << endl << h_name << "����̖��O��ύX/�폜���܂�";
				sleep(1000);
				ChangeOrDelete(num_input);
				break;
			}
		}
	}
}

//�폜���ύX����++
void ChangeOrDelete(int point)
{
	system("cls");
	printf("\n*-- ChangeOrDelete���J���܂���");
	while (1)
	{
		string new_name;
		cout << endl << "�V�������O����͂��Ă�������(0���ƍ폜)"<<endl<<"���� : ";
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

//�폜++
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
	printf("\n*-- DeleteMem���J���܂���");

	
	//------------------------------------------------------------------
	//-�t�@�C�����I�[�v������-------------------------------------------
	//-Namelist(NameSolution.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
	//------------------------------------------------------------------
	if (fopen_s(&fp, Namelist, "r") == EOF)
	{
		printf("\n\n\n***-- Not found NameSolution.csv --***\n\n\n");
	}	
	for (num = 0; num < 256; num++)
	{
		printf("", num);//�Ȃ������ꂪ����Ɠ���
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
		//�擾�����f�[�^�̕\��
	}
	fclose(fp);

	//------------------------------------------------------------------
	//-�t�@�C�����I�[�v������-------------------------------------------
	//-Namelist(NameSolution.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
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

	//*�����ň�ڂ̃t�@�C�����������I��*

	int next_hoge[256][9] = { 0x0 };

	//---------------------------------------------------------------
	//-�t�@�C�����I�[�v������----------------------------------------
	//-Datalis(MemberData.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
	//---------------------------------------------------------------
	if (fopen_s(&fp, Datalist, "r") == EOF)//w�͏㏑��
	{
		printf("\n\n\n***-- Not found MemberData.csv --***\n\n\n");
	}
	for (num = 0; num < 256; num++)
	{
		printf("", num);//�Ȃ������ꂪ����Ɠ���
		ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%u", &next_hoge[num][0], &next_hoge[num][1], &next_hoge[num][2], &next_hoge[num][3], &next_hoge[num][4], &next_hoge[num][5], &next_hoge[num][6], &next_hoge[num][7], &next_hoge[num][8]);
		printf("\nret : %d", ret);
		if (ret == EOF)
		{
			breakpoint = num;
			fclose(fp);
			printf("\n\n-----------------------------------------------");
			break;
		}
		//�擾�����f�[�^�̕\��
	}
	fclose(fp);

	//---------------------------------------------------------------
	//-�t�@�C�����I�[�v������----------------------------------------
	//-Datalis(MemberData.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
	//---------------------------------------------------------------
	if (fopen_s(&fp, Datalist, "w") == EOF)//w�͏㏑��
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

	//*�����łQ�߂̃t�@�C���̕ύX�I��*
	

	cout << endl << endl << "DELETE : "<< point;
}

//�ύX++
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
	printf("\n*-- ChangeManage���J���܂���");
	cout <<endl<< "new_name : "<<data;

	
	//------------------------------------------------------------------
	//-�t�@�C�����I�[�v������-------------------------------------------
	//-Namelist(NameSolution.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
	//------------------------------------------------------------------
	if (fopen_s(&fp, Namelist, "r") == EOF)
	{
		printf("\n\n\n***-- Not found NameSolution.csv --***\n\n\n");
	}
	for (num = 0; num < 256; num++)
	{
		printf("", num);//�Ȃ������ꂪ����Ɠ���
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
	//-�t�@�C�����I�[�v������-------------------------------------------
	//-Namelist(NameSolution.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
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
/*--- x�~���b�o�߂���̂�҂� ---*/
/*--------sleep�֐��̒�`--------*/
/*********************************/
int sleep(unsigned long x)
{
	clock_t  s = clock();
	clock_t  c;

	do {
		if ((c = clock()) == (clock_t)-1)       /* �G���[ */
			return (0);
	} while (1000UL * (c - s) / CLOCKS_PER_SEC <= x);
	return (1);
}