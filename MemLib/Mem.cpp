#include"Mem.h"
#include"stdafx.h"
#include<iostream>

using namespace std;
/*
实现部分
*/

// 初始化
void init() {
	// 初始化函数，建立段表，建立空闲表
	// 建段表
	seg_table_head = new Segment_table_item();
	seg_table_head->seg_num = seg_table_max_num;
	seg_table_max_num += 1;
	seg_table_head->base_addr = NULL;
	seg_table_head->seg_length = 0;
	seg_table_head->next = NULL;
	// cout << "Hello " << endl;
	// 建空闲表
	idle_head = new Idle_section();
	idle_head->addr = 0;
	idle_head->length = 1024;
	idle_head->next = NULL;

	// 程序段
	program_head = NULL;

}

// 创建新的程序块
program *createProgram(
	int pid,
	int Main_length,
	int Sub_length,
	int Data_length,
	int Stack_length) {
	program *re = new program();
	re->main_length = Main_length;
	re->sub_length = Sub_length;
	re->data_length = Data_length;
	re->stack_length = Stack_length;
	return re;
}

// pid -> program
program getProgram(int pid) {
	// 遍历指针
	program *tmp = program_head;
	// 返回程序的指针
	program *re = NULL;
	for (; tmp->next != NULL;tmp = tmp->next) {
		if (tmp->pid == pid) {
			re = tmp; // 找到对应块
			tmp = NULL; // 置空
			break; // 退出循环
		}
	}
	return *re; // 返回对应的指针
}

// 申请内存
int Allocate(int pid) {
	// 获得程序块指针
	program p = getProgram(pid); // 根据pid获得程序段 
	
	// 1.申请Main段
	int main_length = p.main_length;

	// 2.申请sub段

	// 3.申请data段

	// 4.申请stack段

	return 0;
}


/*
void test() {
	cout << "这是Mem.h的测试函数" << endl;
}
*/