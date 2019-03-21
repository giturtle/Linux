#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//双向、带头、链表
//时间复杂度都为O(1)
//数据类型
typedef int DLDataType;

//结点类型
typedef struct DListNode{
  DLDataType val;
  struct DListNode *next; //后继结点
  struct DListNode *prev; //前驱结点
}DListNode;

//双向链表类型
typedef struct {
  DListNode *head;  //指向头结点
}DList;

//*************接口****************

//内部接口，创建结点
DListNode *BuyNode(DLDataType val){
  DListNode *node = (DListNode*)malloc(sizeof(DListNode));
  assert(node);
  node->val = val;
  node->next = node->prev = NULL;

  return node;
}

//初始化
void DListInit(DList *dlist){
  //创建头结点
  //DListNode *head = (DListNode*)malloc(sizeof(DListNode));
  DListNode *head = BuyNode(0);
  head->val = 0;  //头结点的val没有实际意义,通常会存储链表长度
  head->next = head;
  head->prev = head;

  //将头结点放置在链表中
  dlist->head = head;
}

//清空
void DListClear(DList *dlist){
  DListNode *cur ,*next;
  //和单链表有略微区别
  for(cur = dlist->head->next;cur != dlist->head;cur = next){
    next = cur->next;
    free(cur);
  }
  dlist->head->next = dlist->head;
  dlist->head->prev = dlist->head;
}


//销毁
void DListDestroy(DList *dlist){
  DListClear(dlist);
  free(dlist->head);
  //成为一个头结点都没有的无效链表了
  dlist->head = NULL;
}

//增删改查

//头插
void DListPushFront(DList *dlist,DLDataType val){
  //就算是空链表也可以完成同样的逻辑
#if 0
  //一种方法直接调用头插接口完成
  DListInsert(dlist->head->next,val);
#endif
  //1. 先申请结点
  DListNode *node = BuyNode(val);

  //2. 处理next/prev
  //有两个prev，两个next，共4个指针需要变更
  node->prev = dlist->head;
  node->next = dlist->head->next;
  node->next->prev = node;  //相当于dlist->head->next->prev = node;
  dlist->head->next = node;
}

//尾插
#if 0
  DListInsert(dlist->head,val);
#endif
void DListPushBack(DList *dlist,DLDataType val){
  //申请结点
  DListNode *node = BuyNode(val);

  node->prev = dlist->head->prev;
  node->next = dlist->head;
  dlist->head->prev->next = node;
  dlist->head->prev = node;
}

//在pos结点前做插入
void DListInsert(DListNode *pos,DLDataType val){  //这里不用给出链表
  DListNode *node = BuyNode(val);
  node->next = pos;
  node->prev = pos->prev;
  pos->prev->next = node;
  pos->prev = node;
  //上面两步不可交换顺序，否则链表结点就断裂了
}

//打印
void DListPrintByHead(DListNode *head){
  DListNode *cur = head->next;
  for(;cur != head;cur = cur->next){
    printf("%d -> ",cur->val);
  }
  printf("\n");
}
void DListPrintByDlist(DList *dlist){
  DListPrintByHead(dlist->head);
}

//查找
//找到第一个val的结点，返回结点地址
//如果没找到，返回NULL
DListNode *DListFind(DList *dlist,DLDataType val){
  DListNode *cur = dlist->head->next;
  for(;cur != dlist->head;cur = cur->next){
    if(cur->val == val){
      return cur;
    }
  }
  return NULL;
}

void DListErase(DListNode *pos){
  //assert(pos != dlist->head); //删除 pos 结点,pos不是头结点
  pos->prev->next = pos->next;
  pos->next->prev = pos->prev;
  free(pos);
}

void DListPopFront(DList *dlist){
  assert(dlist->head->next != dlist->head); //链表不为空
  DListErase(dlist->head->next);
}


void DListPopBack(DList *dlist){
  assert(dlist->head->next != dlist->head); //链表不为空
  DListErase(dlist->head->prev);
}
