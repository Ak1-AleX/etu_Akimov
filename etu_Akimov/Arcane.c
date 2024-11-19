#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

// подключение функций даты, аркана и тд.
#include "add_funcs.h"

// Проверяем, был ли заголовочный файл подключен
#ifndef ADD_FUNCS_H
#error "Файл не обнаружен"
#endif

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

	// инициализация флага для работы программы и номера аркана
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

	// пока не вышли из программы
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
