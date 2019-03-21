#include "DList.h"

void TestDlist1(){
  DList dlist;

  DListInit(&dlist);
  DListPushFront(&dlist,3);
  DListPushFront(&dlist,2);
  DListPushFront(&dlist,1);

  DListPushBack(&dlist,14);
  DListPushBack(&dlist,15);
  DListPushBack(&dlist,16);

  
  DListNode *pos = DListFind(&dlist,14);
  DListInsert(pos,107);
  DListPrintByDlist(&dlist);

  DListErase(pos);
  DListPrintByDlist(&dlist);

  DListPopFront(&dlist);
  DListPrintByDlist(&dlist);

  DListPopBack(&dlist);
  DListPrintByDlist(&dlist);
  
  DListDestroy(&dlist);
}

int main(){
  TestDlist1();
  return 0;
}
