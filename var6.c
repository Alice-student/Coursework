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


//Прототипы функций
int fill_RAM(RAM_t*, int*); //заполнение массива
int search_RAM(RAM_t*, int); //поиск в массиве
int print_list(RAM_t*, int); //печать массива
int fill_file(RAM_t*, int); //заполнение файла
RAM_t* read_file(int*); //чтение из файла
int sort(RAM_t*, int, int); //сортировка
int change_RAM(RAM_t*, int, int); //изменение отдельной записи
RAM_t* delete_RAM(RAM_t*, int, int); //удаление отдельной записи

int main()
{
	setlocale(LC_ALL, "RUS"); //Подключение русской локализации
	system("chcp 1251"); //для корректного считывания русских символов
	system("cls"); //очистка терминала от сообщения
	//Объявление и инициализация переменных
	int exit = 0; //Иницифализация переменной для выхода из программы
	int choice, count; //переменные, хранящие выбор пользователя
	int size = 1; //размер массива
	RAM_t* list; //объявление массива структур
	list = (RAM_t*)malloc(size * sizeof(RAM_t)); //выделение памяти для массива
	while (exit == 0) {  //цикл работы программы
		printf("\nВыберите действие: \n  1.Создание новой записи\n  2.Поиск записи по ключу\n  3.Показать все записи\n  4.Запись данных в файл\n  5.Чтение данных из файла list.txt\n  6.Сортировка\n  7.Изменение существующих записей\n  8.Удаление записи\n  0. Выход\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1: //добавление записей
		{
			printf("Введите количество записей для добавления: "); 
			scanf("%d", &count); //считавание количества записей
			for (int i = 0; i < count; i++) { //цикл добавления записей
				if (fill_RAM(list, &size) == 1) { //заполнение массива одной записью
					printf("Запись успешно добавлена\n\n");
					fill_file(list, size); //заполнение файла
				}
				else
					printf("Не удалось добавить запись\n\n"); //ошибка добавления
			}
			print_list(list, size);
			break;
		}
		case 2: //поиск по ключам
		{
			if (search_RAM(list, size) != 1) //поиск записей
				printf("Ошибка\n\n"); //ошибка

			break;
		}
		case 3: //печать массива
		{
			int res = print_list(list, size); //функция печать массива
				if (res != 1)
					printf("Ошибка выведения списка\n\n"); //вывод ошибки
				else
					printf("Успешно\n\n"); //вывод сообщения
			break;
		}
		case 4: //запись в файл
		{
			if (fill_file(list, size) != 1) //вызов функции
				printf("Ошибка записи в файл list.txt\n\n"); //ошибка записи
			else 
				printf("Удачная запись в файл list.txt\n\n"); //удачная запись
			break;
		}
		case 5: //чтение из файла
		{
			list = read_file(size); //передача указателя на считанный массив
			size = read_file_size(size); //изменение размера
			print_list(list, size); //печать массива
			break;
		}
		case 6: //сортировка
			printf("Выберите вариант сортировки:\n  1. По объему\n  2. По тактовой частоте\n\n");
			scanf("%d", &choice); //выбор сортировки
			if (sort(list, size, choice) == 1) { //вызов функции
				printf("Сортировка выполнена успешно\n\n"); //сообщение
				fill_file(list, size); //заполнение файла
				print_list(list, size);
			}
			else
				printf("Произошла ошибка сортировки\n\n");  //ошибка
			break;
		case 7: //изменение элемента
			printf("Укажите номер записи в списке, которую хотите изменить: ");
			scanf("%d", &choice); //считывание номера записи для изменения
			if (change_RAM(list, size, choice) == 1) {
				printf("Элемент успешно изменен\n\n");
				fill_file(list, size); //заполнение файла
				print_list(list, size);
			}
			else
				printf("Ошибка изменения элемента\n\n"); //сообщение об ошибке
			break;
		case 8: //удаление записи под номером
			printf("Укажите номер записи для удаления: ");   
			scanf("%d", &choice); //считывание номера записи
			if(delete_RAM(list, choice, size) == 0)  //проверка на возникновение ошибок
				printf("Возникла ошибка\n");
			else 
			{
				size--; //уменьшение размера массива
				printf("Успешное удаления записи\n"); //сообщение
				fill_file(list, size); //изменение файла
				print_list(list, size);
			}
			break;
		case 0: //выход из программы
		{
			exit = 1; //изменение переменной exit
			printf("\nВыход из программы...\n\n"); 
			break;
		}
		default: printf("Неверное действие. Попробуйте снова\n\n");
		}
	}

}

