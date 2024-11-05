//#include <stdio.h>
//#include <locale.h>
//
//int main() {
//	setlocale(LC_ALL, "Ru");
//
//	FILE* arcaneDesc = fopen("log.txt", "r");
//	char arcaneLine[1000];
//	memset(arcaneLine, ' ', sizeof(arcaneLine));
//	fgets(arcaneLine, 1000, arcaneDesc);
//	for (int i = 0; i <= 100; i++) {
//		printf("%c", arcaneLine[i]);
//	}
//	printf("\n");
//	for (int i = 101; i <= 200; i++) {
//		printf("%c", arcaneLine[i]);
//	}
//	printf("\n");
//	for (int i = 201; i <= 300; i++) {
//		printf("%c", arcaneLine[i]);
//	}
//	printf("\n");
//	for (int i = 301; i <= 400; i++) {
//		printf("%c", arcaneLine[i]);
//	}
//	printf("\n");
//	for (int i = 401; i <= 500; i++) {
//		printf("%c", arcaneLine[i]);
//	}
//	printf("\n");
//
//	fclose(arcaneDesc);
//}