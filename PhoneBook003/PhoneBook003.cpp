#define MAX_NAME_LENGTH 11
#define MAX_PHONE_NUMBER_LENGTH 12

#include <iostream>
using namespace std;

struct Node {
    char name[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
    Node* next;
};

int poolIdx = 0;
Node nodePool[1010000];

Node* head;

Node* allocNode(char* name, char* phoneNumber) {
    Node* ret = &nodePool[poolIdx];
    strcpy_s(ret->name, sizeof(ret->name), name);
    strcpy_s(ret->phoneNumber, sizeof(ret->phoneNumber), phoneNumber);
    poolIdx++;
    return ret;
}

void addNode(char* name, char* phoneNumber) {
    Node* newNode = allocNode(name, phoneNumber);
    newNode->next = head;
    head = newNode;
}

Node* searchByName(char* name) {
    clock_t start = clock();
    
    Node* idx = head;

    while (idx != NULL) {
        if (strcmp(idx->name, name) == 0) {
            break;
        }
        else {
            idx = idx->next;
        }
    }
    clock_t end = clock();
    printf("Search Data Time Taken : %lf\n", ((double)end - (double)start) / 1000);

    return idx;
}

bool deleteByName(char* name) {

    if (strcmp(head->name, name) == 0) {
        head = head->next;
        return true;
    }
    Node* idx = head;

    while (idx->next != NULL) {
        if (strcmp(idx->next->name, name) == 0) {
            idx->next = idx->next->next;
            return true;
        }
        idx = idx->next;
    }
    return false;
}

void prepareBook() {
    char buf[10];
    for (int i = 0; i < 1000000; i++) {
        sprintf_s(buf, "%09d", i);
        addNode(buf, buf);
    }
}

void showAllBook() {
    Node* idx = head;
    while (idx != NULL) {
        printf("%s\n", idx->name);
        idx = idx->next;
    }
}

int main()
{
    clock_t start = clock();
    prepareBook();
    clock_t end = clock();
    printf("Add 1Million Data Time Taken : %lf\n", ((double)end - (double)start)/1000);
    //showAllBook();
    
    puts("### Phone Book 003 Start ###");
    int cmd = 0;
    char enterName[MAX_NAME_LENGTH] = { 0 };
    char enterNumber[MAX_PHONE_NUMBER_LENGTH] = { 0 };
    while (true) {
        puts("1. Add New Number\t2. Search By Name\t3. Delete By Name\t4.Quit");

        scanf_s("%d", &cmd);
        
        if (cmd == 1) {
            puts("\t enter name : ");
            scanf_s("%s", enterName, sizeof(enterName));

            puts("\t enter number : ");
            scanf_s("%s", enterNumber, sizeof(enterNumber));

            addNode(enterName, enterNumber);

            puts(" enter success.");
        }
        else if (cmd == 2) {
            puts("\t enter name : ");
            scanf_s("%s", enterName, sizeof(enterName));
            Node* node = searchByName(enterName);
            if (node != NULL) {
                printf(" name : %s, number : %s \n", node->name, node->phoneNumber);
            }
            else {
                puts("No search result.");
            }
        }
        else if (cmd == 3) {
            puts("\t enter name : ");
            scanf_s("%s", enterName, sizeof(enterName));

            if (deleteByName(enterName)) {
                puts("delete success");
            }
            else {
                puts("there is no name");
            }
        }
        else if (cmd == 4) {
            break;
        }
    }
    
    return 0;
}

