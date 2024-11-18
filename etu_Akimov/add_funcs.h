#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

// функции
void Menu(int pos_f, char days_1[], char months_1[], char years_1[]);
void Date(int* day_f, int* ds_f, int* mts_f, int* yrs_f, char days_f[], char months_f[], char years_f[]);
void Right(int pos_f, char days_1[], char months_1[], char years_1[], int* ds_f, int* mts_f, int* yrs_f);
void Arcane(int* day_f);
