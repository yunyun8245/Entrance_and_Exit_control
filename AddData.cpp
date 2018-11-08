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
	char Datalist[] = "MemberData.csv";

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
			fprintf(stderr, "Can't find FeliCa.\n");
			error_routine();
			//scanf_s("%d", &t);

			is_get = 0;
			//return EXIT_FAILURE;
		}

		if (is_get == 1)
		{
			system("cls");

			fprintf(stdout, "number of cards: %d\n", number_of_cards);

			char IDm[] = "card IDm:";
			char PMm[] = "card PMm:";

			print_vector(IDm, card_idm, sizeof(card_idm));
			print_vector(PMm, card_pmm, sizeof(card_pmm));

			if (!close_reader_writer()) {
				fprintf(stderr, "Can't close reader writer.\n");
				scanf_s("%d", &t);

				return EXIT_FAILURE;
			}

			//���C�u�����̉��
			if (!dispose_library()) {
				fprintf(stderr, "Can't dispose library.\n");
				scanf_s("%d", &t);

				return EXIT_FAILURE;
			}


			int ret = 0, f_ret = 0, found = 0;
			int data[10][9] = {0x0};

			if (fopen_s(&fp, Datalist, "r") == EOF)
			{
				printf("ERROR");
			}

			//--------------
			//-�f�[�^�̎擾-
			//--------------
			for (int num = 0; num < 15; num++)
			{
				ret = fscanf_s(fp, "%u,%u,%u,%u,%u,%u,%u,%u,%u", &data[num][0], &data[num][1], &data[num][2], &data[num][3], &data[num][4], &data[num][5], &data[num][6], &data[num][7], &data[num][8]);

				if (ret == EOF)
				{
					data[num][0] = -1;
					break;
				}

				printf("%d,%u,%u,%u,%u,%u,%u,%u,%u,%u\n", ret, data[num][0], data[num][1], data[num][2], data[num][3], data[num][4], data[num][5], data[num][6], data[num][7], data[num][8]);

			}
			fclose(fp);
			//�\���ł��Ă邩�̊m�F�Ɏg����
			//fprintf(stdout, "ERRORPOINT: %02x\n", data[f_ret][6]);

			//----------
			//-��r����-
			//----------
			for (int i = 0; i < 10; i++)
			{
				found = 1;
				for (int j = 0; j < 8; j++)
				{
					if (data[i][j] != card_idm[j])
					{
						found = 0;
					}
				}
				if (found == 1)
				{
					f_ret = i;
					//printf("%d", f_ret);
					break;
				}
			}

			//ID������������found��1�A�Ȃ�������0
			if (found == 1)
			{
				printf("\nFound your ID \n");

				printf("\nYou has arleady recorded\n");

				sleep(3000);

			}
			else
			{
				printf("\nNot found in member list\n\n");
				if (fopen_s(&fp, Datalist, "a") == EOF)
				{
					printf("ERROR");
				}

				for (int j = 0; j < 8; j++)
				{
					fprintf(fp, "%u", card_idm[j]);		//MemberData�ɕۑ�
					fprintf(fp, ",");					//MemberData�ɕۑ�
				}
				unsigned char tt = 0;
				fprintf(fp, "%u", tt);
				fprintf(fp, "\n");
				fclose(fp);

				printf("\nFIN");
				sleep(2000);
				//scanf_s("%d", &t);
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