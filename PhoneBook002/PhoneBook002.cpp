

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

unordered_map<string, string> phoneBook;

int main()
{
    puts("#### Start PhoneBook2 ");

    double start = (double)clock();
    for (int i = 0; i < 1000000; i++)
    {
        char buffer[10] = { 0 };
        sprintf_s(buffer, "%d", i);

        phoneBook[buffer] = buffer;
    }
    double end = (double)clock();
    printf(" insert 1million info. time taken %lf\n\n", (end - start)/1000);

    int cmd = 0;
    char name[10] = { 0 };
    char phoneNumber[11] = { 0 };
    while (true) {
        puts("1.Add\t2.Search by name\t3.Delete by name\t4.Quit");
        scanf_s("%d", &cmd);

        if (cmd == 1) {
            puts("  name: ");
            scanf_s("%s", name, sizeof(name));
            puts("  phone number: ");
            scanf_s("%s", phoneNumber, sizeof(phoneNumber) );

            phoneBook[name] = phoneNumber;
            puts("insert success");
        }
        else if (cmd == 2) {
            puts("  name: ");
            scanf_s("%s", name, sizeof(name));

            if (phoneBook.count(name) == 0) {
                printf("  can't find %s\n", name);
            }
            else {
                const char* number = phoneBook[name].c_str();
                printf("  name : %s, number : %s\n", name, number);
            }
        }
        else if (cmd == 3) {
            puts("  name: ");
            scanf_s("%s", name, sizeof(name));

            if (phoneBook.count(name) == 0) {
                printf("  can't find %s\n", name);
            }
            else {
                const char* number = phoneBook[name].c_str();
                printf("  deleted  name : %s, number : %s\n", name, number);
                phoneBook.erase(name);
            }
        }
        else if (cmd == 4) {
            break;
        }
    }

}


