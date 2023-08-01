
#include <stdio.h>
#include <string.h>
#include <ctime>
using namespace std;

typedef struct PhoneInfo {
	char name[10];
	char phoneNumber[12];

	PhoneInfo* next;
};

PhoneInfo* head;
PhoneInfo* tail;

PhoneInfo phoneInfoPool[1001000];
int phoneInfoIdx = 0;

void addPhoneInfo(const char* name, const char* phoneNumber) {
	PhoneInfo* info = &phoneInfoPool[phoneInfoIdx];
	strcpy_s(info->name, sizeof(info->name), name);
	strcpy_s(info->phoneNumber, sizeof(info->phoneNumber), phoneNumber);
	info->next = head;
	head = info;
	phoneInfoIdx++;
}

PhoneInfo* findInfoByName(const char* name) {
	PhoneInfo* idx = head;
	
	while (idx != NULL) {
		if (strcmp(idx->name, name) == 0) {
			break;
		}
		else {
			idx = idx->next;
		}
	}
	return idx;
}

bool deletePhoneInfo(const char* name) {
	bool isDeleted = false;

	PhoneInfo* idx = head;
	if (idx == NULL) {
		return isDeleted;
	}

	if (strcmp(idx->name, name) == 0) {
		head = head->next;
		return true;
	}

	while (idx->next != NULL) {
		if (strcmp(idx->next->name, name) == 0) {
			idx->next = idx->next->next;
			return true;
		}
		else {
			idx = idx->next;
		}
	}
	
	return isDeleted;
}

void insertManyInfo() {
	clock_t start = clock();
	for (int i = 0; i < 1000000; i++) {
		char bufferName[10] = { 0 };
		sprintf_s(bufferName, "%d", i);
		addPhoneInfo(bufferName, bufferName);
	}
	clock_t end = clock();
	printf(" ## insertManyInfo time taken : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main()
{
	puts("#### Start Phone Book 001 ####");
	insertManyInfo();
	int cmd = 0;
	while (true) {
		puts("Enter Command\n1.Add new\n2.Find by Name\n3.Delete by Name\n9.Quit");
		scanf_s("%d", &cmd);
		char name[10] = { 0 };
		if (cmd == 1) {
			puts("\tEnter name to add : ");
			scanf_s("%s", name, sizeof(name));

			puts("\tEnter phone number to add : ");
			char phoneNumber[12] = { 0 };
			scanf_s("%s", phoneNumber, sizeof(phoneNumber));

			addPhoneInfo(name, phoneNumber);
		}
		else if (cmd == 2) {
			puts("\tEnter name to search: ");
			scanf_s("%s", name, sizeof(name));
			PhoneInfo* info = findInfoByName(name);
			if (info == NULL) {
				printf("\t\tThere is no %s\n", name);
			}
			else {
				printf("\t\tname: %s, phone number: %s\n", info->name, info->phoneNumber);
			}
		}
		else if (cmd == 3) {
			puts("\tEnter name to delete: ");
			scanf_s("%s", name, sizeof(name));
			if (deletePhoneInfo(name) == true) {
				printf("\t\tSuccess to delete %s\n", name);
			}
			else {
				printf("\t\tThere is no %s\n", name);
			}
		}
		else if (cmd == 9) {
			break;
		}

	}

	return 0;
}


