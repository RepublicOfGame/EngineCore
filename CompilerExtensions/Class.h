#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <any>
#include "Log.h"


class Object{

};

class Frame{

};

class Test1 : Object {
public:

    typedef Test1 TClass;
	int MyFunction(int a, long long b){

	}

    // 对于每个成员函数，生成以下的工具函数
	void execMyFunction(Object *Context, Frame* Stack, void* const ReturnAddress){
      // Frame 是栈结构，用于保存参数
      int* a = Stack.read(4);
      long long* b = Stack.read(8);
      *(*int)ReturnAddress = ((TClass*)Context)->MyFunction(*a, *b);
	}
};

