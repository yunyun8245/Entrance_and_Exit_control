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
//���C������
//**************
int main(void)
{
	int t;
	FILE *fp;
	//�A�N�Z�X����t�@�C��
	char filename[] = "../LogData.csv";
	char Datalist[] = "../MemberData.csv";

	int is_get;
	int is_exist;

	while (true)
	{
		int code = sleep(200);                        /* 10�b��~ = 10000*/
		time_t jikan = time(NULL);
		struct tm imanojikan;
		errno_t error;
		is_exist = 0;

		is_get = 1;
		int data[256][9] = { 0 };

		//���C�u�����̏�����
		if (!initialize_library()) {
			system("cls");
			fprintf(stderr, "Can't initialize library.\n");
			scanf_s("%d", &t);

			return EXIT_FAILURE;
		}

		//���[�_�^���C�^�̎����F���ƃI�[�v��
		if (!open_reader_writer_auto()) {
			fprintf(stderr, "Can't open reader writer.\n");
			scanf_s("%d", &t);
			return EXIT_FAILURE;
		}


		//----------------------
		//-�J�[�h�֌W�̕ϐ��錾-
		//----------------------
		structure_polling polling;
		unsigned char system_code[2] = { 0xff, 0xff };	//�ŏ���0x00������
		polling.system_code = system_code;
		polling.time_slot = 0x00;
		unsigned char number_of_cards = 0;
		structure_card_information card_information;
		unsigned char card_idm[8];
		unsigned char card_pmm[8];
		card_information.card_idm = card_idm;
		card_information.card_pmm = card_pmm;

		//�|�[�����O�ƃJ�[�h���̎擾(Polling �R�}���h)
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
			//-�J�[�h�֌W�̕ϐ��錾-
			//----------------------
			char IDm[] = "card IDm:";
			char PMm[] = "card PMm:";

			printf("\n-----------------------------------------------------\n");
			fprintf(stdout, "number of cards: %d\n", number_of_cards);
			print_vector(IDm, card_idm, sizeof(card_idm));
			print_vector(PMm, card_pmm, sizeof(card_pmm));
			printf("-----------------------------------------------------\n");
			
			//�N���[�Y����
			if (!close_reader_writer()) {
				fprintf(stderr, "Can't close reader writer.\n");
				return EXIT_FAILURE;
			}

			//���C�u�����̉��
			if (!dispose_library()) {
				fprintf(stderr, "Can't dispose library.\n");
				return EXIT_FAILURE;
			}

			//�\���ł��Ă邩�̊m�F�Ɏg����
			//fprintf(stdout, "ERRORPOINT: %02x\n",distination[6]);

			int ret = 0, f_ret = -1,lastdata = 0;
			int found = 0;
			
			//---------------------------------------------------------------
			//-�t�@�C�����I�[�v������----------------------------------------
			//-Datalis(MemberData.csv)�ɓo�^����Ă���t�@�C�����I�[�v������-
			//---------------------------------------------------------------
			if (fopen_s(&fp, Datalist, "r") == EOF)
			{
				printf("ERROR");
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
				printf("%d,%u,%u,%u,%u,%u,%u,%u,%u,%d\n", ret, data[num][0], data[num][1], data[num][2], data[num][3], data[num][4], data[num][5], data[num][6], data[num][7], data[num][8]);
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
				printf("\nFound your ID");

				//--------------------------
				//-���łɓ������Ă��邩�T��-
				//data[8]���P�Ȃ�������Ă�-
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
				//-�������Ă��邩�ǂ����Ń��b�Z�[�W���ς��-
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
				printf("\n\nLogData�ɏo�͂��܂����B");
				printf("\n%d�N %d�� %d�� %d�� %d�� %d�b\n", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);

				fprintf(fp, "%04d,%02d%02d,%02d%02d%02d", imanojikan.tm_year + 1900, imanojikan.tm_mon + 1, imanojikan.tm_mday, imanojikan.tm_hour, imanojikan.tm_min, imanojikan.tm_sec);

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
//�G���[�n�̊֐�
//�G���[����������Areturn�̒��O�ɏ����΃G���[ID���\�������
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
//�ǂ݂������l�̕\��
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