int fill_RAM(RAM_t* p_ram, int* size) //функция заполнения массива
{
	int size_n = (*size) + 1;
	if (*size == 0)
	{
		printf("Ошибка\n");
		return 0;
	}
	printf("Укажите тип памяти: ");
	scanf("%s", &p_ram[*size].memory_type);
	printf("Укажите объем памяти: ");
	scanf("%d", &p_ram[*size].size);
	printf("Укажите тактовую частоту: ");
	scanf("%d", &p_ram[*size].clock_frequency);
	printf("Укажите наличие радиатора: ");
	scanf("%s", &p_ram[*size].radiator);
	printf("Укажите цену: ");
	scanf("%f", &p_ram[*size].coast);
	(*size) = size_n;
	return 1;
}

int search_RAM(RAM_t* ram, int size) //функция поиска в массиве
{
	int choice_search, freq, flag = 0, f=0;
	char type[20];
	printf("\nВведите желаемый вариант поиска:\n  1. По значению тактовой частоты\n  2. По значению типа памяти\n  3. По двум значениям\n");
	scanf("%d", &choice_search);
	switch (choice_search)
	{
	case 1: //поиск по тактовой частоте
	{
		printf("Введите значение тактовой частоты: ");
		scanf("%d", &freq);
		printf("\nТовары с совпадающими параметрами:\n");
		for (int i = 1; i < size; i++)
			if (ram[i].clock_frequency == freq)
			{
				flag++;
				if (flag == 1)
				{
					printf("------------------------------------------------------------------------------------------------------------\n");
					printf("|             Тип            |    Объем, Гб   |  Тактовая частота  |     Радиатор      |        Цена       | \n");
					printf("------------------------------------------------------------------------------------------------------------\n");
				}
				printf("|    %20s    |     %4d       |      %8d      |       %5s       |    %10.2f     |\n", ram[i].memory_type, ram[i].size, ram[i].clock_frequency, ram[i].radiator, ram[i].coast);

			}
		if (flag > 0)
			printf("------------------------------------------------------------------------------------------------------------\n\n");
		else
		{
			printf("Элементы не найдены\n\n");
			return 0;
		}
		break;
	}
	case 2: //поиск по типу памяти
	{
		printf("Введите значение типа памяти: ");
		scanf("%s", &type);
		printf("\nТовары с совпадающими параметрами:\n");
		printf("--------------------------------------------------------------------------------------------------------------\n");
		printf("|             Тип            |    Объем, Гб     |  Тактовая частота  |     Радиатор      |        Цена        | \n");
		printf("--------------------------------------------------------------------------------------------------------------\n");
		for (int i = 1; i < size; i++)
		{
			flag = 0;
			if (strcmp(ram[i].memory_type, type) == 0)
				flag++;
			if (flag == 1) {
				printf("|    %20s    |       %4d       |      %8d      |       %5s       |    %10.2f      |\n", ram[i].memory_type, ram[i].size, ram[i].clock_frequency, ram[i].radiator, ram[i].coast);
				f = 1;
			}
		}
		if (f == 1)
			printf("--------------------------------------------------------------------------------------------------------------\n\n");
		else
		{
			printf("Элементы не найдены\n\n");
			return 0;
		}
	}
	case 3: //поиск по обоим параметрам
	{
		printf("Введите значение типа памяти: ");
		scanf("%s", &type);
		printf("Введите значение тактовой частоты: ");
		scanf("%d", &freq);
		printf("\nПродукты с совпадающими параметрами:\n");
		printf("-------------------------------------------------------------------------------------------------------------\n");
		printf("|             Тип            |    Объем, Гб     |  Тактовая частота  |     Радиатор      |        Цена       | \n");
		printf("-------------------------------------------------------------------------------------------------------------\n");
		for (int i = 1; i < size; i++)
		{
			flag = 0;
			if (ram[i].clock_frequency == freq && (strcmp(ram[i].memory_type, type) == 0))
				flag++;
			if (flag == 1) {
				printf("|    %20s    |       %4d       |      %8d      |       %5s       |    %10.2f     |\n", ram[i].memory_type, ram[i].size, ram[i].clock_frequency, ram[i].radiator, ram[i].coast);
				f = 1;
				}
			}
		if (f > 0)
			printf("-------------------------------------------------------------------------------------------------------------\n\n");
		else
		{
			printf("Элементы не найдены\n\n");
			return 0;
		}
	}
	default: printf("Указано неверное значение\n");
	}
	return 1;
}

int print_list(RAM_t* ram, int size) //печать массива
{
	if (size == 1)
		return 0;
	printf("\t\t\t\t\tПолный список записей:\n");
	printf("------------------------------------------------------------------------------------------------------------\n");
	printf("|             Тип            |    Объем, Гб   |  Тактовая частота  |     Радиатор      |        Цена       | \n");
	printf("------------------------------------------------------------------------------------------------------------\n");
	for (int i = 1; i < size; i++)
		printf("|    %20s    |       %4d     |      %8d      |       %5s       |    %10.2f     |\n", ram[i].memory_type, ram[i].size, ram[i].clock_frequency, ram[i].radiator, ram[i].coast);
	printf("------------------------------------------------------------------------------------------------------------\n\n");
	return 1;
}


