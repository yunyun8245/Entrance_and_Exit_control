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

		cout << endl << "���C�����j���[" <<endl<<" 1 : �����o�[�̊Ǘ�"<<endl<<" 2 : ���O�f�[�^�̊Ǘ�"<<endl<<" ���� :";
		cin >> in_data;

		if (in_data == "1")
		{
			cout << endl << endl << "�����o�[�̊Ǘ�";
			MemberManage();
		}
		else if (in_data == "2")
		{
			cout << endl << "���O�f�[�^�̊Ǘ�";
			LogManage();
		}
		else
		{
			cout << endl << "�I�����̐�������͂��Ă�������";
		}
		/*
			int ret = 0, f_ret = -1,lastdata = 0;
			int found = 0;
			
			//---------------------------------------------------------------
			//-�t�@�C�����I�[�v������----------------------------------------
			//-Datalis(MemberData.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
			//---------------------------------------------------------------
			if (fopen_s(&fp, Datalist, "r") == EOF)
			{
				printf("\n\n\n***-- Not found MemberData.csv --***\n\n\n");
			}

			//------------------------------------------
			//-�f�[�^�̎擾(�S���̃f�[�^��data[]�Ɏ擾)-
			//------------------------------------------
			for (int num = 0; num < 256; num++)
			{
				//�f�[�^�̎擾
				ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%u", &data[num][0], &data[num][1], &data[num][2], &data[num][3], &data[num][4], &data[num][5], &data[num][6], &data[num][7], &data[num][8]);

				//�Ō�܂ł�������lastdata�ɍŌ�̂Ƃ��̃��R�[�h����ۑ�����
				if (ret == EOF)
				{
					lastdata = num;
					break;
				}
				//�f�[�^�̕\��
				//printf("%d,%u,%u,%u,%u,%u,%u,%u,%u,%d\n", ret, data[num][0], data[num][1], data[num][2], data[num][3], data[num][4], data[num][5], data[num][6], data[num][7], data[num][8]);
			}
			//�N���[�Y
			fclose(fp);

			//----------------------------------------------------------------
			//-�f�[�^�̌���(data[]�̈ꗗ����A�擾���Ă���card_idm[]��������)-
			//----------------------------------------------------------------
			for (int i = 0 ; i < 256 ; i++)
			{
				//�ŏ���found��1�ɂ��Ă����Bdata[]�Ɣ�r���Ĉ������0�������B
				found = 1;
				for (int j = 0 ; j < 8 ; j++)
				{
					if (data[i][j] != card_idm[j])
					{
						found = 0;
					}
				}

				//�S�Ă̔z��̃f�[�^����v������found��1�̂܂܂Ȃ̂�Break����B
				//f_ret�ɂ͈�v����data[]�̓Y������ۑ����Ă����B
				if (found == 1)
				{
					f_ret = i;
					break;
				}
			}

			//---------------------------------------
			//-ID������������found��1�A�Ȃ�������0-
			//---------------------------------------
			if (found == 1)
			{
				
				printf("\n  Found your ID  ");

				//PlaySound("../wav/login.wav",NULL,SND_FILENAME);

				//--------------------------
				//-���łɓ������Ă��邩�T��-
				//data[8]���P�Ȃ�������Ă�-
				//--------------------------
				if (data[f_ret][8] == 0)
				{
					//���O�C������
					is_exist = 0;
					data[f_ret][8] = 0x1;
					//PlaySound("../wav/login.wav",NULL,SND_FILENAME);
				}
				else if (data[f_ret][8] == 1)
				{
					//���O�A�E�g����
					is_exist = 1;
					data[f_ret][8] = 0x0;
					//PlaySound("../wav/logout.wav",NULL,SND_FILENAME);
				}
				else
				{
					//�G���[����
					is_exist = 0;
					data[f_ret][8] = 0x1;
					//PlaySound("../wav/error.wav",NULL,SND_FILENAME);
				}

				//------------------------------------------
				//-�������Ă��邩�ǂ����Ń��b�Z�[�W���ς��-
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
				//-filename�Ŏw�肵���t�@�C��(LogData.csv)�֏o��-
				//-----------------------------------------------
				fopen_s(&fp, filename, "a");

				//Login��Logout���̃f�[�^���o��
				fprintf(fp, "%u", log_in_out);			//LogData�ɕۑ�
				fprintf(fp, ",");						//LogData�ɕۑ�

				//�J�[�h��ID�o��
				for (int j = 0; j < 8;j++)
				{
					fprintf(fp, "%u", card_idm[j]);			//LogData�ɕۑ�
					fprintf(fp, ",");						//LogData�ɕۑ�
				}

				//�����͎��Ԃ̏o��
				error = localtime_s(&imanojikan, &jikan);
				printf("\n\n  **-- LogData�ɏo�͂��܂��� --**");
				printf("\n  %d�N %d�� %d�� %d�� %d�� %d�b \n", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);

				fprintf(fp, "%04d,%02d,%02d,%02d,%02d,%02d", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);

				fprintf(fp, "\n");							//�Ō�ɉ��s(LogData)
				fclose(fp);

				//--------------------------------------------------
				//-Datalist�Ŏw�肵���t�@�C��(MemberData.csv)�֏o��-
				//--------------------------------------------------
				if (fopen_s(&fp, Datalist, "w") == EOF)
				{
					printf("\nERROR");
				}

				//lastdata�܂�data[]�̒��ɓ����Ă���f�[�^�������o��
				for (int i = 0; i < lastdata; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						unsigned char distination = data[i][j];
						fprintf(fp, "%u", distination);		//MemberData�ɕۑ�
						fprintf(fp, ",");					//MemberData�ɕۑ�
					}

					//�����œ������Ă��邩�ǂ����̃f�[�^data[][8]����������
					fprintf(fp, "%u", data[i][8]);
					fprintf(fp, "\n");
				}
				fprintf(fp, "\n");							//�Ō�ɉ��s(MemberData.csv)
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
			//-�t�@�C�����I�[�v������----------------------------------------
			//-Datalis(MemberData.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
			//---------------------------------------------------------------
			if (fopen_s(&fp, Datalist, "r") == EOF)
			{
				printf("\n\n\n***-- Not found MemberData.csv --***\n\n\n");
			}

			//------------------------------------------
			//-�f�[�^�̎擾(�S���̃f�[�^��data[]�Ɏ擾)-
			//------------------------------------------
			int lastdata=0;
			for (int num = 0; num < 256; num++)
			{
				//�f�[�^�̎擾
				int ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%u", &data[num][0], &data[num][1], &data[num][2], &data[num][3], &data[num][4], &data[num][5], &data[num][6], &data[num][7], &data[num][8]);

				//�Ō�܂ł�������lastdata�ɍŌ�̂Ƃ��̃��R�[�h����ۑ�����
				if (ret == EOF)
				{
					lastdata = num;
					break;
				}
			}
			//�N���[�Y
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
				//�擾�����f�[�^�̕\��
				char inout[4];
				if (data[num][8]==1)
				{
					strcpy_s(inout,"��");
				}
				else
				{
					strcpy_s(inout, "�~");
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

//���O�̊Ǘ�
void LogManage()
{
	system("cls");
	printf("\n*-- LogManage���J���܂���");
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
			/*
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
			*/
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

	/*
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
	*/

	cout << endl << endl << "DELETE : "<< point;
}

//�ύX++
void ChangeMem(string data, int point)
{
	system("cls");
	printf("\n*-- ChangeManage���J���܂���");
	cout <<endl<< "new_name : "<<data;


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