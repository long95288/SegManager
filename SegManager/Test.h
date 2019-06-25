#pragma once
#include"../MemLib/Mem.h"
#include<iostream>

using namespace std;
/*
MemLib测试文件
*/ 

void testCreateProgram() {
	program *newp = getProgram(100,1,2,3,4);

}

// 测试获得程序函数
void testGetProgram() {
	cout << "集成测试模块" << endl;

}


// 开始测试
void startTest() {
	testCreateProgram();
	testGetProgram();
}