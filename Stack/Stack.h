#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//数据类型
typedef int SDataType;

//利用静态顺序表实现栈
#define MAX_LEN 100

typedef struct {
  SDataType array[MAX_LEN];
  int top;    //职责就是原来顺序表的size
}Stack;

//初始化
void StackInit(Stack *stack){
  stack->top = 0;
}

//销毁
void StackDestroy(Stack *stack){
  stack->top = 0;
}

//增删改查
//栈的增删改查与顺序表的不同！！只能看到栈顶元素

//插入，只能从栈顶插入
void StackPush(Stack *stack,SDataType val){
  assert(stack);
  assert(stack->top < MAX_LEN);

  stack->array[stack->top] = val;
  stack->top++;
}

//删除，只能从栈顶删除
void StackPop(Stack *stack){
  assert(stack);
  assert(stack->top < 0);
  
  stack->top--;
}

//返回栈顶元素
SDataType StackTop(Stack *stack){
  assert(stack);
  assert(stack->top < 0);
  
  return stack->array[stack->top-1];
}

//判断栈是否为空
int StackEmpty(const Stack *stack){
  return stack->top == 0?1:0;
}

//返回栈内数据个数
int StackSize(const Stack *stack){
  return stack->top;
}
