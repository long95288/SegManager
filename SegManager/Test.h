#pragma once
#include"Mem.h"
// #include"../MemLib/TestLib.h"
#include<iostream>

using namespace std;
/*
MemLib�����ļ�
*/ 

void testCreateProgram() {
	// program *newp = getProgram(100,1,2,3,4);


}

// ���Ի�ó�����
void testGetProgram() {
	cout << "���ɲ���ģ��" << endl;

}
void testAdd() {
	// ��ֵ���ú����õ���
	int a = 2;
	int b = 3;
	//add(a, b);
	cout << "a=" <<a<< endl;
	//add2(a, b);
	cout << "a=" << a << endl;
}

// ��ʼ����
void startTest() {
	testCreateProgram();
	testGetProgram();
	testAdd();
	
}