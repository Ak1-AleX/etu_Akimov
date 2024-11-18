#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

// функции
void Menu(int pos_f, char days_1[], char months_1[], char years_1[]);
void Date(int* day_f, int* ds_f, int* mts_f, int* yrs_f, char days_f[], char months_f[], char years_f[]);
void Right(int pos_f, char days_1[], char months_1[], char years_1[], int* ds_f, int* mts_f, int* yrs_f);
void Arcane(int* day_f);

// программа
int main() {

	// инициализация ПЕПРЕМЕННЫХ дней, месяцев, лет
	int ds_1 = 1;
	int mts_1 = 1;
	int yrs_1 = 2000;

	// инициализация МАССИВОВ дней, месяцев, лет
	char days_1[3] = "01";
	char months_1[3] = "01";
	char years_1[5] = "2000";

	// инициализация флага и аркана
	bool mainFlag = true;
	int day_1 = 4;
	char saveDate[20];
	memset(saveDate, ' ', sizeof(saveDate));

	// задание цвета консольным составляющим
	HANDLE a;
	a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(a, 13);

	// задание языка и вывод интерфейса	
	setlocale(LC_ALL, "Ru");
	int pos = 1;
	Menu(pos, days_1, months_1, years_1);

	while (mainFlag) {
		int ent = _getch();

		// проверка нажатия
		switch (ent) {

		// проверка нажатия ENTER
		case 13:

			// если выбран ввод даты
			if (pos == 1) {

				//ввод 1 даты
				Date(&day_1, &ds_1, &mts_1, &yrs_1, days_1, months_1, years_1);

				// проверка даты на корректность
				Right(pos, days_1, months_1, years_1, &ds_1, &mts_1, &yrs_1);
			}
			
			// если выбран расчер аркана
			if (pos == 2) {
				Menu(pos, days_1, months_1, years_1);
				
				// расчет аркана
				Arcane(day_1);
			}

			// если выбран вывод всех введенных дат
			if (pos == 3) {
				Menu(pos, days_1, months_1, years_1);
				printf("История введенных дат:\n");

				// вывод всех пердыдущих дат
				FILE* arcaneSave = fopen("log.txt", "r");
				while (fgets(saveDate, 20, arcaneSave) != NULL) {
					printf("%s", saveDate);
				}
			}

			// если выбран выход из программы
			if (pos == 4) {
				mainFlag = false;

				// перезапись истории дат в файле
				FILE* arcaneSave = fopen("log.txt", "w");
				fprintf(arcaneSave, "");
				fclose(arcaneSave);
			}
			break;

		//проверка нажатия стрелочек
		case 224:
			ent = _getch();

			// стрелка вверх
			if (ent == 72) {
				if (pos != 1) {
					pos -= 1;
					Menu(pos, days_1, months_1, years_1);
				}
				else if (pos == 1) {
					pos = 4;
					Menu(pos, days_1, months_1, years_1);
				}
			}

			// стрелка вниз
			if (ent == 80) {
				if (pos != 4) {
					pos += 1;
					Menu(pos, days_1, months_1, years_1);
				}
				else if (pos == 4) {
					pos = 1;
					Menu(pos, days_1, months_1, years_1);
				}
			}
			break;

		// проверка нажатия цифр (1 - 4)
		case 49:
			pos = 1;
			Menu(pos, days_1, months_1, years_1);
			break;
		case 50:
			pos = 2;
			Menu(pos, days_1, months_1, years_1);
			break;
		case 51:
			pos = 3;
			Menu(pos, days_1, months_1, years_1);
			break;
		case 52:
			pos = 4;
			Menu(pos, days_1, months_1, years_1);
			break;

		// проверка нажатия ESC
		case 27:
			
			// перезапись истории дат в файле
			if (true);
			FILE* arcaneSave = fopen("log.txt", "w");
			fprintf(arcaneSave, "");
			fclose(arcaneSave);

			exit(0);
			break;
		}
	}
}

