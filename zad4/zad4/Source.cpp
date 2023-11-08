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
                while (*ptr != '-' && *ptr != '+' && *ptr != '\n' && *ptr != '\0') {
                    ptr++;
                }
            }
            else if (sscanf(ptr, "%dx", &koeficjent[i]) == 1) {
                eksponent[i] = 1;
                i++;
                while (*ptr != '-' && *ptr != '+' && *ptr != '\n' && *ptr != '\0') {
                    ptr++;
                }
            }
            else if (sscanf(ptr, "%d", &koeficjent[i]) == 1) {
                eksponent[i] = 0;
                i++;
                while (*ptr != '-' && *ptr != '+' && *ptr != '\n' && *ptr != '\0') {
                    ptr++;
                }
            }
            if (*ptr == '+') {
                ptr++;
            }
            if (*ptr == '-') {
                ptr++;
                sscanf(ptr, "%dx^%d", &koeficjent[i], &eksponent[i]);
                koeficjent[i] = -koeficjent[i];
                i++;
                while (*ptr != '-' && *ptr != '+' && *ptr != '\n' && *ptr != '\0') {
                    ptr++;
                }
            }
        }
        insert_s(&head, koeficjent, eksponent);
    }
    for (Polinom* curr = head; curr != NULL; curr = curr->next) {
        for (int i = 0; i < MAX_TERMS; i++) {
            if (curr->koeficjent[i] != 0 || curr->eksponent[i] != 0) {
                printf("%d %d\n", curr->koeficjent[i], curr->eksponent[i]);
            }
        }
        printf("novi\n");
    }
    return 0;
}