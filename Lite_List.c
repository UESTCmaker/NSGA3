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
        while(p->pNext)p=p->pNext;
        q = (ListPtr)malloc(sizeof(ListBox));
        q->data = data;
        q->pNext = NULL;
        p->pNext = q;
    }
}

void add_List(ListPtr* head, ListPtr newl){
    while(newl){
            printf("newl->data: %d\n",newl->data);
            add_Data(head,newl->data);
            newl = newl->pNext;
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
