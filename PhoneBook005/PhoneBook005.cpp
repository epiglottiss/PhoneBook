#define NAME_LENGTH 11
#define PNONENUMBER_LENGTH 12
#define SEARCH_RESULT_COUNT 10000

#include <stdio.h>
#include<string.h>
#include<vector>

struct Node {
	char name[NAME_LENGTH];
	char number[PNONENUMBER_LENGTH];
	Node* next;

	Node() {
		memset(name, 0, sizeof(name));
		memset(number, 0, sizeof(number));
		next = NULL;
	}
};

Node pool[1010000];
int poolIdx;

Node* head;

Node* allocNode() {
	return &pool[poolIdx++];
}

void insert(char* name, char* number) {
	Node* newNode = allocNode();
	strcpy_s(newNode->name, sizeof(newNode->name), name);
	strcpy_s(newNode->number, sizeof(newNode->number), number);
	newNode->next = head;
	head = newNode;
}

void searchAllByName(char* name, Node** result, int result_size) {
	Node* idx = head;
	int resultCount = 0;
	
	while (idx != NULL) {
		if (strcmp(name, idx->name) == 0) {
			result[resultCount++] = idx;
		}
		if (resultCount >= result_size) {
			break;
		}
		idx = idx->next;
	}
}

int main()
{
	puts("#### phone book 005 start.\n Search convenience has been improved.");

	int cmd = 0;
	char name[NAME_LENGTH] = { 0 };
	char number[PNONENUMBER_LENGTH] = { 0 };
	while (true) {
		puts("1. add \n2.Search by name\n3.Delete by name\n4.quit");
		scanf_s("%d", &cmd);

		if (cmd == 1) {
			puts(" enter name : ");
			scanf_s("%s", name, sizeof(name));
			
			puts(" enter number : ");
			scanf_s("%s", number, sizeof(number));

			insert(name, number);
		}
		else if (cmd == 2) {
			puts(" enter name : ");
			scanf_s("%s", name, sizeof(name));

			Node* searchResults[SEARCH_RESULT_COUNT] = { 0 };
			searchAllByName(name, searchResults, SEARCH_RESULT_COUNT);

			for (int i = 0; i < SEARCH_RESULT_COUNT; i++) {
				if (searchResults[i] == NULL) {
					break;
				}
				printf(" #%d name : %s, number : %s\n", i, searchResults[i]->name, searchResults[i]->number);
			}
		}
		else if (cmd == 3) {

		}
		else if (cmd == 4) {
			break;
		}
	}

}

