#define _CRT_SECURE_NO_DEPRECATE
#include <locale.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

//Объявление структуры
typedef struct ram {
	char memory_type[20]; //тип памяти
	int size; //объем
	int clock_frequency; //тактовая частота
	char radiator[5]; //наличие радитора
	float coast; //латентность
} RAM_t;





int strings(RAM_t* notebooks, int size) {
	FILE* fp = fopen("list.txt", "r");
	int c = 0;
	if (fp == NULL) {
		return 0;
	}
	while (fscanf(fp, "%s %d %d %s %f\n", &notebooks[c].memory_type, &notebooks[c].size, &notebooks[c].clock_frequency, &notebooks[c].radiator, &notebooks[c].coast) != EOF) {
		c++;
	}
	fclose(fp);
	return c;
}



	int main()
	{
		setlocale(LC_ALL, "RUS"); //Подключение русской локализации
		system("chcp 1251");
		system("cls");
		int size = 100;
		RAM_t* list;
		list = (RAM_t*)malloc(size * sizeof(RAM_t));
		//read_file(list, size);
		size = strings(list, size);
		printf("%d", size);
		printf("%d", size);
		printf("\t\t\t\t\tПолный список записей:\n");
		printf("------------------------------------------------------------------------------------------------------------\n");
		printf("|             Тип            |    Объем, Гб   |  Тактовая частота  |     Радиатор      |        Цена       | \n");
		printf("------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < size; i++)
			printf("|    %20s    |       %4d     |      %8d      |       %5s       |    %10.2f     |\n", list[i].memory_type, list[i].size, list[i].clock_frequency, list[i].radiator, list[i].coast);
	}