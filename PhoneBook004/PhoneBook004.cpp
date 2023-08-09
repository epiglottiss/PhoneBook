
#include <iostream>
#include <list>

struct Info {
    char name[10];
    char number[12];

    Info()
    {
        memset(this, 0, sizeof(Info));
    }
};

std::list<Info> book;

Info* searchByName(char* name) {
    double start = (double)clock();
    Info* ret = NULL;
    
    for (std::list<Info>::iterator it = book.begin(); it != book.end(); it++) {
        if (strcmp(it->name, name) == 0) {
            ret = &*it;
        }
    }
    double end = (double)clock();
    printf("Search Data Time Taken : %lf\n", (end - start) / 1000);
    return ret;
}

bool deleteByName(char* name) {
    for (std::list<Info>::iterator it = book.begin(); it != book.end(); it++) {
        if (strcmp(it->name, name) == 0) {
            book.erase(it);
            return true;
        }
    }
    return false;
}

void prepareData() {
    char buffer[10] = { 0 };
    for (int i = 0; i < 1000000; i++)
    {
        sprintf_s(buffer, "%09d", i);
        Info info;
        strcpy_s(info.name, sizeof(buffer), buffer);
        strcpy_s(info.number, sizeof(buffer), buffer);
        book.push_front(info);
    }
}

int main()
{
    double start = static_cast<double>(clock());
    prepareData();
    double end = static_cast<double>(clock());
    printf("prapare data time taken : %lf\n", (end - start) / 1000);
    puts("### Phone Book 004 Start ###");

    int cmd = 0;
    char name[10];
    char number[12];
    while (true) {
        puts("1.Add new \n2. Search by name\n3.Delete by name\n4.Quit");
        scanf_s("%d", &cmd);

        if (cmd == 1) {
            puts("Enter name :");
            scanf_s("%s", name, sizeof(name));

            puts("Enter number :");
            scanf_s("%s", number, sizeof(number));
            Info info;
            strcpy_s(info.name, sizeof(name), name);
            strcpy_s(info.number, sizeof(number), number);
            book.push_front(info);
        }
        else if (cmd == 2) {
            puts("Enter name :");
            scanf_s("%s", name, sizeof(name));
            
            Info* info = searchByName(name);
            if (info != NULL) {
                printf("name: %s, number: %s\n", info->name, info->number);
            }
            else {
                puts("no name");
            }
        }
        else if (cmd == 3) {
            puts("Enter name :");
            scanf_s("%s", name, sizeof(name));

            if (deleteByName(name))
            {
                puts("delete success");
            }
            else {
                puts("no name");
            }
        }
        else if (cmd == 4) {
            break;
        }
    }
    return 0;
}

