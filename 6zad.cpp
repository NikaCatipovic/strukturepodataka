#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _article{
    char ime[50];
    int cijena;
    int kolicina;
    struct _article *next;
}article;

typedef struct _racun{
    char datum[50];
    struct _racun *next;
    article *arthead;
}racun;


article* newArticle(char* ime, int cijena, int kolicina) {
    article* new_article = (article*)malloc(sizeof(article));
    strcpy(new_article->ime, ime);
    new_article->cijena = cijena;
    new_article->kolicina = kolicina;
    new_article->next = NULL;
    return new_article;
}


void appendArticle(article** head_ref, char* ime, int cijena, int kolicina) {
    article* new_article = newArticle(ime, cijena, kolicina);
    article* last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_article;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_article;
}


racun* newRacun(char* datum) {
    racun* new_racun = (racun*)malloc(sizeof(racun));
    strcpy(new_racun->datum, datum);
    new_racun->next = NULL;
    new_racun->arthead = NULL;
    return new_racun;
}


void appendRacun(racun** head_ref, char* datum) {
    racun* new_racun = newRacun(datum);
    racun* last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_racun;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_racun;
}


void printRacuni(racun* node) {
    while (node != NULL) {
        printf("Receipt date: %s\n", node->datum);
        article* article_node = node->arthead;
        while (article_node != NULL) {
            printf("Article: %s, Price: %d, Quantity: %d\n", article_node->ime, article_node->cijena, article_node->kolicina);
            article_node = article_node->next;
        }
        node = node->next;
    }
}

void find(racun *cur,char *s,char *proizvod){
    while(cur!=NULL){
        if(strcmp(cur->datum,s)==0){break;}
        cur=cur->next;
    }
    article *acurr=cur->arthead;
    while(acurr!=NULL){
        if(strcmp(acurr->ime,proizvod)==0){
            printf("Potroseno je %d novca i kupljeno %d komada",acurr->cijena,acurr->kolicina);
        }
        acurr=acurr->next;
    }
}

int main() {
    racun* head = NULL;
    char lines[50];
    char s[50];
    char lines1[50];
    char date[50];
    char name[50];
    int price;
    int qty;
    FILE *spisak=fopen("racuni.txt","r");
    FILE *f;
    while(fgets(lines,50,spisak)!=NULL){
        sscanf(lines,"%s",s);
        f=fopen(s,"r");
        if(fgets(lines1,50,f)!=NULL){
            sscanf(lines1,"%s",date);
            appendRacun(&head,date);
        }
        fclose(f);
    }
    rewind(spisak);
    racun *curr=head;
    while(fgets(lines,50,spisak)!=NULL){
        sscanf(lines,"%s",s);
        f=fopen(s,"r");
        fgets(lines1,50,f); 
        while(fgets(lines1,50,f)!=NULL){
            sscanf(lines1,"%s %d %d",name,&price,&qty);
            appendArticle(&(curr->arthead),name,price,qty);
        }
        fclose(f);
        curr=curr->next; 
    }

    printRacuni(head);
    char s1[20];
    char s2[20];
    printf("Unesi datum i ime proizvoda\n");
    scanf("%s %s",s1,s2);
    find(head,s1,s2);
    return 0;
}