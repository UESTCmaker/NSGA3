#include <stdio.h>
#include <malloc.h>
#include "Lite_List.h"

void add_Data(ListPtr* head, int data){
    ListPtr q,p = *head;
    if(!*head){
        *head = (ListPtr)malloc(sizeof(ListBox));
        (*head)->data = data;
        (*head)->pNext = NULL;
    }
    else{
        while(p->pNext!=NULL){p=p->pNext;}
        q = (ListPtr)malloc(sizeof(ListBox));
        q->data = data;
        q->pNext = NULL;
        p->pNext = q;
    }
}

void add_List(ListPtr* head, ListPtr newl){
    while(newl){
            add_Data(head,newl->data);
            newl = newl->pNext;
        }
}

int find_List(ListPtr p, int num){
    while(--num)p=p->pNext;
    return p->data;
}

void delete_List(ListPtr *l,int data){
    ListPtr p = *l,q=p,r=p;
    while(q->data!=data)q=q->pNext;
    if(q==p){
            p = p->pNext;
            free(q);
            }
    else if(!q->pNext){
        while(r->pNext!=q)r=r->pNext;
        r->pNext=NULL;
        free(q);
    }
    else{
        while(r->pNext!=q)r=r->pNext;
        r->pNext=q->pNext;
        free(q);
    }
}

int number_List(ListPtr p){
    int number=0;
    while(p){
        number++;
        p=p->pNext;
    }
    return number;
}

void print_List(ListPtr p){
    while(p){
        printf("%d\t",p->data);
        p=p->pNext;
    }
    printf("\n");
}
