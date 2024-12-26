#define _CRT_SECURE_NO_DEPRECATE
#include <locale.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

//���������� ���������
typedef struct ram {
	char memory_type[20]; //��� ������
	int size; //�����
	int clock_frequency; //�������� �������
	char radiator[5]; //������� ��������
	float coast; //�����������
} RAM_t;


//��������� �������
int fill_RAM(RAM_t*, int*); //���������� �������
int search_RAM(RAM_t*, int); //����� � �������
int print_list(RAM_t*, int); //������ �������
int fill_file(RAM_t*, int); //���������� �����
RAM_t* read_file(int*); //������ �� �����
int sort(RAM_t*, int, int); //����������
int change_RAM(RAM_t*, int, int); //��������� ��������� ������
RAM_t* delete_RAM(RAM_t*, int, int); //�������� ��������� ������

int main()
{
	setlocale(LC_ALL, "RUS"); //����������� ������� �����������
	system("chcp 1251"); //��� ����������� ���������� ������� ��������
	system("cls"); //������� ��������� �� ���������
	//���������� � ������������� ����������
	int exit = 0; //�������������� ���������� ��� ������ �� ���������
	int choice, count; //����������, �������� ����� ������������
	int size = 1; //������ �������
	RAM_t* list; //���������� ������� ��������
	list = (RAM_t*)malloc(size * sizeof(RAM_t)); //��������� ������ ��� �������
	while (exit == 0) {  //���� ������ ���������
		printf("\n�������� ��������: \n  1.�������� ����� ������\n  2.����� ������ �� �����\n  3.�������� ��� ������\n  4.������ ������ � ����\n  5.������ ������ �� ����� list.txt\n  6.����������\n  7.��������� ������������ �������\n  8.�������� ������\n  0. �����\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1: //���������� �������
		{
			printf("������� ���������� ������� ��� ����������: "); 
			scanf("%d", &count); //���������� ���������� �������
			for (int i = 0; i < count; i++) { //���� ���������� �������
				if (fill_RAM(list, &size) == 1) { //���������� ������� ����� �������
					printf("������ ������� ���������\n\n");
					fill_file(list, size); //���������� �����
				}
				else
					printf("�� ������� �������� ������\n\n"); //������ ����������
			}
			print_list(list, size);
			break;
		}
		case 2: //����� �� ������
		{
			if (search_RAM(list, size) != 1) //����� �������
				printf("������\n\n"); //������

			break;
		}
		case 3: //������ �������
		{
			int res = print_list(list, size); //������� ������ �������
				if (res != 1)
					printf("������ ��������� ������\n\n"); //����� ������
				else
					printf("�������\n\n"); //����� ���������
			break;
		}
		case 4: //������ � ����
		{
			if (fill_file(list, size) != 1) //����� �������
				printf("������ ������ � ���� list.txt\n\n"); //������ ������
			else 
				printf("������� ������ � ���� list.txt\n\n"); //������� ������
			break;
		}
		case 5: //������ �� �����
		{
			list = read_file(size); //�������� ��������� �� ��������� ������
			size = read_file_size(size); //��������� �������
			print_list(list, size); //������ �������
			break;
		}
		case 6: //����������
			printf("�������� ������� ����������:\n  1. �� ������\n  2. �� �������� �������\n\n");
			scanf("%d", &choice); //����� ����������
			if (sort(list, size, choice) == 1) { //����� �������
				printf("���������� ��������� �������\n\n"); //���������
				fill_file(list, size); //���������� �����
				print_list(list, size);
			}
			else
				printf("��������� ������ ����������\n\n");  //������
			break;
		case 7: //��������� ��������
			printf("������� ����� ������ � ������, ������� ������ ��������: ");
			scanf("%d", &choice); //���������� ������ ������ ��� ���������
			if (change_RAM(list, size, choice) == 1) {
				printf("������� ������� �������\n\n");
				fill_file(list, size); //���������� �����
				print_list(list, size);
			}
			else
				printf("������ ��������� ��������\n\n"); //��������� �� ������
			break;
		case 8: //�������� ������ ��� �������
			printf("������� ����� ������ ��� ��������: ");   
			scanf("%d", &choice); //���������� ������ ������
			if(delete_RAM(list, choice, size) == 0)  //�������� �� ������������� ������
				printf("�������� ������\n");
			else 
			{
				size--; //���������� ������� �������
				printf("�������� �������� ������\n"); //���������
				fill_file(list, size); //��������� �����
				print_list(list, size);
			}
			break;
		case 0: //����� �� ���������
		{
			exit = 1; //��������� ���������� exit
			printf("\n����� �� ���������...\n\n"); 
			break;
		}
		default: printf("�������� ��������. ���������� �����\n\n");
		}
	}

}

