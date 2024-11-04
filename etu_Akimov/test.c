#include <stdio.h>

int main() {
	FILE* arcaneDesc = fopen("log.txt", "r");
	int a = 10;
	fprintf(arcaneDesc, "smth\n");

	fclose(arcaneDesc);
}