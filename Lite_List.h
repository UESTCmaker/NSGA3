#ifndef LITE_LIST_H_INCLUDED
#define LITE_LIST_H_INCLUDED

typedef struct List{
    int data;
    struct List* pNext;
}ListBox,*ListPtr;

void add_Data(ListPtr* l, int data);
void print_List(ListPtr p);

#endif // LITE_LIST_H_INCLUDED