int fill_RAM(RAM_t* p_ram, int* size) //������� ���������� �������
{
	int size_n = (*size) + 1;
	if (*size == 0)
	{
		printf("������\n");
		return 0;
	}
	printf("������� ��� ������: ");
	scanf("%s", &p_ram[*size].memory_type);
	printf("������� ����� ������: ");
	scanf("%d", &p_ram[*size].size);
	printf("������� �������� �������: ");
	scanf("%d", &p_ram[*size].clock_frequency);
	printf("������� ������� ���������: ");
	scanf("%s", &p_ram[*size].radiator);
	printf("������� ����: ");
	scanf("%f", &p_ram[*size].coast);
	(*size) = size_n;
	return 1;
}

int search_RAM(RAM_t* ram, int size) //������� ������ � �������
{
	int choice_search, freq, flag = 0, f=0;
	char type[20];
	printf("\n������� �������� ������� ������:\n  1. �� �������� �������� �������\n  2. �� �������� ���� ������\n  3. �� ���� ���������\n");
	scanf("%d", &choice_search);
	switch (choice_search)
	{
	case 1: //����� �� �������� �������
	{
		printf("������� �������� �������� �������: ");
		scanf("%d", &freq);
		printf("\n������ � ������������ �����������:\n");
		for (int i = 1; i < size; i++)
			if (ram[i].clock_frequency == freq)
			{
				flag++;
				if (flag == 1)
				{
					printf("------------------------------------------------------------------------------------------------------------\n");
					printf("|             ���            |    �����, ��   |  �������� �������  |     ��������      |        ����       | \n");
					printf("------------------------------------------------------------------------------------------------------------\n");
				}
				printf("|    %20s    |     %4d       |      %8d      |       %5s       |    %10.2f     |\n", ram[i].memory_type, ram[i].size, ram[i].clock_frequency, ram[i].radiator, ram[i].coast);

			}
		if (flag > 0)
			printf("------------------------------------------------------------------------------------------------------------\n\n");
		else
		{
			printf("�������� �� �������\n\n");
			return 0;
		}
		break;
	}
	case 2: //����� �� ���� ������
	{
		printf("������� �������� ���� ������: ");
		scanf("%s", &type);
		printf("\n������ � ������������ �����������:\n");
		printf("--------------------------------------------------------------------------------------------------------------\n");
		printf("|             ���            |    �����, ��     |  �������� �������  |     ��������      |        ����        | \n");
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
			printf("�������� �� �������\n\n");
			return 0;
		}
	}
	case 3: //����� �� ����� ����������
	{
		printf("������� �������� ���� ������: ");
		scanf("%s", &type);
		printf("������� �������� �������� �������: ");
		scanf("%d", &freq);
		printf("\n�������� � ������������ �����������:\n");
		printf("-------------------------------------------------------------------------------------------------------------\n");
		printf("|             ���            |    �����, ��     |  �������� �������  |     ��������      |        ����       | \n");
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
			printf("�������� �� �������\n\n");
			return 0;
		}
	}
	default: printf("������� �������� ��������\n");
	}
	return 1;
}

int print_list(RAM_t* ram, int size) //������ �������
{
	if (size == 1)
		return 0;
	printf("\t\t\t\t\t������ ������ �������:\n");
	printf("------------------------------------------------------------------------------------------------------------\n");
	printf("|             ���            |    �����, ��   |  �������� �������  |     ��������      |        ����       | \n");
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
		perror("������ �������� �����");
		return NULL;
	}

	RAM_t* items = NULL;
	int l_size = 1;

	while (1) {
		RAM_t* temp = realloc(items, (l_size + 1) * sizeof(RAM_t));
		if (temp == NULL) {
			perror("������ ��������� ������");
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
RAM_t* read_file(int* size) { //������ �� �����
	FILE* file = fopen("list.txt", "r");
	if (!file) {
		perror("������ �������� �����");
		return NULL;
	}
	RAM_t* items = NULL;
	int l_size = 1;

	while (1) 
	{
		RAM_t* temp = realloc(items, (l_size + 1) * sizeof(RAM_t));
		if (temp == NULL) {
			perror("������ ��������� ������");
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
		printf("������� ��� �������\n\n");
		return 0;
	}
	printf("������� ��� ������: ");
	scanf("%s", &p_ram[pos].memory_type);
	printf("������� ����� ������: ");
	scanf("%d", &p_ram[pos].size);
	printf("������� �������� �������: ");
	scanf("%d", &p_ram[pos].clock_frequency);
	printf("������� ������� ���������: ");
	scanf("%s", &p_ram[pos].radiator);
	printf("������� ����: ");
	scanf("%f", &p_ram[pos].coast);
	return 1;
}

RAM_t* delete_RAM(RAM_t* ram, int n, int size)
{
	int num = n;
	int size_n = size - 1;
	RAM_t* temp = malloc(size_n * sizeof(RAM_t));
	if (temp == NULL) {
		printf("������ ��������� ������\n");
		return 0;
	}
	if (n > size) {
		printf("������� ��� �������\n");
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