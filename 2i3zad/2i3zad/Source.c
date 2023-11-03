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
    strcpy(newperson->name, nam);
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
void find(Person** head, char* surn) {
    Person* curr = *head;
    for (curr; curr != NULL; curr = curr->next) {
        if (strcmp(curr->surname, surn) == 0) {
            printf("%s %s %d\n", curr->name, curr->surname, curr->birth);
            break;
        }
    }
}
void erase(Person** head, char* surn) {
    Person* curr = *head;
    int i = 0, j = 0;
    Person* curr1 = *head;
    for (curr; curr != NULL; curr = curr->next) {
        if (strcmp(curr->surname, surn) == 0) {
            break;
        }
        i++;
    }
    for (curr1; curr1 != NULL; curr1 = curr1->next) {
        if (j == (i - 1)) {
            break;
        }
        j++;
    }

    curr1->next = curr->next;
    free(curr);
}
void insertb(Person** head, char* nam, char* surn, int year, char* surn1) {
    Person* newperson = malloc(sizeof(Person));
    strcpy(newperson->name, nam);
    strcpy(newperson->surname, surn);
    newperson->birth = year;
    Person* curr = *head;
    int i = 0, j = 0;
    Person* curr1 = *head;
    for (curr; curr != NULL; curr = curr->next) {
        if (strcmp(curr->surname, surn1) == 0) {
            break;
        }
        i++;
    }
    for (curr1; curr1 != NULL; curr1 = curr1->next) {
        if (j == (i - 1)) {
            break;
        }
        j++;
    }
    if (curr == *head) {
        newperson->next = *head;
        *head = newperson;
    }
    else {
        curr1->next = newperson;
        newperson->next = curr;
    }

}
void inserta(Person** head, char* nam, char* surn, int year, char* surn1) {
    Person* newperson = malloc(sizeof(Person));
    strcpy(newperson->name, nam);
    strcpy(newperson->surname, surn);
    newperson->birth = year;
    Person* curr = *head;
    int i = 0, j = 0;
    Person* curr1 = *head;
    for (curr; curr != NULL; curr = curr->next) {
        if (strcmp(curr->surname, surn1) == 0) {
            break;
        }
        i++;
    }
    for (curr1; curr1 != NULL; curr1 = curr1->next) {
        if (j == (i + 1)) {
            break;
        }
        j++;
    }

    curr->next = newperson;
    newperson->next = curr1;
}
void main() {
    Person* head = NULL;
    char c[100];
    int n = 0, m = 0, k = 0, l = 0, br = 0;
    char nam[50];
    char surn[50];
    char surnf[50];
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
    printf("Ako zelis pronaci neku osobu unesi 1,ako ne unesi 0\n");
    scanf("%d", &k);
    if (k == 1) {
        printf("Unesi prezime osobe koju zelis pronaci:\n");
        scanf("%s", surn);
        find(&head, surn);
    }
    printf("Ako zelis izbrisati neku osobu unesi 1,ako ne unesi 0\n");
    scanf("%d", &l);
    if (l == 1) {
        printf("Unesi prezime osobe koju zelis izbrisati:\n");
        scanf("%s", surn);
        erase(&head, surn);
        for (Person* curr = head; curr != NULL; curr = curr->next) {
            printf("%s %s %d\n", curr->name, curr->surname, curr->birth);
        }
    }
    printf("Unesi (ime,prezime,godiste)nove osobe i prezime osobe nakon koje zelis unijeti novu osobu:\n");
    scanf("%s %s %d %s", nam, surn, &year, surnf);
    inserta(&head, nam, surn, year, surnf);

    printf("Unesi (ime,prezime,godiste)nove osobe i prezime osobe prije koje zelis unijeti novu osobu:\n");
    scanf("%s %s %d %s", nam, surn, &year, surnf);
    insertb(&head, nam, surn, year, surnf);
    for (Person* curr = head; curr != NULL; curr = curr->next) {
        printf("%s %s %d\n", curr->name, curr->surname, curr->birth);
    }
    FILE* f;
    FILE* fp;
    fp = fopen("stude.txt", "r");
    f = fopen("unos_liste.txt", "w");
    while (fgets(c, sizeof(c), fp) != NULL) {
        br++;
    }
    rewind(fp);
    for (int j = 0; j < br; j++) {
        fscanf(fp, "%s %s %d", nam, surn, &year);
        insert_e(&head, nam, surn, year);
    }
    for (Person* curr = head; curr != NULL; curr = curr->next) {
        fprintf(f, "%s %s %d\n", curr->name, curr->surname, curr->birth);
    }
    fclose(f);
    fclose(fp);

}