#pragma once
#include"../MemLib/Mem.h"
#include<iostream>

using namespace std;
/*
MemLib�����ļ�
*/ 

void testCreateProgram() {
	program *newp = getProgram(100,1,2,3,4);

}

// ���Ի�ó�����
void testGetProgram() {
	cout << "���ɲ���ģ��" << endl;

}


// ��ʼ����
void startTest() {
	testCreateProgram();
	testGetProgram();
}