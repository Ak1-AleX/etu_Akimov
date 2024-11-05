#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>


int Menu(int pos_f, char days_1[], char months_1[], char years_1[]);
int Date(long* day_f, long* ds_f, long* mts_f, long* yrs_f, char days_f[], char months_f[], char years_f[]);


int main() {

	// инициализация ПЕПРЕМЕННЫХ дней, месяцев, лет
	long ds_1 = 1;
	long mts_1 = 1;
	long yrs_1 = 2000;

	// инициализация МАССИВОВ дней, месяцев, лет
	char days_1[3] = "01";
	char months_1[3] = "01";
	char years_1[5] = "2000";

	// инициализация флага и аркана
	bool mainFlag = true;
	long day_1 = 4;
	char saveDate[20];
	memset(saveDate, ' ', sizeof(saveDate));

	// перезапись истории дат в файле
	FILE* arcaneSave = fopen("log.txt", "w");
	fprintf(arcaneSave, "");
	fclose(arcaneSave);

	// задание языка и вывод интерфейса
	HANDLE a;
	a = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(a, 13);
	setlocale(LC_ALL, "Ru");
	int pos = 1;
	Menu(pos, days_1, months_1, years_1);

	while (mainFlag) {
		int ent = _getch();
		switch (ent) {

			// проверка нажатия ENTER
		case 13:
			if (pos == 1) {

				//ввод 1 даты
				Date(&day_1, &ds_1, &mts_1, &yrs_1, days_1, months_1, years_1);

				// проверка на валидацию
				if ((1900 <= yrs_1 && yrs_1 <= 2100) && (1 <= mts_1 && mts_1 <= 12) && (
					(1 <= ds_1 && ds_1 <= 31) && (mts_1 == 1 || mts_1 == 3 || mts_1 == 5 || mts_1 == 7 || mts_1 == 8 || mts_1 == 10 || mts_1 == 12) ||
					(1 <= ds_1 && ds_1 <= 30) && (mts_1 == 4 || mts_1 == 6 || mts_1 == 9 || mts_1 == 11) ||
					(1 <= ds_1 && ds_1 <= 29) && (yrs_1 % 4 == 0) ||
					(1 <= ds_1 && ds_1 <= 28) && (yrs_1 % 4 != 0)
					)) {

					Menu(pos, days_1, months_1, years_1);
				}

				// значенне по дефолту
				else {
					ds_1 = 1;
					mts_1 = 1;
					yrs_1 = 2000;
					days_1[0] = '0';
					days_1[1] = '1';
					months_1[0] = '0';
					months_1[1] = '1';
					years_1[0] = '2';
					years_1[1] = '0';
					years_1[2] = '0';
					years_1[3] = '0';

					Menu(pos, days_1, months_1, years_1);
					printf("Некорректно введенная дата");
				}
			}
			if (pos == 2) {
				Menu(pos, days_1, months_1, years_1);

				// расчет старшего аркана
				FILE* arcaneDesc = fopen("info.txt", "r");
				char arcaneLine[500];

				int arc = 0;
				int arc_day = day_1;
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

				for (int j = 1; j <= 23; j++) {

					// запись описания аркана в массив
					memset(arcaneLine, ' ', sizeof(arcaneLine));
					fgets(arcaneLine, 500, arcaneDesc);

					if (j == arc) {
						printf("\t");
						for (int i = 0; i <= 100; i++) {
							printf("%c", arcaneLine[i]);
						}
						printf("\n");
						printf("\t");
						for (int i = 101; i <= 200; i++) {
							printf("%c", arcaneLine[i]);
						}
						printf("\n");
						printf("\t");
						for (int i = 201; i <= 300; i++) {
							printf("%c", arcaneLine[i]);
						}
						printf("\n");
						printf("\t");
						for (int i = 301; i <= 400; i++) {
							printf("%c", arcaneLine[i]);
						}
						printf("\n");
						printf("\t");
						for (int i = 401; i <= 499; i++) {
							printf("%c", arcaneLine[i]);
						}
						printf("\n");
					}
				}

				fclose(arcaneDesc);
			}
			if (pos == 3) {
				Menu(pos, days_1, months_1, years_1);
				printf("История введенных дат:\n");

				// вывод всех пердыдущих дат
				FILE* arcaneSave = fopen("log.txt", "r");
				while (fgets(saveDate, 20, arcaneSave) != NULL) {
					printf("%s", saveDate);
				}
			}
			if (pos == 4) {
				mainFlag = false;
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
		}
	}
}

// вывод интерфейса
int Menu(int pos_f, char days_1[], char months_1[], char years_1[]) {
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

//ввод даты
int Date(long* day_f, long* ds_f, long* mts_f, long* yrs_f, char days_f[], char months_f[], char years_f[]) {
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




// практика 

/*
Git Branch

Бранчи
file-stream
time-chrono

Git branch
Git checkout
#markdown

ДЗ: 
1) описание 22 арканов в отдельном файле (info.txt) + программа должна считывать аркан и выводить строчку из файла
2) записать в другой файл (log.txt) все когда либо введенные даты

# include <ifstream> - input file stream - считывание с файла
# include <ofstream> - output file stream - запись в файл

1) создание объекта
2) привязка объекта к файлу
3) запись / перезапись объекта (...)
4) отвязать объект (.close)

доп задание:
1) рассчитать время работы алгоритма с помощью библиотек времени (chrono)
2) добавление в интерфейс возможности просмотра всех введеных дат
*/
