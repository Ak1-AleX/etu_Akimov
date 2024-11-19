#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

// ����� ����������
void Menu(int pos_f, char days_1[], char months_1[], char years_1[]) {
	system("cls");
	printf("��� ����������� ������� ����������� ������� ����� ��� �����\n");
	printf("��� ���������� �������� ������� ENTER\n\n");

	// �������� ����������
	char face[4][80] = { "1) ���� ���� �������� (�� 1900 �� 2100�):", "2) ������ �������� ������:", "3) �������� ���� ���", "4) ����� �� ���������" };
	char arrow[8] = "    <--";
	for (int i = 1; i <= 4; i++) {
		printf("%s", face[i - 1]);

		if (i == 1) {
			printf("    %s.%s.%s", days_1, months_1, years_1);
		}

		if (i == pos_f) {
			printf("%s", arrow);
		}
		printf("\n");
	}
	printf("--------------------\n");
}

// ���� ����
void Date(int* day_f, int* ds_f, int* mts_f, int* yrs_f, char days_f[], char months_f[], char years_f[]) {
	system("cls");
	printf("������� ���� (��.��.����): ");

	// ������� ������� ��� ���� � ��� �����
	char date[] = { 's', 's', 's', 's', 's', 's', 's', 's' };
	short lenDate = 0;

	// ���� ����
	for (short i = 0; i < 8; i = lenDate) {
		unsigned char symDate = _getch();

		// ���� ������� �����
		if (isdigit(symDate)) {
			system("cls");
			printf("������� ���� (��.��.����): ");

			date[i] = symDate;
			lenDate += 1;

			// ����� ������������ �������
			for (short j = 0; j < 8; j++) {
				if (date[j] != 's') {
					printf("%c", date[j]);
					if (j == 1 || j == 3) {
						printf(".");
					}
				}
			}
		}

		// ���� ����� BACKSPACE
		if (symDate == '\b') {
			system("cls");
			printf("������� ���� (��.��.����): ");
			if (i != 0) {
				date[i - 1] = 's';
				lenDate -= 1;

				// ����� ������������ �������
				for (short j = 0; j < 8; j++) {
					if (date[j] != 's') {
						printf("%c", date[j]);
						if (j == 1 || j == 3) {
							printf(".");
						}
					}
				}
			}
		}

		// ���� ������ '.' ����� 1 ��� 3 �����
		if ((symDate == '.' || symDate == ':') && (i == 1 || i == 3)) {
			system("cls");
			printf("������� ���� (��.��.����): ");

			date[i] = date[i - 1];
			date[i - 1] = '0';
			lenDate += 1;

			// ����� ������������ �������
			for (short j = 0; j < 8; j++) {
				if (date[j] != 's') {
					printf("%c", date[j]);
					if (j == 1 || j == 3) {
						printf(".");
					}
				}
			}
		}
	}

	// ���������� �������� �������� ������� ����
	days_f[0] = date[0];
	days_f[1] = date[1];

	months_f[0] = date[2];
	months_f[1] = date[3];

	years_f[0] = date[4];
	years_f[1] = date[5];
	years_f[2] = date[6];
	years_f[3] = date[7];

	// ���������� �������� � ���������� ����
	*ds_f = strtol(days_f, NULL, 10);
	*mts_f = strtol(months_f, NULL, 10);
	*yrs_f = strtol(years_f, NULL, 10);

	// ������ �������� ���� ��� ������
	*day_f = strtol(date, NULL, 10);

	// ���������� ���� ��������� ���
	FILE* arcaneSave = fopen("log.txt", "a");
	fprintf(arcaneSave, "%s.%s.%s\n", days_f, months_f, years_f);
	fclose(arcaneSave);
}

// �������� �� ���������� ����
void Right(int pos_f, char days_1[], char months_1[], char years_1[], int* ds_f, int* mts_f, int* yrs_f) {

	// �������� �� ���������
	if ((1900 <= *yrs_f && *yrs_f <= 2100) && (1 <= *mts_f && *mts_f <= 12) && (
		(1 <= *ds_f && *ds_f <= 31) && (*mts_f == 1 || *mts_f == 3 || *mts_f == 5 || *mts_f == 7 || *mts_f == 8 || *mts_f == 10 || *mts_f == 12) ||
		(1 <= *ds_f && *ds_f <= 30) && (*mts_f == 4 || *mts_f == 6 || *mts_f == 9 || *mts_f == 11) ||
		(1 <= *ds_f && *ds_f <= 29) && (*yrs_f % 4 == 0) ||
		(1 <= *ds_f && *ds_f <= 28) && (*yrs_f % 4 != 0)
		)) {

		// ����� ����������
		Menu(pos_f, days_1, months_1, years_1);
	}

	// �������� �� �������
	else {
		*ds_f = 1;
		*mts_f = 1;
		*yrs_f = 2000;
		days_1[0] = '0';
		days_1[1] = '1';
		months_1[0] = '0';
		months_1[1] = '1';
		years_1[0] = '2';
		years_1[1] = '0';
		years_1[2] = '0';
		years_1[3] = '0';

		// ����� ����������
		Menu(pos_f, days_1, months_1, years_1);
		printf("����������� ��������� ����\n");
	}
}

// ����� ������
void Arcane(int* day_f) {

	// ������ �������� ������
	FILE* arcaneDesc = fopen("info.txt", "r");
	char arcaneLine[500];

	int arc = 0;
	int arc_day = day_f;
	while (arc_day > 0) {
		arc += arc_day % 10;
		arc_day /= 10;
	}

	// ���� ����� > 22
	if (arc > 22) {
		arc -= 22;
	}
	if (arc > 22) {
		arc -= 22;
	}
	printf("��� ������� �����: %d\n\n", arc);

	// ������ �������� ������ � ������
	for (int j = 1; j <= 23; j++) {

		memset(arcaneLine, ' ', sizeof(arcaneLine));
		fgets(arcaneLine, 200, arcaneDesc);

		if (j == arc) {
			printf("%s", arcaneLine);
		}
	}
	fclose(arcaneDesc);
}
