#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TERMS 100

typedef struct Polinom {
    int koeficjent[MAX_TERMS];
    int eksponent[MAX_TERMS];
    struct Polinom* next;
} Polinom;

void insert_s(Polinom** head, int* koeficjent, int* eksponent) {
    Polinom* newpolinom = malloc(sizeof(Polinom));
    memcpy(newpolinom->koeficjent, koeficjent, MAX_TERMS * sizeof(int));
    memcpy(newpolinom->eksponent, eksponent, MAX_TERMS * sizeof(int));
    newpolinom->next = *head;
    *head = newpolinom;
}
void sort(Polinom* poli) {
    int min = 0, mink = 0;
    for (int i = 0; i < MAX_TERMS; i++) {
        for (int j = i + 1; j < MAX_TERMS; j++) {
            if (poli->eksponent[i] < poli->eksponent[j]) {
                min = poli->eksponent[i];
                mink = poli->koeficjent[i];
                poli->eksponent[i] = poli->eksponent[j];
                poli->koeficjent[i] = poli->koeficjent[j];
                poli->eksponent[j] = min;
                poli->koeficjent[j] = mink;
            }
        }
    }

}
void zbrajanje(Polinom** head) {
    Polinom* curr = *head;
    for (Polinom* curr1 = curr->next; curr1 != NULL; curr1 = curr1->next) {
        for (int i = 0; i < MAX_TERMS; i++) {
            for (int j = 0; j < MAX_TERMS; j++) {
                if (curr->eksponent[i] == curr1->eksponent[j]) {
                    curr->koeficjent[i] = curr->koeficjent[i] + curr1->koeficjent[j];
                }
            }
        }
    }
    for (int i = 0; i < MAX_TERMS; i++) {
        if (curr->koeficjent[i] != 0 || curr->eksponent[i] != 0) {
            printf("%d %d\n", curr->koeficjent[i], curr->eksponent[i]);
        }
    }

}
void mnozenje(Polinom** head) {
    Polinom* curr = *head;
    int koef[MAX_TERMS] = { 0 };
    int eks[MAX_TERMS] = { 0 };
    int t = 0;
    for (Polinom* curr1 = curr->next; curr1 != NULL; curr1 = curr1->next) {
        for (int i = 0; i < MAX_TERMS; i++) {
            for (int j = 0; j < MAX_TERMS; j++) {
                if (curr->koeficjent[i] != 0 && curr1->koeficjent[j] != 0 && curr->eksponent[j] != 0 && curr1->eksponent[j] != 0) {
                    koef[t] = curr->koeficjent[i] * curr1->koeficjent[j];
                    eks[t] = curr->eksponent[i] + curr1->eksponent[j];
                    t++;
                }
            }
        }
    }
    insert_s(head, koef, eks);
    curr = *head;
    for (int i = 0; i < MAX_TERMS; i++) {
        if (curr->koeficjent[i] != 0 || curr->eksponent[i] != 0) {
            printf("%d %d\n", curr->koeficjent[i], curr->eksponent[i]);
        }
    }
}
int main() {
    Polinom* head = NULL;
    char c[100];
    int br = 0, i = 0;
    FILE* f;
    f = fopen("polinomi.txt", "r");
    if (f == NULL) {
        printf("Could not open file polinomi.txt");
        return 1;
    }
    while (fgets(c, sizeof(c), f) != NULL) {
        br++;
    }
    rewind(f);
    while (fgets(c, sizeof(c), f)) {
        char* ptr = c;
        int koeficjent[MAX_TERMS] = { 0 };
        int eksponent[MAX_TERMS] = { 0 };
        i = 0;
        while (*ptr != '\n' && *ptr != '\0') {
            if (sscanf(ptr, "%dx^%d", &koeficjent[i], &eksponent[i]) == 2) {
                i++;
                while (*ptr != ' ' && *ptr != '\n' && *ptr != '\0') {
                    ptr++;
                }
            }
            if (*ptr == ' ') {
                ptr++;
            }
        }
        insert_s(&head, koeficjent, eksponent);
    }
    for (Polinom* curr = head; curr != NULL; curr = curr->next) {
        sort(curr);
    }
    for (Polinom* curr = head; curr != NULL; curr = curr->next) {
        for (int i = 0; i < MAX_TERMS; i++) {
            if (curr->koeficjent[i] != 0 || curr->eksponent[i] != 0) {
                printf("%d %d\n", curr->koeficjent[i], curr->eksponent[i]);
            }
        }
        printf("novi\n");
    }
    printf("nakon\n");
    //zbrajanje(&head);
    mnozenje(&head);

    return 0;
}