int fill_file(RAM_t* ram, int size) {
	FILE* file = fopen("list.txt", "w");
	if (file == NULL) {
		return 0;
	}

	for (int i = 1; i < size; i++) {
		fprintf(file, "%s,%d,%d,%s,%f\n", ram[i].memory_type, ram[i].size, ram[i].clock_frequency, ram[i].radiator, ram[i].coast);
	}
	fclose(file);
	return 1;
}
int read_file_size(int* size) {
	FILE* file = fopen("list.txt", "r");
	if (!file) {
		perror("Ошибка открытия файла");
		return NULL;
	}

	RAM_t* items = NULL;
	int l_size = 1;

	while (1) {
		RAM_t* temp = realloc(items, (l_size + 1) * sizeof(RAM_t));
		if (temp == NULL) {
			perror("Ошибка выделения памяти");
			free(items);
			fclose(file);
			return NULL;
		}
		items = temp;

		if (fscanf(file, "%[^,],%d,%d,%[^,],%f\n",
			items[l_size].memory_type,
			&items[l_size].size,
			&items[l_size].clock_frequency,
			items[l_size].radiator,
			&items[l_size].coast) != 5) {
			break;
		}

		items[l_size].memory_type[19] = '\0';
		items[l_size].radiator[4] = '\0'; 
		l_size++;
	}
	fclose(file);
	return l_size;
}
RAM_t* read_file(int* size) { //чтение из файла
	FILE* file = fopen("list.txt", "r");
	if (!file) {
		perror("Ошибка открытия файла");
		return NULL;
	}
	RAM_t* items = NULL;
	int l_size = 1;

	while (1) 
	{
		RAM_t* temp = realloc(items, (l_size + 1) * sizeof(RAM_t));
		if (temp == NULL) {
			perror("Ошибка выделения памяти");
			free(items);
			fclose(file);
			return NULL;
		}
		items = temp;
		if (fscanf(file, "%[^,],%d,%d,%[^,],%f\n",
			items[l_size].memory_type,
			&items[l_size].size,
			&items[l_size].clock_frequency,
			items[l_size].radiator,
			&items[l_size].coast) != 5) {
			break;
		}

		items[l_size].memory_type[19] = '\0';
		items[l_size].radiator[4] = '\0'; 
		l_size++;
	}
	fclose(file);
	return items;
}
int sort(RAM_t* ram, int size, int key)
{
	RAM_t temp;
	switch (key)
	{
	case 1:
	{
		for (int i = 0; i < size - 1; i++)
		{
			int min = i;
			for (int j = i; j < size; j++)
			{
				if (ram[j].size < ram[min].size)
					min = j;
			}
			temp = ram[min];
			ram[min] = ram[i];
			ram[i] = temp;
		}
		break;
	}
	case 2:
	{
		for (int i = 0; i < size - 1; i++)
		{
			int min = i;
			for (int j = i; j < size; j++)
			{
				if (ram[j].clock_frequency< ram[min].clock_frequency)
					min = j;
			}
			temp = ram[min];
			ram[min] = ram[i];
			ram[i]= temp;
		}
		break;
	}
	default: return 0;
	}
	return 1;
}

int change_RAM(RAM_t* p_ram, int size, int pos)
{
	if (pos > size)
	{
		printf("Элемент вне массива\n\n");
		return 0;
	}
	printf("Укажите тип памяти: ");
	scanf("%s", &p_ram[pos].memory_type);
	printf("Укажите объем памяти: ");
	scanf("%d", &p_ram[pos].size);
	printf("Укажите тактовую частоту: ");
	scanf("%d", &p_ram[pos].clock_frequency);
	printf("Укажите наличие радиатора: ");
	scanf("%s", &p_ram[pos].radiator);
	printf("Укажите цену: ");
	scanf("%f", &p_ram[pos].coast);
	return 1;
}

RAM_t* delete_RAM(RAM_t* ram, int n, int size)
{
	int num = n;
	int size_n = size - 1;
	RAM_t* temp = malloc(size_n * sizeof(RAM_t));
	if (temp == NULL) {
		printf("Ошибка выделения памяти\n");
		return 0;
	}
	if (n > size) {
		printf("Элемент вне массива\n");
		return 0;
	}
	for (int i = 0; i < size; i++) {
		if (i < num) {
			temp[i] = ram[i];
		}
		else if (i > num) {
			temp[i - 1] = ram[i];
		}
	}
	ram = realloc(ram, size_n * sizeof(RAM_t));
	for (int i = 0; i < size; i++) {
		ram[i] = temp[i];
	}
	return ram;
}