// вывод интерфейса
void Menu(int pos_f, char days_1[], char months_1[], char years_1[]) {
	system("cls");
	printf("Для перемещения стрелки используйте стрелки вверх или цифры\n");
	printf("Для выполнения действия нажмите ENTER\n\n");

	// создание интерфейса
	char face[4][80] = { "1) Ввод даты рождения (от 1900 до 2100г):", "2) Расчет старшего аркана:", "3) Просмотр всех дат", "4) Выход из программы" };
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

// ввод даты
void Date(int* day_f, int* ds_f, int* mts_f, int* yrs_f, char days_f[], char months_f[], char years_f[]) {
	system("cls");
	printf("Введите дату (дд.мм.гггг): ");

	// задание массива для даты и его длины
	char date[] = { 's', 's', 's', 's', 's', 's', 's', 's' };
	short lenDate = 0;

	// ввод даты
	for (short i = 0; i < 8; i = lenDate) {
		unsigned char symDate = _getch();

		// если введено число
		if (isdigit(symDate)) {
			system("cls");
			printf("Введите дату (дд.мм.гггг): ");

			date[i] = symDate;
			lenDate += 1;

			// вывод обновленного массива
			for (short j = 0; j < 8; j++) {
				if (date[j] != 's') {
					printf("%c", date[j]);
					if (j == 1 || j == 3) {
						printf(".");
					}
				}
			}
		}

		// если нажат BACKSPACE
		if (symDate == '\b') {
			system("cls");
			printf("Введите дату (дд.мм.гггг): ");
			if (i != 0) {
				date[i - 1] = 's';
				lenDate -= 1;

				// вывод обновленного массива
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

		// если нажато '.' после 1 или 3 числа
		if ((symDate == '.' || symDate == ':') && (i == 1 || i == 3)) {
			system("cls");
			printf("Введите дату (дд.мм.гггг): ");

			date[i] = date[i - 1];
			date[i - 1] = '0';
			lenDate += 1;

			// вывод обновленного массива
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

	// присвоение массивам значений массива даты
	days_f[0] = date[0];
	days_f[1] = date[1];

	months_f[0] = date[2];
	months_f[1] = date[3];

	years_f[0] = date[4];
	years_f[1] = date[5];
	years_f[2] = date[6];
	years_f[3] = date[7];

	// присовение массивов в переменные даты
	*ds_f = strtol(days_f, NULL, 10);
	*mts_f = strtol(months_f, NULL, 10);
	*yrs_f = strtol(years_f, NULL, 10);

	// полное значение даты для аркана
	*day_f = strtol(date, NULL, 10);

	// сохранение всех введенных дат
	FILE* arcaneSave = fopen("log.txt", "a");
	fprintf(arcaneSave, "%s.%s.%s\n", days_f, months_f, years_f);
	fclose(arcaneSave);
}

// проверка на правильную дату
void Right(int pos_f, char days_1[], char months_1[], char years_1[], int* ds_f, int* mts_f, int* yrs_f){

	// проверка на валидацию
	if ((1900 <= *yrs_f && *yrs_f <= 2100) && (1 <= *mts_f && *mts_f <= 12) && (
		(1 <= *ds_f && *ds_f <= 31) && (*mts_f == 1 || *mts_f == 3 || *mts_f == 5 || *mts_f == 7 || *mts_f == 8 || *mts_f == 10 || *mts_f == 12) ||
		(1 <= *ds_f && *ds_f <= 30) && (*mts_f == 4 || *mts_f == 6 || *mts_f == 9 || *mts_f == 11) ||
		(1 <= *ds_f && *ds_f <= 29) && (*yrs_f % 4 == 0) ||
		(1 <= *ds_f && *ds_f <= 28) && (*yrs_f % 4 != 0)
		)) {

		// вывод интерфейса
		Menu(pos_f, days_1, months_1, years_1);
	}

	// значенне по дефолту
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

		// вывод интерфейса
		Menu(pos_f, days_1, months_1, years_1);
		printf("Некорректно введенная дата\n");
	}
}

// вывод аркана
void Arcane(int* day_f) {

	// расчет старшего аркана
	FILE* arcaneDesc = fopen("info.txt", "r");
	char arcaneLine[500];

	int arc = 0;
	int arc_day = day_f;
	while (arc_day > 0) {
		arc += arc_day % 10;
		arc_day /= 10;
	}

	// если аркан > 22
	if (arc > 22) {
		arc -= 22;
	}
	if (arc > 22) {
		arc -= 22;
	}
	printf("Ваш старший аркан: %d\n\n", arc);

	// запись описания аркана в массив
	for (int j = 1; j <= 23; j++) {

		memset(arcaneLine, ' ', sizeof(arcaneLine));
		fgets(arcaneLine, 200, arcaneDesc);

		if (j == arc) {
			printf("%s", arcaneLine);
		}
	}
	fclose(arcaneDesc);
}
