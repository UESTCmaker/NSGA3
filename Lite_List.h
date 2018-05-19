#ifndef LITE_LIST_H_INCLUDED
#define LITE_LIST_H_INCLUDED

typedef struct List{
    int data;
    struct List* pNext;
}ListBox,*ListPtr;

typedef struct FList{
    ListPtr dataList;
    int Rank;
    struct FList* pNext;
    struct FList* pFront;
}FListBox,*FListPtr;

int find_List(ListPtr p, int num);
int number_List(ListPtr p);
void add_Data(ListPtr* l, int data);
void add_List(ListPtr* l, ListPtr newl);
void print_List(ListPtr p);

#endif // LITE_LIST_H_INCLUDED
