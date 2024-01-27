#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _P{
    int broj;
    struct _P *next;

}P;

void insert_e(P **head,int b){
    P *newperson=malloc(sizeof(P));
    newperson->next=NULL;
    newperson->broj=b;
    if(*head==NULL){
        *head=newperson;
        return;
    }
    P *curr=*head;
    while(curr->next!=NULL){
        curr=curr->next;
    }
    curr->next=newperson;
}

int izracunaj(P **head){
    FILE *f=fopen("postfix.txt","r");
    char c;
    int i=0;
    while(fscanf(f,"%c",&c)!=EOF){
        if(c>'0' && c<'9'){
            insert_e(head,(c-'0'));
        }
        if(c=='+'){
            P *curr=*head;
            P *curr1;
            curr1=curr->next;
            while(curr1->next!=NULL){
                curr=curr->next;
                curr1=curr1->next;
            }
            curr->broj=curr->broj+curr1->broj;
            curr->next=NULL;
            free(curr1);
        }
        if(c=='-'){
            P *curr=*head;
            P *curr1;
            curr1=curr->next;
            while(curr1->next!=NULL){
                curr=curr->next;
                curr1=curr1->next;
            }
            curr->broj=curr->broj-curr1->broj;
            curr->next=NULL;
            free(curr1);
        }
        if(c=='*'){
            P *curr=*head;
            P *curr1;
            curr1=curr->next;
            while(curr1->next!=NULL){
                curr=curr->next;
                curr1=curr1->next;
            }
            curr->broj=curr->broj*curr1->broj;
            curr->next=NULL;
            free(curr1);
        }
        if(c=='/'){
            P *curr=*head;
            P *curr1;
            curr1=curr->next;
            while(curr1->next!=NULL){
                curr=curr->next;
                curr1=curr1->next;
            }
            curr->broj=curr->broj/curr1->broj;
            curr->next=NULL;
            free(curr1);
        }
    }
    P *curr=*head;
    printf("%d",curr->broj);

}
int main(){
    P *head=NULL;
    izracunaj(&head);

}