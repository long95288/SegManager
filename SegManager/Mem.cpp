#include"Mem.h"
#include"stdafx.h"
#include<iostream>

using namespace std;
/*
ʵ�ֲ���
*/
typedef struct Program
{

}Program;

// ��ʼ��
void init() {
	// ��ʼ�������������α��������б�
	// ���α�
	/*
	seg_table_head = new Segment_table_item();
	seg_table_head->seg_num = seg_table_max_num;
	seg_table_max_num += 1;
	seg_table_head->base_addr = NULL;
	seg_table_head->seg_length = 0;
	seg_table_head->next = NULL;
	// cout << "Hello " << endl;
	// �����б�
	idle_head = new Idle_section();
	idle_head->addr = 0;
	idle_head->length = 1024;
	idle_head->next = NULL;

	// �����
	program_head = NULL;
	*/

}

// �����µĳ����
// ʹ��p����ֵ
int createProgram(
	Program &p,
	int pid,
	int Main_length,
	int Sub_length,
	int Data_length,
	int Stack_length) {

	// �µĽṹ��
	return 0;
}


// pid -> program
int getProgram(Program &p, Program head, int pid) {
	// ����ָ��
	/*
	Program *tmp = &head;
	// ���س����ָ��
	Program *re = NULL;
	for (; tmp->next != NULL; tmp = tmp->next) {
		if (tmp->pid == pid) {
			re = tmp; // �ҵ���Ӧ��
			tmp = NULL; // �ÿ�
			break; // �˳�ѭ��
		}
	}*/
	return 0; //

}

// �����ڴ�
int Allocate(int pid) {
	// ��ó����ָ��
	// program p = getProgram(pid); // ����pid��ó���� 

	// 1.����Main��
	// int main_length = p.main_length;

	// 2.����sub��

	// 3.����data��

	// 4.����stack��

	return 0;
}


/*
void test() {
cout << "����Mem.h�Ĳ��Ժ���" << endl;
}
*/