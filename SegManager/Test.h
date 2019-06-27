#pragma once
#include"Mem.h"
// #include"../MemLib/TestLib.h"
#include<iostream>

using namespace std;
/*
MemLib测试文件
*/ 

void testCreateProgram() {
	// program *newp = getProgram(100,1,2,3,4);


}

// 测试获得程序函数
void testGetProgram() {
	cout << "集成测试模块" << endl;

}
void testAdd() {
	// 按值调用和引用调用
	int a = 2;
	int b = 3;
	//add(a, b);
	cout << "a=" <<a<< endl;
	//add2(a, b);
	cout << "a=" << a << endl;
}

// 开始测试
void startTest() {
	testCreateProgram();
	testGetProgram();
	testAdd();
	
}