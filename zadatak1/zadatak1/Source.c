#define _CRT_SECURE_N0_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct {
    char ime[50];
    char prezime[50];
    int bodovi;

}_student;

void main() {
    FILE* f;
    f = fopen_s("stude.txt", "r");
    char c[100];
    int br = 0, i = 0;
    while (fgets(c, sizeof(c), f) != NULL) {
        br++;
    }
    printf("ima ih %d\n", br);
    rewind(f);
    _student* student;
    student = malloc(br * sizeof(_student));
    for (i; i < br; i++) {
        fscanf_s(f, "%s %s %d", student[i].ime, student[i].prezime, &student[i].bodovi);
    }
    for (i = 0; i < br; i++) {
        printf("%s %s %d %dposto\n", student[i].ime, student[i].prezime, student[i].bodovi, student[i].bodovi);
    }
    printf("Maksimalan broj bodova je 100\n");
}