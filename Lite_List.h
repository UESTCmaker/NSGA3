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
}FListBox,*FListPtr;

void add_Data(ListPtr* l, int data);
void print_List(ListPtr p);

#endif // LITE_LIST_H_INCLUDED
