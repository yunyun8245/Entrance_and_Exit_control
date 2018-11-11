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
//****************<NameSolution�ɓo�^����Ă��郁���o�[�̃��R�[�h�𒊏o>*****************
//***************************************************************************************
//---------------------------------------------------------------------------------------

//**************
//���C������
//**************
int main(void)
{
	FILE *fp, *fp_logdata, *fp_dist;
	//�A�N�Z�X����t�@�C��
	char filename[] = "../LogData.csv";
	char Namelist[] = "../NameSolution.csv";
	char Distfile[] = "../DistinationRecord.csv";

	int Member[8];//NameSolution���玝���Ă����f�[�^�������
	char Name[256];//NameSolution��������Ă������O�f�[�^

	int data_log[8];//LogData���玝���Ă����f�[�^������
	int year;
	int day;
	int date;

	int ret_log;
	int ret = 0;
	int in_out = 0;//���O�C�������O�A�E�g���̕ϐ��󂯎��

	//--------------------------------------------------------
	//-�f�[�^�̎擾��NameSolution.csv����S���̃f�[�^���擾��-
	//--------------------------------------------------------
	if (fopen_s(&fp, Namelist, "r") == EOF)
	{
		printf("ERROR");
	}

	//NameSolution�̍Ō�̍s�܂ŌJ��Ԃ�
	while (true)
	{
		printf("\n--------------------------System message-------------------------\n");
		ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%s", &Member[0], &Member[1], &Member[2], &Member[3], &Member[4], &Member[5], &Member[6], &Member[7], Name);
		if (ret == EOF)
		{
			break;
		}
		//�擾�f�[�^�̕\��
		printf("\nSort data -> ID : [  %u,%u,%u,%u,%u,%u,%u,%u  ] ,NAME : [  %s  ]\n", Member[0], Member[1], Member[2], Member[3], Member[4], Member[5], Member[6], Member[7], Name);
		//***Member[]��NameSolution�̃J�[�hID�������Ă���/Name�ɖ��O�������Ă���***

		//---------------------------------------------
		//-�f�[�^�̎擾��LogData.csv����f�[�^���擾��-
		//---------------------------------------------
		if (fopen_s(&fp_logdata, filename, "r") == EOF)
		{
			printf("ERROR");
		}
		ret_log = 0;
		//LogData.csv�̍Ō�܂őS���ǂ�
		while (ret_log != EOF)
		{
			ret_log = fscanf_s(fp_logdata, "%u,%u,%u,%u,%u,%u,%u,%u,%u,%d,%d,%d", &in_out, &data_log[0], &data_log[1], &data_log[2], &data_log[3], &data_log[4], &data_log[5], &data_log[6], &data_log[7], &year, &day, &date);
			if (ret_log == EOF)
			{
				break;
			}

			//-----------------------------------------------------
			//-�f�[�^�̏o�́�DistinationRecord.csv�Ƀf�[�^���o�́�-
			//-----------------------------------------------------
			if (fopen_s(&fp_dist, Distfile, "a") == EOF)
			{
				printf("ERROR");
			}

			//intcmp�͔�r���ē�����������O���Ԃ��Ă���B�������Ȃ�������|�P�B
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
		system("cls");//�R���\�[���N���A
	}

	fclose(fp);
	printf("\nFIN");
	printf("\n\n-----------------------------------------------------------------");
	sleep(4000);
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


//num�͐擪�����r���鐔
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