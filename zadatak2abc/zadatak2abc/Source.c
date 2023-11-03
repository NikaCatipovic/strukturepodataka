#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Person {
    char name[50];
    char surname[50];
    int birth;
    struct Person* next;

} Person;

void insert_s(Person** head, char* nam, char* surn, int year) {
    Person* newperson = malloc(sizeof(Person));
    strcpy_s(newperson->name, nam);
    strcpy(newperson->surname, surn);
    newperson->birth = year;
    newperson->next = *head;
    *head = newperson;
}
void insert_e(Person** head, char* nam, char* surn, int year) {
    Person* newperson = malloc(sizeof(Person));
    newperson->next = NULL;
    strcpy(newperson->name, nam);
    strcpy(newperson->surname, surn);
    newperson->birth = year;
    if (*head == NULL) {
        *head = newperson;
        return;
    }
    Person* curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newperson;
}
void main() {
    Person* head = NULL;
    int n = 0, m = 0;
    char nam[50];
    char surn[50];
    int year;

    printf("Koliko novih studenata zelite dodati na pocetak?");
    scanf("%d", &n);
    printf("Koliko novih studenata zelite dodati na kraj?");
    scanf("%d", &m);
    for (int i = 0; i < n; i++) {
        if (n == 0) { break; }
        printf("Unesi ime prezime i godinu rodenja %d. studenta sa pocetka:", i + 1);
        scanf("%s %s %d", nam, surn, &year);
        insert_s(&head, nam, surn, year);
    }

    for (int i = 0; i < m; i++) {
        if (m == 0) { break; }
        printf("Unesi ime prezime i godinu rodenja %d. studenta sa kraja:", i + 1);
        scanf("%s %s %d", nam, surn, &year);
        insert_e(&head, nam, surn, year);
    }

    for (Person* curr = head; curr != NULL; curr = curr->next) {
        printf("%s %s %d\n", curr->name, curr->surname, curr->birth);
    }
}